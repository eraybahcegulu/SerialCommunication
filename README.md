# CppSerialCommunication
![Screenshot_1](https://github.com/eraybahcegulu/SerialCommunication/assets/84785201/40fb057a-6ba6-4b92-bef2-6a7f573d0164)
![Screenshot_3](https://github.com/eraybahcegulu/SerialCommunication/assets/84785201/93d420f3-b92b-4fb6-a9b9-8a989c2cd40f)
![Screenshot_4](https://github.com/eraybahcegulu/SerialCommunication/assets/84785201/73295d3d-c215-42dc-8bca-1073ea971f12)
![Screenshot_2](https://github.com/eraybahcegulu/SerialCommunication/assets/84785201/8e47925c-538c-4bda-88c5-2305dc4f3a11)

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
	$ premake5 vs2022
	```
1. You can see a complete list of the actions and other options supported by a project with the command

    ```
	$ premake5 --help
	```
