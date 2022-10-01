#ifndef UFO_HPP
#define UFO_HPP

#include "ObjectModelMatrix.hpp"
#define UFO_OBJ_PATH "../../data/ufo/UFO.obj"
#define UFO_STARTING_HIT_POINTS 5

class UFO : public ComplexObjectModelMatrix
{
    private:
    int life_points;
    public: 
    UFO(int id, string name, glm::mat4 model, vector<glm::mat4> transform):
    ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH, transform)
    {
        this->life_points = UFO_STARTING_HIT_POINTS;
    }
    
    UFO(int id, string name, glm::mat4 model):
    ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH)
    {
        this->life_points = UFO_STARTING_HIT_POINTS;
    }
    void take_damage(){
        this->life_points -= 1;
        cout << "\n\n $$$$ UFO: " << this->life_points<< " $$$$\n\n";
        if(this->life_points == 0){
            player_won_the_game = true;
        }
    }
};

#endif