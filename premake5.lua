workspace "Workspace"
    architecture "x64"

    configurations {
        "Debug",
        "Release"
    }

    startproject "Project"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Project"