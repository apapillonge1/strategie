#ifndef PLANTS_H
#define PLANTS_H

#include "qt_graphics_models/game_element.h"
#include "QPainter"

class Plants: public game_element
{
public:
    Plants(QPixmap pixmap, QRect boundingRect);

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget * = nullptr)  override;

private:
    QPixmap m_pixmap;
    QRect m_boundingRect;
};

#endif // PLANTS_H
