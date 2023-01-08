#ifndef __RAY_HPP__
#define __RAY_HPP__

#include <glm/glm.hpp>

class Ray{
    public:
        Ray(glm::vec3 camera_pos, float &yaw, float &pitch){
            this->camera_pos = camera_pos;
            this->yaw = yaw;
            this->pitch = pitch;

            start = glm::vec3(camera_pos.x, camera_pos.y, camera_pos.z);
            end = start;
        }

        void step(float len){
            float x, y, z;
            y = len * sin(glm::radians(pitch));
            
            float d = sqrt(len * len - y * y);
            
            z = d * sin(glm::radians(yaw));
            x = d * cos(glm::radians(yaw));
            
            end.x += x;
            end.y += y;
            end.z += z;
        }

        float get_length(){
            return glm::distance(start, end);
        }

        const glm::vec3& get_end() const {
            return end;
        }

    private:
        glm::vec3 start;
        glm::vec3 end;
        glm::vec3 camera_pos;

        float yaw;
        float pitch;
};

#endif