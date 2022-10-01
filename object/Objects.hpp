#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Player.hpp"
#include "Missile.hpp"
#include "UFO.hpp"
#include "Cow.hpp"
#include "Asteroid.hpp"
#include "ObjectModelMatrix.hpp"

double number_of_missiles = 0;

enum ObjectsIds{
    PLAYER_ID,
    MISSILE_ID,
    UFO_ID,
    COW_ID,
    ASTEROID_ID,
};

void draw_objects();
void create_geometric_objects();
void player_shoot();
void new_object_being_added_to_virtual_screen(ObjectModelMatrix* obj);

Player* player = new Player(PLAYER_ID, "player", Matrix_Translate(0.0f,0.0f,2.0f)*Matrix_Scale(0.1f, 0.1f, 0.1f));
UFO* ufo = new UFO(UFO_ID, "ufo", Matrix_Translate(0.0f, 0.0f, -2.0f)*Matrix_Scale(0.1f, 0.1f, 0.1f));
Cow* cow = new Cow(COW_ID, "cow", Matrix_Scale(0.1f, 0.1f, 0.1f));
Asteroid* asteroid = new Asteroid(ASTEROID_ID, "asteroid",  Matrix_Translate(1.0f, 0.0f, 2.0f)*Matrix_Scale(0.2f, 0.2f, 0.2f));
Asteroid* asteroid2 = new Asteroid(ASTEROID_ID, "asteroid",  Matrix_Translate(-1.0f, 0.0f, 0.0f)*Matrix_Scale(0.3f, 0.3f, 0.3f));

vector <ObjectModelMatrix*> objects = {player, ufo, cow, asteroid,asteroid2};
#endif