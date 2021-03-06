//
//  Core.h
//  EndGame
//
//  Created by Siddharth on 26/05/20.
//

#ifndef Core_h
#define Core_h
#include <EndGame/Src/EndGamePCH.hpp>

//ensuring only OSX platform
#ifndef EG_PLATFORM_OSX
    #error EndGame currently only supports OSX
#endif

//enabling assertions only for Debug
#ifdef EG_ENGINE_DEBUG
	#define EG_ENABLE_ASSERTS
#endif

//bit function
#define BIT(x) (1 << x)

//assertion details
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LOCATION __FILE_NAME__ ":" TOSTRING(__LINE__)

//assertions
#ifdef EG_ENABLE_ASSERTS
	#define EG_ASSERT(x, ...) { if(!(x)) { EG_ERROR("Assertion Failed [{0}]: {1}", LOCATION, __VA_ARGS__); std::raise(SIGINT); } }
	#define EG_ENGINE_ASSERT(x, ...) { if(!(x)) { EG_ENGINE_ERROR("Assertion Failed [{0}]: {1}", LOCATION, __VA_ARGS__); std::raise(SIGINT); } }
#else
	#define EG_ASSERT(x, ...)
	#define EG_ENGINE_ASSERT(x, ...)
#endif

#endif
