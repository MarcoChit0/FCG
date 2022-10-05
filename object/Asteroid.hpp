#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "ObjectModelMatrix.hpp"
#define ASTEROID_OBJ_PATH "../../data/asteroid/A2.obj"
#define ADJUST_ASTEROID_SIZE Matrix_Scale(2.0f, 2.0f, 2.0f)
#define BACKWARD_SPEED 0.2f
#define BACKWARD_TRANSFORMATION Matrix_Translate(0.0f, 0.0f, BACKWARD_SPEED)

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
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, {BACKWARD_TRANSFORMATION})
    {
        float x = model[3].x;
        float y = model[3].y;
        float z = model[3].z;
        this->spawn_point = glm::vec4(x,y,z, 1.0f);
    }
    void go_backward(){
        this->set_transform({BACKWARD_TRANSFORMATION});
    }
    void draw(){
        ComplexObjectModelMatrix::draw();
    }
    void apply_transform(){        
        glm::vec4 translacoes = this->get_model()[3];
        // sair do ponto atual e ir ao ponto de spawn do objeto
        this->update_model(Matrix_Translate(-translacoes.x + spawn_point.x, -translacoes.y + spawn_point.y, -translacoes.z + spawn_point.z));
        // aplicar rotação no eixo x do objeto
        this->update_model(Matrix_Rotate_X(3.1415/16));
        // retornar ao ponto atual com deslocamento no eixo z (movimento em direção ao player)
        this->update_model(Matrix_Translate(translacoes.x - spawn_point.x, translacoes.y - spawn_point.y, (translacoes.z + 0.2f) - spawn_point.z));
    }
};
#endif