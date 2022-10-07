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
#include "../src/shader.hpp"

#define NEARPLANE  -0.1f
#define FARPLANE  -10.0f
#define CAMERA_SPEED 10.0f

bool player_lost_the_game_by_being_killed = false;
bool player_lost_the_game_killing_the_little_cow = false;
bool player_won_the_game = false;


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
GLint material_name_uniform;

// váriaveis utilizadas para o sky box
GLuint program_id2 = 2;
GLuint skybox_vertex_shader_id, skybox_fragment_shader_id;
unsigned int cubemapTexture;

// Variáveis utilizadas para look-at camera
glm::vec4 camera_lookat_l = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); 
// Variáveis utilizadas para free camera
glm::vec4 camera_vector_w;
glm::vec4 camera_vector_u;
glm::vec4 camera_up_vector = glm::vec4(0.0f,1.0f,0.0f,0.0f);
glm::vec4 camera_position_c = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec4 camera_view_vector;
bool using_free_camera = false;

// timer
float prev_time = glfwGetTime();
float current_time = glfwGetTime();
float delta_t;

// Número de texturas carregadas pela função LoadTextureImage()
GLuint g_NumLoadedTextures = 6;

// A cena virtual é uma lista de objetos nomeados, guardados em um dicionário
std::map<std::string, SceneObject> g_VirtualScene;

// Pilha que guardará as matrizes de modelagem.
std::stack<glm::mat4>  g_MatrixStack;

// Vetor que armazena os caminhos das imagens de textura.
std::vector<std::string> texture_images= {
    "../../data/ufo/Textures/UFO_Metal_BaseColor.png",
    "../../data/ufo/Textures/UFO_Metal_Roughness.png",
    "../../data/ufo/Textures/UFO_Metal_Metallic.png",
    "../../data/tc-earth_daymap_surface.jpg",
    // asteroid textures:
    "../../data/asteroid/textures/Albedo.jpg",
    "../../data/asteroid/textures/Displacement.jpg",
    "../../data/asteroid/textures/Emission.jpg",
    "../../data/asteroid/textures/Metalness.jpg",
    "../../data/asteroid/textures/Normal.jpg",
    // cow texrures:
    "../../data/cow/textures/cow_texture.png",
    // missile textures:
    "../../data/missile/textures/MLRS_Rocket_MLRS_Rocket_Mat_BaseColor.png",
    // player textures
    "../../data/player/textures/metallic.png",

};

std::vector<std::string> cube_map_faces = 
{
    "../../data/skybox/right.png",
    "../../data/skybox/left.png",
    "../../data/skybox/top.png",
    "../../data/skybox/bottom.png",
    "../../data/skybox/front.png",
    "../../data/skybox/back.png"
};

float skyboxVertices[] = {
    // positions          
    -1000.0f,  1000.0f, -1000.0f,
    -1000.0f, -1000.0f, -1000.0f,
     1000.0f, -1000.0f, -1000.0f,
     1000.0f, -1000.0f, -1000.0f,
     1000.0f,  1000.0f, -1000.0f,
    -1000.0f,  1000.0f, -1000.0f,

    -1000.0f, -1000.0f,  1000.0f,
    -1000.0f, -1000.0f, -1000.0f,
    -1000.0f,  1000.0f, -1000.0f,
    -1000.0f,  1000.0f, -1000.0f,
    -1000.0f,  1000.0f,  1000.0f,
    -1000.0f, -1000.0f,  1000.0f,

     1000.0f, -1000.0f, -1000.0f,
     1000.0f, -1000.0f,  1000.0f,
     1000.0f,  1000.0f,  1000.0f,
     1000.0f,  1000.0f,  1000.0f,
     1000.0f,  1000.0f, -1000.0f,
     1000.0f, -1000.0f, -1000.0f,

    -1000.0f, -1000.0f,  1000.0f,
    -1000.0f,  1000.0f,  1000.0f,
     1000.0f,  1000.0f,  1000.0f,
     1000.0f,  1000.0f,  1000.0f,
     1000.0f, -1000.0f,  1000.0f,
    -1000.0f, -1000.0f,  1000.0f,

    -1000.0f,  1000.0f, -1000.0f,
     1000.0f,  1000.0f, -1000.0f,
     1000.0f,  1000.0f,  1000.0f,
     1000.0f,  1000.0f,  1000.0f,
    -1000.0f,  1000.0f,  1000.0f,
    -1000.0f,  1000.0f, -1000.0f,

    -1000.0f, -1000.0f, -1000.0f,
    -1000.0f, -1000.0f,  1000.0f,
     1000.0f, -1000.0f, -1000.0f,
     1000.0f, -1000.0f, -1000.0f,
    -1000.0f, -1000.0f,  1000.0f,
     1000.0f, -1000.0f,  1000.0f
};
unsigned int skyboxVAO, skyboxVBO;
Shader *skyboxshader;


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
void load_texture_images(std::vector<std::string> paths);
glm::mat4 create_view_matrix();
glm::mat4 create_projection_matrix();
void game_logic();
unsigned int loadCubemap(std::vector<std::string> faces);
// Curvas de Bezier
glm::vec4 curva_Bezier(int n, glm::vec4 pontos_controle[], float t);
float Bernstein(int n, int k, float t);
int fac(int n);
void free_camera();
void update_timer();
#endif