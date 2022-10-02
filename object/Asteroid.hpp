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
};
    // void go_backward_with_rotation(){
    //     this->set_transform({Matrix_Rotate_X(3.1415/64), Matrix_Rotate_Y(3.1415/96), Matrix_Rotate_Z(3.1415/128), BACKWARD_TRANSFORMATION});
    // }
    // void apply_transform(){        
    //     // backward movement:
    //     this->update_model(this->get_transform()[this->get_transform().size() - 1]);
    //     // rotations:
    //     cout << "\n\n######################\n\n";
    //     if (this->get_transform().size()>1){                
    //         glm::vec4 quarta_coluna = this->get_model()[3];
    //         float x_translation = this->get_model()[3].x;
    //         float y_translation = this->get_model()[3].y;
    //         float z_translation = this->get_model()[3].z;
    //         this->update_model(Matrix_Translate(- x_translation,- y_translation,- z_translation));

    //         for(unsigned long i = 1; i < this->get_transform().size(); i ++){
    //             this->update_model(this->get_transform()[this->get_transform().size() - (i+1)]);
    //         }
    //         this->update_model(Matrix_Translate(x_translation,y_translation,z_translation));
    //         glm::vec4 primeira_coluna = this->get_model()[0];
    //         glm::vec4 segunda_coluna = this->get_model()[1];
    //         glm::vec4 terceira_coluna = this->get_model()[2];
    //         this->set_model(glm::mat4(primeira_coluna, segunda_coluna, terceira_coluna, quarta_coluna));
    //     }
    // }
#endif