#ifndef COLLISIONS_HPP
#define COLLICIONS_HPP 

#include "../object/Objects.hpp"

bool collision_box_cylinder();
bool collision_cube_sphere(ObjectModelMatrix* cube_object,ObjectModelMatrix* sphere_object,glm::mat4 view,glm::mat4 projection);
bool collision_cylinder_circle();

void collision_handler(glm::mat4 view, glm::mat4 projection);

#endif