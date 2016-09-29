#include "clickablelabel.h"
#include <QSignalMapper>

ClickableLabel::ClickableLabel(const QString& text, QWidget* parent, QString tPic, QString tName)
    : QLabel(parent),
      mPic(tPic),
      mName(tName)
{
    signalMapper = new QSignalMapper(this);
    setText(text);

}

ClickableLabel::~ClickableLabel()
{
}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    if(mPic == "")
        emit clicked();
    else
        emit clicked(mPic, mName);
}
