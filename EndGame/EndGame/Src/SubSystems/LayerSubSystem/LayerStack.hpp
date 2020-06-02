//
//  LayerStack.hpp
//  EndGame
//
//  Created by Siddharth on 31/05/20.
//

#ifndef LayerStack_hpp
#define LayerStack_hpp
#include <EndGame/Src/Core.h>
#include <EndGame/Src/SubSystems/LayerSubSystem/Layer.h>

namespace EndGame {
    
    class LayerStack {
        public:
            LayerStack();
            ~LayerStack();
            void pushLayer(Layer *layer);
            void popLayer(Layer *layer);
            void pushOverlay(Layer *overlay);
            void popOverlay(Layer *overlay);
            std::vector<Layer *>::iterator begin() { return layers.begin(); }
            std::vector<Layer *>::iterator end() { return layers.end(); }

        private:
            std::vector<Layer *>layers;
            std::vector<Layer *>::iterator layerBeforeOverlay;
    };
}

#endif
