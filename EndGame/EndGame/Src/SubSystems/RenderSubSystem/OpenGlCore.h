//
//  OpenGlCore.h
//  
//
//  Created by Siddharth on 19/06/20.
//

#ifndef OpenGlCore_h
#define OpenGlCore_h
#include <glad/glad.h>
#include <EndGame/Src/Core.h>
#include <EndGame/Src/EndGamePCH.hpp>

//macro for glad error checking, use if needed
#define GL_CHECK_ERROR(call) GlClearError();\
    call;\
    std::pair<bool, std::string> openGlCallResult = GlCheckError();\
    EG_ENGINE_ASSERT(openGlCallResult.first, "OpenGl Call Error Code: " +  openGlCallResult.second)

namespace EndGame {
    static void GlClearError() {
        while(glGetError() != GL_NO_ERROR);
    }

    static std::pair<bool, std::string> GlCheckError() {
        while(GLenum error = glGetError()) {
            std::string errorCode = std::to_string(error);
            return std::make_pair(false, errorCode);
        }
        return std::make_pair(true, std::string());
    }
}
    
#endif
