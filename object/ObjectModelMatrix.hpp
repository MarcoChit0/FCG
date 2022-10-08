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

using namespace std;

vector <string> tokenize(string line, char delim=' ');

map<string, int> names_to_id = {{"UFO_Glass", 1}, {"UFO_Metal", 2}, {"asteroid", 3}, {"cow", 4}, {"missile", 5}, 
    // PLAYER
    {"HullColor", 6},{"CockpitGlass",7}, {"HullPlain", 8}, {"Engine", 9},
    // COW
    {"cow", 10},{"Cube",11}, {"Material_cowEye.png", 12}, {"Material_1_cowDiff00_test.png", 13}, {"Material_1", 14}
    };

// Estrutura responsável por controlar a posição dos objetos.
class ObjectModelMatrix
{
private:
    int id;
    string name;
    glm::mat4 model;
    vector <glm::mat4> transform;
    string path;
    glm::vec3 bbox_min;
    glm::vec3 bbox_max;

public:
    // GETS:
    string get_name() { return this->name; }
    int get_id() { return this->id; }
    glm::mat4 get_model() { return this->model; }
    string get_path() { return this->path; }
    glm::vec3 get_bbox_min() {return this->bbox_min; }
    glm::vec3 get_bbox_max() {return this->bbox_max; }
    vector<glm::mat4> get_transform() { return this->transform; }

    // SETS:
    void set_transform(vector<glm::mat4> transform){ this->transform = transform; }
    void set_bbox_min(glm::vec3 bbox_min) { this->bbox_min = bbox_min; }
    void set_bbox_max(glm::vec3 bbox_max) { this->bbox_max = bbox_max; }
    void set_model(glm::mat4 model) { this->model = model; }

    // UPDATES:
    void update_model(glm::mat4 op) { this->model = this->model * op; }
    void update_model_extrinsic(glm::mat4 op) { this->model = op * this->model; }

    ObjectModelMatrix(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform){
        this->id = id;
        this->name = name;
        this->model = model;
        this->transform = transform;
        this->path = path;
    }

    ObjectModelMatrix(int id, string name, glm::mat4 model, string path) : ObjectModelMatrix(id, name, model, path, {}) {}
    
    // animation
    virtual void apply_transform(){
        if (!this->transform.empty()){
            for(unsigned long i = 0; i < this->transform.size(); i ++){
                this->model = this->model * this->transform[this->transform.size() - (i+1)];
            }
        }
    }

    virtual void draw(){
        model = this->model;
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(object_id_uniform, names_to_id[this->get_name()]);
        glUniform1i(object_id_uniform, names_to_id[this->name]);
        DrawVirtualObject(this->name.c_str());
    }

    virtual void apply_transform_and_draw(){
        this->apply_transform();
        this->draw();
    }

    virtual void recover_bbox(){
        this->bbox_max = g_VirtualScene[this->name].bbox_max;
        this->bbox_min = g_VirtualScene[this->name].bbox_min;
    }
};


// Estrutura responsável por controlar a posição dos objetos complexos, i.e., objs cujos arquivos que os definem são compostos de "mini-objetos"
class ComplexObjectModelMatrix : public ObjectModelMatrix
{
    private: 
        vector <string> objs_components;
        string path_to_obj_file;
    public:
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform, vector <string> objs_components) :  
        ObjectModelMatrix(id, name, model, path, transform) 
        {
            this->path_to_obj_file = path;
            this->objs_components = objs_components;
        }
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path, vector<glm::mat4> transform): 
        ObjectModelMatrix(id, name, model, path, transform)
        {
            this->path_to_obj_file = path;
            this->recover_objs_components();
        } 
        ComplexObjectModelMatrix(int id, string name, glm::mat4 model, string path): 
        ObjectModelMatrix(id, name, model, path)
        {
            this->path_to_obj_file = path;
            this->recover_objs_components();
        }

        void recover_objs_components(){
            ifstream file; 
            file.open(this->path_to_obj_file);
            if(file.is_open()){
                string line;
                vector<string> tokens;
                while(getline(file, line)){
                    tokens = tokenize(line);
                    // topologia dos objetos no arquivo .obj em uma linha começa com o, g ou usemtl
                    if (tokens[0] == "o" || tokens[0] == "g" || tokens[0] == "usemtl"){
                        this->objs_components.push_back(tokens[1]);
                    }
                }
            }
            else{
                cout << "Error -- Could not open file " << this->path_to_obj_file <<endl;
                exit(1);
            }
        }

        void recover_bbox(){
            float   min_x = g_VirtualScene[this->objs_components[0]].bbox_min.x, 
                    min_y = g_VirtualScene[this->objs_components[0]].bbox_min.y, 
                    min_z = g_VirtualScene[this->objs_components[0]].bbox_min.z;
            float   max_x = g_VirtualScene[this->objs_components[0]].bbox_max.x, 
                    max_y = g_VirtualScene[this->objs_components[0]].bbox_max.y, 
                    max_z = g_VirtualScene[this->objs_components[0]].bbox_max.z;
            // É necessário pegar os menores e maiores coordenadas de TODOS os componentes.
            for(unsigned long i = 0; i < this->objs_components.size(); i++){
                if(min_x > g_VirtualScene[this->objs_components[i]].bbox_min.x) min_x = g_VirtualScene[this->objs_components[i]].bbox_min.x;
                if(min_y > g_VirtualScene[this->objs_components[i]].bbox_min.y) min_y = g_VirtualScene[this->objs_components[i]].bbox_min.y;
                if(min_z > g_VirtualScene[this->objs_components[i]].bbox_min.z) min_z = g_VirtualScene[this->objs_components[i]].bbox_min.z;
                
                if(max_x < g_VirtualScene[this->objs_components[i]].bbox_max.x) max_x = g_VirtualScene[this->objs_components[i]].bbox_max.x;
                if(max_y < g_VirtualScene[this->objs_components[i]].bbox_max.y) max_y = g_VirtualScene[this->objs_components[i]].bbox_max.y;
                if(max_z < g_VirtualScene[this->objs_components[i]].bbox_max.z) max_z = g_VirtualScene[this->objs_components[i]].bbox_max.z;
            }    
            glm::vec3 bbox_min = glm::vec3(min_x, min_y, min_z);
            glm::vec3 bbox_max = glm::vec3(max_x, max_y, max_z);
            this->set_bbox_min(bbox_min);
            this->set_bbox_max(bbox_max);
        }

        virtual void draw(){
            this->apply_transform();
            for(unsigned long i=0; i < this->objs_components.size();i++){
                glm::mat4 model = this->get_model();
                glUniformMatrix4fv(model_uniform, 1, GL_FALSE, glm::value_ptr(model));
                glUniform1i(material_name_uniform, names_to_id[this->objs_components[i].c_str()]);
                std::cout << this->objs_components[i].c_str() << " " << names_to_id[this->objs_components[i].c_str()]    << "\n";
                // Tem que passar não para o nome do objeto, mas sim para o nome do "sub-objeto" que compõe o objeto
                glUniform1i(object_id_uniform,this->get_id());
                DrawVirtualObject(this->objs_components[i].c_str());
            }
        }
        vector <string> get_components() {return this->objs_components;}
};
#endif