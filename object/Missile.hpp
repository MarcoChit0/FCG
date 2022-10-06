#ifndef MISSILE_HPP 
#define MISSILE_HPP

#include "ObjectModelMatrix.hpp"
#define MISSILE_OBJ_PATH "../../data/missile/MLRS_Rocket.obj"
#define ADJUST_MISSILE_POSITION Matrix_Scale(0.25f, 0.25f, 0.25f)*Matrix_Rotate_Y(-3.1415/2.0)*Matrix_Rotate_Z(3.1415/2.0f)
#define FOWARD_SPEED 50.0f

class Missile : public ComplexObjectModelMatrix
{
    public:
    Missile(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH, transform)
    {}
    Missile(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, MISSILE_OBJ_PATH)
    {}
    void draw(){
        this->update_model(Matrix_Translate(0.0f, FOWARD_SPEED*delta_t, 0.0f));
        for(unsigned long i=0; i < this->get_components().size();i++){
            glm::mat4 model = this->get_model();
            glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
            glUniform1i(material_name_uniform, names_to_id[g_VirtualScene[this->get_components().at(i).c_str()].name]);
            glUniform1i(object_id_uniform, names_to_id[this->get_name()]);
            DrawVirtualObject(this->get_components().at(i).c_str());
        }
    }
};

#endif