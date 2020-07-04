//
//  Shader.cpp
//  
//
//  Created by Siddharth on 04/07/20.
//

#include "Shader.hpp"
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

namespace EndGame {
    //MARK: Shader Library methods
    void ShaderLibrary::add(const std::shared_ptr<Shader> &shader) {
        add(shader->getName(), shader);
    }

    void ShaderLibrary::add(const std::string &name, const std::shared_ptr<Shader> &shader) {
        EG_ENGINE_ASSERT(!exists(name), "Shader with " + name + " already exists");
        shaders[name] = shader;
    }

    void ShaderLibrary::load(const std::string &filepath) {
        std::shared_ptr<Shader> shader = RenderApiFactory::createShader(filepath);
        add(shader);
    }

    void ShaderLibrary::load(std::string &name, std::string &vertexSource, std::string &fragmentSource) {
        std::shared_ptr<Shader> shader = RenderApiFactory::createShader(name, vertexSource, fragmentSource);
        add(name, shader);
    }

    bool ShaderLibrary::exists(const std::string &name) {
        return shaders.find(name) != shaders.end();
    }

    std::shared_ptr<Shader> ShaderLibrary::get(const std::string &name) {
        EG_ENGINE_ASSERT(exists(name), "Shader with " + name + " does not exist");
        return shaders[name];
    }
}