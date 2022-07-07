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

    

project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("../bin" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int" .. outputdir .. "/%{prj.name}")

    files {
        "src/main.cpp"
    }

    includedirs{
        "include"
    }

    links { "SerialCommunicationModule" }