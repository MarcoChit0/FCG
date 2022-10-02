#ifndef COW_HPP
#define COW_HPP 

#include "ObjectModelMatrix.hpp"
#define COW_OBJ_PATH "../../data/cow/cow.obj"
#define COW_STARTING_LIFE_POINTS 1
#define BIND_DISTANCE 1.75f
#define COW_BINDED_TO_UFO_MATRIX Matrix_Translate(0.0f, -BIND_DISTANCE, 0.0f)

class Cow : public ObjectModelMatrix
{
    private:
    int life_points;
    public:
    Cow(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ObjectModelMatrix(id, name, model, COW_OBJ_PATH, transform)
    {
        this->life_points = COW_STARTING_LIFE_POINTS;
    }
    Cow(int id, string name, glm::mat4 model):
    ObjectModelMatrix(id, name, model, COW_OBJ_PATH)
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
};

#endif