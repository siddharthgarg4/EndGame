//
//  OrthographicCameraController.cpp
//  
//
//  Created by Siddharth on 06/07/20.
//

#include "OrthographicCameraController.hpp"
#include <EndGame/Src/SubSystems/InputSubSystem/Input.h>
#include <EndGame/Src/SubSystems/InputSubSystem/KeyCodes.h>
#include <EndGame/Src/SubSystems/EventSubSystem/MouseEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>

namespace EndGame {
    OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canCameraRotate,
        float cameraZoomSpeed, float cameraRotationSpeed, float cameraTranslationSpeed,
        float startingCameraZoom, float startingCameraRotation, glm::vec3 startingCameraPosition) :
            aspectRatio(aspectRatio), canCameraRotate(canCameraRotate), cameraZoomSpeed(cameraZoomSpeed), cameraRotationSpeed(cameraRotationSpeed),
            cameraTranslationSpeed(cameraTranslationSpeed), cameraZoom(startingCameraZoom), cameraRotation(startingCameraRotation),
            cameraPosition(startingCameraPosition), camera(-aspectRatio*cameraZoom, aspectRatio*cameraZoom, -cameraZoom, cameraZoom) {
    }

    void OrthographicCameraController::onEvent(Event &event) {
        EventDispatcher dispatcher(event);
        //taking care of mouse scrolled events
        dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent &event) {
            cameraZoom -= event.getYOffset() * cameraZoomSpeed;
            cameraZoom = std::max(cameraZoom, 0.25f);
            camera.setProjection(-aspectRatio*cameraZoom, aspectRatio*cameraZoom, -cameraZoom, cameraZoom);
            return false;
        });
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
        if (EndGame::Input::isKeyPressed(EG_KEY_LEFT)) {
            position.x -= cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(EG_KEY_RIGHT)) {
            position.x += cameraTranslationSpeed * dtime;
        }

        if (EndGame::Input::isKeyPressed(EG_KEY_UP)) {
            position.y += cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(EG_KEY_DOWN)) {
            position.y -= cameraTranslationSpeed * dtime;
        }
        //rotation
        if (canCameraRotate) {
            if (EndGame::Input::isKeyPressed(EG_KEY_A)) {
                rotation += cameraRotationSpeed * dtime;
            } else if (EndGame::Input::isKeyPressed(EG_KEY_D)) {
                rotation -= cameraRotationSpeed * dtime;
            }
        }
        return std::make_tuple(position, rotation);
    }
}
