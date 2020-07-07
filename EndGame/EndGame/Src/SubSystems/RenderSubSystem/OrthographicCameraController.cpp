//
//  OrthographicCameraController.cpp
//  
//
//  Created by Siddharth on 06/07/20.
//

#include "OrthographicCameraController.hpp"
#include <EndGame/Src/SubSystems/InputSubSystem/Input.h>
#include <EndGame/Src/SubSystems/EventSubSystem/MouseEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>

namespace EndGame {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canCameraRotate, bool canCameraZoom,
        float cameraZoomSpeed, float cameraRotationSpeed, float cameraTranslationSpeed, float cameraMaxZoom,
        float startingCameraZoom, float startingCameraRotation, glm::vec3 startingCameraPosition) :
            aspectRatio(aspectRatio), canCameraRotate(canCameraRotate), canCameraZoom(canCameraZoom), cameraZoomSpeed(cameraZoomSpeed), cameraRotationSpeed(cameraRotationSpeed),
            cameraTranslationSpeed(cameraTranslationSpeed), cameraMaxZoom(cameraMaxZoom), cameraZoom(startingCameraZoom), cameraRotation(startingCameraRotation),
            cameraPosition(startingCameraPosition), camera(-aspectRatio*cameraZoom, aspectRatio*cameraZoom, -cameraZoom, cameraZoom) {
    }

    void OrthographicCameraController::onEvent(Event &event) {
        EventDispatcher dispatcher(event);
        if (canCameraZoom) {
            //taking care of mouse scrolled events if zoom enabled
            dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent &event) {
                cameraZoom -= event.getYOffset() * cameraZoomSpeed;
                cameraZoom = std::max(cameraZoom, cameraMaxZoom);
                camera.setProjection(-aspectRatio*cameraZoom, aspectRatio*cameraZoom, -cameraZoom, cameraZoom);
                return false;
            });
        }
        //taking care of window resize events
        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent &event) {
            aspectRatio = (float)event.getWidth()/(float)event.getHeight();
            camera.setProjection(-aspectRatio*cameraZoom, aspectRatio*cameraZoom, -cameraZoom, cameraZoom);
            return false;
        });
    }

    void OrthographicCameraController::onUpdate(const float &timeSinceStart, const float &dtime) {
        std::pair<glm::vec3, float> newCameraTransform = nextFrame(dtime);
        cameraPosition = newCameraTransform.first;
        if (canCameraRotate) {
            cameraRotation = newCameraTransform.second;
        }
        //making translation slower/faster based on zoom
        cameraTranslationSpeed = cameraZoom;
    }

    void OrthographicCameraController::onRender(const float &alpha, const float &dtime) {
        std::pair<glm::vec3, float> nextUpdateCameraTransform = nextFrame(dtime);
        glm::vec3 interpolatedCameraPosition = (cameraPosition * (1-alpha)) + (nextUpdateCameraTransform.first * alpha);
        float interpolatedCameraRotation = (cameraRotation * (1-alpha)) + (nextUpdateCameraTransform.second * alpha);
        //finally updating the camera
        camera.setPosition(interpolatedCameraPosition);
        camera.setRotation(interpolatedCameraRotation);
    }

    std::pair<glm::vec3, float> OrthographicCameraController::nextFrame(const float &dtime) {
        glm::vec3 position = cameraPosition;
        float rotation = cameraRotation;
        //movement
        if (EndGame::Input::isKeyPressed(moveLeftKeyCode)) {
            position.x -= cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(moveRightKeyCode)) {
            position.x += cameraTranslationSpeed * dtime;
        }

        if (EndGame::Input::isKeyPressed(moveUpKeyCode)) {
            position.y += cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(moveDownKeyCode)) {
            position.y -= cameraTranslationSpeed * dtime;
        }
        //rotation
        if (canCameraRotate) {
            if (EndGame::Input::isKeyPressed(rotateLeftKeyCode)) {
                rotation += cameraRotationSpeed * dtime;
            } else if (EndGame::Input::isKeyPressed(rotateRightKeyCode)) {
                rotation -= cameraRotationSpeed * dtime;
            }
        }
        return std::make_tuple(position, rotation);
    }

    void OrthographicCameraController::setCameraRotateKeyCodes(const uint32_t &rotateRightKeyCode, const uint32_t &rotateLeftKeyCode) {
        this->rotateRightKeyCode = rotateRightKeyCode; 
        this->rotateLeftKeyCode = rotateLeftKeyCode;
    }

    void OrthographicCameraController::setCameraMoveKeyCodes(const uint32_t &upKeyCode, const uint32_t &downKeyCode, const uint32_t &rightKeyCode, const uint32_t &leftKeyCode) {
        moveUpKeyCode = upKeyCode;
        moveDownKeyCode = downKeyCode;
        moveRightKeyCode = rightKeyCode;
        moveLeftKeyCode = leftKeyCode;
    }
}
