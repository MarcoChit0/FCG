#ifndef COW_HPP
#define COW_HPP 

#include "ObjectModelMatrix.hpp"
#define COW_OBJ_PATH "../../data/cow/cow.obj"

class Cow : public ObjectModelMatrix
{
    public:
    Cow(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ObjectModelMatrix(id, name, model, COW_OBJ_PATH, transform)
    {}
    Cow(int id, string name, glm::mat4 model):
    ObjectModelMatrix(id, name, model, COW_OBJ_PATH)
    {}
};

#endif