#ifndef SCENE_OBJECT_HPP
#define SCENE_OBJECT_HPP

#include <string>
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
//#include <tiny_obj_loader.h>

// Estrutura responsável por salvar os dados do objeto renderizado.
struct SceneObject
{
    std::string  name;        // Nome do objeto
    size_t       first_index; // Índice do primeiro vértice dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    size_t       num_indices; // Número de índices do objeto dentro do vetor indices[] definido em BuildTrianglesAndAddToVirtualScene()
    GLenum       rendering_mode; // Modo de rasterização (GL_TRIANGLES, GL_TRIANGLE_STRIP, etc.)
    GLuint       vertex_array_object_id; // ID do VAO onde estão armazenados os atributos do modelo
    glm::vec3    bbox_min; // Axis-Aligned Bounding Box do objeto
    glm::vec3    bbox_max;
    tinyobj::material_t material;
};

#endif