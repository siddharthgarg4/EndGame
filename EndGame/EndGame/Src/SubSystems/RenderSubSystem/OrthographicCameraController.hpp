//
//  OrthographicCameraController.hpp
//  
//
//  Created by Siddharth on 06/07/20.
//

#ifndef OrthographicCameraController_hpp
#define OrthographicCameraController_hpp
#include <glm/glm.hpp>
#include <EndGame/Src/EndGamePCH.hpp>
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>
#include <EndGame/Src/SubSystems/InputSubSystem/KeyCodes.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OrthographicCamera.hpp>

namespace EndGame {

    class OrthographicCameraController {
        public:
            //giving default values -> set in order if needed
            OrthographicCameraController(float aspectRatio, bool canCameraRotate = true, 
                bool canCameraZoom = true, float cameraZoomSpeed = 1.0f, float cameraRotationSpeed = 180.0f, 
                float cameraTranslationSpeed = 20.0f, float cameraMaxZoom = 0.25f, float startingCameraZoom = 1.0f, 
                float startingCameraRotation = 0.0f, glm::vec3 startingCameraPosition = glm::vec3(0.0f));
            //methods to hook into
            void onEvent(Event &event);
            //simply updates the data but not the camera, that is responsibility of user to do on rendering
            void onUpdate(const float &timeSinceStart, const float &dtime);
            //update the camera based on interpolated data
            void onRender(const float &alpha, const float &dtime);
            //for interpolation, returns data of next frame without any data mutation
            //position, rotation is format of output
            std::pair<glm::vec3, float> nextFrame(const float &dtime);
            //setters
            void setAspectRatio(const float &aspectRatio) { this->aspectRatio = aspectRatio; }
            void setCameraRotationSwitch(const bool &canCameraRotate) { this->canCameraRotate = canCameraRotate; }
            void setCameraZoomSwitch(const bool &canCameraZoom) { this->canCameraZoom = canCameraZoom; }
            void setCameraMaxZoom(const float &cameraMaxZoom) { this->cameraMaxZoom = cameraMaxZoom; }
            void setCameraZoomSpeed(const float &cameraZoomSpeed) { this->cameraZoomSpeed = cameraZoomSpeed; }
            void setCameraRotationSpeed(const float &cameraRotationSpeed) { this->cameraRotationSpeed = cameraRotationSpeed; }
            void setCameraTranslationSpeed(const float &cameraTranslationSpeed) { this->cameraTranslationSpeed = cameraTranslationSpeed; }
            void setCurrentCameraZoom(const float &cameraZoom) { this->cameraZoom = cameraZoom; }
            void setCurrentCameraRotation(const float &cameraRotation) { this->cameraRotation = cameraRotation; }
            void setCurrentCameraPosition(const glm::vec3 &cameraPosition) { this->cameraPosition = cameraPosition; }
            void setCameraRotateKeyCodes(const uint32_t &rotateRightKeyCode, const uint32_t &rotateLeftKeyCode);
            void setCameraMoveKeyCodes(const uint32_t &upKeyCode, const uint32_t &downKeyCode, const uint32_t &rightKeyCode, const uint32_t &leftKeyCode);
            //getters
            const float &getAspectRatio() { return aspectRatio; }
            const bool &getCameraRotationSwitch() { return canCameraRotate; }
            const bool &getCameraZoomSwitch() { return canCameraZoom; }
            const float &getCameraMaxZoom() { return cameraMaxZoom; }
            const float &getCameraZoomSpeed() { return cameraZoomSpeed; }
            const float &getCameraRotationSpeed() { return cameraRotationSpeed; }
            const float &getCameraTranslationSpeed() { return cameraTranslationSpeed; }
            const float &getCurrentCameraZoom() { return cameraZoom; }
            const float &getCurrentCameraRotation() { return cameraRotation; }
            const glm::vec3 &getCurrentCameraPosition() { return cameraPosition; }
            const uint32_t &getCameraMoveUpKeyCode() { return moveUpKeyCode; }
            const uint32_t &getCameraMoveDownKeyCode() { return moveDownKeyCode; }
            const uint32_t &getCameraMoveLeftKeyCode() { return moveLeftKeyCode; }
            const uint32_t &getCameraMoveRightKeyCode() { return moveRightKeyCode; }
            const uint32_t &getCameraRotateRightKeyCode() { return rotateRightKeyCode; }
            const uint32_t &getCameraRotateLeftKeyCode() { return rotateLeftKeyCode; }
            OrthographicCamera &getCamera() { return camera; }
            const OrthographicCamera &getCamera() const { return camera; }
        private:
            //actual camera data
            float aspectRatio;
            //whether camera is allowed to rotate/zoom
            bool canCameraRotate;
            bool canCameraZoom;
            //camera movement ratio
            float cameraMaxZoom;
            float cameraZoomSpeed;
            float cameraRotationSpeed;
            float cameraTranslationSpeed;
            //camera position
            float cameraZoom;
            float cameraRotation;
            glm::vec3 cameraPosition;
            //actual camera
            OrthographicCamera camera;
            //key codes
            uint32_t moveLeftKeyCode = EG_KEY_A;
            uint32_t moveRightKeyCode = EG_KEY_D;
            uint32_t moveUpKeyCode = EG_KEY_W;
            uint32_t moveDownKeyCode = EG_KEY_S;
            uint32_t rotateLeftKeyCode = EG_KEY_Q;
            uint32_t rotateRightKeyCode = EG_KEY_E;
    };
}

#endif
