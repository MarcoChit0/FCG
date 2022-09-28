#include "Objects.hpp"

using namespace std; 

void draw_objects(vector <ObjectModelMatrix*> objs){
    for(unsigned long i = 0; i < objs.size(); i++){
        objs[i]->draw();
    }
}

void create_geometric_objects()
{
    for (unsigned long i = 0; i < objects.size(); i++)
    {   
        ObjectModel object_model(objects[i]->get_path());
        ComputeNormals(&object_model);
        BuildTrianglesAndAddToVirtualScene(&object_model);
    }
}

void player_shoot(){

    number_of_missiles += 1;
    Missile* m = new Missile(MISSILE_ID, "missile", player->get_model()*ADJUST_MISSILE_POSITION);
    m->go_foward();
    objects.push_back(m);
}