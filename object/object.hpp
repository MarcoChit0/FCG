#include <iostream>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../core/core.hpp"
#include "../user_input/user_input.hpp"
#include <glm/gtx/string_cast.hpp>

#define SPHERE 0
#define BUNNY 1
#define PLANE 2

using namespace std;

class Object
{
private:
    int id;
    string name;
    glm::mat4 model;
    vector <glm::mat4> transform;

public:
    // GETS:
    string get_name() { return this->name; }
    int get_id() { return this->id; }
    glm::mat4 get_model() { return this->model; }

    Object(int id, string name, glm::mat4 model, vector<glm::mat4> transform){
        this->id = id;
        this->name = name;
        this->model = model;
        this->transform = transform;
    }
    
    Object(int id, string name, glm::mat4 model) : Object(id, name, model, {}) {}
    
    // animation
    void apply_transform(){
        if (!this->transform.empty()){
            for(int i = this->transform.size() - 1; i >=0; i --){
                this->model = this->model * this->transform[i];
            }
        }
    }

    void draw(){
        this->apply_transform();
        model = this->model;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(object_id_uniform, this->id);
        DrawVirtualObject(this->name.c_str());
    }
};


Object* Sphere = new Object(SPHERE, "sphere", Matrix_Translate(-1.0f, 0.0f, 0.0f) * Matrix_Rotate_Z(0.6f) * Matrix_Rotate_X(0.2f), {Matrix_Rotate_Y(0.026)});
Object* Bunny = new Object(BUNNY, "bunny", Matrix_Translate(1.0f, 0.0f, 0.0f), {Matrix_Rotate_X(0.026)});
Object* Plane = new Object(PLANE, "plane", Matrix_Translate(0.0f, -1.1f, 0.0f));

vector <Object*> objects = {Sphere, Bunny, Plane};

void draw_objects(vector <Object*> objs){
    for(unsigned long i = 0; i < objs.size(); i++){
        objs[i]->draw();
    }
}