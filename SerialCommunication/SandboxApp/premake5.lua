project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("../bin" .. outputdir .. "/%{prj.name}")
    objdir("../bin-int" .. outputdir .. "/%{prj.name}")

    files {
        "src/main.cpp"
    }

    includedirs{
        "../SerialCommunication/include"
    }

    links { "SerialCommunicationModule" }