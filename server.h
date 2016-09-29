#ifndef SERVER_H
#define SERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>
#include "orderserver.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class DatabaseManager;
class vector;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(quint16 port, std::vector<Table*> *tTable, bool debug = false, QObject *parent = Q_NULLPTR);
    ~Server();
    QByteArray AddOrder(QJsonObject tObject);

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    DatabaseManager db;
    std::vector<Table*> *mTable;
};

#endif // SERVER_H
