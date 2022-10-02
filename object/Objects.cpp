#include "Objects.hpp"

using namespace std; 

void draw_objects(){
    for(unsigned long i = 0; i < objects.size(); i++){
        if(objects[i]->get_id() == COW_ID){
            cow->bind_to_ufo(ufo->get_model());
        }
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
    obj->recover_bbox();
}

void player_shoot(){
    float current_time = glfwGetTime();
    if(current_time>=time_last_missile_created+COOLDOWN_MISSILE_TIME){
        number_of_missiles += 1;
        Missile* m = new Missile(MISSILE_ID, "missile", player->get_model()*ADJUST_MISSILE_POSITION);
        m->go_foward();
        new_object_being_added_to_virtual_screen(m);
        objects.push_back(m);
        time_last_missile_created = glfwGetTime();        
    }
}

void ufo_throws_asteroid(float current_time){
    if (current_time>=(time_last_asteroid_created+COOLDOWN_ASTEROID_TIME)){
        number_of_asteroids += 1;
        Asteroid* a = new Asteroid(ASTEROID_ID, "asteroid", ufo->get_model()*ADJUST_ASTEROID_SIZE);
        // a->go_backward_with_rotation();
        a->go_backward();
        new_object_being_added_to_virtual_screen(a);
        objects.push_back(a);
        time_last_asteroid_created = glfwGetTime();
    }
}