#include "server.h"
#include "table.h"
#include "databasemanager.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>
#include <vector>
#include <string>

QT_USE_NAMESPACE

Server::Server(quint16 port, std::vector<Table*> *tTable, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_clients(),
    m_debug(debug),
    mTable(tTable)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port)) {
        if (m_debug)
            qDebug() << "Server listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &Server::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &Server::closed);
    }
}

Server::~Server()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void Server::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &Server::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &Server::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &Server::socketDisconnected);

    m_clients << pSocket;
}

void Server::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
/*
 * Pseudo code (frontend):
 * Add websocket capability
 * Connect the socket to the server, hardcode 127.0.0.1:PORT first
 * Recieve JSon object from the server
 * Present JSon object to the user, in a temporary label, just to check communication
 *
 * TODO:
 *
 * Frontend:
 * Send JSonObjects containing "select", "from" and "where" statements specifying what database table, column and row the server sends as an answer.
 * Fix the frontend layout into something more useable, using a table made clickable through JQuery is probably a good idea.
 * Have a shoppingcart-like module which immidiatelly shows the objects clicked, perhaps only do this when "right-clicked" and
 *  immidiatelly send a query to the server when "left-clicked" (or vice versa)
 *
 * Backend:
 * Parse different JSonObjects from the client, these come packages in one big JSonObject wrapper.
 * Basic SQL logic follows:
 * One object will be the "select" object which will select the columns the client specifies.
 * One object will be the "from" object which will specify which table to extract the columns from.
 * One object will be the "where" object that will specify which rows in a table to take and which to ignore.
 *
 * After those are done work on accepting a JSonObject which contains a unknown number of JOIN's, call this the "join" JSonObject
 * This will all be entered into a API/Interface so the person doing the frontend will know what to send and how to package/label it.
 *
 * Pretty up the code, fix the Databasemanager class, it is pretty useless atm.
*/
    if(message.contains("update"))
    {
        QJsonArray theVector;
        for(Table* tables : *mTable)
            for(QJsonObject ordersOnTable : tables->toJSON())
                theVector.prepend(ordersOnTable);
        QJsonObject tJsonObject;
        tJsonObject.insert("vector", theVector);
        tJsonObject.insert("eventID", 0);   //TODO: this is a placeholder, change when implementing the eventID system

        QString t = QJsonDocument(tJsonObject).toJson();
        if (pClient)
            pClient->sendTextMessage("update"+QJsonDocument(tJsonObject).toJson());
    }
    else if(message.contains("orderevent"))
    {
            QJsonDocument tDoc = QJsonDocument::fromJson(message.replace("orderevent", "").toUtf8());
            QByteArray tarr = AddOrder(tDoc.object());
            QJsonDocument tNewOrder = QJsonDocument::fromJson(tarr);
            for(QWebSocket * clients : m_clients)
                clients->sendTextMessage("orderevent"+tNewOrder.toJson());
    }
}

void Server::processBinaryMessage(QByteArray message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

void Server::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}


QByteArray Server::AddOrder(QJsonObject tObject)
{
    QVariantMap tOrderMap = tObject.toVariantMap();
    return mTable->at(tOrderMap["table"].toInt())->addOrder(tOrderMap["picture"].toString(), tOrderMap["name"].toString());
}

