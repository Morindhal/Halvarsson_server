#ifndef ORDERSERVER_H
#define ORDERSERVER_H

#include <QMainWindow>
#include "databasemanager.h"

class Server;
class Table;
class vector;

namespace Ui {
class OrderServer;
}

class OrderServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit OrderServer(QWidget *parent = 0);
    ~OrderServer();
    unsigned int pCurrentHighestOrderID;

private slots:
    void on_serverOn_clicked();

    void on_serverOff_clicked();

private:
    Ui::OrderServer *ui;
    void updateServerState();
    Server *server = NULL;
    int port;
    std::vector<Table*> mTable;
};

#endif // ORDERSERVER_H
