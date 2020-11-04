cmake_minimum_required(VERSION 3.11)
project (OpenGLFramework)

set (CMAKE_CXX_STANDARD 11)
option(USE_CURRENT_PATH "Enable Current Path" ON)
if(USE_CURRENT_PATH)
	set(CURRENT_PATH "${CMAKE_SOURCE_DIR}")
endif()
configure_file(config.h.ini ${CMAKE_SOURCE_DIR}/src/config.h)

find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
#find_package(PkgConfig CONFIG REQUIRED)
find_package(PNG REQUIRED)


message("${CMAKE_MODULE_PATH}")
message("${PNG_LIBRARIES}")

#pkg_check_modules(PNG REQUIRED libpng)
set(EXEC main)



add_executable(${EXEC}
	./src/main.cpp
	./src/Shader.cpp
	./src/Shader.h
##	./src/Camera.h
##	./src/Camera.cpp
	./src/Mesh.h
	./src/Mesh.cpp
	./deps/glad/src/glad.c
	./assets/shaders/vertex.glsl
	./assets/shaders/fragment.glsl
	)

#set(GLFW3_INCLUDE_DIRS ./deps/glfw/include)

target_include_directories(${EXEC}
#	PUBLIC ${GLFW3_INCLUDE_DIRS}
	PUBLIC ./deps/glad/include
    PUBLIC ${ASSIMP_INCLUDE_DIRS}
#	PUBLIC ./deps/assimp/x64/include
#	PUBLIC ./deps/glm
)

target_link_libraries(${EXEC}
	PRIVATE glfw
	PRIVATE glm::glm
    PRIVATE "${ASSIMP_LIBRARY_DIRS}/${ASSIMP_LIBRARIES}"
    #    PRIVATE PNG::PNG
    )

message ("${ASSIMP_LIBRARIES}")
message("${GLM_INCLUDE_DIRS}")
message("${glm_FOUND}")

target_link_libraries(${EXEC} PRIVATE ${ASSIMP_LIBRARY})
