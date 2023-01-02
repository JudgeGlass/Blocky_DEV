#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include <GL/glew.h>

class Shader{
    public:
        Shader(const std::string vertex_file, const std::string fragment_file);

        void load_shader();

        GLuint get_program_id();
        GLuint get_uniform_location(const std::string name);

    private:
        const std::string vertex_file;
        const std::string fragment_file;

        GLuint vertex_shader_id;
        GLuint fragment_shader_id;
        GLuint program_id;

};

#endif