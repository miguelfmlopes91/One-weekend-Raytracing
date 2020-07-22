//
//  material.h
//  RayTracing
//
//  Created by Miguel Lopes on 14/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#pragma once
#include "constants.h"
#include <random>
#include <cstdlib>

class material {
    public:
        virtual bool scatter(const ray& r_in,
                             const hit_record& rec,
                             color& attenuation,
                             ray& scattered
                                                ) const = 0;
};

//vec3 random_in_unit_sphere() {
//    vec3 p;
//    do {
//        p = 2.0*vec3(random_double(),random_double(),random_double()) - vec3(1,1,1);
//    } while (p.squared_length() >= 1.0);
//    return p;
//}


class lambertian : public material {
    public:
        lambertian(const color& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const {
            vec3 scatter_direction = rec.normal + random_unit_vector();
            scattered = ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    public:
        color albedo;
};


class metal : public material {
    public:
        metal(const color& a) : albedo(a) {}

        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected);
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    public:
        color albedo;
};
