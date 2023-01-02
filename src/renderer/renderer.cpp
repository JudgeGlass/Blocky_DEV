#include <renderer/renderer.hpp>

Renderer::Renderer(Blocky *game){
    this->game = game;
}

void Renderer::init(){
    std::vector<Block> blocks;
    blocks.push_back(Block(0, 0, 0, 0));
    blocks.push_back(Block(1, 0, 0, 0));
    blocks.push_back(Block(2, 0, 0, 0));
    blocks.push_back(Block(1, 1, 0, 0));
    blocks.push_back(Block(1, 2, 0, 0));
    blocks.push_back(Block(1, 3, 0, 0));
    blocks.push_back(Block(1, 4, 0, 0));

    chunk = new Chunk(0, 0, 16, 16, 255);
    

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

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    chunk->generate();
}

void Renderer::input(){
    const float cameraSpeed = 0.05f; // adjust accordingly
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

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)game->get_screen_width() / (float)game->get_screen_height(), 0.1f, 100.0f);
    // glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 rotation = glm::rotate(counter, glm::vec3(4, 0, 3));
    glm::mat4 model = glm::mat4(1.0f);
    // glm::mat4 mvp = projection * view * model * rotation;
    // GLuint matrixID = shader->get_uniform_location("MVP");
    // glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);
    
    // glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    // glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    // glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    // glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    // glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    // glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);


    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 MVP = projection * view * model;
    GLuint matrixID = shader->get_uniform_location("MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);


    glUseProgram(shader->get_program_id());
    counter += 0.02f;

    chunk->render(texture);
}

Renderer::~Renderer(){
    delete shader;
}