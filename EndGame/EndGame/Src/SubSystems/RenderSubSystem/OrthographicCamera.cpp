//
//  OrthographicCamera.cpp
//  
//
//  Created by Siddharth on 20/06/20.
//

#include "OrthographicCamera.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace EndGame {
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top):
    rotation(0.0f), position(0.0f), viewMatrix(1.0f), projectionMatrix(glm::ortho(left, right, bottom, top)) {
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }


    void OrthographicCamera::setProjection(float left, float right, float bottom, float top) {
        projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    void OrthographicCamera::recalculateMatrices() {
        //converting rotation from deg to radians
        float negativeRotation = glm::radians(rotation * -1.0f);
        glm::vec3 negativePosition = position * -1.0f;
        viewMatrix = glm::translate(glm::mat4(1.0f), negativePosition) * 
            glm::rotate(glm::mat4(1.0f), negativeRotation, glm::vec3(0, 0, 1));
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
}
