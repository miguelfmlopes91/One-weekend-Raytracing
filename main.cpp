//
//  main.cpp
//  RayTracing
//
//  Created by Miguel Lopes on 11/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#include "constants.h"
#include "color.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"
#include <cfloat>
#include <iostream>

bool hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;
    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - sqrt(discriminant) ) / a;
    }
}

///I then did a standard graphics trick of scaling that to 0.0≤𝑡≤1.0. When 𝑡=1.0 I want blue. When 𝑡=0.0 I want white. In between, I want a blend. This forms a “linear blend”, or “linear interpolation”, or “lerp” for short, between two things. A lerp is always of the form

// blendedValue = (1−𝑡)⋅startValue+𝑡⋅endValue,
color ray_color(const ray& r, const hittable& world, int depth) {
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


int main(int argc, const char * argv[]) {
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 384;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    
    auto viewport_height = 2.0;
       auto viewport_width = aspect_ratio * viewport_height;
       auto focal_length = 1.0;

       auto origin = point3(0, 0, 0);
       auto horizontal = vec3(viewport_width, 0, 0);
       auto vertical = vec3(0, viewport_height, 0);
       auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
    
    hittable_list world;

    world.add(make_shared<sphere>(
        point3(0,0,-1), 0.5, make_shared<lambertian>(color(0.7, 0.3, 0.3))));

    world.add(make_shared<sphere>(
        point3(0,-100.5,-1), 100, make_shared<lambertian>(color(0.8, 0.8, 0.0))));

    world.add(make_shared<sphere>(point3(1,0,-1), 0.5, make_shared<metal>(color(.8,.6,.2))));
    world.add(make_shared<sphere>(point3(-1,0,-1), 0.5, make_shared<metal>(color(.8,.8,.8))));
    
    camera cam;

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    return 0;
}
