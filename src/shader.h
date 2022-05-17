#pragma once
#include "ray.h"
#include "materials.h"
#include "objects.h"
#include <glm/glm.hpp>
#include <vector>
#include <memory>
glm::vec3 scene_hit(ray& ray, std::vector<std::shared_ptr<object>>& objects, int max_depth);
void shader();
void random_scene(std::vector<std::shared_ptr<object>>& objects);
void render_image(int y1,int y2,int image_width, int pixel_sample_size, int image_height, glm::vec3 pov,glm::vec3 bottom_left, std::vector<std::shared_ptr<object>>& objects,glm::vec3 view_height,glm::vec3 view_width);
