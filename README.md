# Employee Management System

## Project Introduction

This is a file management system developed in C++ with a significant advantage in extensibility. To add new modules, simply inherit from the `AbstractModule` abstract class and create a corresponding derived class. Register the new module in the main program to enable it without modifying any other parts of the code. The abstract class is declared in `include/module.h` and implemented in `lib/module.cpp`. The main program file is located at `lib/main.cpp`.

## Deployment Instructions

1. Clone the repository to your local machine using the following command:

   ```bash
   git clone https://github.com/Cipivious/employee_management_system.git
   ```

2. After cloning, navigate to the project directory using the `cd` command:

   ```bash
   cd employee_management_system
   ```

3. Compile the project from the root directory (ensure CMake is installed and configured on your system):

   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. After compilation, an executable named `MyExecutable` will be generated. On its first run, it will automatically create a file named `info.txt` to save data.

## Alternative Version

There is also a single-file version of the project available in the `one_file_version` folder. This version can be used if CMake is not installed on your system.
