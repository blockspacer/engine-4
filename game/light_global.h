#pragma once

#include "light_base.h"

class c_light_global : public base_light {
public:
	DEC_CLASS(light_global, base_light);
	BEGIN_KEYVALUES(c_light_global)
	KEYFIELD(m_vecPos, KV_T_VECTOR3, "position");
	KEYFIELD(m_vecRot, KV_T_VECTOR3, "rotation");
	KEYFIELD(m_colColor, KV_T_RGBA, "color");
	KEYFIELD(m_flAngle, KV_T_FLOAT, "angle");
	END_KEYVALUES()

	void precache();
	void spawn();

	bool is_drawable() override;

	void get_light(gfx::shader_light& l) override;

private:
	float m_flAngle;
};
