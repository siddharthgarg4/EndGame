//
//  RenderApiUtilities.cpp
//  EndGame
//
//  Created by Siddharth on 08/06/20.
//

#include "RenderApiUtilities.hpp"
#include <glad/glad.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OpenGlShader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RendererApi.hpp>

namespace EndGame {
    uint32_t RenderApiUtilities::shaderDataTypeSize(ShaderDataType type) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return 0;
            }
            case RendererApi::Api::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).size;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
        return 0;
    }

    uint32_t RenderApiUtilities::shaderDataTypeCount(ShaderDataType type) {
        switch(RendererApi::getApi()) {
            case RendererApi::Api::None: {
                EG_ENGINE_ASSERT(false, "RenderApi::Api::None is currently not supported!");
                return 0;
            }
            case RendererApi::Api::OpenGl: {
                return OpenGlShader::shaderDataTypeToOpenGlDataType(type).count;
            }
        }
        EG_ENGINE_ASSERT(false, "Unknown RendererAPI::Api!");
        return 0;
    }

    std::string RenderApiUtilities::readContentsFile(const std::string &filepath) {
        std::string pathRelativeToExe = filepathRelativeToExe(filepath);
        std::ifstream input(pathRelativeToExe, std::ios::in | std::ios::binary);
        std::string fileContents;
        if (input) {
            input.seekg(0, std::ios::end);
            fileContents.resize(input.tellg());
            input.seekg(0, std::ios::beg);
            input.read(&fileContents[0], fileContents.size());
            input.close();
        } else {
            EG_ENGINE_ERROR("Could not open file '{0}'", pathRelativeToExe);
        }
        return fileContents;
    }

    std::string RenderApiUtilities::filepathRelativeToExe(const std::string &filepath) {
        std::string relativeToExe = "../../../";
        return relativeToExe + filepath;
    }

    std::string RenderApiUtilities::getFileNameFromPath(const std::string &filepath) {
        size_t lastDot = filepath.find_last_of(".");
        size_t lastSlash = filepath.find_last_of("\\/");
        size_t startFileName = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        std::string fileName = filepath.substr(startFileName, 
            (lastDot == std::string::npos ? filepath.size() : lastDot) - startFileName);
            return fileName;
    }
}
