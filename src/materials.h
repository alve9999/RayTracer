#pragma once
#include "Ray.h"
#include <glm/glm.hpp>

glm::vec3 random_sphere_point();

class materials {
public:
	materials() {};
	virtual ray reflect(ray& incoming_ray) { return incoming_ray;};

	virtual glm::vec3 ray_colour(glm::vec3 light) { return glm::vec3(); };
};

class diffuse : public materials {
public:
	glm::vec3 absorption;

	diffuse(glm::vec3 aAbsorption);

	ray reflect(ray& incoming_ray);

	glm::vec3 ray_colour(glm::vec3 light);

	ray refract(ray& incoming_ray) { return incoming_ray; };

};

class metal : public materials {
public:
	glm::vec3 albedo;
	float fuzzines;

	metal(float aFuzzines, glm::vec3 aAlbedo);

	ray reflect(ray& incoming_ray);

	glm::vec3 ray_colour(glm::vec3 light);

	ray refract(ray& incoming_ray) { return incoming_ray; };
};

class glass : public materials {
public:
	float refractive_index;
	glass(float aRefractive_index);

	ray reflect(ray& incoming_ray);

	glm::vec3 ray_colour(glm::vec3 light);

	float schlink_aproximation(float cos);
};