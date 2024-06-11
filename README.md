# WeatherWidget
Description:
The Weather Widget is a graphical user interface (GUI) application built using Qt framework in C++. It displays weather information such as temperature, weather condition, and location. The widget features dynamic backgrounds and animations to simulate weather changes. Users can interact with the widget by clicking on the sun to change the weather condition.

Files:
widget.h: Header file containing the declaration of the Widget class, which inherits from QWidget. It includes declarations for member variables and functions used to create and manage the weather widget.

widget.cpp: Source file containing the implementation of the Widget class defined in widget.h. It includes the implementation of constructor, paintEvent, mousePressEvent, changeWeather, updateTime, and other helper functions.

main.cpp: Main source file containing the entry point of the application. It creates an instance of the QApplication and Widget classes to run the weather widget application.

Usage:
To use the Weather Widget application, compile the source files using a C++ compiler with Qt framework installed. Then, run the executable file generated after compilation. The weather widget will be displayed, showing the current weather information. Users can click on the sun to simulate weather changes.

Dependencies:
Qt framework
C++ compiler (e.g., g++, MSVC)
