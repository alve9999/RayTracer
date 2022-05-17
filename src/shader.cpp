#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "object.h"
#include "ray.h"
#include "material.h"

#define rand ((float)rand() / RAND_MAX)

glm::vec3 scene_hit(ray& ray, std::vector<std::shared_ptr<object>>& objects, int max_depth) {
    max_depth--;
    std::vector<float> souloutions;
    std::vector<int> index;
    if (max_depth < 0) {
        return glm::vec3(0, 0, 0);
    }
    bool hit = false;
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->check_hit(ray, 0.001, INFINITY)) {
            souloutions.push_back(ray.reg_hit.t);
            index.push_back(i);
            hit = true;

        }
    }
    if (hit) {
        int closest = index[std::min_element(souloutions.begin(), souloutions.end()) - souloutions.begin()];
        objects[closest]->check_hit(ray, 0.001, INFINITY);
        ray = objects[closest]->material->reflect(ray);
        ray.reg_hit.colour = scene_hit(ray, objects, max_depth);
        return objects[closest]->material->ray_colour(ray.reg_hit.colour);
    }
    auto t = 0.5 * (glm::normalize(ray.direction).y + 1.0);
    return glm::vec3(255.0f, 255.0f, 255.0f) * (1.0f - t) + glm::vec3(128.0f, 200.0f, 255.0f) * t;
}
void random_scene(std::vector<std::shared_ptr<object>>& objects) {
    std::vector<std::shared_ptr<object>> objects;
    glm::vec3 center(0, -1000, 0);
    diffuse diffuse1(glm::vec3(0.5, 0.5, 0.5));
    sphere sphere1(center, 1000.0f, diffuse1);
    objects.push_back(std::make_shared<sphere>(sphere1));
    glass material1 = glass(1.5);
    objects.push_back(std::make_shared<sphere>(glm::vec3(0, 1, 0), 1.0, material1));
    diffuse material2(glm::vec3(0.4, 0.2, 0.1));
    objects.push_back(std::make_shared<sphere>(glm::vec3(-4, 1, 0), 1.0, material2));
    metal material3(1, glm::vec3(0.7, 0.6, 0.5));
    objects.push_back(std::make_shared<sphere>(glm::vec3(4, 1, 0), 1.0, material3));
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double random_material = rand;
            glm::vec3 center(a + 0.9 * rand, 0.2, b + 0.9 * rand);
            if (random_material < 0.7) {
                diffuse* material = new diffuse(glm::vec3(rand, rand, rand));
                sphere* sphere1 = new sphere(center, 0.2, *material);
                objects.push_back(std::make_shared<sphere>(*sphere1));
            }
            else if (random_material < 0.85) {
                metal* material = new metal(0.97, glm::vec3(rand, rand, rand));
                sphere* sphere1 = new sphere(center, 0.2, *material);
                objects.push_back(std::make_shared<sphere>(*sphere1));
            }
            else {
                glass* material = new glass(1.5);
                sphere* sphere1 = new sphere(center, 0.2, *material);
                objects.push_back(std::make_shared<sphere>(*sphere1));
            }
        }
    }
}
void render_image(int y1,int y2,int image_width, int pixel_sample_size, int image_height, glm::vec3 pov,glm::vec3 bottom_left, std::vector<std::shared_ptr<object>>& objects,glm::vec3 view_height,glm::vec3 view_width) {
    for (int j = y2 - 1; j >= y1; --j) {
        for (int i = 0; i < image_width; ++i) {

            glm::vec3 pixel_colour(0, 0, 0);
            for (int k = 0; k < pixel_sample_size; k++) {
                float u = (float(i) + rand) / float(image_width - 1);
                float v = (float(j) + rand) / float(image_height - 1);
                ray ray = get_ray(u, v, pov, bottom_left, view_height, view_width);
                glm::vec3 colour = scene_hit(ray, objects, 50);
                pixel_colour += colour;
            }
            glColor3f(pixel_colour.x/255,pixel_colour.y/255,pixel_colour.z/255);
            glVertex2i(i,j);
        }
        std::lock_guard<std::mutex> guard(mute_count);
        count++;
    }
}

void shader(){
    float image_height = 1080;
    float ratio = (16.0f / 9.0f);
    int image_width = static_cast<int>(image_height*ratio);

    // camera
    glm::vec3 pov = glm::vec3(-13, -2, -5);
    glm::vec3 pol = glm::vec3(0, 0, 0);
    glm::vec3 vup = glm::vec3(0, -1, 0);
    glm::vec3 w = glm::normalize(pov - pol);
    glm::vec3 u = glm::normalize(cross(vup, w));
    glm::vec3 v = glm::normalize(cross(w, u));
    
    double vfov=20;
    double h = tan((vfov*PI/180) / 2);
    double viewport_height = 2.0 * h;
    double viewport_width = ratio * viewport_height;

    glm::vec3 view_height = v*viewport_height;
    glm::vec3 view_width = u*viewport_width;
    int pixel_sample_size = 500;
    int max_depth = 50;
    glm::vec3 bottom_left = pov - (view_width / 2) - (view_height / 2) - w;

    //multithreading
    int thread_count = 8;
    std::vector<std::thread> thread_pool;
    
    // Render
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < thread_count; i++) {
        thread_pool.push_back(std::thread(render_image, (image_height / 8) * i, (image_height / 8) * (i + 1), image_width, pixel_sample_size, image_height, pov, bottom_left, std::ref(objects), view_height, view_width));
    }
    for (int i = 0; i < thread_count; i++) {
        while (std::thread::id() == std::thread().get_id()) {
            auto percent = float(count) / float(image_height);
            if (count>=(image_height)) {
                break;
            }
            std::cerr << percent * 100 << "%" << std::endl;
        }
        thread_pool[i].join();
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(t2 - t1);
    std::cerr << time_span.count();
}