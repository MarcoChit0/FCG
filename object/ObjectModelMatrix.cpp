#include "ObjectModelMatrix.hpp"

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