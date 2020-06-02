//
//  DebugOverlay.hpp
//  EndGame
//
//  Created by Siddharth on 02/06/20.
//

#ifndef DebugOverlay_hpp
#define DebugOverlay_hpp
#include <EndGame/Src/SubSystems/LayerSubSystem/Layer.h>

namespace EndGame {

    class DebugOverlay : public Layer {
        public:
            DebugOverlay() : Layer("DebugOverlay") {}
            ~DebugOverlay() {}
            //layer methods
            void onAttach() override;
            void onDetach() override;
            void onUpdate() override;
            void onEvent(Event &event) override;

        private:
            double frameTime = 0.0;
    };
}

#endif
