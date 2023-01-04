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

float counter = 0;
void Renderer::draw(double &mouse_x, double &mouse_y){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 0.7f, 1.0f, 1);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glUseProgram(shader->get_program_id());
    world->get_player()->set_mouse_pos(mouse_x, mouse_y);
    world->get_player()->render(shader, game);
    world->render(texture);
}

Renderer::~Renderer(){
    delete world;
    delete shader;
}