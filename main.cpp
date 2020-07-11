//
//  main.cpp
//  RayTracing
//
//  Created by Miguel Lopes on 11/07/2020.
//  Copyright © 2020 Miguel Lopes. All rights reserved.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    
    int nx = 200;
    int ny = 100;
    std::cout<< "P3\n" << nx << " " << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2;
            
            int ir = int(255.99*r);
            int ig = int(255.99*g);
            int ib = int(255.99*b);
            
            std::cout<< ir << " "<< ig << " " << ib << std::endl;;
        }
    }
    
    
    return 0;
}
