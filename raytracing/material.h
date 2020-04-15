#pragma once
#include "hitable.h"

std::default_random_engine e;
std::uniform_real_distribution<double> uniform(0, 1);

class material {
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& atten, ray& scattered) const = 0;
	vec3 random_direction_in_unit_sphere() const {
		vec3 direction;
		do {
			direction = 2.0 * vec3(uniform(e), uniform(e), uniform(e)) - vec3(1.0, 1.0, 1.0);
		} while (direction.squared_length() >= 1.0);
		return direction;
	}
	vec3 reflect(const vec3& v, const vec3& n) const {
		return v - 2 * dot(n, v) * n;
	}
};