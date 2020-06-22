//
//  Layer.h
//  EndGame
//
//  Created by Siddharth on 31/05/20.
//

#ifndef Layer_h
#define Layer_h
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/EventSubSystem/Event.h>

namespace EndGame {

    class Layer {
        public:
            Layer(const std::string &debugName = "Layer") : debugName(debugName) {}
            //virtual methods
            virtual ~Layer() {}
            virtual void onAttach() {}
            virtual void onDetach() {}
            //update the state, dtime represents timestep, timeSinceStart passed in case layer wants to use
            virtual void onUpdate(const float &timeSinceStart, const float &dtime) {}
            //actually render, alpha represents difference between current and next state
            virtual void onRender(const float &alpha, const float &dtime) {}
            //allows each layer to custom use imgui
            virtual void onImguiRender() {}
            virtual void onEvent(Event &event) {}
            inline const std::string &getDebugName() const { return debugName; }
        protected:
            std::string debugName;
    };
}

#endif
