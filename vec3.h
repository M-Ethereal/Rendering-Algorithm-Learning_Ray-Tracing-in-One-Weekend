#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  public:
    float e[3];
  public:
    // constructor
    vec3() {} // ???how can I init this with default {0,0,0}???
    
    vec3(float e0, float e1, float e2) { 
      e[0] = e0; e[1] = e1; e[2] = e2; 
    }

    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    float operator[](int i) const { return e[i]; }
    float& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v) {
      e[0] += v.e[0];
      e[1] += v.e[1];
      e[2] += v.e[2];
      return *this;
    }

    vec3& operator*=(const float t) {
      e[0] *= t;
      e[1] *= t;
      e[2] *= t;
    }

    vec3& operator/=(const float t) {
      return *this *= 1/t;
    }

    float length_squared() const {
      return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    float length() const {
      return sqrt(length_squared());
    }
};

// Type aliases for vec3
using point3 = vec3; // 3D point
using color = vec3; // RGB color


// vec3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}

inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

inline static vec3 random_vec3() {
  return vec3(random_double(), random_double(), random_double());
}

inline static vec3 random_vec3_min_max(double min, double max) {
  return vec3(random_double(min,max), random_double(min,max), random_double(min,max));
}

vec3 random_in_unit_sphere() {
    while (true) {
      auto p = random_vec3_min_max(-1,1);
      if (p.length_squared() >= 1) continue;
      return p;
    }
}

#endif