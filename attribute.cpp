#include "attribute.h"
#include "ui_attribute.h"

Attribute::Attribute(QWidget *parent, QString tAttributeName, double tPrice) :
    QWidget(parent),
    ui(new Ui::Attribute),
    mAttributeName(tAttributeName),
    mPrice(tPrice)
{
    ui->setupUi(this);
}

Attribute::~Attribute()
{
    delete ui;
}

QString Attribute::toJSON()
{
    return mAttributeName;
}
