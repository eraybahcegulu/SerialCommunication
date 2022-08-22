project "SerialCommunicationModule"
    kind "StaticLib"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    
    includedirs
    {
        "include",
        "vendor/spdlog/include"
    }

    files 
    {
        "src/SerialPort.cpp",
        "include/SerialPort.h",
        "include/Core.h",
        "vendor/spdlog/include/spdlog/**.h"
    }