#pragma once

#include <phys/object.h>
#include <vector>

namespace phys {
	class simulation {
	public:
		size_t add_object(const phys::object& obj);
		void simulate(float delta);

		phys::object& get_object(size_t iIndex);
		size_t size() const { return m_objects.size(); }
	private:
		std::vector<phys::object> m_objects;

		phys::object m_empty;
	};
}
