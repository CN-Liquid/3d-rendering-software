# 3d-rendering-software
A simple 3d renderer
# Project Members
* [Aakash Adhikari (Contact - 9823763231)](https://github.com/CN-Liquid)
* [Aweenas Kumar Yadav (Contact - 9826773339)](https://github.com/awenassyyy)
* [Nabin Joshi (Contact - 9806455120)](https://github.com/Nabin-16)
* [Kshitiz Portel (Contact - 9744330530)](https://github.com/KshitizPortel)
# Prequisites
All necessary files for compilation is already 
included with the software
# Compilation
The program should be compiled using the command\
```bash
g++ -I src/include -L src/lib -o main main.cpp -m64 -lmingw32 -lSDL2main -lSDL2
```
or by running make.bat or if makefile is installed then simply by executing make in the directory of the program.\
\
The g++ compiler should default to 64-bit compile mode if the 64-bit version is installed, if not the program will compile fine but crash after executing for some time. So make sure the 64-bit version of g++ is setup before compiling the program.

# Running The program
To render a scene we need to provide an object file that contains the vertices and indices information of the scene .That can be done manually or by downloading the obj files of different models from the internet and extracting the vertices and indices information. We have provided some test object files with our program.\
Those can be rendered by passing the name of the file to the load_object_from_file function inside the render function in the main file.
