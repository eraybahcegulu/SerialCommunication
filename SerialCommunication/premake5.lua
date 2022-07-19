project "SerialCommunicationModule"
    kind "StaticLib"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    
    includedirs
    {
        "include"
    }

    files 
    {
        "src/SerialPort.cpp",
        "include/SerialPort.h"
    }