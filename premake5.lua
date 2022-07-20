workspace "SerialCommunication"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "SandboxApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["spdlog"] = "SerialCommunication/vendor/spdlog/include"

includedirs
{
    "SerialCommunication/vendor/spdlog/include"
}

include "SerialCommunication"
include "SandboxApp"