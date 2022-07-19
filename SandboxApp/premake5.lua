project "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
        "src/main.cpp"
    }

    includedirs
    {
        "%{wks.location}/SerialCommunication/include"
    }

    links { "SerialCommunicationModule" }