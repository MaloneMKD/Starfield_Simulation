#include "FieldScene.h"
#include <QDebug>
#include <QGraphicsItem>
#include <math.h>
#include <random>
#include <time.h>
#include <QList>

FieldScene::FieldScene(QRectF rect, QGraphicsView *view, QObject *parent): QGraphicsScene(rect, parent)
{
    // Initialize other variables
    m_view = view;
    m_focus_point = QPointF(0, 0);
    is_pressed = false;

    // Turn off the scroll bar
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Set up stars
    for(int i = 0; i < NUM_STARS; i++)
    {
        // Create a star
        Star *temp = new Star(QRectF(0, 0, 8, 8));

        // Set position
        temp->setPos(mapToRange(rand() % VIEW_WIDTH, 0, VIEW_WIDTH, -VIEW_WIDTH/2.0, VIEW_WIDTH/2.0 - 10),
                     mapToRange(rand() % VIEW_HEIGHT, 0, VIEW_HEIGHT, -VIEW_HEIGHT/2.0, VIEW_HEIGHT/2.0 - 10));

        // Star appearance
        temp->setPen(Qt::NoPen);
        temp->setBrush(QBrush(Qt::white));

        // Get dx and dy of the line from the center of the view to the star
        QLineF tempLine = QLineF(0, 0, temp->sceneBoundingRect().center().x(), temp->sceneBoundingRect().center().y());

        //m_scene->addLine(tempLine, QPen(Qt::red));
        temp->setDx(tempLine.dx());
        temp->setDy(tempLine.dy());

        // Append star to list
        m_stars.append(temp);
    }

    // Draw stars
    foreach(Star *temp,  m_stars)
        this->addItem(temp);

    //Setup timer
    m_timer = new QTimer(this);
    m_timer->setInterval(0);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(updateObjects()));
    m_timer->start();
}

void FieldScene::updateObjects()
{
    // Add dx and dy to the position
    for(int i = 0; i < NUM_STARS; i++)
    {
        m_stars[i]->setPos(m_stars[i]->scenePos().x() + m_stars[i]->dx()/100.0, m_stars[i]->scenePos().y() + m_stars[i]->dy()/100.0);

        // If the star is out of the view it must be set back to the center (0, 0)
        if(m_stars[i]->scenePos().x() > VIEW_WIDTH/2.0 - 10 || m_stars[i]->scenePos().x() < -VIEW_WIDTH/2.0 ||
            m_stars[i]->scenePos().y() > VIEW_HEIGHT/2.0 - 10 || m_stars[i]->scenePos().y() < -VIEW_HEIGHT/2.0)
        {
            m_stars[i]->setPos(mapToRange(rand() % VIEW_WIDTH, 0, VIEW_WIDTH, -VIEW_WIDTH/2.0, VIEW_WIDTH/2.0 - 10),
                               mapToRange(rand() % VIEW_HEIGHT, 0, VIEW_HEIGHT, -VIEW_HEIGHT/2.0, VIEW_HEIGHT/2.0 - 10));

            // Get dx and dy of the line from the center of the view to the star
            QLineF tempLine = QLineF(m_focus_point.x(), m_focus_point.y(), m_stars[i]->sceneBoundingRect().center().x(), m_stars[i]->sceneBoundingRect().center().y());
            m_stars[i]->setDx(tempLine.dx());
            m_stars[i]->setDy(tempLine.dy());
        }

        // Change size. The further away the center the bigger
        QLineF tempLine = QLineF(m_focus_point.x(), m_focus_point.y(), m_stars[i]->sceneBoundingRect().center().x(), m_stars[i]->sceneBoundingRect().center().y());
        m_stars[i]->setScale(0.1 + tempLine.length() / 1000);
    }

    this->update();
    m_view->update();
}

void FieldScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_focus_point = QPointF(-event->scenePos().x(), -event->scenePos().y());
    is_pressed = true;
}

void FieldScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event)
    m_focus_point = QPointF(0, 0);
    is_pressed = false;
}

void FieldScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(is_pressed)
        m_focus_point = QPointF(-event->scenePos().x(), -event->scenePos().y());
}

qreal FieldScene::mapToRange(qreal number, qreal inputStart, qreal inputEnd, qreal outputStart, qreal outputEnd)
{
    qreal r = inputEnd - inputStart;
    qreal R = outputEnd - outputStart;
    qreal x = number - inputStart;
    qreal y = (R / r) * x;
    return outputStart + y;
}
