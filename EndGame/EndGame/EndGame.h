//
//  EndGame.h
//  EndGame
//
//  Created by Siddharth on 24/05/20.
//  Copyright © 2020 Siddharth. All rights reserved.
//

#ifndef EndGame_h
#define EndGame_h
//For use by the EndGame applications

//MARK: Application
#include <EndGame/Src/Application.hpp>

//MARK: Entry Point
#include <EndGame/Src/EntryPoint.hpp>

//MARK: Events
#include <EndGame/Src/SubSystems/EventSubSystem/KeyEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/ApplicationEvent.h>
#include <EndGame/Src/SubSystems/EventSubSystem/MouseEvent.h>

//MARK: Layers 
#include <EndGame/Src/SubSystems/LayerSubSystem/Layer.h>
#include <EndGame/Src/SubSystems/DebugSubSystem/DebugOverlay.hpp>

//MARK: Input
#include <EndGame/Src/SubSystems/InputSubSystem/Input.h>
#include <EndGame/Src/SubSystems/InputSubSystem/KeyCodes.h>
#include <EndGame/Src/SubSystems/InputSubSystem/MouseButtonCodes.h>

//MARK: Rendering Components
#include <EndGame/Src/SubSystems/RenderSubSystem/Shader.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/Texture.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/VertexArray.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/OrthographicCamera.hpp>
//MARK: Rendering
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderCommand.h>
#include <EndGame/Src/SubSystems/RenderSubSystem/Renderer.hpp>
#include <EndGame/Src/SubSystems/RenderSubSystem/RenderApiFactory.hpp>

#endif
