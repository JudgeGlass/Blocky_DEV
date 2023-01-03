#include <renderer/renderer.hpp>

Renderer::Renderer(Blocky *game){
    this->game = game;
}

void Renderer::init(){
    world = new World(16, 16);

    shader = new Shader("vertex.shader", "fragment.shader");
    
    shader->load_shader();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Make Texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("atlas.png", &width, &height, &nrChannels, 0);
    if(!data){
        std::cout << "Failed to load texture" << std::endl;
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 

    GLfloat anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    world->generate();
}

void Renderer::input(){
    const float cameraSpeed = 0.5f; // adjust accordingly
    if (glfwGetKey(game->get_window(), GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(game->get_window(), GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(game->get_window(), GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(game->get_window(), GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if(glfwGetKey(game->get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if(glfwGetKey(game->get_window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraUp;
}

float counter = 0;
void Renderer::draw(){
    input();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 0.7f, 1.0f, 1);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)game->get_screen_width() / (float)game->get_screen_height(), 0.1f, 500.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 r = glm::rotate((float)-sin(counter) - (float) cos(counter), glm::vec3(0, 1, 0));
    glm::mat4 MVP = projection * view * model ;//* r;
    
    GLuint matrixID = shader->get_uniform_location("MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);


    glUseProgram(shader->get_program_id());
    //counter += 0.002f;

    world->render(texture);
}

Renderer::~Renderer(){
    delete world;
    delete shader;
}