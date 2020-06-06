//
//  GraphicsContext.h
//  
//
//  Created by Siddharth on 05/06/20.
//

#ifndef GraphicsContext_h
#define GraphicsContext_h

namespace EndGame {

    class GraphicsContext {
        public:
            virtual void init() = 0;
            virtual void swapBuffers() = 0;
    };
}

#endif
