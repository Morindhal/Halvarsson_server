#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>

class QSignalMapper;

class ClickableLabel : public QLabel
{
Q_OBJECT
public:
    explicit ClickableLabel( const QString& text="", QWidget* parent=0, QString tPic = "", QString tName = "" );
    ~ClickableLabel();
signals:
    void clicked();
    void clicked(const QString &mPic, const QString &mName);
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    QString mPic;
    QString mName;
    QSignalMapper *signalMapper;
};

#endif // CLICKABLELABEL_H
