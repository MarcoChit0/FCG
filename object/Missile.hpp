#ifndef MISSILE_HPP 
#define MISSILE_HPP

#include "ObjectModelMatrix.hpp"
#define MISSILE_OBJ_PATH "../../data/missile/MLRS_Rocket.obj"
#define ADJUST_MISSILE_POSITION Matrix_Scale(0.25f, 0.25f, 0.25f)*Matrix_Rotate_Y(-3.1415/2.0)*Matrix_Rotate_Z(3.1415/2.0f)
#define FOWARD_SPEED 1.0f

class Missile : public ObjectModelMatrix
{
    public:
    Missile(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH, transform)
    {}
    Missile(int id, string name, glm::mat4 model):
    ObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH)
    {}
    void draw(){
        this->update_model(Matrix_Translate(0.0f, FOWARD_SPEED*delta_t, 0.0f));
        ObjectModelMatrix::draw();
    }
};

#endif