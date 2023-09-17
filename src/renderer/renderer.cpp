#include <renderer/renderer.hpp>

Renderer::Renderer(Blocky *game){
    this->game = game;
}

void Renderer::init(){
    world = new World(16, 16);

    hud = new HUD(std::shared_ptr<Player>(world->get_player()));

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(game->get_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    shader = new Shader("../resources/shaders/vertex.glsl", "../resources/shaders/fragment.glsl");
    
    shader->load_shader();


    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Make Texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("../resources/textures/atlas.png", &width, &height, &nrChannels, 0);
    if(!data){
        std::cout << "Failed to load texture" << std::endl;
    }

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    GLfloat anisotropy;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisotropy);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    world->generate();
    glfwSetInputMode(game->get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

float counter = 0;
void Renderer::draw(){
    current_time = glfwGetTime();
    delta = current_time - last_time;
    last_time = current_time;

    hud->render(delta);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 0.7f, 1.0f, 1);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glUseProgram(shader->get_program_id());
    
    world->get_player()->render(shader);
    world->render(texture);
    world->render_transparent(texture);

    glUseProgram(0);
}

void Renderer::update(double &mouse_x, double &mouse_y){
    world->get_player()->set_mouse_pos(mouse_x, mouse_y);
    world->get_player()->update(game, delta);
}

GLuint Renderer::get_texture() {
    return texture;
}

Renderer::~Renderer(){
    delete world;
    delete shader;
}