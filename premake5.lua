workspace "SerialCommunication"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "SandboxApp"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "SerialCommunication"
include "SandboxApp"