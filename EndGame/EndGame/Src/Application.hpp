//
//  Application.hpp
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>

namespace EndGame {
class Application {
public:
    Application();
    virtual ~Application();
    
    void run();
};

Application *createApplication();
}

#endif /* Application_hpp */
