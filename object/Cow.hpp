#ifndef COW_HPP
#define COW_HPP 

#include "ObjectModelMatrix.hpp"
#define COW_OBJ_PATH "../../data/cow/cow.obj"
#define COW_STARTING_LIFE_POINTS 1
#define BIND_DISTANCE 1.75f
#define ROTATION_DEGREE (3.1415/16)
#define ROTATION_SPEED 10.0F
#define COW_BINDED_TO_UFO_MATRIX Matrix_Translate(0.0f, -BIND_DISTANCE, 0.0f) * Matrix_Scale(0.25f, 0.25f, 0.25f)

class Cow : public ComplexObjectModelMatrix
{
    private:
    int life_points;
    vector<glm::mat4> movement;
    public:
    Cow(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, COW_OBJ_PATH, transform)
    {
        this->life_points = COW_STARTING_LIFE_POINTS;
    }
    Cow(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, COW_OBJ_PATH)
    {
        this->life_points = COW_STARTING_LIFE_POINTS;
    }
    void take_damage(){
        this->life_points -= 1;
        if(this->life_points == 0){
            player_lost_the_game_killing_the_little_cow = true;
        }
    }
    void bind_to_ufo(glm::mat4 ufo_model){
        this->set_model(ufo_model*COW_BINDED_TO_UFO_MATRIX);
    }
    void rotate_x(){
        this->movement.push_back(Matrix_Rotate_X(ROTATION_DEGREE)*delta_t*ROTATION_SPEED);
    }
    void rotate_y(){
        this->movement.push_back(Matrix_Rotate_Y(ROTATION_DEGREE)*delta_t*ROTATION_SPEED);
    }
    void rotate_z(){
        this->movement.push_back(Matrix_Rotate_Z(ROTATION_DEGREE)*delta_t*ROTATION_SPEED);
    }
    void draw(){
        if (this->movement.size() > 0){
            for(unsigned long i = 0; i < this->movement.size(); i++){
                this->update_model(this->movement[this->movement.size()-(i+1)]);
            }                
        }
        ComplexObjectModelMatrix::draw();
    }
};

#endif