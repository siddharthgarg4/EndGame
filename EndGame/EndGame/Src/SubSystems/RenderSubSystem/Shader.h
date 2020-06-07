//
//  Shader.h
//  EndGame
//
//  Created by Siddharth on 06/06/20.
//

#ifndef Shader_h
#define Shader_h

namespace EndGame {

    class Shader {
        public:
            virtual ~Shader() {}
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
    };
}

#endif
