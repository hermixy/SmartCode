SmartCode is an educational purpos IDE written in C++,based on the Qt framework,it can be ported to many platforms,it’s composed of a text editor based on the qscintilla project and use gcc Compiler to compiler C++ files,the current project manager use XML for saving and loading projects.

Required Configuration to build :

- Qt 4.8.0 or higher version of the Qt library

- QSCINTILLA 2

- GCC 4.4.0 or higher

The project use Qmake for managing project

The project is splitted into sub project each sub project is compiled to a dynamic Link library (DLL) :

- The app module : contain main and mainwindow 

- The core module : contain common classes used cross the application

- The build module : use to invoke compiler and debugger and generate makefiles.

- The gui module : contain application interface

- The texteditor : contain the Text Editor

- The compability module : contain classes responsible for reading projects from another IDE ‘s,only CodeBlocks is supported for now.

- The options module : contain IDE ‘s various configuration as compilers managing and detection and texteditor preferences  and more.

- The consoleluncher module : used to execute compiled programs.

- The search module : used to search files in IDE or text in texteditor.

- Version control module : contain tools used for versioning,only git is supported.
