
#ifndef MODEL_H
#define MODEL_H

#include <stdexcept>
#include <string>
#include <vector>

#include <algorithm>
#include <cmath>
#include <iostream>

extern const unsigned int max_lens_system_size;

enum class ObjectOrientation
{
    up,
    down
};

ObjectOrientation getOppositeOrientation(ObjectOrientation orientation);

class Object
{
protected:
    float x_coordinate;
    float size;
    ObjectOrientation orientation;

public:
    Object();
    Object(float x_coordinate, float obj_size, ObjectOrientation orientation);

    float get_x_coordinate() const;
    float get_size() const;
    ObjectOrientation get_orientation() const;
};

enum class ImageType
{
    real,
    imaginary
};

class Image : public Object
{
    ImageType type;

public:
    Image();
    Image(float x_coordinate, float size, ObjectOrientation orientation, ImageType type);

    ImageType get_type() const;
};

class Lens
{
    float x_coordinate;
    float focal_length;
    float refractive_index;
    bool active;

public:
    Lens(float x_coordinate = 0.0f, float focal_length = 0.0f, bool is_active = false,
         float refractive_index = 1.5f);
    Lens(float x_coordinate, float r1, float r2, bool is_active = false,
         float refractive_index = 1.5f);

    Image calculateImage(const Object &in_object) const;

    float get_x_coordinate() const;
    float get_focal_length() const;
    float get_refractive_index() const;
    bool is_active() const;

    static float calculateFocalLen(float r1, float r2, float refractive_index = 1.5f);
};

class LensSystemModel
{
    std::vector<Lens> lens_system;
    Object object;
    Image image;

public:
    LensSystemModel();
    LensSystemModel(Object object);

    void calculate();

    void setLens(int lens_index, Lens new_lens);
    Lens getLens(int lens_index);

    Image get_image() const;
    void set_object(const Object &new_object);
};

#endif // MODEL_H
