#pragma once
#include "ray.h"
#include "materials.h"
#include <glm/glm.hpp>
#include <memory>
#include <vector>

class object {
public:
	materials* material;
	object() {};
	virtual bool check_hit(ray& ray, float tmin, float tmax) { return false; };
};


class sphere : public object {
public:
	sphere(vec3 aCenter, float aRadius,materials& aMaterial);
	vec3 center;
	float radius;
	bool check_hit(ray& ray, float tmin, float tmax);
};
