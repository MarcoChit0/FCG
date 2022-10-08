#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define PLAYER_ID 0
#define MISSILE_ID 1
#define UFO_ID 2
#define COW_ID 3

uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Id referente ao material utilizado
uniform int material_name_uniform;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage6;
uniform sampler2D TextureImage7;
uniform sampler2D TextureImage8;
uniform sampler2D TextureImage9;


// ASTEROID TEXTURES:
uniform sampler2D TextureImage10;
uniform sampler2D TextureImage11;
uniform sampler2D TextureImage12;
uniform sampler2D TextureImage13;
uniform sampler2D TextureImage14;

// COW TEXTURES:
uniform sampler2D TextureImage15;

// MISSILE TEXTURES:
uniform sampler2D TextureImage16;

// PLAYER TEXTURES:
uniform sampler2D TextureImage17;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923


void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    
    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    
    /* Espectro da fonte de iluminação */
    vec3 I = vec3(1.0, 1, 1);
    /* Espectro da luz ambiente */
    vec3 Ia = vec3(1, 0.9, 0.9);

    vec4 lightPos = vec4(0.0, 100.0, 1.0, 1.0);
    vec4 lightDir = vec4(0.0, -1.0, 0.0, 0.0);
    vec4 l = normalize(lightPos - p);
    vec4 r = normalize(-l + 2*n*(dot(n, l)));

    vec4 h = normalize(l + v);


    vec3 Image_Kd, Image_Mettalic,
         Ks, Ka, lambert_diffuse, ambient, blinnPhong, diffuse, specular;

    //check in ObjectModelMatrix.hpp the ids

    /* UFO_Glass -- for more information, check ObjectModelMatrix.names_to_id */
    if(material_name_uniform == 1) {
        U = texcoords.x;
        V = texcoords.y;

        Image_Kd = texture(TextureImage8, vec2(U,V)).rgb;
        
        float q = 50.0;

        Ks = vec3(0.2, 0.2, 0.3);
        Ka = vec3(0.6, 0.6, 0.6);

        // Equação de Iluminação
        lambert_diffuse = Image_Kd * I * max(0,dot(n,l));
        ambient = Ka * Ia;
        blinnPhong = Ks * I * pow(max(0, dot(n, h)), q);

        color = lambert_diffuse + ambient + blinnPhong;

    } /* UFO_Metal -- for more information, check ObjectModelMatrix.names_to_id */
    else if(material_name_uniform == 2) {
        U = texcoords.x;
        V = texcoords.y;

        Image_Kd = texture(TextureImage8, vec2(U,V)).rgb;
        Image_Mettalic = texture(TextureImage7, vec2(U,V)).rgb;

        Ks = vec3(0.15, 0.15, 0.15);
        Ka = vec3(0.1, 0.1, 0.1);

        diffuse = Image_Kd * I * max(0,dot(n,l));
        ambient = Ka * Ia;
        specular = Ks * I * pow(max(0, dot(n, h)), 30.0);
    
        color = diffuse + ambient + specular;
        color += Image_Mettalic * 0.1;
        
    }  
    /* missile -- for more information, check ObjectModelMatrix.names_to_id */
    else if(material_name_uniform == 5){
        U = texcoords.x;
        V = texcoords.y;
        
        Image_Kd = texture(TextureImage11, vec2(U, V)).rgb;

        diffuse = Image_Kd * I * (max(0,dot(n,l)) + 0.01);
        color = diffuse;
    } /* player -- for more information, check ObjectModelMatrix.names_to_id */
    else if (material_name_uniform == 6 || material_name_uniform == 7 || 
            material_name_uniform == 8 || material_name_uniform == 9 
            ){
        // ponto central da esfera
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        // raio da esfera
        float ray = bbox_max.y - bbox_center.y;
        // ponto p'
        vec4 point_p = bbox_center + ray * normalize(position_model - bbox_center);
        // vetor p
        vec4 vec_p = point_p - bbox_center;
        // ang. theta
        float theta = atan(vec_p.x, vec_p.z);
        // ang. phi
        float phi = asin(vec_p.y/ ray);
        // coor. textura U
        U = (theta + M_PI)/(2*M_PI);
        // coor. textura V
        V = (phi + M_PI_2)/M_PI;

        Ks = vec3(0.4, 0.4, 0.4);
        Ka = vec3(0.1, 0.1, 0.1 );
        float q = 45.0;

        Image_Kd = texture(TextureImage14, vec2(U,V)).rgb;

        lambert_diffuse = Image_Kd * I * max(0,dot(n,l)+0.01);
        ambient = Ka * Ia;
        blinnPhong = Ks * I * pow(max(0, dot(n, h)), q);

        color = lambert_diffuse + ambient + blinnPhong;
        
        
    } /* cow -- for more information, check ObjectModelMatrix.names_to_id */
    else if(
        material_name_uniform == 10
        || material_name_uniform == 11
        || material_name_uniform == 12
        || material_name_uniform == 13
        ){
            U = texcoords.x;
            V = texcoords.y;
            
            Image_Kd = texture(TextureImage10, vec2(U, V)).rgb;

            diffuse = Image_Kd * I * (max(0,dot(n,l)) + 0.01);

            color = diffuse;
    } else if(material_name_uniform == 14) { // asteroid
        U = texcoords.x;
        V = texcoords.y;

        Image_Kd = texture(TextureImage9, vec2(U, V)).rgb;
        Image_Mettalic = texture(TextureImage13, vec2(U, V)).rgb;

        diffuse = Image_Kd * I * (max(0,dot(n,l)) + 0.01);
        
        color.rgb = diffuse;

        diffuse = Image_Mettalic * I * (max(0,dot(n,l)) + 0.01);

        color.rgb += Image_Mettalic;
        
    }
    else {
        // ponto central da esfera
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;
        // raio da esfera
        float ray = bbox_max.y - bbox_center.y;
        // ponto p'
        vec4 point_p = bbox_center + ray * normalize(position_model - bbox_center);
        // vetor p
        vec4 vec_p = point_p - bbox_center;
        // ang. theta
        float theta = atan(vec_p.x, vec_p.z);
        // ang. phi
        float phi = asin(vec_p.y/ ray);
        // coor. textura U
        U = (theta + M_PI)/(2*M_PI);
        // coor. textura V
        V = (phi + M_PI_2)/M_PI;


        Ks = vec3(0.4, 0.4, 0.4);
        Ka = vec3(0.1, 0.1, 0.1 );
        float q = 45.0;

        Image_Kd = texture(TextureImage14, vec2(U,V)).rgb;


        lambert_diffuse = Image_Kd * I * max(0,dot(n,l)+0.01);
        ambient = Ka * Ia;
        blinnPhong = Ks * I * pow(max(0, dot(n, h)), q);

        color = lambert_diffuse + ambient + blinnPhong;
    }
}

