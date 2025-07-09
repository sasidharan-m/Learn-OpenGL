//
//  camera.h
//  Camera
//
//  Created by Sasidharan Mahalingam on 4/7/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// enum to abstract the camera movement directions
enum class Camera_Movement {
    forward,
    backward,
    left,
    right
};

// default camera values
const float yaw = -90.0f;
const float pitch = 0.0f;
const float speed = 2.5f;
const float sensitivity = 0.1f;
const float zoom = 45.0f;

// A camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    private:
        // camera attributes
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 world_up;
        // Euler angles
        float camera_yaw;
        float camera_pitch;
        // camera options
        float movement_speed;
        float mouse_sensitivity;
        float zoom_fov;

        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
        {
            // calculate the new front vector
            glm::vec3 front_vec;
            front_vec.x = cos(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
            front_vec.y = sin(glm::radians(camera_pitch));
            front_vec.z = sin(glm::radians(camera_yaw)) * cos(glm::radians(camera_pitch));
            front = glm::normalize(front_vec);
            // also recalculate the up and right vectors
            right = glm::normalize(glm::cross(front, world_up));
            up = glm::normalize(glm::cross(right, front));
        }

    public:
        // constructor with vectors
        Camera(glm::vec3 position_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f), float yaw_ = yaw, float pitch_ = pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(speed), mouse_sensitivity(sensitivity), zoom_fov(zoom)
        {
            position = position_;
            world_up = up_;
            camera_yaw = yaw_;
            camera_pitch = pitch_;
            updateCameraVectors();
        }

        // constructor with scalar values
        Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw_, float pitch_) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movement_speed(speed), mouse_sensitivity(sensitivity), zoom_fov(zoom)
        {
            position = glm::vec3(pos_x, pos_y, pos_z);
            world_up = glm::vec3(up_x, up_y, up_z);
            camera_yaw = yaw_;
            camera_pitch = pitch_;
            updateCameraVectors();
        }

        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 getViewMatrix()
        {
            return glm::lookAt(position, position + front, up);
        }

        // returns the view matrix using custom lookat implementation
        glm::mat4 getViewMatrixCustom()
        {
            glm::vec3 cameraZ = glm::normalize(position - (position + front));
            glm::vec3 cameraX = glm::normalize(glm::cross(up, cameraZ));
            glm::vec3 cameraY = glm::normalize(glm::cross(cameraZ, cameraX));

            glm::mat4 translation = glm::mat4(1.0f);
            translation[3][0] = -position.x;
            translation[3][1] = -position.y;
            translation[3][2] = -position.z;

            glm::mat4 rotation = glm::mat4(1.0f);
            rotation[0][0] = cameraX.x;
            rotation[1][0] = cameraX.y;
            rotation[2][0] = cameraX.z;
            rotation[0][1] = cameraY.x;
            rotation[1][1] = cameraY.y;
            rotation[2][1] = cameraY.z;
            rotation[0][2] = cameraZ.x;
            rotation[1][2] = cameraZ.y;
            rotation[2][2] = cameraZ.z;

            // return the manually calculated lookAt matrix
            return rotation * translation;
        }

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void processKeyboard(Camera_Movement direction, float delta_time)
        {
            float velocity = movement_speed * delta_time;
            if (direction == Camera_Movement::forward)
                position += front * velocity;
            if (direction == Camera_Movement::backward)
                position -= front * velocity;
            if (direction == Camera_Movement::left)
                position -= right * velocity;
            if (direction == Camera_Movement::right)
                position += right * velocity;
        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void processMouseMovement(float xoffset, float yoffset, GLboolean constrain_pitch = true)
        {
            xoffset *= mouse_sensitivity;
            yoffset *= mouse_sensitivity;

            camera_yaw   += xoffset;
            camera_pitch += yoffset;

            // make sure that when pitch is out of bounds, screen doesn't get flipped
            if (constrain_pitch)
            {
                if (camera_pitch > 89.0f)
                    camera_pitch = 89.0f;
                if (camera_pitch < -89.0f)
                    camera_pitch = -89.0f;
            }

            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors();
        }

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void processMouseScroll(float yoffset)
        {
            zoom_fov -= (float)yoffset;
            if (zoom_fov < 1.0f)
                zoom_fov = 1.0f;
            if (zoom_fov > 45.0f)
                zoom_fov = 45.0f;
        }

        // member function that returns the camera position
        glm::vec3 getPosition()
        {
            return position;
        }
};

#endif