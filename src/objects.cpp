#include "objects.h"
#include <glm/glm.hpp>

sphere::sphere(glm::vec3 aCenter, float aRadius,materials& aMaterial) {
    center = aCenter;
    radius = aRadius;
    material = &aMaterial;
}

bool sphere::check_hit(ray& ray,  float tmin, float tmax){
    glm::vec3 k = ray.origin + center;
    float a =glm::dot(ray.direction, ray.direction);
    float h = glm::dot(k, ray.direction);
    float c = glm::dot(k, k) - radius * radius;
    if (((h * h) - (a * c)) < 0) {
        return false;
    }
    float ans = (-h - sqrt(h * h - a * c)) / a;
    if (ans<tmin || ans>tmax) {
        ans = (-h - sqrt(h * h - a * c)) / a;
        if (ans<tmin || ans>tmax) {
            return false;
        }
    }
    ray.reg_hit.normal = glm::normalize(ray.at(ans) + center);
    ray.reg_hit.t = ans;
    if (glm::dot(ray.reg_hit.normal, glm::normalize(ray.direction)) < 0) {
        ray.reg_hit.outside = false;
    }
    else {
        ray.reg_hit.outside = true;
    }
    
    return true;
}
