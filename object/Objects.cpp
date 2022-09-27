#include "Objects.hpp"

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

// TODO: debug
void player_shoot(){
    Missile* missile = new Missile(MISSILE_ID, "missile", player->get_model());
    missile->adjust_position();
    missile->go_foward();
    objects.push_back(missile);
    number_of_missiles += 1;
}