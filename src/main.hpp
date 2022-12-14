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
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>  // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h> // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


// Headers da biblioteca para carregar modelos obj
#include <tiny_obj_loader.h>
#include <stb_image.h>

// Headers locais, definidos na pasta "include/"
#include "utils.h"
#include "matrices.h"

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
#include "../object/ObjectModelMatrix.hpp"
#include "../object/ObjectModelMatrix.cpp"
#include "../object/SceneObject.hpp"
#include "../object/ObjectModel.hpp"
#include "../object/Objects.hpp"
#include "../object/Objects.cpp"
#include "shader.hpp"

// COLLISIONS:
#include "../collisions/collisions.hpp"
#include "../collisions/collisions.cpp"

// CONST:
const char* window_title = "INF01047 - Trabalho Final";
GLFWwindow *initialize(int argc, char *argv[]);
void frame(GLFWwindow *window);
#endif