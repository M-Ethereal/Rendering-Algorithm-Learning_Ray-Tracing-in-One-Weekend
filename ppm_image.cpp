#include "color.h"
#include "vec3.h"

#include <iostream>
using namespace std;

int main(){
  //define the height and the width of the image
  int height = 256;
  int width = 256;

  //render

  //To creat a ppm file, the info below is necessary
  cout << "P3\n" << width << ' ' << height << "\n255\n";

  for (int j = height; j > 0; --j){
    cerr << "\rScanlines remaining:" << j << ' ' << flush;
    for (int i = 0; i < width; ++i){
      // auto r = float(i) / width;
      // auto g = float(j) / height;
      // auto b = 0.25;
      color pixel_color(float(i) / width, float(j) / height, 0.25);

      // int ir = static_cast<int> (256 * r);
      // int ig = static_cast<int> (256 * g);
      // int ib = static_cast<int> (256 * b);
      // cout << ir << ' ' << ig << ' ' << ib << '\n';
      write_color(cout, pixel_color);
    }
  }
  cerr << "done!";
}