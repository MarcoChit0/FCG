#ifndef TEXT_RENDERING_HPP
#define TEXT_RENDERING_HPP

#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include "../user_input/user_input.hpp"
#include "utils.h"
#include "dejavufont.h"

GLuint textVAO;
GLuint textVBO;
GLuint textprogram_id;
GLuint texttexture_id;

const GLchar* const textvertexshader_source = ""
"#version 330\n"
"layout (location = 0) in vec4 position;\n"
"out vec2 texCoords;\n"
"void main()\n"
"{\n"
    "gl_Position = vec4(position.xy, 0, 1);\n"
    "texCoords = position.zw;\n"
"}\n"
"\0";

const GLchar* const textfragmentshader_source = ""
"#version 330\n"
"uniform sampler2D tex;\n"
"in vec2 texCoords;\n"
"out vec4 fragColor;\n"
"void main()\n"
"{\n"
    "fragColor = vec4(0, 0, 0, texture(tex, texCoords).r);\n"
"}\n"
"\0";

// Declaração de funções auxiliares para renderizar texto dentro da janela
// OpenGL. Estas funções estão definidas no arquivo "textrendering.cpp".
void TextRendering_Init();
float TextRendering_LineHeight(GLFWwindow* window);
float TextRendering_CharWidth(GLFWwindow* window);
void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale);
void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale);
void TextRendering_PrintVector(GLFWwindow* window, glm::vec4 v, float x, float y, float scale);
void TextRendering_PrintMatrixVectorProduct(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale);
void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale);
void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale);

// Funções abaixo renderizam como texto na janela OpenGL algumas matrizes e
// outras informações do programa. Definidas após main().
void TextRendering_ShowModelViewProjection(GLFWwindow* window, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec4 p_model);
void TextRendering_ShowProjection(GLFWwindow* window);
void TextRendering_ShowFramesPerSecond(GLFWwindow* window);

#endif