#include <world/player.hpp>

#include <iostream>

Player::Player(glm::vec3 pos, World *world){
    camera_pos = pos;
    this->world = world;
}

void Player::render(Shader *shader){
    GLint viewport_data[4];
    glGetIntegerv(GL_VIEWPORT, viewport_data);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)viewport_data[2] / (float)viewport_data[3], 0.1f, 500.0f);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
    glm::mat4 MVP = projection * view * model ;//* r;
    
    GLuint matrixID = shader->get_uniform_location("MVP");
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

}

void Player::update(Blocky *game){
    input(game);

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
    else if(pitch < -89.0f)
        pitch = -89.0f;

    if(yaw > 360)
        yaw = 0;
    else if(yaw < 0)
        yaw = 360;

    if(first_mouse){
        last_x = mouse_x;
        last_y = mouse_y;
    }

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    std::cout << "DIRECTION: " << (yaw) << ", " << (pitch) << std::endl;
    float x, y, z;

    float l = 5;
    y = l * sin(glm::radians(pitch));
    float d = sqrt(l * l - y * y);
    z = d * sin(glm::radians(yaw));
    x =  d * cos(glm::radians(yaw));
    y += (camera_pos.y + 0.6f);
    z += camera_pos.z;
    x += camera_pos.x;
 
    std::cout << "X: " << (int)x % 16 << "\tY: " << y << "\tZ: " << (int)z % 16 << "\tCX: " << (int)x/16 << "\tCZ: " << (int)z/16<< std::endl;
    // for(Ray ray({camera_pos.x, camera_pos.y, camera_pos.z}, glm::normalize(direction)); ray.getLength() < 6; ray.step(0.05f, yaw, -pitch)){
    //     x = (int) ray.getEnd().x;
    //     y = (int) ray.getEnd().y;
    //     z = (int) ray.getEnd().z;

    //     //std::cout << "RX: " << x << "\tRY: " << y << "\tRZ: " << z << "\t\tPX: " << (int)camera_pos.x << "\tPY: " << (int)camera_pos.y << "\tPZ: " << (int)camera_pos.z << std::endl;

        

    // }

    if(glfwGetKey(game->get_window(), GLFW_KEY_F) == GLFW_PRESS){
            std::cout << "PRESSED F" << std::endl;
            
            world->get_chunk((int)(x / 16), (int)(z / 16))->set_block((int)x % 16, y, (int)z % 16, ID::STONE);

            world->get_chunk((int)(x / 16), (int)(z / 16))->rebuild_mesh();
            //break;
        }

    camera_front = glm::normalize(direction);
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