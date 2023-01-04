#include <world/player.hpp>

#include <iostream>

Player::Player(glm::vec3 pos){
    camera_pos = pos;
    
}

void Player::render(Shader *shader, Blocky *game){
    input(game);

    std::cout << "MX: " << mouse_x << "\tMY: " << mouse_y << std::endl;
    float x_offset = mouse_x - last_x;
    float y_offset = last_y - mouse_y;
    last_x = mouse_x;
    last_y = mouse_y;

    const float sensitivity = 0.1f;
    x_offset *= sensitivity;
    y_offset *= sensitivity;

    yaw += x_offset;
    pitch += y_offset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    if(first_mouse){
        last_x = mouse_x;
        last_y = mouse_y;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front = glm::normalize(direction);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)game->get_screen_width() / (float)game->get_screen_height(), 0.1f, 500.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    //glm::mat4 r = glm::rotate((float)-sin(counter) - (float) cos(counter), glm::vec3(0, 1, 0));
    glm::mat4 MVP = projection * view * model ;//* r;
    
    GLuint matrixID = shader->get_uniform_location("MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

}

void Player::input(Blocky *game){
    const float camera_speed = 0.5f; // adjust accordingly
    if (glfwGetKey(game->get_window(), GLFW_KEY_W) == GLFW_PRESS)
        camera_pos += camera_speed * camera_front;
    if (glfwGetKey(game->get_window(), GLFW_KEY_S) == GLFW_PRESS)
        camera_pos -= camera_speed * camera_front;
    if (glfwGetKey(game->get_window(), GLFW_KEY_A) == GLFW_PRESS)
        camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
    if (glfwGetKey(game->get_window(), GLFW_KEY_D) == GLFW_PRESS)
        camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * camera_speed;
    if(glfwGetKey(game->get_window(), GLFW_KEY_SPACE) == GLFW_PRESS)
        camera_pos += camera_speed * camera_up;
    if(glfwGetKey(game->get_window(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera_pos -= camera_speed * camera_up;
}

void Player::set_mouse_pos(const double x, const double y){
    mouse_x = x;
    mouse_y = y;
}