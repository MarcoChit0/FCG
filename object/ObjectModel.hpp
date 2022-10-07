#ifndef OBJ_MODEL_HPP
#define OBJ_MODEL_HPP

#include <tiny_obj_loader.h>
#include <vector>
#include <iostream>

// Estrutura responsável por ler o arquivo '.obj' e carregar o modelo armazenado no arquivo.
struct ObjectModel
{
    tinyobj::attrib_t                 attrib;
    std::vector<tinyobj::shape_t>     shapes;
    std::vector<tinyobj::material_t>  materials;

    ObjectModel(std::string filename, const char* mtl_basepath = NULL, bool triangulate = true)
    {
        std::cout << "Carregando modelo: " << filename << std::endl;
        const char* c_filename = filename.c_str();

        const char *mtl_basepath2 = "../../data/mtls/";

        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, c_filename, mtl_basepath2, triangulate);

        if (!err.empty())
            fprintf(stderr, "\n%s\n", err.c_str());

        if (!ret)
            throw std::runtime_error("Erro ao carregar modelo.");
        
        printf("OK.\n");
    }
};


#endif