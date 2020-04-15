#pragma once

#include "hitable.h"
#include "material.h"

class metal :public material {
public:
	metal(const vec3& a, float f) :albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& atten, ray& scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.point, reflected + fuzz * random_direction_in_unit_sphere());
		atten = albedo;
		return (dot(scattered.direction(), rec.normal) >= 0);
	}
	vec3 albedo;
	float fuzz;
};

