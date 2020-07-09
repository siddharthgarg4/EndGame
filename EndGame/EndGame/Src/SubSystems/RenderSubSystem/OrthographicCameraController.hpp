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

    struct OrthoCamControllerData {
        //camera aspect ratio
        float aspectRatio = (1280.0f/720.0f);
        //camera rotation/zoom switch
        bool canCameraRotate = true;
        bool canCameraZoom = true;
        //camera data
        float cameraZoom = 1.0f;
        float cameraMaxZoom = 0.25f;
        float cameraRotation = 0.0f;
        glm::vec3 cameraPosition = glm::vec3(0.0f);
        //camera movement speed
        float cameraZoomSpeed = 1.0f;
        float cameraRotationSpeed = 180.0f;
        float cameraTranslationSpeed = 20.0f;
        //Constructors
        OrthoCamControllerData() {}
        OrthoCamControllerData(float aspectRatio) : aspectRatio(aspectRatio) {}
    };

    struct OrthoCamControllerKeys {
        uint32_t left = EG_KEY_A;
        uint32_t right = EG_KEY_D;
        uint32_t up = EG_KEY_W;
        uint32_t down = EG_KEY_S;
        uint32_t rotateLeft = EG_KEY_Q;
        uint32_t rotateRight = EG_KEY_E;
    };

    class OrthographicCameraController {
        public:
            //giving default values -> set in order if needed
            OrthographicCameraController(OrthoCamControllerData data = OrthoCamControllerData(), OrthoCamControllerKeys keys = OrthoCamControllerKeys());
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
            void setCameraAspectRatio(const float &aspectRatio) { data.aspectRatio = aspectRatio; }
            void setCameraRotationSwitch(const bool &canCameraRotate) { data.canCameraRotate = canCameraRotate; }
            void setCameraZoomSwitch(const bool &canCameraZoom) { data.canCameraZoom = canCameraZoom; }
            void setCameraMaxZoom(const float &cameraMaxZoom) { data.cameraMaxZoom = cameraMaxZoom; }
            void setCameraZoomSpeed(const float &cameraZoomSpeed) { data.cameraZoomSpeed = cameraZoomSpeed; }
            void setCameraRotationSpeed(const float &cameraRotationSpeed) { data.cameraRotationSpeed = cameraRotationSpeed; }
            void setCameraTranslationSpeed(const float &cameraTranslationSpeed) { data.cameraTranslationSpeed = cameraTranslationSpeed; }
            void setCurrentCameraZoom(const float &cameraZoom) { data.cameraZoom = cameraZoom; }
            void setCurrentCameraRotation(const float &cameraRotation) { data.cameraRotation = cameraRotation; }
            void setCurrentCameraPosition(const glm::vec3 &cameraPosition) { data.cameraPosition = cameraPosition; }
            //set entire structs
            void setCameraControllerData(const OrthoCamControllerData &data) { this->data = data; }
            void setCameraControllerKeys(const OrthoCamControllerKeys &keys) { this->keys = keys; }
            //getters
            const float &getCameraAspectRatio() { return data.aspectRatio; }
            const bool &getCameraRotationSwitch() { return data.canCameraRotate; }
            const bool &getCameraZoomSwitch() { return data.canCameraZoom; }
            const float &getCameraMaxZoom() { return data.cameraMaxZoom; }
            const float &getCameraZoomSpeed() { return data.cameraZoomSpeed; }
            const float &getCameraRotationSpeed() { return data.cameraRotationSpeed; }
            const float &getCameraTranslationSpeed() { return data.cameraTranslationSpeed; }
            const float &getCurrentCameraZoom() { return data.cameraZoom; }
            const float &getCurrentCameraRotation() { return data.cameraRotation; }
            const glm::vec3 &getCurrentCameraPosition() { return data.cameraPosition; }
            //get entire structs
            const OrthoCamControllerData &getCameraControllerData() { return data; }
            const OrthoCamControllerKeys &getCameraControllerKeys() { return keys; }
            //get the camera
            OrthographicCamera &getCamera() { return camera; }
            const OrthographicCamera &getCamera() const { return camera; }
        private:
            OrthoCamControllerData data;
            OrthoCamControllerKeys keys;
            OrthographicCamera camera;
    };
}

#endif
