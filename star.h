#ifndef STAR_H
#define STAR_H

#include <QGraphicsEllipseItem>

class Star : public QGraphicsEllipseItem
{
public:
    Star(QRectF rect, QGraphicsItem *parent=nullptr);


    float dx() const;
    void setDx(float newDx);

    float dy() const;
    void setDy(float newDy);

private:
    float m_dx;
    float m_dy;
};

#endif // STAR_H
