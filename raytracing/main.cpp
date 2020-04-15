#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
using namespace std;
ofstream fout(R"(..\file.ppm)");

vec3 center1(0, 0, -1);
vec3 center2(0, -100.5, -1);
vec3 center3(1, 0, -1);
vec3 center4(-1, 0, -1);
float radius1 = 0.5;
float radius2 = 100.0;
float radius3 = 0.5;
float radius4 = 0.5;
float t_min = 0.0001; //t_min>0.0用来排除ray和自己相交这种情况
float t_max = 100.0;
int Samples = 4;
float bounding_rate = 0.5;

//vec3 random_direction_in_unit_sphere() {
//	vec3 direction;
//	do {
//		direction = 2.0 * vec3(uniform(e), uniform(e), uniform(e)) - vec3(1.0, 1.0, 1.0);
//	} while (direction.squared_length() >= 1.0);
//	return direction;
//}

vec3 Color(const ray& r, const hitable& world, int depth) {
	hit_record rec;
	bool hitable = world.hit(r, t_min, t_max, rec);
	if (hitable) {
		//rec.point + rec.normal表示新单位圆的圆心，所以这里的noraml法线应该是归一化的
		//表示在圆心基础上进行了direction方位的偏移
		ray scattered;
		vec3 atten;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, atten, scattered)) {
			return atten * Color(scattered, world, depth + 1);
		}
		else {
			return vec3(0.0, 0.0, 0.0);
		}
	}
	vec3 unit_direction = unit_vector(r.direction());
	assert(unit_direction.y() <= 1 && unit_direction.y() >= -1);
	float height = unit_direction.y() * 0.5 + 0.5;
	vec3 white(1.0, 1.0, 1.0);
	vec3 blue(0.5, 0.7, 1.0);
	return (1.0 - height)* white + height * blue;
}

int main() {
	int nx = 800;
	int ny = 400;
	camera cam;
	hitable* sph1 = new sphere(center1, radius1, new lambertian(vec3(0.8,0.3,0.3)));
	hitable* sph2 = new sphere(center2, radius2, new lambertian(vec3(0.8, 0.8, 0.0)));
	hitable* sph3 = new sphere(center3, radius3, new metal(vec3(0.8, 0.6, 0.2), 0.3));
	hitable* sph4 = new sphere(center4, radius4, new dielectric(4.5));
	hitable* sph5 = new sphere(center4, -radius4+0.05, new dielectric(4.5));
	hitable* objects[5];
	objects[0] = sph1;
	objects[1] = sph2;
	objects[2] = sph3;
	objects[3] = sph4;
	objects[4] = sph5;
	hitable_list world(objects, 5);

	fout << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; --j) {
		for (int i = 0; i < nx; ++i) {
			vec3 color(0.0, 0.0, 0.0);
			for (int k = 0; k < Samples; ++k) {
				float u = float((i + uniform(e)) / float(nx));
				float v = float((j + uniform(e)) / float(ny));
				ray r = cam.get_ray(u,v);
				color += Color(r, world, 0);
			}
			color /= float(Samples);
			//gamma
			int ir = int(255 * sqrt(color[0]));
			int ig = int(255 * sqrt(color[1]));
			int ib = int(255 * sqrt(color[2]));
			fout << ir << " " << ig << " " << ib << "\n";
		}
	}
	return 0;
}







