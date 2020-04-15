#pragma once
#include "hitable.h"

class hitable_list : public hitable{
public:
	hitable_list() {}
	hitable_list(hitable** l, int n):list(l), list_size(n) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

	hitable** list;
	int list_size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	float cloest = t_max;
	hit_record temp_rec;
	bool IsHit = false;
	for (int n = 0; n < list_size; ++n) {
		if (list[n]->hit(r, t_min, cloest, temp_rec)) {
			cloest = temp_rec.t;
			rec = temp_rec;
			IsHit = true;
		}
	}
	return IsHit;
}

