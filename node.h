#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>
#include <edge.h>

class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

class Node : public QGraphicsItem
{
    friend Edge::Edge(Node *sourceNode, Node *destNode);
public:
    Node();
    ~Node() override;
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const override { return Type; }
    static const int RADIUS = 30;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    bool mark() const;
    void setMark(bool mark);

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void addEdge(Edge *edge);
private:
    QList<Edge *> edgeList;
    bool _mark;
};

#endif // NODE_H
