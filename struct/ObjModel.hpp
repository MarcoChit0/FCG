#ifndef OBJ_MODEL_HPP
#define OBJ_MODEL_HPP

#include <tiny_obj_loader.h>
#include <vector>
#include <iostream>

struct ObjModel
{
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;

    ObjModel(std::string filename, const char* basepath = NULL, bool triangulate = true)
    {
        std::cout << "Carregando modelo: " << filename << std::endl;
        const char* c_filename = filename.c_str();

        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, c_filename, basepath, triangulate);

        if (!err.empty())
            fprintf(stderr, "\n%s\n", err.c_str());

        if (!ret)
            throw std::runtime_error("Erro ao carregar modelo.");
        
        printf("OK.\n");
    }
};

#endif