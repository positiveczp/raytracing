#pragma once
#include "material.h"

class dielectric : public material {
public:
	dielectric(float ri) : ref_idx(ri) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& atten, ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		float reflect_prob;
		float cosine;
		atten = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		if (dot(r_in.direction(), rec.normal) > 0) {
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
			reflect_prob = schlick(cosine, ref_idx);
		}
		else {
			scattered = ray(rec.point, reflected);
			reflect_prob = 1.0;
		}
		if (uniform(e) < reflect_prob) {
			scattered = ray(rec.point, reflected);
		}
		else {
			scattered = ray(rec.point,refracted);
		}
		return true;
	}
	bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) const {
		vec3 uv = unit_vector(v);
		float dt = dot(uv, n);
		float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
		if (discriminant > 0) {
			refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
			return true;
		}
		else
			return false;
	}
	float schlick(float cosine, float ref_idx) const {
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
	float ref_idx;
};



