#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "ObjectModelMatrix.hpp"
#define ASTEROID_OBJ_PATH "../../data/asteroid/A2.obj"

class Asteroid : public ComplexObjectModelMatrix
{
    public: 
    Asteroid(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, transform)
    {}
    Asteroid(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, {Matrix_Rotate_X(3.1415/64.0), Matrix_Rotate_Y(3.1415/128.0),  Matrix_Rotate_Z(3.1415/96.0)})
    {}
};

#endif