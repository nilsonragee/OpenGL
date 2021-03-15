#include <fstream>
#include <sstream>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "opengl.h"

//
// --- Global variables ---
//
Camera camera;
Mouse mouse;
Frame_Time frame_time;
Screen screen;
GPU_Info gpu_info;

bool imgui_draw_edit_window = true;
bool imgui_draw_demo_window = false;

//
// --- Callbacks ---
//
void framebuffer_size_callback(GLFWwindow* window, int new_screen_width, int new_screen_height) {
	screen.width = new_screen_width;
	screen.height = new_screen_height;
	screen.aspect_ratio = (float)new_screen_width / (float)new_screen_height;
	glViewport(0, 0, new_screen_width, new_screen_height);
	printf("[%f] - New window size: %dx%d\n", frame_time.current, screen.width, screen.height);
}

void mouse_callback(GLFWwindow* window, double new_mouse_x, double new_mouse_y) {
	float offset_x = new_mouse_x - mouse.x;
	float offset_y = mouse.y - new_mouse_y; // Reversed, since  y-coordinates go from bottom to top.
	mouse.x = new_mouse_x;
	mouse.y = new_mouse_y;

	offset_x *= mouse.sensitivity;
	offset_y *= mouse.sensitivity;

	// In 'Cursor mode' we don't move camera.
	if (!mouse.cursor_mode) {
		camera.yaw += offset_x;
		camera.pitch += offset_y;

		if (camera.pitch > PITCH_MAX_ANGLE)
			camera.pitch = PITCH_MAX_ANGLE;
		if (camera.pitch < -PITCH_MAX_ANGLE)
			camera.pitch = -PITCH_MAX_ANGLE;

		glm::vec3 direction;
		direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
		direction.y = sin(glm::radians(camera.pitch));
		direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

		camera.front = glm::normalize(direction);
	}
}

void scroll_callback(GLFWwindow* window, double offset_x, double offset_y) {
	camera.fov -= (float) offset_y;
	printf("[%f] - Camera FOV: %f\n", frame_time.current, camera.fov);
}

void process_input(GLFWwindow* window) {
	// Temp.
	float camera_speed = 3.0f * frame_time.delta;
	glm::vec3 cross_front_up = glm::cross(camera.front, camera.up);
	glm::vec3 camera_right = glm::normalize(cross_front_up);

	//      if(glfwGetKey(window, GLFW_KEY)) == GLFW_PRESS)
	//  or: if(glfwGetKey(window, GLFW_KEY))
	//
	// NOTE: It doesn't work like GLFW key press callback function
	// where there is additional GLFW_REPEAT and GLFW_PRESS is treated
	// as a single press. Here, GLFW_PRESS updates every frame.
	if (glfwGetKey(window, GLFW_KEY_W)) {
		camera.position += camera.front * camera_speed;
	}

	if (glfwGetKey(window, GLFW_KEY_S)) {
		camera.position -= camera.front * camera_speed;
	}

	if (glfwGetKey(window, GLFW_KEY_A)) {
		camera.position -= camera_right * camera_speed;
	}

	if (glfwGetKey(window, GLFW_KEY_D)) {
		camera.position += camera_right * camera_speed;
	}
}

void single_press_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_GRAVE_ACCENT && action == GLFW_PRESS) {
		imgui_draw_edit_window = !imgui_draw_edit_window;
		printf("[%f] - 'Edit' window mode: %s\n", frame_time.current, (imgui_draw_edit_window) ? "SHOW" : "HIDE");
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		mouse.cursor_mode = !mouse.cursor_mode;

		if (mouse.cursor_mode) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		} else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		printf("[%f] - Cursor mode: %s\n", frame_time.current, (mouse.cursor_mode) ? "ON" : "OFF");
	}
}

void glfw_error_callback(int error_code, const char* description) {
	printf("GLFW ERROR: %s (Error code: %d)\n", description, error_code);
}

int main()
{
	GLFWwindow* window;

	glfwSetErrorCallback(glfw_error_callback);

	if (glfwInit()) {
		printf("GLFW initialized.\n");
	} else {
		printf("ERROR: Failed to initialize GLFW!\n");
		ASSERT(false);
		exit(EXIT_FAILURE);
	}

	// OpenGL 3.3, Core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context.
	// Put  glfwGetPrimaryMonitor()  after the window's name to make it fullscreen.
	// ... "name", glfwGetPrimaryMonitor(), NULL);
	GLFWmonitor* monitor = NULL;
	window = glfwCreateWindow(screen.width, screen.height, "OpenGL", monitor, NULL);
	if (window) {
		printf("GLFW Window created. (%dx%d, %s)\n", screen.width, screen.height, (monitor) ? "Fullscreen" : "Windowed");
	} else {
		printf("ERROR: Failed to open GLFW window!\n");
		ASSERT(false);
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	
	// In the 2nd argument we are telling GLFW
	// the function, that will execute whenever
	// frame buffer changes (when window changes its size)
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	// Callback function for processing single press.
	// Keys which are being listened continuously are
	// in process_input().
	glfwSetKeyCallback(window, single_press_key_callback);

	// Tell GLFW to capture mouse movements and don't draw the cursor.
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, mouse.x, mouse.y);

	// Vertical sync (VSync).
	// How many frames we will skip:
	// 1 - will skip every 2nd frame.
	glfwSwapInterval(1);

	if (glewInit() == GLEW_OK) {
		printf("GLEW initialized.\n");
	} else {
		printf("ERROR: Failed to initialize GLEW!\n");
		ASSERT(false);
		exit(EXIT_FAILURE);
	}

	gpu_info.vendor = (const char*) glGetString(GL_VENDOR);
	gpu_info.renderer = (const char*) glGetString(GL_RENDERER);
	printf("GPU Vendor: %s, GPU Renderer: %s\n", gpu_info.vendor, gpu_info.renderer);

	/* DEMO SCENE START */
	// const int vertices_amount = 4 * (3 + 3);
	// const int indices_amount = 2 * 3;

	float vertices[] = {
		// Position           Normal
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	Shader_Source lighting_shader_source = parse_shader("resources/shaders/lighting.glsl");
	unsigned int lighting_shader = create_shader(lighting_shader_source.vertex_shader, lighting_shader_source.fragment_shader);
	if (lighting_shader) {
		printf("Shader 'lighting' loaded.\n");
	} else {
		printf("Failed to load 'lighting' shader!\n");
	}

	Shader_Source light_object_shader_source = parse_shader("resources/shaders/light_object.glsl");
	unsigned int light_object_shader = create_shader(light_object_shader_source.vertex_shader, light_object_shader_source.fragment_shader);
	if (light_object_shader) {
		printf("Shader 'light_object' loaded.\n");
	} else {
		printf("Failed to load 'light_object' shader!\n");
	}

	unsigned int vertex_buffer_object;
	glGenBuffers(1, &vertex_buffer_object);

	//
	// --- Cube ---
	//
	unsigned int object_vertex_array_object;
	glGenVertexArrays(1, &object_vertex_array_object);
	glBindVertexArray(object_vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//
	// --- Light cube ---
	//
	unsigned light_object_vertex_array_object;
	glGenVertexArrays(1, &light_object_vertex_array_object);
	glBindVertexArray(light_object_vertex_array_object);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);

	//
	// --- Coordinate Systems (3D Rendering) ---
	//
	glm::mat4 lighting_model = glm::mat4(1.0f);
	glm::mat4 light_object_model = glm::mat4(1.0f);

	// glm::vec3 object_position = glm::vec3(0.0f);
	glm::vec3 light_cube_position = glm::vec3(2.0f, 1.5f, -2.0f);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection;

	unsigned int lighting_model_location = glGetUniformLocation(lighting_shader, "model");
	unsigned int lighting_view_location = glGetUniformLocation(lighting_shader, "view");
	unsigned int lighting_projection_location = glGetUniformLocation(lighting_shader, "projection");

	unsigned int light_object_model_location = glGetUniformLocation(light_object_shader, "model");
	unsigned int light_object_view_location = glGetUniformLocation(light_object_shader, "view");
	unsigned int light_object_projection_location = glGetUniformLocation(light_object_shader, "projection");

	// Here we enable 'Z-buffer' to allow us render
	// 3D objects without overwriting already rendered pixels.
	glEnable(GL_DEPTH_TEST);

	//
	// --- Colors ---
	//
	glm::vec3 object_color(1.0f, 0.5f, 0.31f);
	glm::vec3 light_color(1.0f, 1.0f, 1.0f);

	unsigned int view_position_location = glGetUniformLocation(lighting_shader, "view_position");
	unsigned int light_cube_position_location = glGetUniformLocation(lighting_shader, "light_position");
	unsigned int object_light_color_location = glGetUniformLocation(lighting_shader, "light_color");
	unsigned int object_color_location = glGetUniformLocation(lighting_shader, "object_color");

	unsigned int light_cube_color_location = glGetUniformLocation(light_object_shader, "light_color");

	// Move camera.
	camera.position = glm::vec3(3.5f, 2.5f, 4.0f);
	/* DEMO SCENE END */

	//
	// --- ImGui ---
	//
	IMGUI_CHECKVERSION();
	auto imgui_context = ImGui::CreateContext();
	if (imgui_context) {
		printf("ImGui context created.\n");
	} else {
		printf("Failed to create ImGui context!\n");
	}
	ImGuiIO &imgui_io = ImGui::GetIO();

	// Disable windows state saving for now.
	imgui_io.IniFilename = NULL;
	imgui_io.WantSaveIniSettings = false;
	
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	// Temp.
	const char* glsl_version = "#version 330";
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImGui::SetCurrentContext(imgui_context);

	glm::vec4 clear_color = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		frame_time.current = glfwGetTime();
		frame_time.delta = frame_time.current - frame_time.last;
		frame_time.last = frame_time.current;

		glClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		process_input(window);

		light_cube_position.x = sin(glfwGetTime()) * 2.0f;
		light_cube_position.y = 0.0f;
		light_cube_position.z = cos(glfwGetTime()) * 2.0f;

		// light_object_model = glm::translate(light_object_model, light_cube_position);

		projection = glm::perspective(glm::radians(camera.fov), screen.aspect_ratio, NEAR_CLIP_PLANE_DISTANCE, FAR_CLIP_PLANE_DISTANCE);
		view = glm::lookAt(camera.position, camera.position + camera.front, camera.up);

		/* DEMO SCENE RENDER */
		// --- Lighting ---
		// Cube
		glUseProgram(lighting_shader);
		glUniform3fv(view_position_location, 1, &camera.position[0]);
		glUniform3fv(light_cube_position_location, 1, &light_cube_position[0]);
		glUniform3fv(object_light_color_location, 1, &light_color[0]);
		glUniform3fv(object_color_location, 1, &object_color[0]);
		glUniformMatrix4fv(lighting_projection_location, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(lighting_view_location, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(lighting_model_location, 1, GL_FALSE, &lighting_model[0][0]);

		glBindVertexArray(object_vertex_array_object);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Light cube
		light_object_model = glm::mat4(1.0f);
		light_object_model = glm::translate(light_object_model, light_cube_position);
		light_object_model = glm::scale(light_object_model, glm::vec3(0.2f));

		glUseProgram(light_object_shader);
		glUniform3fv(light_cube_color_location, 1, &light_color[0]);
		glUniformMatrix4fv(light_object_projection_location, 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(light_object_view_location, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(light_object_model_location, 1, GL_FALSE, &light_object_model[0][0]);

		glBindVertexArray(light_object_vertex_array_object);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		/* DEMO SCENE RENDER */

		// 
		// --- ImGui Render ---
		//
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (imgui_draw_demo_window) {
			ImGui::ShowDemoWindow(&imgui_draw_demo_window);
		}

		if (imgui_draw_edit_window) {
			ImGui::Begin("Edit");
			ImGui::Checkbox("Demo Window", &imgui_draw_demo_window);
			ImGui::ColorEdit3("Clear color", &clear_color[0]);
			ImGui::ColorEdit3("Cube color", &object_color[0]);
			ImGui::ColorEdit3("Light cube color", &light_color[0]);
			ImGui::InputFloat3("Camera XYZ", &camera.position[0]);
			ImGui::InputFloat3("Light cube XYZ", &light_cube_position[0]);
			ImGui::Text("GPU Vendor: %s", gpu_info.vendor);
			ImGui::Text("GPU Renderer: %s", gpu_info.renderer);
			ImGui::Text("Frametime: %.3f ms/frame (%.1f FPS)", 1000.0f / imgui_io.Framerate, imgui_io.Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
		glFlush();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteProgram(lighting_shader);
	glDeleteProgram(light_object_shader);
	glDeleteVertexArrays(1, &object_vertex_array_object);
	glDeleteVertexArrays(1, &light_object_vertex_array_object);

	glfwTerminate();

	exit(EXIT_SUCCESS);
} 