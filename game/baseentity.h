#pragma once

#include "basethinker.h"
#include "vector.h"

#define DEC_CLASS(classname, basename) \
	typedef basename BaseClass; \
	virtual const char* get_classname() { return #classname; }
#define REGISTER_ENTITY(classname, mapname) static entity_factory<classname> mapname(#mapname);

class base_entity : public base_thinker
{
public:
	~base_entity() {}
	virtual void precache() = 0;
	virtual void spawn();
	virtual bool is_drawable() {
		return false;
	}

	virtual const char* get_classname() = 0;

	// Returns with the absolute position of the entity.
	//
	// NOTE: The absolute position of the entity's parent (if it has any)
	// will be accounted for.
	virtual vec3 get_abspos() const;

	// Returns with the relative position of the entity.
	//
	// NOTE: If it has no parent, this is the absolute position too.
	virtual vec3 get_relpos() const;

	// Sets the absolute position
	//
	// NOTE: If the entity has a parent, this has no effect
	virtual void set_abspos(const vec3& v);

	// Sets the relative position
	//
	// NOTE: If the entity has no parent, this sets the absolute position.
	virtual void set_relpos(const vec3& v);

	// Sets the parent of the entity.
	// NOTE: When pEnt is NULL or nullptr, the entity will be detached
	// from the parent.
	virtual void set_parent(base_entity* pEnt);

	// Returns a pointer to the parent
	virtual base_entity* get_parent() {
		return m_pParent;
	}

	virtual void set_rotation(const vec3& v);

	// Returns the absolute rotation matrix of the entity
	virtual glm::mat4 get_rotation_matrix() const;
	// Returns the relative rotation of the entity.
	virtual vec3 get_relrot() const {
		return m_vecRot;
	}

	virtual float get_scale() const {
		return 1;
	}

protected:
	// This is the absolute pos if this ent has no parent
	// Otherwise this is relative
	vec3 m_vecPos;

	// X Y Z Euler
	// Converted to glm::mat4 before generating transform matrix
	vec3 m_vecRot;

	base_entity* m_pParent = NULL;
	//CPhysObj* m_pPhysObj = NULL;

	size_t m_iModelID;

	bool m_bSpawned = false;

private:
	friend class entsys;
};

typedef void(base_entity::*thinkfunc)();

base_entity* CreateEntity(const char* mapname);
base_entity* CreateEntityNoSpawn(const char* mapname);
#define CREATE_ENTITY(mapname) CreateEntity(mapname)
#define CREATE_ENTITY_NOSPAWN(mapname) CreateEntityNoSpawn(mapname)
#define KILL_ENTITY(ent) gpGlobals->pEntSys->kill_entity(ent)

//#include "keyvalues2.h"
