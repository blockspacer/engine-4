set(SRC
	stdafx.cpp
	stdafx.h

	simulation.cpp
	object.cpp

	mesh.cpp
)

set(SRC_PUBLIC
	../public/include/phys/phys.h
	../public/include/phys/simulation.h
	../public/include/phys/object.h

	../public/include/phys/mesh.h
)

vs_pch(stdafx)

set(CMAKE_CXX_STANDARD 17)

add_library(phys STATIC
	${SRC}
	${SRC_PUBLIC}
	CMakeLists.txt
)

IF(WIN32)
# Create filters
source_group("Source Files" FILES ${SRC})
source_group("Public Headers" FILES ${SRC_PUBLIC})
ENDIF()

vs_link_no(phys)
