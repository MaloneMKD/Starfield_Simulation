#include "star.h"

Star::Star(QRectF rect, QGraphicsItem *parent): QGraphicsEllipseItem(rect, parent)
{

}

float Star::dx() const
{
    return m_dx;
}

void Star::setDx(float newDx)
{
    m_dx = newDx;
}

float Star::dy() const
{
    return m_dy;
}

void Star::setDy(float newDy)
{
    m_dy = newDy;
}

