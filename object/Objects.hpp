#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Player.hpp"
#include "Missile.hpp"
#include "UFO.hpp"
#include "Cow.hpp"
#include "Asteroid.hpp"
#include "ObjectModelMatrix.hpp"

#define COOLDOWN_MISSILE_TIME 1
#define COOLDOWN_ASTEROID_TIME 2.5
double number_of_missiles = 0;
double number_of_asteroids = 0;
float time_last_missile_created = 0.0f;
float time_last_asteroid_created = 0.0f;

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
void ufo_throws_asteroid();

Player* player = new Player(PLAYER_ID, "player", Matrix_Translate(0.0f,0.0f,2.0f)*Matrix_Scale(0.1f, 0.1f, 0.1f));
UFO* ufo = new UFO(UFO_ID, "ufo", Matrix_Translate(0.0f, 0.0f, -2.0f)*Matrix_Scale(0.1f, 0.1f, 0.1f));
Cow* cow = new Cow(COW_ID, "cow", Matrix_Scale(0.1f, 0.1f, 0.1f));
Cow* c2 = new Cow(COW_ID, "cow", Matrix_Translate(0.1f, 0.1f, 0.1f));

vector <ObjectModelMatrix*> objects = {player, ufo, cow, c2};
#endif