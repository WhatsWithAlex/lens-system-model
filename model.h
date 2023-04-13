
#ifndef MODEL_H
#define MODEL_H

#include <stdexcept>
#include <string>
#include <vector>

#include "utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>

extern const unsigned int max_lens_system_size;
extern const float lens_refractive_index;

class Object
{
protected:
    float x_coordinate;
    float size;
    ObjectOrientation orientation;

public:
    Object();
    Object(float x_coordinate, float obj_size, ObjectOrientation orientation);

    // std::vector<LightRay> generateLightRays(Lens next_lens);

    float get_x_coordinate() const;
    float get_size() const;
    ObjectOrientation get_orientation() const;
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
    bool active;

public:
    Lens(float x_coordinate = 0.0f, float focal_length = 0.0f, bool is_active = false);
    Lens(float x_coordinate, float r1, float r2, bool is_active);

    // LightRay calculateLightRay(LightRay in_ray);

    Image calculateImage(const Object &in_object) const;

    float get_x_coordinate() const;
    float get_focal_length() const;
    bool is_active() const;

    static float calculateFocalLen(float r1, float r2);
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

// class LightRay
// {
// public:
//     Point2D point1;
//     Point2D point2;

//     LightRay(Point2D point1, Point2D point2);

//     Point2D getIntersection(LightRay ray);
// };

#endif // MODEL_H
