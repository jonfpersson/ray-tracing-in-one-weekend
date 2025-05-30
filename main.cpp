#include <iostream>
#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "cube.h"
#include "camera.h"
#include "material.h"
#include <chrono>

hittable_list random_scene() {
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_material));

    for (int64_t a = -2; a < 2; a++) {
        for (int64_t b = -2; b < 2; b++) {
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - point3(4, 0.2, 0)).length() > 0.9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = color::random() * color::random();
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<cube>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = color::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = make_shared<metal>(albedo);
                    world.add(make_shared<cube>(center, 0.2, sphere_material));
                }
            }
        }
    }

 
    auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
    world.add(make_shared<cube>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5));
    world.add(make_shared<cube>(point3(3, 1, 0), 1.0, material3));

    world.add(make_shared<cube>(point3(7, 1, 4.5), 1.0, material3));


    return world;
}

color ray_color(const ray& r, const hittable& world, int64_t depth) {
    hit_record rec;
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0,0,0);

  if (world.hit(r, 0.001, infinity, rec)) {
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth-1);
        return color(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {

   // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int64_t image_width = 400;
    const int64_t image_height = static_cast<int64_t>(image_width / aspect_ratio);
    const int64_t samples_per_pixel = 30;
    const int64_t max_depth = 5;

    // World
    auto world = random_scene();

    // Camera
    camera cam(point3(13,2,3), point3(0,0,0), vec3(0,1,0), 60.0, aspect_ratio);

    // Render

    //printf("P3 %i %i 255", image_width, image_height);
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int64_t j = image_height-1; j >= 0; --j) {
        for (int64_t i = 0; i < image_width; ++i) {
            //std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
           
            color pixel_color(0, 0, 0);
            for (int64_t s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    // End measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // Print the execution time
    int64_t total_rays = image_height * image_width * max_depth * samples_per_pixel;
    std::cerr << "Execution time: " << duration.count() << " milliseconds" << std::endl;
    std::cerr << "Total rays: " << total_rays << std::endl;
    std::cerr << "Total rays/millisecond: " << total_rays / (duration.count()) << std::endl;

}
