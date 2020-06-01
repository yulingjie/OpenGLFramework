cmake_minimum_required(VERSION 3.11)
project (OpenGLFramework)



find_package(glfw3 3.3 REQUIRED PATHS ./deps/glfw/lib/cmake/glfw3)

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
	)

set(GLFW3_INCLUDE_DIRS ./deps/glfw/include)

target_include_directories(${EXEC}
	PUBLIC ${GLFW3_INCLUDE_DIRS}
	PUBLIC ./deps/glad/include	
)
target_link_libraries(${EXEC} 
	glfw)
