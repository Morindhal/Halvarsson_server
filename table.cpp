#include "table.h"
#include "ui_table.h"
#include "clickablelabel.h"
#include "order.h"
#include "orderserver.h"
#include <vector>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
//#include "QtAwesome/QtAwesome.h"

Table::Table(QWidget *parent, int tTableNmbr, double tTab) :
    QDialog(parent),
    ui(new Ui::Table),
    mTableNmbr(tTableNmbr),
    mTab(tTab)
{
    mParentServerApp = (OrderServer*)parent;
    ui->setupUi(this);
    //QtAwesome* awesome = new QtAwesome( qApp );
    //awesome->initFontAwesome();
    QLabel* tLabel2 = new QLabel("", this);
    tLabel2->setText(QString(std::to_string(mTableNmbr+1).c_str()) );
    tLabel2->setFont(QFont( "Arial", 30, QFont::Bold));
    ui->Table_Nmbr->addWidget(tLabel2);
}

Table::~Table()
{
    delete ui;
}

std::vector<QJsonObject>  Table::toJSON()
{
    std::vector<QJsonObject> tOrders;
    for(Order *order : mOrders)
        tOrders.push_back( order->toJSON());
    return tOrders;
}

void Table::closeOrder(int tOrderID)
{
    for(int i = 0 ; i<mOrders.size() ; i++)
        if(((Order*)mOrders.at(i))->pOrderID == tOrderID)
        {
            delete mOrders.at(i);
            mOrders.erase(mOrders.begin()+i);
        }
}


QByteArray Table::addOrder(const QString &tPic, const QString &tName)
{
    Order* tOrder = new Order(this,tPic,tName,20,mParentServerApp->pCurrentHighestOrderID++);
    mOrders.push_back(tOrder);
    displayOrders();
    return QJsonDocument(tOrder->toJSON()).toJson();
}

void Table::displayOrders()
{
    int i = 0, n = 0;
    foreach (Order* order, mOrders)
            ui->Table_Layout->removeWidget(order);
    foreach (Order* order, mOrders)
    {
        ui->Table_Layout->addWidget(order, n%2, i);
        ++n;
        if(n%2== 0)
            ++i;
    }
}
