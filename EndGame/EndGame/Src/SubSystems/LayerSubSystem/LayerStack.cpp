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
        numberOfLayers++;
    }

    void LayerStack::popLayer(Layer *layer) {
        auto foundLayerLocation = std::find(layers.begin(), layers.end(), layer);
        if (foundLayerLocation != layers.end()) {
            layers.erase(foundLayerLocation);
            numberOfLayers--;
        }
    }

    void LayerStack::pushOverlay(Layer *overlay) {
        layers.emplace_back(overlay);
    }

    void LayerStack::popOverlay(Layer *overlay) {
        auto foundOverlayLocation = std::find(layers.begin(), layers.end(), overlay);
        if (foundOverlayLocation != layers.end()) {
            layers.erase(foundOverlayLocation);
        }
    }
}
