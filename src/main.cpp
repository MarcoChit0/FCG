#include "main.hpp"

int main(int argc, char *argv[])
{
    srand(time(0));

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
    window = glfwCreateWindow(1600, 1200, window_title, NULL, NULL);
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
    FramebufferSizeCallback(window, 1600, 1200);

    // Imprimimos no terminal informações sobre a GPU do sistema
    printf("GPU: %s, %s, OpenGL %s, GLSL %s\n",
           glGetString(GL_VENDOR),
           glGetString(GL_RENDERER),
           glGetString(GL_VERSION),
           glGetString(GL_SHADING_LANGUAGE_VERSION));

    // Carregamos os shaders de vértices e de fragmentos
    LoadShadersFromFiles();

    skyboxshader = new Shader("/home/bervig/Documents/UFRGS/Quinto Semestre/Fundamentos de Computação Gráfica/FCG/src/skybox_vertex.vs",
     "/home/bervig/Documents/UFRGS/Quinto Semestre/Fundamentos de Computação Gráfica/FCG/src/skybox_fragment.fs");  
   
    cubemapTexture = loadCubemap(cube_map_faces);
    load_texture_images(texture_images);
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

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
    update_timer();

    // Definimos a cor do "fundo" do framebuffer como branco. 
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    //  "Pintamos" todos os pixels do framebuffer com a cor definida acima,
    //  e também resetamos todos os pixels do Z-buffer (depth buffer).
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(using_free_camera){
        free_camera();
    }
    else{
        lookat_camera();
    }

    //position glm::vec3(0.0f, 0.0f, 0.0f), front: glm::vec3(0.0f, 0.0f, -1.0f)
    //up
   /*glm::mat4 view = glm::mat4(glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
 */ glm::mat4 view = create_view_matrix();
    glm::mat4 projection = create_projection_matrix();
    

    // Pedimos para a GPU utilizar o programa de GPU criado acima (contendo os shaders de vértice e fragmentos).
    glUseProgram(program_id);

    // Enviamos as matrizes "view" e "projection" para a GPU.
    glUniformMatrix4fv(view_uniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, glm::value_ptr(projection));

    ufo_throws_asteroid();
    draw_objects();
    collision_handler();
    game_logic();

    //glUseProgram(program_id2);
    skyboxshader->use();
    skyboxshader->setInt("skybox", 0);

    // draw skybox as last
    glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
    skyboxshader->use();
    skyboxshader->setMat4("view", view);
    skyboxshader->setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default


    // Imprime dados na tela
    TextRendering_ShowProjection(window);
    TextRendering_ShowFramesPerSecond(window);
    glfwSwapBuffers(window);

    // Verificamos com o sistema operacional se houve alguma interação com o usuário
    glfwPollEvents();
}

