    #include "main.h"
    #include<iostream>

    #include <cmath>
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    // #include <map> 

    #include <string>
    // #include "../Library/imgui-master/imgui.h"
    // #include "../Library/imgui-master/backends/imgui_impl_glut.h" // ImGui integration for GLUT




    int POS_X, POS_Y;

    bool LIGHT_OFF = false;

    std::string model_name = "Models/final_track1.obj";

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


    Model carModel; // Assuming you have a Model class for loading models

    // Car position
    float car_pos_x = 0.0f;
    float car_pos_y = 8.4f;
    float car_pos_z = -3.0f;

    float car_rotation = 0.0f;
    float rotation_speed = 2.0f; // Adjust the rotation speed as needed

    // std::map<unsigned char, bool> keyStates;

    bool wPressed = false;
    bool aPressed = false;
    bool sPressed = false;
    bool dPressed = false;

    // ---------------------------------------------------
    std::string selectedColor;


    // Path to the car models for different colors
    std::map<std::string, std::string> carModelPaths = {
        {"Red", "Models/red_car.obj"},
        {"Green", "Models/green_car.obj"},
        {"Yellow", "Models/yellow_car.obj"},
        {"Blue", "Models/blue_car.obj"},
        {"Pink", "Models/pink_car.obj"}
    };

    //  ------------------------

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

        // --------
        // Render the car model
        glPushMatrix();
        glTranslatef(car_pos_x, car_pos_y, car_pos_z);
        glRotatef(car_rotation, 0.0f, 1.0f, 0.0f); // Apply rotation to the car
        carModel.draw();
        glPopMatrix();

        glutSwapBuffers();
    }

// Keyboard up function
void keyboardUp(unsigned char key, int x, int y) {
    // Set key states to false when keys are released
    if (key == 'w') {
        wPressed = false;
    } else if (key == 'a') {
        aPressed = false;
    } else if (key == 's') {
        sPressed = false;
    } else if (key == 'd') {
        dPressed = false;
    }
}   

void timer(int value) {
            // Check for key combinations and perform actions
if (wPressed && aPressed) {
        // Move car forward and rotate left
        glm::vec3 forwardVector = glm::rotate(glm::mat4(0.6f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, -0.05f, 1.0f); // Decreased speed
        car_pos_x += forwardVector.x;
        car_pos_z += forwardVector.z;
        car_rotation += rotation_speed;
    } else if (wPressed && dPressed) {
        // Move car forward and rotate right
        glm::vec3 forwardVector = glm::rotate(glm::mat4(0.6f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, -0.1f, 1.0f);
        car_pos_x += forwardVector.x;
        car_pos_z += forwardVector.z;
        car_rotation -= rotation_speed;
    }else if (sPressed && aPressed) {
        // Move car backward and rotate left
        glm::vec3 backwardVector = glm::rotate(glm::mat4(0.6f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);
        car_pos_x += backwardVector.x;
        car_pos_z += backwardVector.z;
        car_rotation += rotation_speed; // Rotate car left
    } else if (sPressed && dPressed) {
        // Move car backward and rotate right
        glm::vec3 backwardVector = glm::rotate(glm::mat4(0.6f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.05f, 1.0f); // Decreased speed
        car_pos_x += backwardVector.x;
        car_pos_z += backwardVector.z;
        car_rotation -= rotation_speed; // Rotate car right
    }else if (wPressed) {
        // Move car forward
        glm::vec3 forwardVector = glm::rotate(glm::mat4(1.0f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, -0.1f, 1.0f);
        car_pos_x += forwardVector.x;
        car_pos_z += forwardVector.z;
    }

    if (aPressed) {
        // Rotate car left
        car_rotation += rotation_speed; // Rotate car left
    }
    if (sPressed) {
        // Move car backward
        glm::vec3 backwardVector = glm::rotate(glm::mat4(1.0f), glm::radians(car_rotation), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(0.0f, 0.0f, 0.1f, 1.0f);
        car_pos_x += backwardVector.x;
        car_pos_z += backwardVector.z;
    }
    if (dPressed) {
        // Rotate car right
       car_rotation -= rotation_speed; // Rotate car right
    }

    // Redisplay the scene
    if (is_updated) {
        is_updated = false;
        glutPostRedisplay();
    }


    // Redisplay the scene
    glutPostRedisplay();
    glutTimerFunc(INTERVAL, timer, 0);
}



    void mouse(int button, int state, int x, int y) {
        is_updated = true;

        if (button == GLUT_LEFT_BUTTON) {
            if (state == GLUT_DOWN) {
                x_old = x;
                y_old = y;

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
    } else     if (key == 'w') {
        wPressed = true;
    } else if (key == 'a') {
        aPressed = true;
    } else if (key == 's') {
        sPressed = true;
    } else if (key == 'd') {
        dPressed = true;  // Rotate car right
    } else if (key == '1') { // Move car up ('1' key)
        car_pos_y -= 0.1f; // Move car up
    } else if (key == '2') { // Move car down ('2' key)
        car_pos_y += 0.1f; // Move car down
    }else if (key == 'r') {
        selectedColor = "Red";
        carModel.load(carModelPaths[selectedColor].c_str());
    } else if (key == 'g') {
        selectedColor = "Green";
        carModel.load(carModelPaths[selectedColor].c_str());
    } else if (key == 'y') {
        selectedColor = "Yellow";
        carModel.load(carModelPaths[selectedColor].c_str());
    } else if (key == 'b') {
        selectedColor = "Blue";
        carModel.load(carModelPaths[selectedColor].c_str());
    } else if (key == 'p') {
        selectedColor = "Pink";
        carModel.load(carModelPaths[selectedColor].c_str());
    }


    glutPostRedisplay(); // Request a redisplay to update the scene
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


    int main(int argc, char **argv) {
        glutInit(&argc, argv);
        
        glutKeyboardFunc(keyboard); // Register the keyboard function

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
        glutSetOption(GLUT_MULTISAMPLE, 8);
        POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
        POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;



        glutInitWindowPosition(POS_X, POS_Y);
        glutInitWindowSize(WIDTH, HEIGHT);
        glutCreateWindow("Main Window");
        init();


        glutDisplayFunc(display);
        glutMouseFunc(mouse);
        glutMotionFunc(motion);
        glutKeyboardFunc(keyboard); // Register the keyboard function
        glutKeyboardUpFunc(keyboardUp);
        glutSpecialFunc(specialKeyboard); // Register the special keyboard function

        glutTimerFunc(0, timer, 0);

        // -------------------------
        selectedColor = "Blue";
        carModel.load(carModelPaths[selectedColor].c_str());


        glutMainLoop();
        return 0;
    }
