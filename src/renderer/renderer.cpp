#include <renderer/renderer.hpp>

Renderer::Renderer(Blocky *game){
    this->game = game;
}

void Renderer::init(){
    shader = new Shader("vertex.shader", "fragment.shader");
    
    shader->load_shader();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //Make VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // USE VAO

    // Make VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 108, vertex_buffer, GL_STATIC_DRAW); // Give VBO data

    glGenBuffers(1, &CBO);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 108, color_buffer, GL_STATIC_DRAW); // Give CBO data
}

void Renderer::draw(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)game->get_screen_width() / (float)game->get_screen_height(), 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(4, 3, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 rotation = glm::rotate(0.0f, glm::vec3(4, 3, 3));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 mvp = projection * view * model ;//* rotation;
    GLuint matrixID = shader->get_uniform_location("MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvp[0][0]);

    glUseProgram(shader->get_program_id());
    glEnableVertexAttribArray(0);

    // Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    // Color data
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glDrawArrays(GL_TRIANGLES, 0, 108 / 3);
    glDisableVertexAttribArray(0);
}

Renderer::~Renderer(){
    delete shader;
}