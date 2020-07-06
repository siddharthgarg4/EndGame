//
//  Shader.hpp
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#ifndef Shader_hpp
#define Shader_hpp
#include <glm/glm.hpp>
#include <EndGame/Src/EndGamePCH.hpp>

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
            virtual const std::string &getName() const = 0;
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

    class ShaderLibrary {
        public:
            void add(const std::shared_ptr<Shader> &shader);
            void add(const std::string &name, const std::shared_ptr<Shader> &shader);
            std::shared_ptr<Shader> load(const std::string &filepath);
            std::shared_ptr<Shader> load(const std::string &name, std::string &vertexSource, std::string &fragmentSource);
            bool exists(const std::string &name);
            std::shared_ptr<Shader> get(const std::string &name);
        private:
            std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    };
}

#endif
