cmake_minimum_required(VERSION 3.11)
project (OpenGLFramework)



option(USE_CURRENT_PATH "Enable Current Path" ON)
if(USE_CURRENT_PATH)
	set(CURRENT_PATH "${CMAKE_SOURCE_DIR}")
endif()
configure_file(config.h.ini ${CMAKE_SOURCE_DIR}/src/config.h)


if(NOT CMAKE_CL_64)	
	find_package(glfw3 3.3 REQUIRED PATHS ./deps/glfw/x86/lib/cmake/glfw3)
else()
	find_package(glfw3 3.3 REQUIRED PATHS ./deps/glfw/x64/lib/cmake/glfw3)
endif()


if (NOT ${glfw3_FOUND})
	message(FATAL_ERROR "glfw3 not found!")
endif (NOT ${glfw3_FOUND})

message(STATUS "glfw3_FOUND is ${glfw3_FOUND}")

message(STATUS "${GLFW3_LIBRARIES}")
set(EXEC main)


add_executable(${EXEC} 
	./src/main.cpp
	./src/Shader.cpp
	./src/Shader.h
	./deps/glad/src/glad.c
	./assets/shaders/vertex.glsl
	./assets/shaders/fragment.glsl	
	)

set(GLFW3_INCLUDE_DIRS ./deps/glfw/include)

target_include_directories(${EXEC}
	PUBLIC ${GLFW3_INCLUDE_DIRS}
	PUBLIC ./deps/glad/include	
)
target_link_libraries(${EXEC} 
	glfw)
