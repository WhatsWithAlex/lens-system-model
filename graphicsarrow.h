
#ifndef GRAPHICSARROW_H
#define GRAPHICSARROW_H

#include <QGraphicsView>
#include <QGraphicsLineItem>

enum class ArrowType
{
    common,
    reversed
};

class GraphicsArrow : public QGraphicsLineItem
{
public:
    GraphicsArrow(QPointF from, QPointF to, QColor color = Qt::black, ArrowType type = ArrowType::common,
                  float arrowhead_length = 10.0f, float arrowhead_angle_degrees = 45.0f);

    QRectF boundingRect() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    QPointF arrowhead[3];
};

#endif // GRAPHICSARROW_H


