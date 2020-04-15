#pragma once
#include <random>
#include "hitable.h"
#include "material.h"

class lambertian:public material{
public:
	lambertian(const vec3& a) :albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& atten, ray& scattered) const {
		vec3 target = rec.point + rec.normal + random_direction_in_unit_sphere();
		scattered = ray(rec.point, target - rec.point);
		atten = albedo;
		return true;
	}

	vec3 albedo;
};
