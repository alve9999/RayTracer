#include "materials.h"
#include <glm/glm.hpp>
#define rand ((float)rand() / RAND_MAX)

glm::vec3 random_sphere_point() {
    glm::vec3 random_point;
    while (1) {
        random_point = glm::vec3(rand * 2.0f - 1.0f, rand * 2.0f - 1.0f, rand * 2.0f - 1.0f);
        if (glm::length(random_point) < 1) {
            return random_point;
        }
    }
}
diffuse::diffuse(glm::vec3 aAbosorption) {
	absorption = aAbosorption;
}
ray diffuse::reflect(ray& incoming_ray) {
	glm::vec3 origin = incoming_ray.at(incoming_ray.reg_hit.t);
	//my method
	//glm::vec3 direction = incoming_ray.reg_hit.normal.unit_vector() + random_sphere_point();
	//lambertian
	glm::vec3 direction = glm::normalize(incoming_ray.reg_hit.normal) + glm::normalize(random_sphere_point());
	ray outgoing_ray(direction, origin);
	outgoing_ray.reg_hit = incoming_ray.reg_hit;
	return outgoing_ray;
}

glm::vec3 diffuse::ray_colour(glm::vec3 light){
	return light*absorption;
}

metal::metal(float aFuzzines,glm::vec3 aAlbedo) {
	fuzzines = aFuzzines;
	albedo = aAlbedo;
};

ray metal::reflect(ray& incoming_ray) {
	glm::vec3 origin = incoming_ray.at(incoming_ray.reg_hit.t);
	glm::vec3 direction = (incoming_ray.direction - incoming_ray.reg_hit.normal * 2.0f * glm::dot(incoming_ray.direction, incoming_ray.reg_hit.normal)+(random_sphere_point()) * (1-fuzzines));
	ray outgoing_ray(direction, origin);
	outgoing_ray.reg_hit = incoming_ray.reg_hit;
	return outgoing_ray;
}

glm::vec3 metal::ray_colour(glm::vec3 light) {
	return albedo*light;
}
glass::glass(float aRefractive_index) {
	refractive_index = aRefractive_index;
}
ray glass::reflect(ray& incoming_ray) {
	float k = 1/refractive_index;
	float cos = glm::dot(-incoming_ray.direction, incoming_ray.reg_hit.normal)/(-glm::length(incoming_ray.direction), glm::length(incoming_ray.reg_hit.normal));
	float sin = sqrt(1.0-cos*cos);
	if (incoming_ray.reg_hit.outside == true) {
		k =refractive_index;
	}

	if (k * sin > 1.0f ||schlink_aproximation(cos)>rand) {
		glm::vec3 origin = incoming_ray.at(incoming_ray.reg_hit.t);
		glm::vec3 direction = incoming_ray.direction - incoming_ray.reg_hit.normal * 2.0f * glm::dot(incoming_ray.direction, incoming_ray.reg_hit.normal);
		ray outgoing_ray(direction, origin);
		outgoing_ray.reg_hit = incoming_ray.reg_hit;
		return outgoing_ray;
	}
	glm::vec3 outgoing_ray_a = (incoming_ray.direction+(incoming_ray.reg_hit.normal*cos))*k;
	glm::vec3 outgoing_ray_b = incoming_ray.reg_hit.normal * (float)(-sqrt(1 - (glm::length(outgoing_ray_a) * glm::length(outgoing_ray_a))));
	ray outgoing_ray(outgoing_ray_a + outgoing_ray_b, incoming_ray.at(incoming_ray.reg_hit.t));
	outgoing_ray.reg_hit = incoming_ray.reg_hit;
	return outgoing_ray;
}


glm::vec3 glass::ray_colour(glm::vec3 light) {
	return light;
}

float glass::schlink_aproximation(float cos) {
	float R = ((refractive_index - 1) / (refractive_index + 1)) * ((refractive_index - 1) / (refractive_index + 1));
	return R + (1 - R) * pow(1.0f-cos,5);
}