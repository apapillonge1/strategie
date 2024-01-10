#include "plants.h"

Plants::Plants(QPixmap pixmap, QRect boundingRect)
    :m_pixmap(pixmap), m_boundingRect(boundingRect)
{

}

void Plants::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(m_boundingRect, m_pixmap);
    painter->drawRect(m_boundingRect);
}
