#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "ObjectModelMatrix.hpp"
#define ASTEROID_OBJ_PATH "../../data/asteroid/A2.obj"
#define ADJUST_ASTEROID_SIZE Matrix_Scale(2.0f, 2.0f, 2.0f)
#define TRANSLATION_SPEED 2.5f
#define ROTATION_SPEEED 5.0F
#define ASTEROID_ROTATION_DEGREE 3.1415/16

class Asteroid : public ObjectModelMatrix
{
    private:
    glm::vec4 spawn_point;
    public: 
    Asteroid(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, transform)
    {
        float x = model[3].x;
        float y = model[3].y;
        float z = model[3].z;
        this->spawn_point = glm::vec4(x,y,z, 1.0f);
    }
    Asteroid(int id, string name, glm::mat4 model):
    ObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, {})
    {
        float x = model[3].x;
        float y = model[3].y;
        float z = model[3].z;
        this->spawn_point = glm::vec4(x,y,z, 1.0f);
    }
    void draw(){
        // this->update_model(Matrix_Rotate_X(ROTATION_DEGREE)*ROTATION_SPEED);
        // this->update_model_extrinsic(Matrix_Translate(0.0f, 0.0f, TRANSLATION_SPEED*delta_t)); 
        this->update_model(Matrix_Translate(0.0f, 0.0f, TRANSLATION_SPEED*delta_t));
        ObjectModelMatrix::draw();
    }
};
#endif