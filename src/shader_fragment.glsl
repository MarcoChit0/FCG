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
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

vec3 get_ilummination(vec3 Kd0, vec3 Ka, vec3 Ks, vec3 I, vec3 Ia, float q, vec4 n, vec4 h, vec4 l) {   
    vec3 lambert_diffuse, ambient, blinnPhong;
    // Equação de Iluminação
    lambert_diffuse = Kd0 * I * max(0,dot(n,l));

    ambient = Ka * Ia;
    //vec3 phong = Ks * I * pow(max(0, dot(r, v)), q);
    blinnPhong = Ks * I * pow(max(0, dot(n, h)), q);

    return lambert_diffuse + ambient + blinnPhong;
}

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


     /* Iluminação */

    /* Espectro da fonte de iluminação */
    vec3 I = vec3(1.0, 1.0, 1.0);
    /* Espectro da luz ambiente */
    vec3 Ia = vec3(0.6, 0.6, 0.6);

    vec4 lightPos = vec4(0.0, 100.0, 1.0, 1.0);
    vec4 lightDir = vec4(0.0, -1.0, 0.0, 0.0);
    vec4 l = normalize(lightPos - p);
    vec4 r = normalize(-l + 2*n*(dot(n, l)));


    //Vetor usado para iluminação de Blinn-Phong
    vec4 h = normalize(l + v);


    vec3 Kd0, Image_Kd, Image_Ns, Image_Mettalic,
         Ks, Ka, lambert_diffuse, ambient, blinnPhong, diffuse, specular;

    //check in ObjectModelMatrix.hpp the ids

    //object_id == 2 UFO_metal
    if(material_name_uniform == 2) {
        U = texcoords.x;
        V = texcoords.y;

        
        Image_Kd = texture(TextureImage0, vec2(U,V)).rgb;
        Image_Ns = texture(TextureImage1, vec2(U,V)).rgb;
        Image_Mettalic = texture(TextureImage1, vec2(U,V)).rgb;


        Ks = vec3(0.15, 0.15, 0.15);
        Ka = vec3(0.5, 0.5, 0.5);

        diffuse = Image_Kd * I * max(0,dot(n,l));
        ambient = Ka * Ia;
        specular = Ks * I * pow(max(0, dot(n, h)), 20.0);
    
        color = diffuse + ambient + specular;
        color += Image_Mettalic *0.1;

    } else {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        float rho = length(position_model - bbox_center);
        float theta = atan(position_model.x, position_model.z);
        float phi = asin(position_model.y / rho);

        U = (theta + M_PI) / (2 * M_PI);
        V = (phi + M_PI_2) / M_PI;


        Kd0 = texture(TextureImage3, vec2(U,V)).rgb;
        
        float q = 20.0;

        /* Refletancia especular */
        Ks = vec3(0.2, 0.2, 0.3);
        /* Refletancia ambiente */
        Ka = vec3(0.4, 0.4, 0.4);

        // Equação de Iluminação
        lambert_diffuse = Kd0 * I * max(0,dot(n,l));
        ambient = Ka * Ia;
        blinnPhong = Ks * I * pow(max(0, dot(n, h)), q);

        color = lambert_diffuse + ambient + blinnPhong;

        
        color = pow(color, vec3(1.0,1.0,1.0)/1.2);
    }
   
    
} 

