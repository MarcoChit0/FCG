#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Player.hpp"
#include "Missile.hpp"
#include "ObjectModelMatrix.hpp"

double number_of_missiles = 0;

enum ObjectsIds{
    PLAYER_ID,
    MISSILE_ID,
};

void draw_objects(vector <ObjectModelMatrix*> objs);
void create_geometric_objects();
void player_shoot();

Player* player = new Player(PLAYER_ID, "player", Matrix_Scale(0.1f, 0.1f, 0.1f), "../../data/SmallSpaceFighter.obj");
Missile* missile = new Missile(MISSILE_ID, "missile", Matrix_Translate(0.0f, 0.0f, -0.5f)*Matrix_Scale(0.05f, 0.05f, 0.05f)*Matrix_Rotate_Y(-3.1415/2.0)*Matrix_Rotate_Z(3.1415/2.0f), {});
// Missile* missile = new Missile(MISSILE_ID, "missile", Matrix_Translate(0.0f, 0.0f, -0.5f)*Matrix_Scale(0.05f, 0.05f, 0.05f)*Matrix_Rotate_Y(-3.1415/2.0)*Matrix_Rotate_Z(3.1415/2.0f), {});
vector <ObjectModelMatrix*> objects = {player, missile};
#endif