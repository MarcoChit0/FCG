#ifndef CORE_HPP
#define CORE_HPP

#include "../object/ObjectModel.hpp"
#include "../object/SceneObject.hpp"
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader.h>
#include <stb_image.h>
#include <fstream>
#include <sstream>
#include "utils.h"
#include "matrices.h"
#include "../user_input/user_input.hpp"

#define NEARPLANE  -0.1f
#define FARPLANE  -10.0f

// Variáveis que definem um programa de GPU (shaders).
GLuint vertex_shader_id;
GLuint fragment_shader_id;
GLuint program_id = 0;
GLint model_uniform;
GLint view_uniform;
GLint projection_uniform;
GLint object_id_uniform;
GLint bbox_min_uniform;
GLint bbox_max_uniform;

// Número de texturas carregadas pela função LoadTextureImage()
GLuint g_NumLoadedTextures = 0;

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
std::map<std::string, SceneObject> g_VirtualScene;

// Pilha que guardará as matrizes de modelagem.
std::stack<glm::mat4>  g_MatrixStack;

// Vetor que armazena os caminhos das imagens de textura.
std::vector<std::string> texture_images= {
    "../../data/tc-earth_daymap_surface.jpg",
    "../../data/tc-earth_nightmap_citylights.gif"
};

// Declaração de funções utilizadas para pilha de matrizes de modelagem.
void PushMatrix(glm::mat4 M);
void PopMatrix(glm::mat4& M);
// Constrói representação de um ObjectModel como malha de triângulos para renderização
void BuildTrianglesAndAddToVirtualScene(ObjectModel*);
void ComputeNormals(ObjectModel* model); 
void LoadShadersFromFiles(); 
void LoadTextureImage(const char* filename);
void DrawVirtualObject(const char* object_name);
GLuint LoadShader_Vertex(const char* filename);  
GLuint LoadShader_Fragment(const char* filename);
void LoadShader(const char* filename, GLuint shader_id);
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);
void PrintObjModelInfo(ObjectModel*); 
// void create_geometric_object(std::string path);
// void create_geometric_objects(std::vector<std::string> paths);
void load_texture_images(std::vector<std::string> paths);
glm::mat4 create_view_matrix();
glm::mat4 create_projection_matrix();

#endif