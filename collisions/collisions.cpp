#include "collisions.hpp"

bool collision_cube_sphere(
        ObjectModelMatrix* cube_object,
        ObjectModelMatrix* sphere_object,
        glm::mat4 view,
        glm::mat4 projection
    )
{
    // recupera os pontos delimitadores da bounding box de ambos os objetos:
    glm::vec4 bbox_min_cube     =   glm::vec4(cube_object->get_bbox_min().x,cube_object->get_bbox_min().y,cube_object->get_bbox_min().z,1.0f);
    glm::vec4 bbox_max_cube     =   glm::vec4(cube_object->get_bbox_max().x,cube_object->get_bbox_max().y,cube_object->get_bbox_max().z,1.0f) ;
    glm::vec4 bbox_min_sphere   =   glm::vec4(sphere_object->get_bbox_min().x,sphere_object->get_bbox_min().y,sphere_object->get_bbox_min().z,1.0f) ;
    glm::vec4 bbox_max_sphere   =   glm::vec4(sphere_object->get_bbox_max().x,sphere_object->get_bbox_max().y,sphere_object->get_bbox_max().z,1.0f) ;

    // aplicar transformações mvp para as bounding box acompanharem os objetos no espaço.
    bbox_min_cube =     projection * view * cube_object->get_model() * bbox_min_cube;
    bbox_max_cube =     projection * view * cube_object->get_model() * bbox_max_cube;
    bbox_min_sphere =   projection * view * sphere_object->get_model() * bbox_min_sphere;
    bbox_max_sphere =   projection * view * sphere_object->get_model() * bbox_max_sphere;   

    // receuperar coordenadas específicas da esfera: centro e raio.
    glm::vec4 temp = (bbox_max_sphere + bbox_min_sphere);
    glm::vec4 sphere_center = glm::vec4(temp.x/2, temp.y/2, temp.z/2, 1.0f);
    float ray = length(bbox_max_sphere - sphere_center)/2;

    // recuperar pontos específicos do cubo: seus 8 vértices.
    float bbox_x[] = {bbox_min_cube.x, bbox_max_cube.x};
    float bbox_y[] = {bbox_min_cube.y, bbox_max_cube.y};
    float bbox_z[] = {bbox_min_cube.z, bbox_max_cube.z};
    glm::vec4 cube_point;
    glm::vec4 test_vector;

    //  para cada ponto p em 8 pontos do cubo:
    //      gerar vetor do ponto p ao centro da esfera
    //      calcular comprimento desse vetor
    //      se esse comprimento for menor que o do raio da esfera:
    //          houve colisão
    //  se não nenhum comprimento for menor do que o do raio da esfera, não colidiu    
    for (int z = 0; z < 2; z++){
        for (int y = 0; y < 2; y++){
            for (int x = 0; x < 2; x++){
                // ponto p
                cube_point = glm::vec4(bbox_x[x], bbox_y[y], bbox_z[z], 1.0f);
                // vetor do ponto p ao centro da esfera 
                test_vector = cube_point - sphere_center;
                if(length(test_vector)<ray){
                    // houve colisão por um dos pontos do cubo estar "tocando" no raio 
                    return true;
                }
            }   
        }       
    }
    return false;
}

void collision_handler(glm::mat4 view, glm::mat4 projection){
    if (collision_cube_sphere(player, asteroid, view, projection)){
        cout << "##################################################" << endl;
    }
}