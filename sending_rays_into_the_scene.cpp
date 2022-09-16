#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
using namespace std;

//Add a sphere!
//Test whether there is an intersection
//C(Cx,Cy,Cz) is the sphere center
//Suppose there is a point P(x,y,z)=A+tb
//When (P(t)-C)(P(t)-C)=r^2 has at least one root
//the ray hit the sphere
//Find the solution of t^2*b*b + 2tb(A-C) + (A-C)(A-C) - r^2 = 0
bool hit_sphere(const point3& center, float radius, const ray& r){
  vec3 P_A = r.origin() - center;
  auto a = dot(r.direction(), r.direction());
  auto b = 2.0 * dot(P_A, r.direction());
  auto c = dot(P_A, P_A) - radius*radius;
  auto discriminant = b*b - 4*a*c;
  return (discriminant > 0);
}

color ray_color(const ray& r) {
  //Place a sphere at(0,0,-1) and test it!
  if (hit_sphere(point3(0,0,-1), 0.5, r)) {
    return color(0.7, 0.2, 0.4);
  }
  //t from 0 to 1 == height from bottom to top == color from white to blue
  vec3 unit_direction = unit_vector(r.direction()); //normalizing the vector
  auto t = 0.5 * (unit_direction.y() + 1.0); //-1 < y < 1, make 0 < t < 1
  return (1.0-t)*color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); //lerp: blendedValue = (1-t)*startValue + t*endValue
}

int main(){
  //image info
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);

  //camera
  auto viewport_height = 2.0;
  auto viewport_width = aspect_ratio * viewport_height;
  auto focal_length = 1.0;

  auto origin = point3(0, 0, 0);
  auto horizontal = vec3(viewport_width, 0, 0);
  auto vertical = vec3(0, viewport_height, 0);
  auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

  //render

  //To creat a ppm file, the info below is necessary
  cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height; j > 0; --j){
    cerr << "\rScanlines remaining:" << j << ' ' << flush;
    for (int i = 0; i < image_width; ++i){
      auto u = float(i) / (image_width);
      auto v = float(j) / (image_height);
      ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
      color pixel_color = ray_color(r);
      write_color(cout, pixel_color);
    }
  }
  cerr << "done!";
}