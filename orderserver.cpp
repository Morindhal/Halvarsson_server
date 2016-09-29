#include "orderserver.h"
#include "ui_orderserver.h"
#include "server.h"
#include "table.h"
#include <vector>

OrderServer::OrderServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OrderServer),
    port(1234),
    pCurrentHighestOrderID(0)
{
    ui->setupUi(this);
    connect(ui->exitAction,SIGNAL(triggered(bool)),SLOT(close()));
    for(int n = 0 ; n<10 ; n++)
    {
        mTable.push_back(new Table(this, n));
        ui->TablesLayout->addWidget(mTable.at(n));
    }
}

OrderServer::~OrderServer()
{
    delete ui;
}

void OrderServer::on_serverOn_clicked()
{
    bool debug = false;

    if(!server)
    {
        centralWidget()->findChild<QPushButton*>("serverOn")->setEnabled(false);
        centralWidget()->findChild<QPushButton*>("serverOff")->setEnabled(true);
        qDebug() << "New server!";
        server = new Server(port, &mTable, debug);
    }
    OrderServer::updateServerState();
}


void OrderServer::on_serverOff_clicked()
{
    if(server)
    {
        centralWidget()->findChild<QPushButton*>("serverOff")->setEnabled(false);
        centralWidget()->findChild<QPushButton*>("serverOn")->setEnabled(true);
        qDebug() << "Kill server!";
        delete server;
        server = NULL;
    }
    OrderServer::updateServerState();
}

void OrderServer::updateServerState()
{
    /*if(!server)
        centralWidget()->findChild<QLabel*>("serverState")->setText("Server is currently OFF");
    else
        centralWidget()->findChild<QLabel*>("serverState")->setText("Server is currently ON");*/
}
