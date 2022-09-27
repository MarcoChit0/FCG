#include "Objects.hpp"

void draw_objects(vector <ObjectModelMatrix*> objs){
    for(unsigned long i = 0; i < objs.size(); i++){
        objs[i]->draw();
    }
}

void create_geometric_object(ObjectModelMatrix* obj)
{
    ObjectModel object_model(obj->get_path());
    ComputeNormals(&object_model);
    BuildTrianglesAndAddToVirtualScene(&object_model);
}

void create_geometric_objects(vector<ObjectModelMatrix*> objs)
{
    for (unsigned long i = 0; i < objs.size(); i++)
    {
        create_geometric_object(objs[i]);
    }
}
