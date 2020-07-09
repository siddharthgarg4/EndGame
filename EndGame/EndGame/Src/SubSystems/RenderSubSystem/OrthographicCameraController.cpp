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
    OrthographicCameraController::OrthographicCameraController(OrthoCamControllerData data, OrthoCamControllerKeys keys) :
        data(data), keys(keys), camera((-data.aspectRatio)*data.cameraZoom, data.aspectRatio*data.cameraZoom, -data.cameraZoom, data.cameraZoom) {
    }

    void OrthographicCameraController::onEvent(Event &event) {
        EventDispatcher dispatcher(event);
        if (data.canCameraZoom) {
            //taking care of mouse scrolled events if zoom enabled
            dispatcher.dispatch<MouseScrolledEvent>([this](MouseScrolledEvent &event) {
                data.cameraZoom -= event.getYOffset() * data.cameraZoomSpeed;
                data.cameraZoom = std::max(data.cameraZoom, data.cameraMaxZoom);
                camera.setProjection((-data.aspectRatio)*data.cameraZoom, data.aspectRatio*data.cameraZoom, -data.cameraZoom, data.cameraZoom);
                return false;
            });
        }
        //taking care of window resize events
        dispatcher.dispatch<WindowResizeEvent>([this](WindowResizeEvent &event) {
            data.aspectRatio = (float)event.getWidth()/(float)event.getHeight();
            camera.setProjection((-data.aspectRatio)*data.cameraZoom, data.aspectRatio*data.cameraZoom, -data.cameraZoom, data.cameraZoom);
            return false;
        });
    }

    void OrthographicCameraController::onUpdate(const float &timeSinceStart, const float &dtime) {
        std::pair<glm::vec3, float> newCameraTransform = nextFrame(dtime);
        data.cameraPosition = newCameraTransform.first;
        if (data.canCameraRotate) {
            data.cameraRotation = newCameraTransform.second;
        }
        //making translation slower/faster based on zoom
        data.cameraTranslationSpeed = data.cameraZoom;
    }

    void OrthographicCameraController::onRender(const float &alpha, const float &dtime) {
        std::pair<glm::vec3, float> nextUpdateCameraTransform = nextFrame(dtime);
        glm::vec3 interpolatedCameraPosition = (data.cameraPosition * (1-alpha)) + (nextUpdateCameraTransform.first * alpha);
        float interpolatedCameraRotation = (data.cameraRotation * (1-alpha)) + (nextUpdateCameraTransform.second * alpha);
        //finally updating the camera
        camera.setPosition(interpolatedCameraPosition);
        camera.setRotation(interpolatedCameraRotation);
    }

    std::pair<glm::vec3, float> OrthographicCameraController::nextFrame(const float &dtime) {
        glm::vec3 position = data.cameraPosition;
        float rotation = data.cameraRotation;
        //movement
        if (EndGame::Input::isKeyPressed(keys.left)) {
            position.x -= data.cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(keys.right)) {
            position.x += data.cameraTranslationSpeed * dtime;
        }

        if (EndGame::Input::isKeyPressed(keys.up)) {
            position.y += data.cameraTranslationSpeed * dtime;
        } else if (EndGame::Input::isKeyPressed(keys.down)) {
            position.y -= data.cameraTranslationSpeed * dtime;
        }
        //rotation
        if (data.canCameraRotate) {
            if (EndGame::Input::isKeyPressed(keys.rotateLeft)) {
                rotation += data.cameraRotationSpeed * dtime;
            } else if (EndGame::Input::isKeyPressed(keys.rotateRight)) {
                rotation -= data.cameraRotationSpeed * dtime;
            }
        }
        return std::make_pair(position, rotation);
    }
}
