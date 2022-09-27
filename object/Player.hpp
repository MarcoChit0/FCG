#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ObjectModelMatrix.hpp"

#define SPEED 1.0f

class Player : public ComplexObjectModelMatrix
{
    private:
        int life_points;
        float speed;
        vector<glm::mat4> movement;
    public:
        Player(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform, vector <string> objs_names):
        ComplexObjectModelMatrix(id, name, model, path, transform, objs_names) 
        {
            this->speed = SPEED;
            this->movement = {};
        }
        Player(int id, string name, glm::mat4 model, string path) : 
        ComplexObjectModelMatrix(id, name, model, path)
        {
            this->speed = SPEED;
            this->movement = {};
        } 
        void take_damage();
        void move_right(){
            this->movement.push_back(Matrix_Translate(this->speed,0.0f, 0.0f));
        }
        void move_left(){
            this->movement.push_back(Matrix_Translate(-this->speed, 0.0f, 0.0f));
        }
        void shoot();

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