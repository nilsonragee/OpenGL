#include <fstream>
#include <sstream>

#include "opengl.h"

//
// --- Shaders ---
//
Shader_Source parse_shader(const std::string& file_path) {
    Shader_Source result;
    std::ifstream stream(file_path);    // File stream
    std::string line;                   // Reading line
    std::stringstream string_stream[2]; // String streams
    int shader_id = -1;                 // Shader to write (0 = vertex, 1 = fragment)
    auto not_found = std::string::npos;
    while (getline(stream, line)) {
        if (line.find("#shader") != not_found) {
            if (line.find("vertex") != not_found) {
                shader_id = 0;
            }
            else if (line.find("fragment") != not_found) {
                shader_id = 1;
            }
        }
        else string_stream[shader_id] << line << "\n";
    }
    result.vertex_shader = string_stream[0].str();
    result.fragment_shader = string_stream[1].str();

    return result;
}

unsigned int compile_shader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* source_c_string = source.c_str();
    glShaderSource(id, 1, &source_c_string, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "ERROR: Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader) {
    unsigned int program = glCreateProgram();
    unsigned int compiled_vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int compiled_fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, compiled_vertex_shader);
    glAttachShader(program, compiled_fragment_shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(compiled_vertex_shader);
    glDeleteShader(compiled_fragment_shader);

    return program;
}


//
// --- OpenGL Error handling ---
//
void gl_clear_error() {
    while (glGetError() != GL_NO_ERROR); // or !glGetError()
}

bool gl_log_call(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

