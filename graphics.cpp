#include "graphics.h"
// #include "Button.h"
// #include "fish.h"
#include <iostream>
#include <time.h>
#include "rect.h"
#include "triangle.h"
#include "fish.h"
#include <vector>
#include "boat.h"
#include "hook.h"
#include <fstream>
using namespace std;

// globals
GLdouble width, height;
int wd;
int choice;
int tally = 0;
bool clicked = false;
string name;

hook user = createHook(dimens(40,40), 50.0, 50.0);

vector<unique_ptr<fish>> fishies;
vector<unique_ptr<boat>> boats;

// obtain and validate string input from user
string getStringInput(string message) {
    string input;
    // assume the input is valid by default
    bool valid = true;

    cout << message;
    cin >> input;

    // check each character in the input; don't allow digits
    for (int i = 0; i < input.length(); i++){
        (!isdigit(input[i])) ? valid = valid : valid = false;
    }

    // as long as at least one character in the user input is not a valid character, repeatedly ask for user input
    while (!(valid)) {
        // print helpful message before asking again
        cout << "Please use only letters." << endl;
        cout << message;

        // clear variables and obtain user input
        cin.clear();
        string junk;
        getline(cin, junk);
        cin >> input;

        // repeat validation
        valid = true;
        for (int i = 0; i < input.length(); i++){
            (!isdigit(input[i])) ? valid = valid : valid = false;
        }
    }

    // return final validated input
    return input;
}

// obtain and validate integer input from the user
int getIntInput(string message) {
    string input;
    int inputInt;

    // assume the input is a valid integer by default
    bool valid = true;

    cout << message;
    cin >> input;

    // check each character in the input; only allow digits or negative sign
    for (int i = 0; i < input.length(); i++){
        (isdigit(input[i])) ? valid = valid : valid = false;
    }

    if (valid) {
        inputInt = stoi(input);
        if (inputInt > 4 || inputInt < 1) {
            valid = false;
        }
    }

    // as long as at least one character in the user input is not an int, repeatedly ask for user input
    while (!(valid)) {
        // print helpful message before asking again
        cout << "Please enter an integer value between 1 and 4." << endl;
        cout << message;

        // clear variables and obtain user input
        cin.clear();
        string junk;
        getline(cin, junk);
        cin >> input;

        // repeat integer validation
        valid = true;
        for (int i = 0; i < input.length(); i++){
            (isdigit(input[i])) ? valid = valid : valid = false;
        }

        if (valid) {
            inputInt = stoi(input);
            if (inputInt > 4 || inputInt < 1) {
                valid = false;
            }
        }
    }

    // once user input is a valid integer, return it
    return inputInt;
}

// writing to a file code modified from: https://www.delftstack.com/howto/cpp/how-to-append-text-to-a-file-in-cpp/
// appends the name and final score from the game once it has been finished
void writeScore() {
    string filename("../scores.txt");
    ofstream file_out;
    file_out.open(filename, ios_base::app);
    file_out << name << "\t" << tally << endl;
    file_out.close();
}

// print the saved scores from the file to the console
void showScores() {
    ifstream inFile("../scores.txt");

    cout << "Here are the scores for your most recent games:" << endl;
    string line;
    while (inFile && inFile.peek() != EOF) {
        getline(inFile, line);
        cout << line << endl;
    }
}

// initialize conditions
void init() {
    width = 1200;
    height = 800;
    srand(time(0));

    // string input - obtain the user's name
    string message = "Please enter your name: ";
    name = getStringInput(message);
    cout << "Welcome, " << name << "!" << endl;

    // int input - obtain a choice for boat color
    message = "Please choose either 1, 2, 3, or 4: ";
    choice = getIntInput(message);
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // boat colors based on user input: brown, yellow, green, purple
    vector<float> boatColor;
    if (choice == 1) {
        boatColor.push_back(135/255.0);
        boatColor.push_back(101/255.0);
        boatColor.push_back(76/255.0);
    } else if (choice == 2) {
        boatColor.push_back(1.0);
        boatColor.push_back(1.0);
        boatColor.push_back(0.0);
    } else if (choice == 3) {
        boatColor.push_back(0.0);
        boatColor.push_back(1.0);
        boatColor.push_back(0.0);
    } else {
        boatColor.push_back(0.5);
        boatColor.push_back(0.0);
        boatColor.push_back(0.5);
    }

    // draw water for 80% fo the window
    Rect water = Rect(dimensions(width, height * 0.8));
    water.setColor(0.0f,0.0f, 1.0f, 0.8f);
    water.setCenterX(width/2);
    water.setCenterY(height * 0.6);
    water.draw();

    // initialize the fish color (red by default)
    vector<float> fishColor;
    fishColor.push_back(1.0);
    fishColor.push_back(0.0);
    fishColor.push_back(0.0);

    // create boat
    double boatHeight = 100;
    boats.push_back(make_unique<boat>(createBoat(dim(400,boatHeight), width/2, (height * 0.2) - (boatHeight / 2.0) + 30, boatColor)));


    // create fish, add to a vector of all fish
    fishies.push_back(make_unique<fish>(createFish(ds(120,40), fishRight, 1000,250, fishColor)));
    fishies.push_back(make_unique<fish>(createFish(ds(220,80), fishLeft, 400,500, fishColor)));
    fishies.push_back(make_unique<fish>(createFish(ds(200,50), fishRight, 600,700, fishColor)));



    // draw the boat
    boats[0]->body.draw();
    for (int i=0; i < 2; ++i) {
        boats[0]->triPieces[i]->draw();
    }

    // draw the water
    water.draw();

    // draw the three fish
    for (int i=0; i < 3; ++i) {
        fishies[i]->body.draw();
        for (int j = 0; j < 3; j++) {
            fishies[i]->triPieces[j]->draw();
        }

    }

    // draw the hook (in the top left corner of the window until the cursor is moved)
    user.rectanglePiece.draw();
    for (int i=0; i < 2; ++i) {
        user.triPieces[i]->draw();
    }

    // render
    glFlush();

}

void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        // end the game
        glutDestroyWindow(wd);
        // print game results
        cout << "You caught " << tally << " fish! Thanks for playing!" << endl;
        // write score to a file and print all scores in the file
        writeScore();
        showScores();
        // exit the program
        exit(0);
    }

    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    // move the boat left or right with the arrow keys, but not up or down
    switch(key) {
        case GLUT_KEY_DOWN:

            break;
        case GLUT_KEY_LEFT:
            moveBoat(boats[0], 15.0, "left");
            break;
        case GLUT_KEY_RIGHT:
            moveBoat(boats[0], 15.0, "right");
            break;
        case GLUT_KEY_UP:

            break;
    }

    glutPostRedisplay();
}

// cursor will look like a fishing hook
void cursor(int x, int y) {
    user = createHook(dimens(40,40), x, y);

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    double fishX, fishY, fishWidth, fishHeight;
    // when the left mouse button is clicked
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // check to see if it was clicked on a fish
        for (unique_ptr<fish> &fishy : fishies) {
            // get dimensions of all fish
            fishX = fishy->body.getCenterX();
            fishY = fishy->body.getCenterY();
            fishWidth = fishy->d.width;
            fishHeight = fishy->d.height;
            // if mouse was overlapping with fish when button was clicked
            if ((x < fishX + fishWidth/2 && x > fishX - fishWidth/2) && (y < fishY + fishHeight/2 && y > fishY - fishHeight / 2)) {
                // reset the fish
                resetFish(fishy);
                clicked = true;
            }
        }
    }

    // to ensure an accurate tally, count the fish caught when the mouse button is released after being clicked
    if (clicked && button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        tally += 1;
        clicked = false;
    }

    glutPostRedisplay();
}

// timer to move the three fish across the screen
void fishTimer(int dummy) {
    for (unique_ptr<fish> &fishy : fishies) {
        // move each fish in the vector
        moveFish(fishy, 5.0);

        // if it has moved off the screen in either direction:
        if (fishy->triPieces[2]->getCenterX() < -200) {
            // Set it to the right of the screen so that it passes through again
            resetFish(fishy);
        } else if (fishy->triPieces[2]->getCenterX() > 1630) {
            // or reset it to the left of the screen
            resetFish(fishy);
        }

    }

    glutPostRedisplay();
    glutTimerFunc(20, fishTimer, dummy);
}


/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Fishing Game!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, fishTimer, 0);

    // Enter the event-processing loop
    glutMainLoop();


    return 0;
}
