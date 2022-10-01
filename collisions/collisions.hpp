#ifndef COLLISIONS_HPP
#define COLLICIONS_HPP 

#include "../object/Objects.hpp"

bool collision_cube_cylinder(ObjectModelMatrix* cube_object,ObjectModelMatrix* cylinder_object);
bool collision_cube_sphere(ObjectModelMatrix* cube_object,ObjectModelMatrix* sphere_object);
bool collision_cylinder_sphere(ObjectModelMatrix* cylinder_object,ObjectModelMatrix* sphere_object);

void collided_player_asteroid(ObjectModelMatrix* a, int a_pos);
void collided_missile_asteroid(ObjectModelMatrix* a, int a_pos, ObjectModelMatrix* m, int m_pos);
void collided_asteroid_missile(ObjectModelMatrix* a, int a_pos, ObjectModelMatrix* m, int m_pos);
void collided_missile_ufo(ObjectModelMatrix* m, int m_pos);
void collided_missile_cow(ObjectModelMatrix* m, int m_pos);

void collision_handler();

#endif