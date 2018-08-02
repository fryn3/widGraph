#include "edge.h"
#include "node.h"
#include "graphwidget.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

Node::Node() : _mark(0)
{
    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

Node::~Node()
{
    while (!edgeList.isEmpty())
        delete edgeList.takeFirst();
}

void Node::addEdge(Edge *edge)
{
    edgeList << edge;
    edge->adjust();
}

void Node::removeEdge(Edge *edge)
{
    edgeList.removeOne(edge);
}

bool Node::mark() const
{
    return _mark;
}

void Node::setMark(bool mark)
{
    _mark = mark;
    update();
}

QList<Edge *> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    return shape().boundingRect();
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    painter->setBrush((option->state & QStyle::State_Selected ? Qt::cyan: Qt::white));
    painter->setPen(QPen(_mark ? Qt::magenta : Qt::black, 2));
    painter->drawEllipse(-RADIUS, -RADIUS, 2 * RADIUS, 2 * RADIUS);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        foreach (Edge *edge, edgeList)
            edge->adjust();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

