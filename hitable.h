//
//  hitable.h
//  RayTracing
//
//  Created by Miguel Lopes on 13/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#pragma once
#include "ray.h"

struct hit_record {
    float t;
    vec3 p;
    vec3 normal;
};

class hitable {
public:
    virtual bool hit(const ray& r,
                     float t_min,
                     float t_max,
                     hit_record& rec) const = 0;
};
