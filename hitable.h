//
//  hitable.h
//  RayTracing
//
//  Created by Miguel Lopes on 13/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#pragma once
#include "ray.h"

class material;

struct hit_record {
    double t;
    vec3 p; // probability
    vec3 normal;
    shared_ptr<material> mat_ptr;//how rays interact with the surface
    bool front_face;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;

};
