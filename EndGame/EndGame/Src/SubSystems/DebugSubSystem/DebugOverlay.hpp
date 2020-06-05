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
            static void preImguiRender();
            static void postImguiRender();
            //layer methods
            void onAttach() override;
            void onDetach() override;
            void onImguiRender() override;

        private:
            double frameTime = 0.0;
    };
}

#endif
