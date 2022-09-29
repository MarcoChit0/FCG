#ifndef UFO_HPP
#define UFO_HPP

#include "ObjectModelMatrix.hpp"
#define UFO_OBJ_PATH "../../data/ufo/UFO.obj"

class UFO : public ComplexObjectModelMatrix
{
    public: 
    UFO(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH, transform)
    {}
    UFO(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH)
    {}
};

#endif