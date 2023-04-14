
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
    GraphicsArrow(QPoint from, QPoint to, QColor color = Qt::black, ArrowType type = ArrowType::common);

    //    QRectF boundingRect() const override;
    //    QPainterPath shape() const override;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

private:
    ArrowType type;
};

#endif // GRAPHICSARROW_H


