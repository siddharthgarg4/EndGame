//
//  OrthographicCamera.hpp
//  
//
//  Created by Siddharth on 20/06/20.
//

#ifndef OrthographicCamera_hpp
#define OrthographicCamera_hpp
#include <glm/glm.hpp>

namespace EndGame {

    class OrthographicCamera {
        public:
            OrthographicCamera(float left, float right, float bottom, float top);
            //setters
            void setProjection(float left, float right, float bottom, float top);
            inline void setRotation(float rotation) { this->rotation = rotation; recalculateMatrices(); }
            inline void setPosition(glm::vec3 position) { this->position = position; recalculateMatrices(); }
            //getters
            inline const float &getRotation() const { return rotation; }
            inline const glm::vec3 &getPosition() const { return position; }
            inline const glm::mat4 &getViewMatrix() const { return viewMatrix; }
            inline const glm::mat4 &getProjectionMatrix() const { return projectionMatrix; }
            inline const glm::mat4 &getViewProjectionMatrix() const { return viewProjectionMatrix; }
        private:
            void recalculateMatrices();
            float rotation;
            glm::vec3 position;
            glm::mat4 viewMatrix;
            glm::mat4 projectionMatrix;
            glm::mat4 viewProjectionMatrix;
    };
}

#endif
