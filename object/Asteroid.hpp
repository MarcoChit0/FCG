#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "ObjectModelMatrix.hpp"
#define ASTEROID_OBJ_PATH "../../data/asteroid/A2.obj"
#define ADJUST_ASTEROID_SIZE Matrix_Scale(1.5f, 1.5f, 1.5f)
#define BACKWARD_SPEED 0.2f
#define BACKWARD_TRANSFORMATION Matrix_Translate(0.0f, 0.0f, BACKWARD_SPEED)

class Asteroid : public ComplexObjectModelMatrix
{
    private:
    double number_of_backward_transformations = 0;
    public: 
    Asteroid(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, transform)
    {}
    Asteroid(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, ASTEROID_OBJ_PATH, {Matrix_Rotate_X(3.1415), Matrix_Rotate_Y(3.1415)})
    {}
    // void go_backward_with_rotation(){
    //     this->set_transform({Matrix_Rotate_X(3.1415/64), BACKWARD_TRANSFORMATION});
    // }
    // void apply_transform(){
    //     cout << endl << this->number_of_backward_transformations << endl;
    //     // BACKWARD TRANSFORMATION
    //     this->update_model(this->get_transform()[this->get_transform().size() - 1]);
    //     this->number_of_backward_transformations += 1;

    //     if (!this->get_transform().empty()){
    //         for(unsigned long i = 1; i < this->get_transform().size(); i ++){
    //             float translation = (this->number_of_backward_transformations * BACKWARD_SPEED);
    //             this->update_model(Matrix_Translate(0.0f, 0.0f, -translation));
    //             this->update_model(this->get_transform()[this->get_transform().size() - (i+1)]);
    //             this->update_model(Matrix_Translate(0.0f, 0.0f, translation));
    //         }
    //     }
    // }
    void go_backward(){
        this->set_transform({BACKWARD_TRANSFORMATION});
    }
};

#endif