//
//  RenderApiUtilities.hpp
//  EndGame
//
//  Created by Siddharth on 08/06/20.
//

#ifndef RenderApiUtilities_hpp
#define RenderApiUtilities_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.hpp>

namespace EndGame {

    class RenderApiUtilities {
        public:
            static uint32_t shaderDataTypeSize(ShaderDataType type);
            static uint32_t shaderDataTypeCount(ShaderDataType type);
            //file related functions
            static std::string readContentsFile(const std::string &filepath);
            static std::string getFileNameFromPath(const std::string &filepath);
            static std::string filepathRelativeToExe(const std::string &filepath);
    };
}

#endif
