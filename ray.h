//
//  ray.h
//  RayTracing
//
//  Created by Miguel Lopes on 12/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#pragma once
#include "vec3.h"

class ray {
    public:
        ray() {}
        ray(const point3& origin, const vec3& direction)
            : orig(origin), dir(direction)
        {}

        point3 origin() const  { return orig; }
        vec3 direction() const { return dir; }

        point3 at(double t) const {
            return orig + t*dir;
        }

    public:
        point3 orig;
        vec3 dir;
};

