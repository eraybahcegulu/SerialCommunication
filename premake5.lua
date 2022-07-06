workspace "SerialCommunication"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "SerialCommunicationModule"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "SerialCommunication"