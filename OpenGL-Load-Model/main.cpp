#include "main.h"
#include<iostream>

int POS_X, POS_Y;

bool LIGHT_OFF = false;

std::string model_name = "Models/sample-tree-with-car.obj";

GLfloat light_pos[] = {-10.0f, 10.0f, 100.00f, 1.0f};

float pos_x, pos_y, pos_z;
float angle_x = 30.0f, angle_y = 0.0f;

int x_old = 0, y_old = 0;
int current_scroll = 10;
float zoom_per_scroll;

bool is_holding_mouse = false;
bool is_updated = false;

Model model;



// -------------------------------------------------------------------------------

int windowWidth = 800;
int windowHeight = 600;

// --------------------------------------------------

void init() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20.0, 1.0, 1.0, 2000.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    model.load(model_name.c_str());

    pos_x = model.pos_x;
    pos_y = model.pos_y;
    pos_z = model.pos_z - 1.0f;

    zoom_per_scroll = -model.pos_z / 10.0f;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(pos_x, pos_y, pos_z);
    glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    model.draw();
    glutSwapBuffers();
}

// void lightControlDisplay() {
//     glClear(GL_COLOR_BUFFER_BIT);

//     // Render GUI
//     glColor3f(1.0f, 1.0f, 1.0f);
//     glRasterPos2f(-0.9f, 0.9f);
//     glutBitmapString(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char*>("Light Position Control"));
    
//     // Render sliders
//     glRasterPos2f(-0.9f, 0.7f);
//     glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("X:"));
//     glutWireCube(light_pos[0] * 0.1f);

//     glRasterPos2f(-0.9f, 0.5f);
//     glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("Y:"));
//     glutWireCube(light_pos[1] * 0.1f);

//     glRasterPos2f(-0.9f, 0.3f);
//     glutBitmapString(GLUT_BITMAP_HELVETICA_12, reinterpret_cast<const unsigned char*>("Z:"));
//     glutWireCube(light_pos[2] * 0.1f);

//     glFlush();
//     glutSwapBuffers();
// }

void timer(int value) {
    if (is_updated) {
        is_updated = false;
        glutPostRedisplay();
    }
    glutTimerFunc(INTERVAL, timer, 0);
}

void mouse(int button, int state, int x, int y) {
    is_updated = true;

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            x_old = x;
            y_old = y;
            std::cout << "Mouse clicked at window coordinates: (" << x << ", " << y << ")" << std::endl;
            is_holding_mouse = true;
        } else
            is_holding_mouse = false;
    } else if (state == GLUT_UP) {
        switch (button) {
            case 3:
                if (current_scroll > 0) {
                    current_scroll--;
                    pos_z += zoom_per_scroll;
                }
                break;
            case 4:
                if (current_scroll < 40) {
                    current_scroll++;
                    pos_z -= zoom_per_scroll;
                }
                break;
        }
    }
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 27) { // Escape key
        exit(0);
    } else if (key == GLUT_KEY_F1) { // ASCII code for F1 key (112)
        // Perform the action you want when F1 is pressed
        std::cout << "F1 key pressed! Something should happen..." << std::endl;
    }
}


void motion(int x, int y) {
    if (is_holding_mouse) {
        is_updated = true;

        angle_y += (x - x_old);
        x_old = x;
        if (angle_y > 360.0f)
            angle_y -= 360.0f;
        else if (angle_y < 0.0f)
            angle_y += 360.0f;

        angle_x += (y - y_old);
        y_old = y;
        if (angle_x > 90.0f)
            angle_x = 90.0f;
        else if (angle_x < -90.0f)
            angle_x = -90.0f;
    }
}

void specialKeyboard(int key, int x, int y) {
    if (key == GLUT_KEY_F1) {
            glDisable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
    }
    else if (key == GLUT_KEY_F2){
            glDisable(GL_LIGHT1);
            glEnable(GL_LIGHT0);
    }else {
        switch (key) {
            case GLUT_KEY_LEFT:
                std::cout << "left " << std::endl;
                light_pos[0] -= 1.0f;
                break;
            case GLUT_KEY_RIGHT:
                std::cout << "right" << std::endl;
                light_pos[0] += 1.0f;
                break;
            case GLUT_KEY_UP:
                std::cout << "up " << std::endl;
                light_pos[1] += 1.0f;
                break;
            case GLUT_KEY_DOWN:
                std::cout << "down" << std::endl;
                light_pos[1] -= 1.0f;
                break;
            case GLUT_KEY_PAGE_UP:
                std::cout << "pageup " << std::endl;
                light_pos[2] += 1.0f;
                break;
            case GLUT_KEY_PAGE_DOWN:
                std::cout << "pagedown " << std::endl;
                light_pos[2] -= 1.0f;
                break;
        }
    }

    glutPostRedisplay(); // Request a redisplay to update the scene
}

// void reshape(int width, int height) {
//     glViewport(0, 0, width, height);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//     glMatrixMode(GL_MODELVIEW);
//     glLoadIdentity();
// }

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutKeyboardFunc(keyboard); // Register the keyboard function

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;


    // ---------------
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Main Window");
    init();
    // ----------------

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard); // Register the keyboard function
    glutSpecialFunc(specialKeyboard); // Register the special keyboard function
    glutTimerFunc(0, timer, 0);




    // ---------------
    // glutInitWindowSize(400, 300);
    // glutInitWindowPosition(300, 300); 
    // glutCreateWindow("Light Position Control");
    // glutDisplayFunc(lightControlDisplay);
    // glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    // glutReshapeFunc(reshape);

    // --------------


    glutMainLoop();
    return 0;
}
