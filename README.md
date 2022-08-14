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
