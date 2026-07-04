#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>
#include <vector>
#include <atomic>


// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double() {
    // Returns a random real in [0,1).
    // thread_local: each thread gets its own generator, so parallel rendering
    // is race-free (std::rand() is not thread-safe). mt19937 is also higher
    // quality than rand().
    static thread_local std::mt19937 generator(std::random_device{}());
    static thread_local std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

// Common Headers

#include "color.cpp"
#include "ray.cpp"
#include "vec3.cpp"
#include "interval.cpp"

#endif
