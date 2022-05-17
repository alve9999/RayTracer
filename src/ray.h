#pragma once
#include "glm/fwd.hpp"
#include <glm/glm.hpp>

class hit {
public:
	float t;
	bool outside;
	glm::vec3 normal;
	glm::vec3 colour;
	hit() {};
	hit(float aT, bool aOutside, glm::vec3 aNormal, glm::vec3 aColour);
};

class ray {
public:
    glm::vec3 direction, origin;
	hit reg_hit;

    ray(glm::vec3 adirection, glm::vec3 aorigin);

    bool intersects_triangle(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    glm::vec3 at(const float t);
};
