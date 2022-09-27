#ifndef OBJECTS_HPP
#define OBJECTS_HPP

#include "Player.hpp"
#include "ObjectModelMatrix.hpp"

enum ObjectsIds{
    PLAYER_ID,
};

// Examples: 
// ObjectModelMatrix* Sphere = new ObjectModelMatrix(SPHERE, "sphere", Matrix_Translate(-1.0f, 0.0f, 0.0f) * Matrix_Rotate_Z(0.6f) * Matrix_Rotate_X(0.2f),"../../data/sphere.obj", {Matrix_Rotate_Y(0.026)});
// ObjectModelMatrix* Bunny = new ObjectModelMatrix(BUNNY, "bunny", Matrix_Translate(1.0f, 0.0f, 0.0f),"../../data/bunny.obj", {Matrix_Rotate_X(0.026)});
// ObjectModelMatrix* Plane = new ObjectModelMatrix(PLANE, "plane", Matrix_Translate(0.0f, -1.1f, 0.0f), "../../data/plane.obj");
// ObjectModelMatrix* Cow = new ObjectModelMatrix(COW, "cow", Matrix_Translate(-1.0f, -1.0f, -1.0f), "../../data/cow.obj");
Player* player = new Player(PLAYER_ID, "Player", Matrix_Scale(0.1f, 0.1f, 0.1f), "../../data/SmallSpaceFighter.obj", O_TYPE);

vector <ObjectModelMatrix*> objects =  {player};

void draw_objects(vector <ObjectModelMatrix*> objs);
void create_geometric_object(ObjectModelMatrix* obj);
void create_geometric_objects(vector<ObjectModelMatrix*> objs);
#endif