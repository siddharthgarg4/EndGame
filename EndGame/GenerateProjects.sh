#!/bin/sh

promptUserInput() {
    while true; do
        read -p "$1 y/n " yn
        case "${yn:-y}" in 
            [Yy]* ) return 0;;
            [Nn]* ) return 1;;
            * ) echo "please answer y/n";;
        esac
    done
}
if [ $# -ne 0 ] && [ $# -ne 1 ]; then 
    echo "Error! wrong number of flags! script terminated!"
    exit
else
    if [ $# -eq 0 ]; then
        isQuickBuild=false
        isCompileRun=false
    else
        if [ $1 == "-quick-build" ]; then
            isQuickBuild=true
            isCompileRun=false
        elif [ $1 == "-compile-run" ]; then 
            isCompileRun=true
            isQuickBuild=false
        else
            echo "Error! wrong usage of flag! script terminated!"
            exit
        fi
    fi
fi

echo "Welcome to EndGame"
if $isQuickBuild || ( [ $isCompileRun != true ] && promptUserInput  "Do you want to remove any old projects?" ); then
    rm -rf Sandbox.* EndGame.* bin *.ini
    vendor/premake/premake5 xcode4 --file="vendor/premake/premake5.lua"
fi

if $isQuickBuild || $isCompileRun || promptUserInput  "Do you want to compile EndGame library and Sandbox application?"; then 
    echo "Xcode compile started..."
    xcodebuild -scheme Sandbox -workspace EndGame.xcworkspace > xcode.log
    echo "Xcode compile complete"
fi

if $isQuickBuild || $isCompileRun || promptUserInput  "Do you want to run Sandbox Application"; then 
    bin/Debug-macosx-x86_64/EndGame/Sandbox
fi
