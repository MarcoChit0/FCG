#include "ObjectModelMatrix.hpp"

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

vector<string> tokenize(string line, char delim){
    vector<string> tokens = {};
    stringstream ss_line(line);
    string temporary; 
    while(getline(ss_line, temporary, delim)){
        tokens.push_back(temporary);
    }
    return tokens;
}

string ObjectTypeToString(ObjectTypes type){
    switch (type)
    {
    case O_TYPE:
        return "o";
        break;
    case G_TYPE:
        return "g";
        break;
    case USEMTL_TYPE:
        return "usemtl";
        break;
    default:
        return NULL;
        break;
    }
}