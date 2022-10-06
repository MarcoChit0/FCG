#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "ObjectModelMatrix.hpp"
#define ASTEROID_OBJ_PATH "../../data/asteroid/A2.obj"
#define ADJUST_ASTEROID_SIZE Matrix_Scale(2.0f, 2.0f, 2.0f)
#define TRANSLATION_SPEED 2.5f
#define ROTATION_SPEEED 5.0F
#define ROTATION_DEGREE 3.1415/16

class Asteroid : public ComplexObjectModelMatrix
{
    private:
    glm::vec4 spawn_point;
    public: 
    Asteroid(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, transform)
    {
        float x = model[3].x;
        float y = model[3].y;
        float z = model[3].z;
        this->spawn_point = glm::vec4(x,y,z, 1.0f);
    }
    Asteroid(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH)
    {
        float x = model[3].x;
        float y = model[3].y;
        float z = model[3].z;
        this->spawn_point = glm::vec4(x,y,z, 1.0f);
    }
    void draw(){
        this->update_model(Matrix_Rotate_X(ROTATION_DEGREE)*ROTATION_SPEED);
        this->update_model_extrinsic(Matrix_Translate(0.0f, 0.0f, TRANSLATION_SPEED*delta_t));
        for(unsigned long i=0; i < this->get_components().size();i++){
            glm::mat4 model = this->get_model();
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(material_name_uniform, names_to_id[g_VirtualScene[this->get_components().at(i).c_str()].name]);
            glUniform1i(object_id_uniform, names_to_id[this->get_name()]);
            DrawVirtualObject(this->get_components().at(i).c_str());
        }
    }
    void apply_transform(){        
        glm::vec4 translacoes = this->get_model()[3];
        // aplica rotação intrínseca no eixo x do objeto (no seu sistema de
        // coordenadas local)
        this->update_model(Matrix_Rotate_X(3.1415/16));
        // aplica deslocamento extrínseco no eixo z (movimento em direção ao
        // player), movimentando o objeto em relação ao seu ponto atual
        this->update_model_extrinsic(Matrix_Translate(0.0f, 0.0f, 0.2f));
    }
};
#endif