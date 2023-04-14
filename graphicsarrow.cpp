
#include "graphicsarrow.h"

GraphicsArrow::GraphicsArrow(QPoint from, QPoint to, QColor color, ArrowType type)
    : QGraphicsLineItem(0), type(type)
{
    setPen(QPen(color, 3, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
    setLine(QLineF(from, to));
}

//QRectF GraphicsArrow::boundingRect() const
//{
//    qreal extra = (pen().width() + 20) / 2.0;

//    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
//                                      line().p2().y() - line().p1().y()))
//        .normalized()
//        .adjusted(-extra, -extra, extra, extra);
//}

void GraphicsArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->drawLine(line());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
