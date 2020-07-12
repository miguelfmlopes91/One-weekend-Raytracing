//
//  main.cpp
//  RayTracing
//
//  Created by Miguel Lopes on 11/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#include <iostream>
#include "ray.h"


bool hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant > 0); //formula resolvente de func quadrática
}

///returns color of the background, simple gradient
///linear blend / lerp / linear interpolation
///A lerp is always of the form:
///blended_value = (1-t)*start_value + t*end_value, with tgoing from zero to one.
vec3 color(const ray& r) {
    
    //test
    if (hit_sphere(vec3(0,0,1), 0.5, r)) {
        return vec3(1, 0, 0);
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y() + 1.0);
    
    //p(t) = A + t*B
    ///Here p​ is a 3D position along a line in 3D.
    ///A​ is the ray origin and B​ is the ray direction.
    ///The ray parameter t is a real number.
    
    return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}



int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    std::cout<< "P3\n" << nx << " " << ny << "\n255\n";
    
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            
            ray r(origin,
                  lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            
            std::cout<< ir << " "<< ig << " " << ib << std::endl;;
        }
    }
    
    
    return 0;
}
