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
    ray(const vec3& a, const vec3& b){ A = a; B = b;}
    vec3 origin() const { return A;}
    vec3 direction() const { return B;}
    vec3 point_at_parameter(float t) const {return A + t*B;}
    
    
    vec3 A;
    vec3 B;
};
