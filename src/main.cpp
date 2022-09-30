#include "main.hpp"

int main(int argc, char *argv[])
{
    GLFWwindow *window = initialize(argc, argv);

    while (!glfwWindowShouldClose(window))
    {
        frame(window);
    }
    glfwTerminate();
    return 0;
}

GLFWwindow *initialize(int argc, char *argv[])
{
    // Inicializamos a biblioteca GLFW, utilizada para criar uma janela do
    // sistema operacional, onde poderemos renderizar com OpenGL.
    int success = glfwInit();
    if (!success)
    {
        fprintf(stderr, "ERROR: glfwInit() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos o callback para impressão de erros da GLFW no terminal
    glfwSetErrorCallback(ErrorCallback);

    // Pedimos para utilizar OpenGL versão 3.3 (ou superior)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window;
    window = glfwCreateWindow(800, 600, window_title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        fprintf(stderr, "ERROR: glfwCreateWindow() failed.\n");
        std::exit(EXIT_FAILURE);
    }

    // Definimos as funções de callback
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetCursorPosCallback(window, CursorPosCallback);
    glfwSetScrollCallback(window, ScrollCallback);

    // Indicamos que as chamadas OpenGL deverão renderizar nesta janela
    glfwMakeContextCurrent(window);

    // Carregamento de todas funções definidas por OpenGL 3.3, utilizando a biblioteca GLAD.
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    // Função de callback de redimensionalização da janela
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    // Forçar resolução da janela
    FramebufferSizeCallback(window, 800, 600);

    // Imprimimos no terminal informações sobre a GPU do sistema
    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n",
           glGetString(GL_VENDOR),
           glGetString(GL_RENDERER),
           glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Carregamos os shaders de vértices e de fragmentos
    LoadShadersFromFiles();

    load_texture_images(texture_images);

    // Construímos a representação de objetos geométricos através de malhas de triângulos
    create_geometric_objects();

    if (argc > 1)
    {
        ObjectModel model(argv[1]);
        BuildTrianglesAndAddToVirtualScene(&model);
    }

    // Inicializamos o código para renderização de texto.
    TextRendering_Init();

    // Habilitamos o Z-buffer.
    glEnable(GL_DEPTH_TEST);

    // Habilitamos o Backface Culling.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    return window;
}

// Realiza as operações de rendeziração
void frame(GLFWwindow *window)
{
    // Definimos a cor do "fundo" do framebuffer como branco. 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //  "Pintamos" todos os pixels do framebuffer com a cor definida acima,
    //  e também resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo os shaders de vértice e fragmentos).
    glUseProgram(program_id);

    glm::mat4 view = create_view_matrix();
    glm::mat4 projection = create_projection_matrix();

    // Enviamos as matrizes "view" e "projection" para a GPU.
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

    draw_objects();

    collision_handler(view, projection);

    // Imprime dados na tela
    TextRendering_ShowEulerAngles(window);
    TextRendering_ShowProjection(window);
    TextRendering_ShowFramesPerSecond(window);
    glfwSwapBuffers(window);

    // Verificamos com o sistema operacional se houve alguma interação com o usuário
    glfwPollEvents();
}