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

void Player::update(Blocky *game, double delta){
    input(game, delta);

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
 
    glm::vec3 last_pos;

    click_sleep += delta;
    //std::cout << "DELTA: " << delta * 1000 << "\tSLEEP: " << click_sleep << std::endl;

    for(Ray ray(glm::vec3(camera_pos.x, camera_pos.y + 0.5f, camera_pos.z), yaw, pitch); ray.get_length() < 6; ray.step(0.05f)){
        float x = ray.get_end().x;
        float y = ray.get_end().y;
        float z = ray.get_end().z;

        int cx = (int) (x / 16);
        int cz = (int) (z / 16);

        if(cx < 0 || cz < 0 || cx > 15 || cz > 15) break;

        int xx = (int) x % 16;
        int yy = (int) y;
        int zz = (int) z % 16;

        Block b = *world->get_chunk(cx, cz)->get_block(xx, yy, zz);
       // std::cout << "BLOCK: " << std::to_string(b.get_type()) << "\tL: " << (int)b.get_light() << "\tSKY: " << std::to_string(b.get_is_sky()) << "\tX: " << xx << "\tZ: " << zz << std::endl;
        
        if(b.get_type() != ID::AIR){
            if(click_sleep >= 0.2f){
                if(glfwGetMouseButton(game->get_window(), GLFW_MOUSE_BUTTON_1)){   
                    Block b(xx, yy, zz, ID::AIR, 1.0f, false);
                    world->get_chunk(cx, cz)->set_block(b);

                    world->rebuild_chunks_around(cx, cz);

                    std::cout << "NEW LIGHT LEVEL: " << (int)world->get_chunk(cx, cz)->get_block(xx, yy, zz)->get_light() << std::endl;

                    click_sleep = 0.0f;
                }

                if(glfwGetMouseButton(game->get_window(), GLFW_MOUSE_BUTTON_2)){  
                    Block b((int)last_pos.x % 16, (int)last_pos.y, (int)last_pos.z % 16, ID::DIRT, 1, false);
                    world->get_chunk(cx, cz)->set_block(b);
                    
                    world->rebuild_chunks_around(cx, cz);

                    click_sleep = 0.0f; 
                }

                if(glfwGetKey(game->get_window(), GLFW_KEY_F) == GLFW_PRESS){
                    Block b((int)last_pos.x % 16, (int)last_pos.y, (int)last_pos.z % 16, ID::GLASS, 15, true);
                    world->get_chunk(cx, cz)->set_block(b);

                    world->rebuild_chunks_around(cx, cz);

                    click_sleep = 0.0f;
                }
            }
        }

        last_pos = ray.get_end();
    }

    camera_front = glm::normalize(direction);
}

void Player::input(Blocky *game, double delta){
    const float camera_speed = 12.5f * delta; // adjust accordingly
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
    if(glfwGetKey(game->get_window(), GLFW_KEY_P) == GLFW_PRESS){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

const glm::vec3& Player::get_pos() const {
    return camera_pos;
}

void Player::set_mouse_pos(const double x, const double y){
    mouse_x = x;
    mouse_y = y;
}