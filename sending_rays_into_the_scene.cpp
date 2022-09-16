#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>
using namespace std;

color ray_color(const ray& r) {
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