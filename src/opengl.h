#pragma once

#include <iostream>
#include <string>

#define GLEW_STATIC
#include "../libs/GLEW/glew.h"
#include "../libs/GLFW/glfw3.h"
#include "../libs/GLM/glm.hpp"
#include "../libs/GLM/gtc/matrix_transform.hpp"

// __debugbreak is for internal use in MSVC
// and may not work in other environments.
#define ASSERT(x) if (!(x)) __debugbreak();

#ifdef HANDLE_GL_ERRORS
#define GL_CALL(x) gl_clear_error();            \
    x;                                          \
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))
#else 
#define GL_CALL(x) x
#endif

struct Shader {
	unsigned int id;
	const char* vertex_shader;
	const char* fragment_shader;
};

struct Camera {
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float pitch = 0.0f;
	float yaw = -90.0f;
	float fov = 45.0f;
};

struct Mouse {
	float x = 0;
	float y = 0;
	float sensitivity = 0.1f;
	bool cursor_mode = false;
};

struct Frame_Time {
	float last = 0.0f;
	float current = 0.0f;
	float delta = 0.0f;
};

struct Screen {
	int width = 1280;
	int height = 720;
	float aspect_ratio = (float)width / (float)height;
};

struct Shader_Source {
	std::string vertex_shader;
	std::string fragment_shader;
};

struct Vertex_Buffer {
	unsigned int id;
	unsigned int size;
	const void* data;
};

struct Index_Buffer {
	unsigned int id;
	unsigned int amount;
	const unsigned int* data;
};

struct GPU_Info {
	const char* vendor;
	const char* renderer;
};

const float NEAR_CLIP_PLANE_DISTANCE = 0.01f;
const float FAR_CLIP_PLANE_DISTANCE = 200.0f;
const float PITCH_MAX_ANGLE = 89.0f;

//
// --- Shaders ---
//
Shader_Source parse_shader(const std::string& file_path);
unsigned int compile_shader(unsigned int type, const std::string& source);
unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);

//
// --- Callbacks ---
//
void framebuffer_size_callback(GLFWwindow* window, int new_screen_width, int new_screen_height);
void mouse_callback(GLFWwindow* window, double new_mouse_x, double new_mouse_y);
void scroll_callback(GLFWwindow* window, double offset_x, double offset_y);
void process_input(GLFWwindow* window);

//
// --- OpenGL Error handling ---
//
void gl_clear_error();
bool gl_log_call(const char* function, const char* file, int line);