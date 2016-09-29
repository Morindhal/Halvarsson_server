#ifndef TABLE_H
#define TABLE_H

#include <QDialog>

class Vector;
class Order;
class OrderServer;

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QWidget *parent = 0, int tTableNmbr = 0, double tTab = 0);
    int mTableNmbr;
    ~Table();
    std::vector<QJsonObject> toJSON();
    void displayOrders();

public slots:
    void closeOrder(int tOrderID);
    QByteArray addOrder(const QString &tPic, const QString &tName);


private:
    Ui::Table *ui;
    std::vector<Order*> mOrders;
    double mTab;
    OrderServer *mParentServerApp;
};

#endif // TABLE_H
