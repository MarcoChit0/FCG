#ifndef CORE_HPP
#define CORE_HPP

#include "../struct/ObjModel.hpp"
#include "../struct/SceneObject.hpp"
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
#include "utils.h"
#include "matrices.h"


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

// Abaixo definimos variáveis globais utilizadas em várias funções do código.

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
std::map<std::string, SceneObject> g_VirtualScene;

// Pilha que guardará as matrizes de modelagem.
std::stack<glm::mat4>  g_MatrixStack;

// Declaração de funções utilizadas para pilha de matrizes de modelagem.
void PushMatrix(glm::mat4 M);
void PopMatrix(glm::mat4& M);

// Constrói representação de um ObjModel como malha de triângulos para renderização
void BuildTrianglesAndAddToVirtualScene(ObjModel*);

// Computa normais de um ObjModel, caso não existam.
void ComputeNormals(ObjModel* model); 

// Carrega os shaders de vértice e fragmento, criando um programa de GPU
void LoadShadersFromFiles(); 

// Função que carrega imagens de textura
void LoadTextureImage(const char* filename);

// Desenha um objeto armazenado em g_VirtualScene
void DrawVirtualObject(const char* object_name);

// Carrega um vertex shader
GLuint LoadShader_Vertex(const char* filename);  

// Carrega um fragment shader
GLuint LoadShader_Fragment(const char* filename);

// Função utilizada pelas duas acima
void LoadShader(const char* filename, GLuint shader_id);

// Cria um programa de GPU
GLuint CreateGpuProgram(GLuint vertex_shader_id, GLuint fragment_shader_id);

// Função para debugging
void PrintObjModelInfo(ObjModel*); 

#endif