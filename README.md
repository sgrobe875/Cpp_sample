# Final-Project-sgrobe
Sarah Grobe

## Program Description
This program is a 2D fishing video game. Fish swim across the screen in both directions, and the user can move around a fishing hook which follows the cursor to catch the fish by clicking on them. Each time a fish is caught, it will disappear from the screen and increment a tallying variable, which will then return the total number of fish caught to the user at the end of the game. Additionally, once the game has been finished by hitting the escape key to close the graphics window, the name and final score of the user will be appended to a file. The name of the user is obtained from their input into the console at the beginning of the program run. All of the records in the file will then be printed into the console for the user before the program exits.

This program was created and run on a Mac (11.6.2), and required no additional installations.

The only piece of code which was accessed from outside the materials of this course or CS 124 is the portion for writing to a file, lines 120-126 in graphics.cpp. The following website was used to help with the syntax, and the code from it was used as a guide for writing the code in the writeScore function:
https://www.delftstack.com/howto/cpp/how-to-append-text-to-a-file-in-cpp/

## Module Concepts

### Module 2
This project utilizes the is-a and has-a relationships from module 2, and polymorphism as a result of those relationships. For instance, the Triangle and Rect classes are subclasses of Shape, and some of the structs are collections of these shapes, such as the fish being comprised of three triangles and a rectangle. Additionally, the reading and writing of scores to a file references the module 2 I/O stream concepts.


### Module 4
Visually, this project uses many of the graphics features from module 4. In particular, timers, keyboard events, mouse click events, and cursor effects were utilized, as well as the drawing of many different shapes within the graphics window.
