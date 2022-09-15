#ifndef MAIN_HPP
#define MAIN_HPP

#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers da biblioteca para carregar modelos obj
#include <tiny_obj_loader.h>
#include <stb_image.h>

// Headers locais, definidos na pasta "include/"
#include "utils.h"
#include "matrices.h"

// STRUCTS:
#include "../struct/SceneObject.hpp"
#include "../struct/ObjModel.hpp"

// USER INPUT:
#include "../user_input/user_input.hpp"
#include "../user_input/user_input.cpp"

// CORE:
#include "../core/core.hpp"
#include "../core/core.cpp"

// TEXT RENDERING:
#include "../text_rendering/text_rendering.hpp"
#include "../text_rendering/text_rendering.cpp"

// OBJECTS:
#include "../object/object.hpp"

// CONST:
const char* window_title = "INF01047 - Trabalho Final";

std::vector<std::string> texture_images= {
    "../../data/tc-earth_daymap_surface.jpg",
    "../../data/tc-earth_nightmap_citylights.gif"
};

std::vector<std::string> obj_models= {
    "../../data/sphere.obj",
    "../../data/bunny.obj",
    "../../data/plane.obj"
};


GLFWwindow *initialize(int argc, char *argv[]);
void frame(GLFWwindow *window);
void create_geometric_object(std::string path);
void create_geometric_objects(std::vector<std::string> paths);
void load_texture_images(std::vector<std::string> paths);
glm::mat4 create_view_matrix();
#endif