#include <iostream>
#include "Camera.hpp"

namespace gps {
    //Camera constructor
    Camera::Camera(const glm::vec3 &cameraPosition)
            : cameraPosition(cameraPosition),
            cameraTarget(cameraPosition + glm::vec3(0.0f, 0.0f, 1.0f)),
            cameraUpDirection(glm::vec3(0.0f, 1.0f, 0.0f)),
            cameraRightDirection(glm::vec3(-1.0f, 0.0f, 0.0f)),
            cameraFrontDirection(glm::vec3(0.0f, 0.0f, 1.0f)),
            speed(0.001f) {}
    Camera::Camera(const glm::vec3 &cameraPosition, const glm::vec3 &cameraTarget, const glm::vec3 &cameraUpDirection)
            : cameraPosition(cameraPosition), cameraTarget(cameraTarget), cameraUpDirection(cameraUpDirection),
            cameraFrontDirection(glm::normalize(cameraTarget - cameraPosition)),
            cameraRightDirection(glm::cross(cameraFrontDirection, cameraUpDirection)),
            speed(0.01f){}

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        return glm::lookAt(cameraPosition, cameraTarget, cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        switch (direction) {
            case MOVE_FORWARD:
                cameraPosition += speed * cameraFrontDirection;
                break;
            case MOVE_BACKWARD:
                cameraPosition -= speed * cameraFrontDirection;
                break;
            case MOVE_LEFT:
                cameraPosition -= speed * cameraRightDirection;
                break;
            case MOVE_RIGHT:
                cameraPosition += speed * cameraRightDirection;
                break;
            default:
                break;
        }
        this->cameraTarget = this->cameraPosition + this->cameraFrontDirection;
//        std::cout << "CameraPos " << this->cameraPosition.x << " " << this->cameraPosition.y << " " << this->cameraPosition.z << "\n";
    }

    void Camera::move(MOVE_DIRECTION direction) {
        move(direction, this->speed);
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        /// TODO
        /// update W dir and R dir
        /// update target

//        std::cout << " camera -> pitch: " << pitch << " yaw: " << yaw << "\n";


        glm::mat4 frontRotMat = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), this->cameraRightDirection);
        frontRotMat = glm::rotate(frontRotMat, glm::radians(yaw), cameraUpDirection);

        glm::mat4 upRotMat = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), this->cameraRightDirection);

        this->cameraFrontDirection = frontRotMat * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
        this->cameraUpDirection = upRotMat * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
        this->cameraRightDirection = glm::cross(cameraFrontDirection, cameraUpDirection);
        this->cameraTarget = cameraPosition + cameraFrontDirection;

//        std::cout << "vec3: (" << cameraFrontDirection.x << ", " << cameraFrontDirection.y << ", " << cameraFrontDirection.z << ")" << std::endl;
//        std::cout << "vec3: (" << cameraTarget.x << ", " << cameraTarget.y << ", " << cameraTarget.z << ")" << std::endl;

    }
}