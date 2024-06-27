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

## Implementation

Quick overview of how the "Weather Widget" task was implemented:

Initialization: When you create a widget, establish the window title and size, as well as the labels for temperature, location, weather, and time. Set up timers to update the time and weather conditions.

Layout: For better organisation, arrange the labels vertically and horizontally.

Background: To create a picturesque backdrop, apply a gradient background and draw mountain shapes with QPainter.

Weather Indicator: Draw circles symbolising the sun and moon based on the weather conditions. Handle mouse clicks on the sun to cause weather variations.

Weather Update: Create a function that changes weather conditions cyclically throughout predetermined cities, along with accompanying temperatures, weather conditions, and visual styles. Adjust the label texts, colours, gradients, and background accordingly.

Time Update: The widget's current time should be updated on a regular basis.

## How It Works

![Demo](https://www.canva.com/design/DAGJTnc5020/mffbZvSEK35Ie8cH1aJtMg/watch?utm_content=DAGJTnc5020&utm_campaign=designshare&utm_medium=link&utm_source=editor)

[Watch the Demo Video](https://www.kapwing.com/e/6672860e1855819b7c7200e0)

