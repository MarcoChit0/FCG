#ifndef MISSILE_HPP 
#define MISSILE_HPP

#include "ObjectModelMatrix.hpp"
#define MISSILE_OBJ_PATH "../../data/missile/MLRS_Rocket.obj"
#define BASIC_MISSILE_POSITION Matrix_Translate(0.0f, 0.0f, -0.5f)*Matrix_Scale(0.05f, 0.05f, 0.05f)*Matrix_Rotate_Y(-3.1415/2.0)*Matrix_Rotate_Z(3.1415/2.0f)
class Missile : public ComplexObjectModelMatrix
{
    public:
    Missile(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH, transform)
    {}
    Missile(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH)
    {}
    Missile(int id, string name):
    Missile(id, name, BASIC_MISSILE_POSITION)
    {}
};

#endif