//
//  Texture.h
//  
//
//  Created by Siddharth on 04/07/20.
//

#ifndef Texture_h
#define Texture_h
#include <EndGame/Src/EndGamePCH.hpp>

namespace EndGame {

    class Texture {
        public:
            virtual ~Texture() = default;
            virtual uint32_t getWidth() = 0;
            virtual uint32_t getHeight() = 0;
            virtual void bind(uint32_t slot = 0) = 0;
            virtual void unbind() = 0;
            virtual void setData(uint32_t size, void *data) = 0;
            virtual bool operator==(const Texture &other) const = 0;
    };

    class Texture2D : public Texture {

    };
}

#endif