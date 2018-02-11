#pragma once

#include <vector>

// a model parsed from a SMD file

struct model_bone {
	char szName[SMD_MAX_BONE_NAME_SIZ];
	int iID;
	int iParentID;
};

struct model_bone_state {
	float px, py, pz;
	float rx, ry, rz;
};

struct model_triangle_vertex {
	int iBoneID;
	float px, py, pz;
	float nx, ny, nz;
	float u, v;
};

struct model_triangle {
	size_t iModelMaterial;
	// CLOCKWISE!
	std::vector<model_triangle_vertex> vertices;
};

struct model_material {
	long long int iModelMaterial;
	char szName[SMD_MAX_MATERIAL_PATH_SIZ];
};

struct model_keyframe {
	int iFrame;
	std::pair<int, model_bone_state> bones;
};

struct model {
	std::vector<model_bone> bones;
	std::vector<model_keyframe> animation;
	std::vector<model_material> materials;
	std::vector<model_triangle> triangles;

	long long int iLastMatID = -1;
};