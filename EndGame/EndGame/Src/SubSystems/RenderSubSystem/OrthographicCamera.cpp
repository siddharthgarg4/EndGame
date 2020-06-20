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

    void OrthographicCamera::recalculateMatrices() {
        float negativeRotation = rotation * -1.0f;
        glm::vec3 negativePosition = position * -1.0f;
        viewMatrix = glm::translate(glm::mat4(1.0f), negativePosition) * 
            glm::rotate(glm::mat4(1.0f), negativeRotation, glm::vec3(0, 0, 1));
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }
}
