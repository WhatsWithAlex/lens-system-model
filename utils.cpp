#include "utils.h"


ObjectOrientation getOppositeOrientation(ObjectOrientation orientation) 
{
    return 
        orientation == ObjectOrientation::up 
        ? ObjectOrientation::down 
        : ObjectOrientation::up;
}
