#include "ray.h"
#include <glm/glm.hpp>

hit::hit(float aT, bool aOutside, glm::vec3 aNormal, glm::vec3 aColour) {
    t = aT;
    outside = aOutside;
    normal = aNormal;
    colour = aColour;
}

ray::ray(glm::vec3 adirection, glm::vec3 aorigin) {
    direction = adirection;
    origin = aorigin;
}

glm::vec3 ray::at(const float t) {
    return origin + direction * t;
}