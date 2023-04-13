
#ifndef LENS_UTILS_H
#define LENS_UTILS_H

struct Point2D
{
    float x, y;

    Point2D(float x_value, float y_value)
        : x(x_value)
        , y(y_value) {};
};

enum class ObjectOrientation
{
    up,
    down
};

enum class ImageType
{
    real,
    imaginary
};

ObjectOrientation getOppositeOrientation(ObjectOrientation orientation);

struct LensState
{
    float x = 0.0f;
    float focal_length = 0.0f;
    float r1 = 0.0f;
    float r2 = 0.0f;
    bool is_active = false;
    bool is_focal_length_set = true;
};

#endif // LENS_UTILS_H
