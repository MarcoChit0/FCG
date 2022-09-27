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