
#include <QVector2D>
#include "graphicsarrow.h"

GraphicsArrow::GraphicsArrow(QPointF from, QPointF to, QColor color, ArrowType type,
                             float arrowhead_length, float arrowhead_angle_degrees)
    : QGraphicsLineItem(0)
{
    setPen(QPen(color, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setLine(QLineF(from, to));

    if (type == ArrowType::reversed) arrowhead_angle_degrees = 180.0f - arrowhead_angle_degrees;
    float arrowhead_angle_rad = 2 * M_PI * arrowhead_angle_degrees / 360.0f;

    QVector2D dif = QVector2D(to - from).normalized();

    float l_rotate_angle_rad = M_PI - arrowhead_angle_rad;
    float l_x = dif.x() * qCos(l_rotate_angle_rad) - dif.y() * qSin(l_rotate_angle_rad);
    float l_y = dif.x() * qSin(l_rotate_angle_rad) + dif.y() * qCos(l_rotate_angle_rad);
    QPointF arrowhead_left = QPointF(arrowhead_length * l_x, arrowhead_length * l_y) + to;

    float r_rotate_angle_rad = M_PI + arrowhead_angle_rad;
    float r_x = dif.x() * qCos(r_rotate_angle_rad) - dif.y() * qSin(r_rotate_angle_rad);
    float r_y = dif.x() * qSin(r_rotate_angle_rad) + dif.y() * qCos(r_rotate_angle_rad);
    QPointF arrowhead_right = QPointF(arrowhead_length * r_x, arrowhead_length * r_y) + to;

    arrowhead[0] = arrowhead_left;
    arrowhead[1] = to;
    arrowhead[2] = arrowhead_right;
}

QRectF GraphicsArrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void GraphicsArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(pen());
    painter->drawLine(line());
    painter->drawPolyline(arrowhead, 3);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
