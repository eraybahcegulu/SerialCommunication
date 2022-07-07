workspace "SerialCommunication"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "SerialCommunicationModule"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "../SandboxApp"

project "SerialCommunicationModule"
    kind "StaticLib"

    targetdir("../bin" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int" .. outputdir .. "/%{prj.name}")

    
    includedirs{
        "include"
    }

    files {
        "src/SerialPort.cpp",
        "include/SerialPort.h"
    }