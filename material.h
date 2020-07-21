//
//  material.h
//  RayTracing
//
//  Created by Miguel Lopes on 14/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#pragma once
#include <random>
#include <cstdlib>

class material {
public:
    virtual bool scatter(const ray& r_in,
                         const hit_record& rec,
                         vec3& attenuation,
                         ray& scattered) const = 0;
    

    vec3 reflect(const vec3& v, const vec3& n) const {
         return v - 2*dot(v,n)*n;
    }
    

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
        lambertian(const vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const  {
             vec3 target = rec.p + rec.normal + random_in_unit_sphere();
             scattered = ray(rec.p, target-rec.p);
             attenuation = albedo;
             return true;
        }

        vec3 albedo;
};


class metal : public material {
    public:
    metal(const vec3& a, float f) : albedo(a) {
        if(f < 1) fuzz = f;
        else fuzz = 1;
    }
    
        virtual bool scatter(const ray& r_in,
                             const hit_record& rec,
                             vec3& attenuation,
                             ray& scattered) const  {
            vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = ray(rec.p, reflected + fuzz*random_in_unit_sphere());
            attenuation = albedo;
            return (dot(scattered.direction(), rec.normal) > 0);
        }
        vec3 albedo;
        float fuzz;
};