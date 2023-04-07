#pragma once

struct Point2D
{
    float x, y;

    Point2D(float x_value, float y_value) : x(x_value), y(y_value){};
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

struct LensSettings
{
    float x;
    float focal_length;
    float r1 = 0.0f;
    float r2 = 0.0f;
    bool is_active = false;
};
