#include <game/blocky.hpp>

void glfw_error_callback(int error, const char *msg){
    std::string s;
    s = "[" + std::to_string(error) + "] " + msg + "\n";
    std::cerr << s << std::endl;
}

void glfw_window_size_callback(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

Blocky::Blocky(const int width, const int height){
    renderer = new Renderer(this);

    screen_width = width;
    screen_height = height;
}

void Blocky::init(){
    glewExperimental = true;
    glfwSetErrorCallback(glfw_error_callback);
    
    if(!glfwInit()){
        std::cerr << "Failed to init GLFW! Aborting..." << std::endl;
        glfwTerminate();
        exit(-1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screen_width, screen_height, "Blocky", NULL, NULL);
    if(window == NULL){
        std::cerr << "Failed to create OpenGL window! Aborting..." << std::endl;
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glewExperimental = true;

    if(glewInit() != GLEW_OK){
        std::cerr << "Failed to init GLEW! Aborting..." << std::endl;
        exit(-1);
    }

    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    renderer->init();
}

void Blocky::loop(){
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0){
        renderer->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    clean();
}

void Blocky::clean(){
    delete renderer;

    glfwTerminate();
}

int Blocky::get_screen_width() const {
    return screen_width;
}

int Blocky::get_screen_height() const {
    return screen_height;
}

Blocky::~Blocky(){
    clean();
}