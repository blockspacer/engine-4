cmake_minimum_required(VERSION 3.2.3)

vs_pch(stdafx)

# Add source files here

set(SRC_CORE
	stdafx.cpp
	stdafx.h
	
	main.cpp
)

set(SRC_PUBLIC
	../public/include/iserver.h
	../public/include/dl.h
)

add_executable(engineds
	${SRC_CORE}
	${SRC_PUBLIC}
	CMakeLists.txt
)
builddir(engineds)
vs_link_static(engineds)

IF(UNIX AND NOT APPLE)
target_link_libraries(engineds dl pthread ifsys)
ELSE()
target_link_libraries(engineds ifsys)
ENDIF()
install(TARGETS engineds DESTINATION bin/../)

IF(WIN32)
# Create filters
source_group("Source Files" FILES ${SRC_GAME})
source_group("Public Header Files" FILES ${SRC_PUBLIC})
ENDIF()

add_dependencies(engineds server_dll)
