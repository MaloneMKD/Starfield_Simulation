#ifndef FIELD_SCENE_H
#define FIELD_SCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QtGui>
#include <QtCore>
#include <QTimer>
#include <QGraphicsSceneMouseEvent>
#include <star.h>

class FieldScene: public QGraphicsScene
{
    Q_OBJECT

public:
    FieldScene(QRectF rect, QGraphicsView *view, QObject *parent);

    qreal mapToRange(qreal number, qreal inputStart, qreal inputEnd, qreal outputStart, qreal outputEnd);

public slots:
    void updateObjects();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QGraphicsView *m_view;
    QTimer *m_timer;
    QList<Star*> m_stars;
    QPointF m_focus_point;
    const int VIEW_WIDTH = 1518;
    const int VIEW_HEIGHT = 724;
    const int NUM_STARS = 200;
    bool is_pressed;
};

#endif // FIELD_SCENE_H
