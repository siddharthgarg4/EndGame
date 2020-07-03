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
            //upload uniform methods overloaded for different types
            //vec and mat is assumed to be of type float
            virtual void uploadUniform(const std::string &name, const int &data) = 0;
            virtual void uploadUniform(const std::string &name, const float &data) = 0;
            virtual void uploadUniform(const std::string &name, const glm::vec2 &data) = 0;
            virtual void uploadUniform(const std::string &name, const glm::vec3 &data) = 0;
            virtual void uploadUniform(const std::string &name, const glm::vec4 &data) = 0;
            virtual void uploadUniform(const std::string &name, const glm::mat3 &data) = 0;
            virtual void uploadUniform(const std::string &name, const glm::mat4 &data) = 0;
    };
}

#endif
