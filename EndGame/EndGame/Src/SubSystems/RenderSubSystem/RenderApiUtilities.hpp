//
//  RenderApiUtilities.hpp
//  EndGame
//
//  Created by Siddharth on 08/06/20.
//

#ifndef RenderApiUtilities_hpp
#define RenderApiUtilities_hpp
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.h>

namespace EndGame {

    class RenderApiUtilities {
        public:
            static uint32_t shaderDataTypeSize(ShaderDataType type);
            static uint32_t shaderDataTypeCount(ShaderDataType type);
    };
}

#endif
