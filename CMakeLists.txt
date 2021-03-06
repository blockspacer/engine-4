cmake_minimum_required(VERSION 2.8.11)
project(engine)

macro(builddir target)
#set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/_build/bin")
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/_build/")
set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/_build/")
#set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/_build/bin")
set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug/_build/bin/")
set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release/_build/bin/")
endmacro(builddir)

#include_directories(common)

# precompiled header for visual studio
macro(vs_pch pchbase)
	if(MSVC)
#		set_source_files_properties(${SRC}
#									PROPERTIES COMPILE_FLAGS "/Yu\"${pchbase}.h\" /Fp\"${pchbase}.pch\""
#									OBJECT_DEPENDS "${pchbase}.pch")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Yu\"${pchbase}.h\"")
		set_source_files_properties(${pchbase}.cpp
									PROPERTIES COMPILE_FLAGS "/Yc\"${pchbase}.h\""
									OBJECT_CREATES "${pchbase}.pch")
	endif(MSVC)
endmacro(vs_pch)

# include foreign source file
macro(src_frgn path)
	list(APPEND SRC ${CMAKE_SOURCE_DIR}/${path})
	if(MSVC)
		set_source_files_properties(${CMAKE_SOURCE_DIR}/${path}
									PROPERTIES COMPILE_FLAGS "/Y-")
	endif(MSVC)
endmacro(src_frgn)

macro(vs_link_static target)
	if(MSVC)
		set_target_properties(${target} PROPERTIES CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
		set_target_properties(${target} PROPERTIES CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MT")
	endif(MSVC)
endmacro()

macro(vs_link_no target)
	if(MSVC)
		set_target_properties(${target} PROPERTIES CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /NODEFAULTLIB :msvcrt")
		set_target_properties(${target} PROPERTIES CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /NODEFAULTLIB :msvcrt")
	endif(MSVC)
endmacro()

if(MSVC)
	set(CMAKE_CXX_FLAGS_DEBUG
	  "/DWIN32 /D_WINDOWS /DDEBUG /EHsc /wd4355 /wd4251 /wd4250 /wd4996 /MP /permissive- /Zi"
	  CACHE STRING "Debug compiler flags" FORCE
	)
	set(CMAKE_CXX_FLAGS
	  "/DWIN32 /D_WINDOWS /EHsc /wd4355 /wd4251 /wd4250 /wd4996 /MP /permissive-"
	  CACHE STRING "Release compiler flags" FORCE
	)
endif(MSVC)
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -msse3 -mfpmath=sse")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -msse3 -mfpmath=sse")
endif()

# include libenl for all projects
include_directories(${CMAKE_SOURCE_DIR}/libenl/include/)
# include externals
link_directories(${CMAKE_SOURCE_DIR}/public/lib/)
include_directories(${CMAKE_SOURCE_DIR}/public/include/)

IF(WIN32)
include_directories(${CMAKE_SOURCE_DIR}/public/include/win32/)
ENDIF()

include_directories(/usr/include/directfb/)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/build/" CACHE STRING "Deploy dir" FORCE)
set (CMAKE_CXX_STANDARD 17)
IF(CMAKE_BUILD_TYPE MATCHES "Debug")
add_definitions(-DDEBUG)
ENDIF()

IF(UNIX AND NOT APPLE)
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
ENDIF()
SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

#add_subdirectory(smd_parser)
add_subdirectory(phys)
add_subdirectory(mathlib)
add_subdirectory(graphics)
add_subdirectory(imgui)
add_subdirectory(libenl)
add_subdirectory(mdlc)
IF(WIN32)
add_subdirectory(logger)
ENDIF()
add_subdirectory(phys_testbed)
add_subdirectory(mdlviewer)
add_subdirectory(matedit)
add_subdirectory(networking)
add_subdirectory(server_dll)
add_subdirectory(client_dll)
add_subdirectory(launcher)
add_subdirectory(engineds)
add_subdirectory(elf)
add_subdirectory(ifsys)
add_subdirectory(elf_test)
add_subdirectory(deferred_test)
add_subdirectory(etfedit)
add_subdirectory(platlayer)
add_subdirectory(efs)
