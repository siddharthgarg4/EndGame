//
//  Shader.h
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#ifndef Shader_h
#define Shader_h
#include <glm/glm.hpp>

namespace EndGame {

    enum class ShaderDataType {
        None = 0, 
        Bool,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4
    };
    
    class Shader {
        public:
            virtual ~Shader() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual void uploadUniformMat4(const std::string &name, const glm::mat4 &matrix) = 0;
    };
}

#endif
