# CppSerialCommunication

## Description

Library for communicating with COM ports on a Windows system.

* `premake` based build system

## Building Using Premake

1. Clone the git repository onto your local storage.

1. Include the spdlog library 

    ```
    SerialCommunication/vendor/spdlog
	```

1. Change into root repository directory

    ```
	$ cd SerialCommunication
	```

1. Generate project files by running a command like this one

    ```
	$ premake5 vs2019
	```
1. You can see a complete list of the actions and other options supported by a project with the command

    ```
	$ premake5 --help
	```