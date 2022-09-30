#ifndef COLLISIONS_HPP
#define COLLICIONS_HPP 

#include "../object/Objects.hpp"

bool collision_cube_cylinder(ObjectModelMatrix* cube_object,ObjectModelMatrix* cylinder_object);
bool collision_cube_sphere(ObjectModelMatrix* cube_object,ObjectModelMatrix* sphere_object);
bool collision_cylinder_circle();

void collision_handler();

#endif