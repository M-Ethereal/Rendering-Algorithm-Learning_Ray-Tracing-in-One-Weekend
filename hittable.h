#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hit_record {
  point3 p;
  vec3 normal;
  double t;
  //add a new contribute to record where the normal towards
  bool front_face;

  //we want the normal always point against the ray
  inline void set_face_normal(const ray& r, const vec3& outward_normal) {
    front_face = dot(r.direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class hittable {
  public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif