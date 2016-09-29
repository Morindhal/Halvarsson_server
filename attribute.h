#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QWidget>

namespace Ui {
class Attribute;
}

class Attribute : public QWidget
{
    Q_OBJECT

public:
    explicit Attribute(QWidget *parent = 0, QString tAttributeName = "default", double tPrice = 0);
    ~Attribute();
    QString toJSON();

    QString mAttributeName;
private:
    Ui::Attribute *ui;
    double mPrice;
};

#endif // ATTRIBUTE_H
