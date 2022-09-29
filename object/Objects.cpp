#include "Objects.hpp"

using namespace std; 

void draw_objects(){
    for(unsigned long i = 0; i < objects.size(); i++){
        objects[i]->draw();
    }
}

void create_geometric_objects()
{
    for (unsigned long i = 0; i < objects.size(); i++)
    {   
        new_object_being_added_to_virtual_screen(objects[i]);
    }
}

void new_object_being_added_to_virtual_screen(ObjectModelMatrix* obj)
{
    ObjectModel object_model(obj->get_path());
    ComputeNormals(&object_model);
    BuildTrianglesAndAddToVirtualScene(&object_model); 
}

void player_shoot(){
    number_of_missiles += 1;
    Missile* m = new Missile(MISSILE_ID, "missile", player->get_model()*ADJUST_MISSILE_POSITION);
    m->go_foward();
    new_object_being_added_to_virtual_screen(m);
    objects.push_back(m);
}