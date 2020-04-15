#pragma once
#include "hitable.h"

class sphere : public hitable {
public:
	sphere() {}
	sphere(vec3 cen, float r, material* mat) :center(cen), radius(r), mat_ptr(mat) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

	vec3 center;
	float radius;
	material* mat_ptr;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(r.direction(), oc);
	float c = dot(oc, oc) - radius * radius;
	float dis = b * b - 4 * a * c;
	if (dis > 0) {
		float temp = (-b - sqrt(dis)) / (2.0 * a);
		if (temp >= t_min && temp <= t_max) {
			rec.t = temp;
			rec.point = r.point_at_parameter(temp);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			//rec.normal = rec.point - center;
			//rec.normal /= radius;
			return true;
		}
		temp = (-b + sqrt(dis)) / (2.0 * a);
		if (temp >= t_min && temp <= t_max) {
			rec.t = temp;
			rec.point = r.point_at_parameter(temp);
			rec.normal = (rec.point - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}
