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