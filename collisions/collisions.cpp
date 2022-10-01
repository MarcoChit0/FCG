#include "collisions.hpp"

bool collision_cube_sphere(ObjectModelMatrix* cube_object,ObjectModelMatrix* sphere_object)
{
    // recupera os pontos delimitadores da bounding box de ambos os objetos:
    glm::vec4 bbox_min_cube     =   glm::vec4(cube_object->get_bbox_min().x,cube_object->get_bbox_min().y,cube_object->get_bbox_min().z,1.0f);
    glm::vec4 bbox_max_cube     =   glm::vec4(cube_object->get_bbox_max().x,cube_object->get_bbox_max().y,cube_object->get_bbox_max().z,1.0f) ;
    glm::vec4 bbox_min_sphere   =   glm::vec4(sphere_object->get_bbox_min().x,sphere_object->get_bbox_min().y,sphere_object->get_bbox_min().z,1.0f) ;
    glm::vec4 bbox_max_sphere   =   glm::vec4(sphere_object->get_bbox_max().x,sphere_object->get_bbox_max().y,sphere_object->get_bbox_max().z,1.0f) ;

    //cout << "\n\nmax: "<<to_string(bbox_max_sphere) << endl;
    //cout << "min: "<<to_string(bbox_min_sphere) << endl;
    //cout << "raio deles: " << length(bbox_max_sphere - bbox_min_sphere)/2 << endl;

    // aplicar transformações model para as bounding box acompanharem os objetos no espaço.
    bbox_min_cube =      cube_object->get_model() * bbox_min_cube;
    bbox_max_cube =      cube_object->get_model() * bbox_max_cube;
    bbox_min_sphere =    sphere_object->get_model() * bbox_min_sphere;
    bbox_max_sphere =    sphere_object->get_model() * bbox_max_sphere;   


    // receuperar coordenadas específicas da esfera: centro e raio.
    glm::vec4 temp = (bbox_max_sphere + bbox_min_sphere);
    glm::vec4 sphere_center = glm::vec4(temp.x/2, temp.y/2, temp.z/2, 1.0f);
    float ray = length(bbox_max_sphere - sphere_center);
    

    // recuperar pontos específicos do cubo: seus 8 vértices.
    float bbox_x[] = {bbox_min_cube.x, (bbox_min_cube.x + bbox_max_cube.x)/2, bbox_max_cube.x};
    float bbox_y[] = {bbox_min_cube.y, (bbox_min_cube.y + bbox_max_cube.y)/2,bbox_max_cube.y};
    float bbox_z[] = {bbox_min_cube.z, (bbox_min_cube.z + bbox_max_cube.z)/2, bbox_max_cube.z};
    glm::vec4 cube_point;
    glm::vec4 test_vector;

    //cout << "\n#############################\n";
    //  para cada ponto p em 8 pontos do cubo:
    //      gerar vetor do ponto p ao centro da esfera
    //      calcular comprimento desse vetor
    //      se esse comprimento for menor que o do raio da esfera:
    //          houve colisão
    //  se não nenhum comprimento for menor do que o do raio da esfera, não colidiu    
    for (int z = 0; z < 3; z++){
        for (int y = 0; y < 3; y++){
            for (int x = 0; x < 3; x++){
                // ponto p
                cube_point = glm::vec4(bbox_x[x], bbox_y[y], bbox_z[z], 1.0f);
                // vetor do ponto p ao centro da esfera 
                test_vector = cube_point - sphere_center;
                //cout << "\n--------------------\n";
                //cout << "cube point: " << to_string(cube_point) << endl;
                //cout << "bbox_max_sphere: " << to_string(bbox_max_sphere) << endl;
                //cout << "sphere center: " << to_string(sphere_center) << endl;
                //cout << "length(test_vector): " << length(test_vector)<< endl;
                //cout << "ray: " << ray << endl;
                if(length(test_vector)<ray){
                    // houve colisão por um dos pontos do cubo estar "tocando" no raio 
                    return true;
                }
            }   
        }       
    }
    return false;
}

void collision_handler(){
    for(unsigned long i = 0; i < objects.size(); i++){
        // MISSILE HITS COW
        if (objects[i]->get_id() == MISSILE_ID && collision_cube_cylinder(cow, objects[i])){
           collided_missile_cow(objects[i], i);
           return;
        }        
        // MISSILE HITS UFO
        if (objects[i]->get_id() == MISSILE_ID && collision_cube_cylinder(ufo, objects[i])){
           collided_missile_ufo(objects[i], i);
           return;
        }
        // MISSILE HITS ASTEROID
        if (objects[i]->get_id() == MISSILE_ID){
            for(unsigned long j = i; j < objects.size(); j++){
                if (objects[j]->get_id() == ASTEROID_ID && collision_cylinder_sphere(objects[i], objects[j])){
                    collided_missile_asteroid(objects[i], i, objects[j], j);
                    return;
                }
            }
        }
        // ASTEROID HITS MISSILE
        if (objects[i]->get_id() == ASTEROID_ID){
            for(unsigned long j = i; j < objects.size(); j++){
                if (objects[j]->get_id() == MISSILE_ID && collision_cylinder_sphere(objects[j], objects[i])){
                    collided_asteroid_missile(objects[i], i, objects[j], j);
                    return;
                }
            }
        }
        // ASTEROID HITS PLAYER
        if (objects[i]->get_id() == ASTEROID_ID && collision_cube_sphere(player, objects[i])){
            collided_player_asteroid(objects[i], i);
            return;
        }
    }
}

bool collision_cube_cylinder(ObjectModelMatrix* cube_object,ObjectModelMatrix* cylinder_object)
{
    // recupera os pontos delimitadores da bounding box de ambos os objetos:
    glm::vec4 bbox_min_cube     =   glm::vec4(cube_object->get_bbox_min().x,cube_object->get_bbox_min().y,cube_object->get_bbox_min().z,1.0f);
    glm::vec4 bbox_max_cube     =   glm::vec4(cube_object->get_bbox_max().x,cube_object->get_bbox_max().y,cube_object->get_bbox_max().z,1.0f) ;
    glm::vec4 bbox_min_cylinder =   glm::vec4(cylinder_object->get_bbox_min().x,cylinder_object->get_bbox_min().y,cylinder_object->get_bbox_min().z,1.0f) ;
    glm::vec4 bbox_max_cylinder =   glm::vec4(cylinder_object->get_bbox_max().x,cylinder_object->get_bbox_max().y,cylinder_object->get_bbox_max().z,1.0f) ;

    // aplicar transformações model para as bounding box acompanharem os objetos no espaço.
    bbox_min_cube =         cube_object->get_model() * bbox_min_cube;
    bbox_max_cube =         cube_object->get_model() * bbox_max_cube;
    bbox_min_cylinder =     cylinder_object->get_model() * bbox_min_cylinder;
    bbox_max_cylinder =     cylinder_object->get_model() * bbox_max_cylinder;   

    // recupera os pontos sobre os quais o eixo y do cilindro está estabelecido. Recupera tbm o raio do circulo da base do cilindro.
    glm::vec2 pmax_circulo_base_cilindro = glm::vec2(bbox_max_cylinder.x, bbox_max_cylinder.z);
    glm::vec2 pmin_circulo_base_cilindro = glm::vec2(bbox_min_cylinder.x, bbox_min_cylinder.z);
    float raio = length(pmax_circulo_base_cilindro - pmin_circulo_base_cilindro)/2;
    glm::vec4 pmax_cilindro = glm::vec4(
        (pmax_circulo_base_cilindro.x + pmin_circulo_base_cilindro.x)/2,
        bbox_max_cylinder.y,
        (pmax_circulo_base_cilindro.y + pmin_circulo_base_cilindro.y)/2, // coord[z]
        1.0f);
    glm::vec4 pmin_cilindro = glm::vec4(
        (pmax_circulo_base_cilindro.x + pmin_circulo_base_cilindro.x)/2,
        bbox_min_cylinder.y,
        (pmax_circulo_base_cilindro.y + pmin_circulo_base_cilindro.y)/2, // coord[z]
        1.0f);

    // componentes x e z do circulo dianteiro
    float pmax_cilindro_x_positions[] = {pmax_cilindro.x - raio, pmax_cilindro.x, pmax_cilindro.x + raio};
    float pmax_cilindro_z_positions[] = {pmax_cilindro.z - raio, pmax_cilindro.z, pmax_cilindro.z + raio};
    // componentes x e z do circulo trasiero 
    float pmin_cilindro_x_positions[] = {pmin_cilindro.x - raio, pmin_cilindro.x, pmin_cilindro.x + raio};
    float pmin_cilindro_z_positions[] = {pmin_cilindro.z - raio, pmin_cilindro.z, pmin_cilindro.z + raio};
    if(pmax_cilindro.y>=bbox_min_cube.y){
        for(int z = 0; z < 3; z++){
            for(int x = 0; x <3; x++){
                if(
                    // verifica se x e z do circulo dianteiro entram em contato com o cubo, i.e., se eles pertencem aos intervalos do cubo
                    ((bbox_min_cube.x <= pmax_cilindro_x_positions[x] && pmax_cilindro_x_positions[x] <= bbox_max_cube.x) &&
                    (bbox_min_cube.z <= pmax_cilindro_z_positions[z] && pmax_cilindro_z_positions[z] <= bbox_max_cube.z))
                    ||
                    // verifica se x e z do circulo traseiro entram em contato com o cubo, i.e., se eles pertencem aos intervalos do cubo
                    (
                        // para isso, o circulo trasiero precisa ter passado do intervalo y do cubo
                        (pmin_cilindro.y>=bbox_min_cube.y)
                        &&
                        // também, x e y precisam pertencer aos intervalos do cubo
                        ((bbox_min_cube.x <= pmin_cilindro_x_positions[x] && pmin_cilindro_x_positions[x] <= bbox_max_cube.x) &&
                        (bbox_min_cube.z <= pmin_cilindro_z_positions[z] && pmin_cilindro_z_positions[z] <= bbox_max_cube.z))
                    )
                )
                return true;
            }
        }
    }
    return false;
}

bool collision_cylinder_sphere(ObjectModelMatrix* cylinder_object,ObjectModelMatrix* sphere_object){
    // recupera as bbox.
    glm::vec4 bbox_min_cylinder =   glm::vec4(cylinder_object->get_bbox_min().x,cylinder_object->get_bbox_min().y,cylinder_object->get_bbox_min().z,1.0f) ;
    glm::vec4 bbox_max_cylinder =   glm::vec4(cylinder_object->get_bbox_max().x,cylinder_object->get_bbox_max().y,cylinder_object->get_bbox_max().z,1.0f) ;
    glm::vec4 bbox_min_sphere   =   glm::vec4(sphere_object->get_bbox_min().x,sphere_object->get_bbox_min().y,sphere_object->get_bbox_min().z,1.0f) ;
    glm::vec4 bbox_max_sphere   =   glm::vec4(sphere_object->get_bbox_max().x,sphere_object->get_bbox_max().y,sphere_object->get_bbox_max().z,1.0f) ;

    // aplica as mesmas transformações que os objetos sofreram sobre as suas respectivas bbox.
    bbox_min_cylinder =     cylinder_object->get_model() * bbox_min_cylinder;
    bbox_max_cylinder =     cylinder_object->get_model() * bbox_max_cylinder;
    bbox_min_sphere =       sphere_object->get_model() * bbox_min_sphere;
    bbox_max_sphere =       sphere_object->get_model() * bbox_max_sphere;   

    // recupera raio e centro da esfera.
    glm::vec4 temp = (bbox_max_sphere + bbox_min_sphere);
    glm::vec4 sphere_center = glm::vec4(temp.x/2, temp.y/2, temp.z/2, 1.0f);
    float ray = length(bbox_max_sphere - sphere_center)/2;

    // recupera centros dos circulos (de baixo e de cima) do cilindro.
    glm::vec2 pmax_circulo_base_cilindro = glm::vec2(bbox_max_cylinder.x, bbox_max_cylinder.z);
    glm::vec2 pmin_circulo_base_cilindro = glm::vec2(bbox_min_cylinder.x, bbox_min_cylinder.z);
    float raio = length(pmax_circulo_base_cilindro - pmin_circulo_base_cilindro)/2;
    // centro do circulo de cima.
    glm::vec4 pmax_cilindro = glm::vec4(
        (pmax_circulo_base_cilindro.x + pmin_circulo_base_cilindro.x)/2,
        bbox_max_cylinder.y,
        (pmax_circulo_base_cilindro.y + pmin_circulo_base_cilindro.y)/2, // coord[z]
        1.0f);
    // centro do circulo de baixo.
    glm::vec4 pmin_cilindro = glm::vec4(
        (pmax_circulo_base_cilindro.x + pmin_circulo_base_cilindro.x)/2,
        bbox_min_cylinder.y,
        (pmax_circulo_base_cilindro.y + pmin_circulo_base_cilindro.y)/2, // coord[z]
        1.0f);

    // posições de x e de z do circulo de cima do cilindro.
    float pmax_cilindro_x_positions[] = {pmax_cilindro.x - raio, pmax_cilindro.x, pmax_cilindro.x + raio};
    float pmax_cilindro_z_positions[] = {pmax_cilindro.z - raio, pmax_cilindro.z, pmax_cilindro.z + raio};
    // posições de x e de z do circulo de baixo do cilindro.
    float pmin_cilindro_x_positions[] = {pmin_cilindro.x - raio, pmin_cilindro.x, pmin_cilindro.x + raio};
    float pmin_cilindro_z_positions[] = {pmin_cilindro.z - raio, pmin_cilindro.z, pmin_cilindro.z + raio};

    glm::vec4 cylinder_point;
    glm::vec4 test_vector;
    // testa colisão do cirulo de cima com a esfera.
    if(pmax_cilindro.y>= bbox_min_sphere.y){
        for(int z = 0; z < 3; z++){
            for(int x = 0; x <3; x++){
                cylinder_point = glm::vec4(pmax_cilindro_x_positions[x],pmax_cilindro.y,pmax_cilindro_z_positions[z], 1.0f);
                test_vector = cylinder_point - sphere_center;
                if(length(test_vector)<ray){
                    return true;
                }
            }
        }
    }
    // testa colisão do circulo de baixo com a esfera.
    if(pmin_cilindro.y>= bbox_min_sphere.y){
        for(int z = 0; z < 3; z++){
            for(int x = 0; x <3; x++){
                cylinder_point = glm::vec4(pmin_cilindro_x_positions[x],pmin_cilindro.y,pmin_cilindro_z_positions[z], 1.0f);
                test_vector = cylinder_point - sphere_center;
                if(length(test_vector)<ray){
                    return true;
                }
            }
        }
    }
    return false;
}

void collided_player_asteroid(ObjectModelMatrix* a, int a_pos){
    objects.erase(objects.begin()+a_pos);
    delete a;
    player->take_damage();
}

void collided_missile_asteroid(ObjectModelMatrix* m, int m_pos, ObjectModelMatrix* a, int a_pos){
    objects.erase(objects.begin()+a_pos);
    objects.erase(objects.begin()+m_pos);
    delete a;
    delete m;
}

void collided_asteroid_missile(ObjectModelMatrix* a, int a_pos, ObjectModelMatrix* m, int m_pos){
    objects.erase(objects.begin()+m_pos);
    objects.erase(objects.begin()+a_pos);
    delete m;
    delete a;
}

void collided_missile_ufo(ObjectModelMatrix* m, int m_pos){
    objects.erase(objects.begin()+m_pos);
    delete m;
    ufo->take_damage();
};

void collided_missile_cow(ObjectModelMatrix* m, int m_pos){
    objects.erase(objects.begin()+m_pos);
    delete m;
    cow->take_damage();
}