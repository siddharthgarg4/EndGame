# EndGame

![EndGame](/resources/endgame-cover.png?raw=true"EndGame")

## Project Description

EndGame is a ***C++ Game Engine*** that compiles as a static library focused at enabling third party users (such as developers and designers) to easily create and render 2D applications/games.

The aim for this engine is to eventually be cross-platform and cross-rendering API, however due to time and resource restrictions it currently only supports MacOS (utilising OpenGl rendering). 

This project has given me a greater understanding of Graphics and Game Development.

**Currently Implemented SubSystems** - Window, Debug, Event, Input, Layer, Logging, Batch Rendering, Camera

## Getting Started

Terminology:

**EndGame** - Static library that is called by the application

**SandBox** - An example application that utilises EndGame

Requirements: 

1.**MacOS** device(that supports OpenGL 4.1 version - https://support.apple.com/en-ca/HT202823)

2.**Xcode**(can be easily downloaded through AppStore - https://developer.apple.com/xcode/)

3.**Xcode Terminal Tools**(run `xcode-select --install` in terminal to ensure you have this downloaded)

There are two ways of running the SandBox Application(that utilises EndGame):

### Method A

1. run `vendor/premake/premake5 xcode4 --file="vendor/premake/premake5.lua"` from within `EndGame/EndGame` folder to build the xcode project and workspace

2. open the workspace file(EndGame.xcworkspace), run the ***Sandbox Application***(it will automatically build EndGame library) and give it permission to launch the application

### Method B

1. In order to automate this process, I have created a file called ***GenerateProjects.sh*** that can be run using `./GenerateProjects.sh`. It will ask whether you want to build the project, compile the project and finally run the application.
 
    The above shell file can also be run with two flags: 

    a. `./GenerateProjects.sh -quick-build` will automatically clear old projects, workspace, build them again, compile the project and run the Sandbox Application.

    b. `./GenerateProjects.sh -compile-run` as the name suggests will simply compile existing projects and workspace and run the Sandbox Application.

## How I built it

* **GLFW** - Window handling/creation

* **OpenGL** - Rendering

* **ImGui** - Debugging

* **GLM** - Math Library

* **SPDLog** - Logging

## What's next for EndGame

* **PacMan Game** - Currently working on building a PacMan game utilising the EndGame engine

* **Entity Component System**

* **Scripting**

* **Enabling Cross-platform functionality**
