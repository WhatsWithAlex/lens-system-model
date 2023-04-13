
#include "model.h"

const unsigned int max_lens_system_size = 5;
extern const float lens_refractive_index = 1.5f;

//          Object          //
Object::Object()
    : x_coordinate(0.0f)
    , size(0.0f)
    , orientation(ObjectOrientation::up) {}

Object::Object(float x_coordinate, float obj_size, ObjectOrientation orientation)
    : x_coordinate(x_coordinate)
    , orientation(orientation)
{
    if (obj_size < 0.0f)
        throw std::logic_error("Object size can not be negative");

    size = obj_size;
}

float Object::get_x_coordinate() const { return x_coordinate; }

float Object::get_size() const { return size; }

ObjectOrientation Object::get_orientation() const { return orientation; }

//          Image           //
Image::Image() : type(ImageType::real) {}
Image::Image(float x_coordinate, float size, ObjectOrientation orientation, ImageType type)
    : Object(x_coordinate, size, orientation)
    , type(type) {}

ImageType Image::get_type() const { return type; }

//          Lens            //
float Lens::calculateFocalLen(float r1, float r2)
{
    return (r1 * r2) / ((lens_refractive_index - 1.0f) * (r2 - r1));
}

Lens::Lens(float x_coordinate, float focal_length, bool is_active)
    : x_coordinate(x_coordinate)
    , focal_length(focal_length)
    , active(is_active) {}

Lens::Lens(float x_coordinate, float r1, float r2, bool is_active)
    : x_coordinate(x_coordinate)
    , active(is_active)
{
    focal_length = Lens::calculateFocalLen(r1, r2);
}

Image Lens::calculateImage(const Object &in_object) const
{
    const float distance_to_object = x_coordinate - in_object.get_x_coordinate();
    const float distance_to_image =
        focal_length * distance_to_object / (distance_to_object - focal_length);
    const float size_scale = -(distance_to_image / distance_to_object);

    float image_x_coordinate = x_coordinate + distance_to_image;
    const float image_size = std::abs(size_scale) * in_object.get_size();
    ObjectOrientation image_orienatation;
    ImageType image_type;

    if (size_scale < 0)
        image_orienatation = getOppositeOrientation(in_object.get_orientation());
    else
        image_orienatation = in_object.get_orientation();

    if (size_scale * distance_to_object < 0)
        image_type = ImageType::real;
    else
        image_type = ImageType::imaginary;

    return Image(image_x_coordinate, image_size, image_orienatation, image_type);
}

float Lens::get_x_coordinate() const { return x_coordinate; }

float Lens::get_focal_length() const { return focal_length; }

bool Lens::is_active() const { return active; }

//      LensSystemModel      //
LensSystemModel::LensSystemModel(): lens_system(max_lens_system_size) {}

LensSystemModel::LensSystemModel(Object object) : object(object) {}

void LensSystemModel::calculate()
{
    std::vector<Lens> lens_sorted = lens_system;
    std::sort(
        lens_sorted.begin(),
        lens_sorted.end(),
        [](const Lens &a, const Lens &b) -> bool {
            return a.get_x_coordinate() < b.get_x_coordinate();
        });

    Object *current_object = &object;
    Image current_image;
    for (const Lens current_lens : lens_sorted) {
        if (!current_lens.is_active())
            continue;

        current_image = current_lens.calculateImage(*current_object);
        current_object = &current_image;
    }

    image = *((Image *)current_object);
}

void LensSystemModel::setLens(int lens_index, Lens new_lens) {
    lens_system[lens_index] = new_lens;
}

Lens LensSystemModel::getLens(int lens_index)
{
    return lens_system[lens_index];
}

Image LensSystemModel::get_image() const { return image; }

void LensSystemModel::set_object(const Object &new_object) { object = new_object; }
