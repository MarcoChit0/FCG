#ifndef UFO_HPP
#define UFO_HPP

#include "ObjectModelMatrix.hpp"
#define UFO_OBJ_PATH "../../data/ufo/UFO.obj"
#define UFO_STARTING_HIT_POINTS 5
#define CONTROL_POINTS_PER_BEZIER_CURVE 3
const float inicio_curva01 = 0.0f, fim_curva01 = 1.5f;
const float inicio_curva02 = 1.5f, fim_curva02 = 2.5f;
const float inicio_curva03 = 2.5f, fim_curva03 = 5.0f;
const float tempo_ciclo = 5.0f;
const float tempo_delay = 3.0f;

glm::vec4 pc_curva_01[] =
    {
        glm::vec4(-1.5f, 0.0f, -2.0f, 1.0f),
        glm::vec4(-0.30f, 0.5f, -2.0f, 1.0f),
        glm::vec4(-0.15f, 0.5f, -2.0f, 1.0f),
        glm::vec4(0.0f, 0.0f, -2.0f, 1.0f),
};

glm::vec4 pc_curva_02[] =
    {
        glm::vec4(0.0f, 0.0f, -2.0f, 1.0f),
        glm::vec4(0.5f, -0.5f, -2.0f, 1.0f),
        glm::vec4(1.0f, -0.5f, -2.0f, 1.0f),
        glm::vec4(1.5f, 0.0f, -2.0f, 1.0f),
};

glm::vec4 pc_curva_03[] =
    {
        glm::vec4(1.5f, 0.0f, -2.0f, 1.0f),
        glm::vec4(0.5f, 0.0f, -2.5f, 1.0f),
        glm::vec4(-0.5f, 0.0f, -2.5f, 1.0f),
        glm::vec4(-1.5f, 0.0f, -2.0f, 1.0f),
};

class UFO : public ComplexObjectModelMatrix
{
private:
    int life_points;
public:
    UFO(int id, string name, glm::mat4 model, vector<glm::mat4> transform) : ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH, transform)
    {
        this->life_points = UFO_STARTING_HIT_POINTS;
    }

    UFO(int id, string name, glm::mat4 model) : ComplexObjectModelMatrix(id, name, model, UFO_OBJ_PATH)
    {
        this->life_points = UFO_STARTING_HIT_POINTS;
    }

    void take_damage()
    {
        this->life_points -= 1;
        cout << "\n\n $$$$ UFO: " << this->life_points << " $$$$\n\n";
        if (this->life_points == 0)
        {
            player_won_the_game = true;
        }
    }

    glm::mat4 bezier_curves()
    {
        float current_time = glfwGetTime();
        glm::vec4 pontos_curva;
        float porcentagem_ciclo = current_time / (tempo_ciclo * tempo_delay);
        porcentagem_ciclo = porcentagem_ciclo - floor(porcentagem_ciclo); // [0,1]
        float seleciona_curva = porcentagem_ciclo * tempo_ciclo; // [0, tempo_ciclo]
        if (inicio_curva01 <= seleciona_curva && seleciona_curva <= fim_curva01)
        {
            float tempo_curva01 = (seleciona_curva - inicio_curva01) / (fim_curva01 - inicio_curva01);
            pontos_curva = curva_Bezier(CONTROL_POINTS_PER_BEZIER_CURVE, pc_curva_01, tempo_curva01);
        }
        if (inicio_curva02 <= seleciona_curva && seleciona_curva <= fim_curva02)
        {
            float tempo_curva02 = (seleciona_curva - inicio_curva02) / (fim_curva02 - inicio_curva02);
            pontos_curva = curva_Bezier(CONTROL_POINTS_PER_BEZIER_CURVE, pc_curva_02, tempo_curva02);
        }
        if (inicio_curva03 <= seleciona_curva && seleciona_curva <= fim_curva03)
        {
            float tempo_curva03 = (seleciona_curva - inicio_curva03) / (fim_curva03 - inicio_curva03);
            pontos_curva = curva_Bezier(CONTROL_POINTS_PER_BEZIER_CURVE, pc_curva_03, tempo_curva03);
        }
        float x_translation = this->get_model()[3].x;
        float y_translation = this->get_model()[3].y;
        float z_translation = this->get_model()[3].z;
        return Matrix_Translate(pontos_curva.x - x_translation, pontos_curva.y - y_translation, pontos_curva.z - z_translation);
    }

    void draw(){
        this->update_model(this->bezier_curves());
        ComplexObjectModelMatrix::draw();
    }
};
#endif