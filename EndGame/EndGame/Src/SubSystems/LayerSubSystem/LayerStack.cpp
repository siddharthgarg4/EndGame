//
//  LayerStack.cpp
//  EndGame
//
//  Created by Siddharth on 31/05/20.
//

#include "LayerStack.hpp"

namespace EndGame {

    LayerStack::~LayerStack() {
        for (Layer *layer: layers) {
            delete layer;
        }
    }

    void LayerStack::pushLayer(Layer *layer) {
        layers.emplace(layers.begin() + numberOfLayers, layer);
        layer->onAttach();
        numberOfLayers++;
    }

    void LayerStack::popLayer(Layer *layer) {
        //search from start of layers to the end
        auto foundLayerLocation = std::find(layers.begin(), layers.begin() + numberOfLayers, layer);
        if (foundLayerLocation != layers.begin() + numberOfLayers) {
            layers.erase(foundLayerLocation);
            layer->onDetach();
            numberOfLayers--;
        }
    }

    void LayerStack::pushOverlay(Layer *overlay) {
        layers.emplace_back(overlay);
        overlay->onAttach();
    }

    void LayerStack::popOverlay(Layer *overlay) {
        //search from start of overlays to the end
        auto foundOverlayLocation = std::find(layers.begin() + numberOfLayers, layers.end(), overlay);
        if (foundOverlayLocation != layers.end()) {
            overlay->onDetach();
            layers.erase(foundOverlayLocation);
        }
    }
}
