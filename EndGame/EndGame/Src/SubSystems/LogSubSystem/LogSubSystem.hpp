//
//  LogSubSystem.hpp
//  EndGame
//
//  Created by Siddharth on 25/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef LogSubSystem_hpp
#define LogSubSystem_hpp

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace EndGame {

    class LogSubSystem {
        public:
            static void init();
            inline static std::shared_ptr<spdlog::logger> &getEngineLogger() { return engineLogger; };
            inline static std::shared_ptr<spdlog::logger> &getClientLogger() { return clientLogger; };

        private:
            static std::shared_ptr<spdlog::logger> engineLogger;
            static std::shared_ptr<spdlog::logger> clientLogger;
    };
}

//MARK: Engine Logger Macros
#define EG_ENGINE_ERROR(...) ::EndGame::LogSubSystem::getEngineLogger()->error(__VA_ARGS__)
#define EG_ENGINE_WARNING(...) ::EndGame::LogSubSystem::getEngineLogger()->warn(__VA_ARGS__)
#define EG_ENGINE_INFO(...) ::EndGame::LogSubSystem::getEngineLogger()->info(__VA_ARGS__)
#define EG_ENGINE_TRACE(...) ::EndGame::LogSubSystem::getEngineLogger()->trace(__VA_ARGS__)
#define EG_ENGINE_CRITICAL(...) ::EndGame::LogSubSystem::getEngineLogger()->critical(__VA_ARGS__)

//MARK: Client Logger Macros
#define EG_ERROR(...) ::EndGame::LogSubSystem::getClientLogger()->error(__VA_ARGS__)
#define EG_WARNING(...) ::EndGame::LogSubSystem::getClientLogger()->warn(__VA_ARGS__)
#define EG_INFO(...) ::EndGame::LogSubSystem::getClientLogger()->info(__VA_ARGS__)
#define EG_TRACE(...) ::EndGame::LogSubSystem::getClientLogger()->trace(__VA_ARGS__)
#define EG_CRITICAL(...) ::EndGame::LogSubSystem::getClientLogger()->critical(__VA_ARGS__)

#endif
