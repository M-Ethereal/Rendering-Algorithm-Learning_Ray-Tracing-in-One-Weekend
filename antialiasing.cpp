#include "common_utilities.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

#include <iostream>
using namespace std;

// update the color function using hittable list
color ray_color(const ray& r, const hittable& world) {
  hit_record rec;
  if (world.hit(r, 0, infinity, rec)) {
    return 0.5 * (rec.normal + color(1,1,1));
  }
  //creat a blue scene
  vec3 unit_direction = unit_vector(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0); //lerp: blendedValue = (1-t)*startValue + t*endValue
}

int main(){
  //image info
  const auto aspect_ratio = 16.0 / 9.0;
  const int image_width = 400;
  const int image_height = static_cast<int>(image_width / aspect_ratio);
  const int samples_per_pixel = 100;

  // World
  hittable_list world;
  world.add(make_shared<sphere>(point3(0,0,-1),0.5));
  world.add(make_shared<sphere>(point3(0,-100.5,-1), 100)); // the earth

  //camera
  // auto viewport_height = 2.0;
  // auto viewport_width = aspect_ratio * viewport_height;
  // auto focal_length = 1.0;

  // auto origin = point3(0, 0, 0);
  // auto horizontal = vec3(viewport_width, 0, 0);
  // auto vertical = vec3(0, viewport_height, 0);
  // auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);
  camera cam;

  //render

  //To creat a ppm file, the info below is necessary
  cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = image_height; j > 0; --j){
    cerr << "\rScanlines remaining:" << j << ' ' << flush;
    for (int i = 0; i < image_width; ++i){
      // auto u = float(i) / (image_width);
      // auto v = float(j) / (image_height);
      // ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
      // color pixel_color = ray_color(r, world);
      // write_color(cout, pixel_color);
      color pixel_color(0, 0, 0);
      for (int s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width);
        auto v = (j + random_double()) / (image_height);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world);
      }
      write_color(cout, pixel_color, samples_per_pixel);
    }
  }
  cerr << "\nDone!\n";
}