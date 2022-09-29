#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Objects.hpp"
#include "ObjectModelMatrix.hpp"
#define SPEED 1.0f
#define PLAYER_OBJ_PATH "../../data/player/SmallSpaceFighter.obj"

class Player : public ComplexObjectModelMatrix
{
    private:
        int life_points;
        float speed;
        vector<glm::mat4> movement;
        double shots;
    public:
        Player(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform, vector <string> objs_names):
        ComplexObjectModelMatrix(id, name, model, path, transform, objs_names) 
        {
            this->shots = 0;
            this->speed = SPEED;
            this->movement = {};
        }
        Player(int id, string name, glm::mat4 model, string path) : 
        ComplexObjectModelMatrix(id, name, model, path)
        {
            this->shots = 0;
            this->speed = SPEED;
            this->movement = {};
        } 
        Player(int id, string name, glm::mat4 model) : Player(id, name, model, PLAYER_OBJ_PATH)
        {}

        void take_damage();
        void move_right(){
            this->movement.push_back(Matrix_Translate(this->speed,0.0f, 0.0f));
        }
        void move_left(){
            this->movement.push_back(Matrix_Translate(-this->speed, 0.0f, 0.0f));
        }
        void draw(){
            if (this->movement.size() > 0){
                glm::mat4 movement = this->movement[this->movement.size()-1];
                this->movement.pop_back();
                this->update_model(movement);                
            }
            ComplexObjectModelMatrix::draw();
        }
};

#endif