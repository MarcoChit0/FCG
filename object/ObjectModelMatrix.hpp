#ifndef OBJECT_MODEL_MATRIX_HPP
#define OBJECT_MODEL_MATRIX_HPP

#include <fstream>
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
#define CYBERTRUCKDELOREAN 3
#define COW 4
#define SMALLSAPCEFIGHTER 5

using namespace std;

vector <string> tokenize(string line, char delim=' ');

enum ObjectTypes
{
    O_TYPE, 
    G_TYPE,
    USEMTL_TYPE,
};

string ObjectTypeToString(ObjectTypes type);

// Estrutura responsável por controlar a posição dos objetos.
class ObjectModelMatrix
{
private:
    int id;
    string name;
    glm::mat4 model;
    vector <glm::mat4> transform;
    string path;

public:
    // GETS:
    string get_name() { return this->name; }
    int get_id() { return this->id; }
    glm::mat4 get_model() { return this->model; }
    string get_path() { return this->path; }

    ObjectModelMatrix(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform){
        this->id = id;
        this->name = name;
        this->model = model;
        this->transform = transform;
        this->path = path;
    }
    
    ObjectModelMatrix(int id, string name, glm::mat4 model, string path) : ObjectModelMatrix(id, name, model, path, {}) {}
    
    // animation
    void apply_transform(){
        if (!this->transform.empty()){
            for(int i = this->transform.size() - 1; i >=0; i --){
                this->model = this->model * this->transform[i];
            }
        }
    }

    virtual void draw(){
        this->apply_transform();
        model = this->model;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(object_id_uniform, this->id);
        DrawVirtualObject(this->name.c_str());
    }
};

class ComplexObjectModelMatrix : public ObjectModelMatrix
{
    private: 
        vector <string> objs_names;
        string path_to_obj_file;
        ObjectTypes type;
    public:
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path, ObjectTypes type, vector<glm::mat4> transform, vector <string> objs_names) :  
        ObjectModelMatrix(id, name, model, path, transform) 
        {
            this->type = type;
            this->path_to_obj_file = path;
            this->objs_names = objs_names;
        }
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path, ObjectTypes type, vector<glm::mat4> transform): 
        ObjectModelMatrix(id, name, model, path, transform)
        {
            this->type = type;
            this->path_to_obj_file = path;
            this->recover_objs_names();
        } 
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path, ObjectTypes type): 
        ObjectModelMatrix(id, name, model, path)
        {
            this->type = type;
            this->path_to_obj_file = path;
            this->recover_objs_names();
        }

        void recover_objs_names(){
            ifstream file; 
            file.open(this->path_to_obj_file);
            if(file.is_open()){
                string line;
                vector<string> tokens;
                while(getline(file, line)){
                    tokens = tokenize(line);
                    // topologia dos objetos no arquivo .obj em uma linha começa com o, g ou usemtl
                    if (tokens[0] == ObjectTypeToString(this->type)){
                        this->objs_names.push_back(tokens[1]);
                    }
                }
            }
            else{
                cout << "Error -- Could not open file " << this->path_to_obj_file <<endl;
                exit(1);
            }
        }
        void draw(){
            this->apply_transform();
            for(unsigned long i=0; i < this->objs_names.size();i++){
                glm::mat4 model = this->get_model();
                glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
                glUniform1i(object_id_uniform, this->get_id());
                DrawVirtualObject(this->objs_names[i].c_str());
            }
        }

};

// // TODO: implememtar meĉanica player
// class Player : ObjectModelMatrix 
// {
//     public:
//         Player(int id, string name, glm::mat4 model, vector<glm::mat4> transform) : ObjectModelMatrix(id, name, model, transform) {}
//         Player(int id, string name, glm::mat4 model) : ObjectModelMatrix(id, name, model) {}
//         void move();
//         void shot();
// };

ObjectModelMatrix* Sphere = new ObjectModelMatrix(SPHERE, "sphere", Matrix_Translate(-1.0f, 0.0f, 0.0f) * Matrix_Rotate_Z(0.6f) * Matrix_Rotate_X(0.2f),"../../data/sphere.obj", {Matrix_Rotate_Y(0.026)});
ObjectModelMatrix* Bunny = new ObjectModelMatrix(BUNNY, "bunny", Matrix_Translate(1.0f, 0.0f, 0.0f),"../../data/bunny.obj", {Matrix_Rotate_X(0.026)});
ObjectModelMatrix* Plane = new ObjectModelMatrix(PLANE, "plane", Matrix_Translate(0.0f, -1.1f, 0.0f), "../../data/plane.obj");
ComplexObjectModelMatrix* CyberpunkDeLorean = new ComplexObjectModelMatrix(CYBERTRUCKDELOREAN, "CyberpunkDeLorean", Matrix_Translate(-1.0f, 1.0f, -1.0f)*Matrix_Scale(0.5f, 0.5f, 0.5f), "../../data/CyberpunkDeLorean.obj", USEMTL_TYPE);
ObjectModelMatrix* Cow = new ObjectModelMatrix(COW, "cow", Matrix_Translate(-1.0f, -1.0f, -1.0f), "../../data/cow.obj");
ComplexObjectModelMatrix* SmallSpaceFighter = new ComplexObjectModelMatrix(SMALLSAPCEFIGHTER, "SmallSpaceFighter", Matrix_Translate(1.0f, 1.0f, 1.0f)*Matrix_Scale(0.1f, 0.1f, 0.1f), "../../data/SmallSpaceFighter.obj", O_TYPE);

vector <ObjectModelMatrix*> objects = {Sphere, Bunny, Plane, CyberpunkDeLorean, Cow, SmallSpaceFighter};

void draw_objects(vector <ObjectModelMatrix*> objs);
void create_geometric_object(ObjectModelMatrix* obj);
void create_geometric_objects(vector<ObjectModelMatrix*> objs);
#endif