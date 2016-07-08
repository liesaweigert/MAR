#include <GL/glew.h>
#define GLFW_INCLUDE_GLU

#include <iostream>
#include "GLFW/glfw3.h"
#include <opencv/cv.h>
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include "opencv2/opencv.hpp"
#include "MarkerTracker.h"
#include "RenderText.h"

#include <GLUT/glut.h>

using namespace cv;
using namespace std;


//camera settings
const int camera_width = 1280;
const int camera_height = 720;
const int virtual_camera_angle = 83;
unsigned char bkgnd[camera_width*camera_height * 3];

GLfloat black [4] = {0.0, 0.0, 0.0, 1.0};
GLfloat white [4] = {1.0, 1.0, 1.0, 1.0};
GLfloat red [4] = {1.0, 0.0, 0.0, 1.0};
GLfloat darkblue [4] = {0.0, 0.0, 0.5, 1.0};

/* program & OpenGL initialization */
void initGL(int argc, char *argv[])
{
	// initialize the GL library
	// pixel storage/packing stuff
	glPixelStorei(GL_PACK_ALIGNMENT, 1); // for glReadPixels​
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // for glTexImage2D​
	glPixelZoom(1.0, -1.0);

	// enable and set colors
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0, 0, 0, 1.0);

	// enable and set depth parameters
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);


	// light parameters
	GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_amb[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_dif[] = { 0.9, 0.9, 0.9, 1.0 };

	// enable lighting
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initVideoStream(cv::VideoCapture &cap)
{

	if (cap.isOpened())
		cap.release();

	cap.open(0); // open the default camera
}

void display(GLFWwindow* window, const Mat &img_bgr)
{
	memcpy(bkgnd, img_bgr.data, sizeof(bkgnd));

	int width0, height0;
	glfwGetFramebufferSize(window, &width0, &height0);

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// draw background image
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, camera_width, 0.0, camera_height);

	glRasterPos2i(0, camera_height - 1);
    glDrawPixels(camera_width, camera_height, GL_BGR, GL_UNSIGNED_BYTE, bkgnd);

	glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void render_bond(Eigen::Matrix4f from, Eigen::Matrix4f to){
	float radius = 0.01;

	float x_from = from(3, 0);
	float y_from = from(3, 1);
	float z_from = from(3, 2);

	float x_to = to(3, 0);
	float y_to = to(3, 1);
	float z_to = to(3, 2);

	//calculate the distance of the two atoms
	float x_diff = abs(x_from - x_to);
	float y_diff = abs(y_from - y_to);
	float z_diff = abs(z_from - z_to);

	float distance = sqrt(x_diff * x_diff + y_diff * y_diff + z_diff * z_diff);

	if (distance > 0 && distance < 0.4) {
		//glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glLineWidth(25);
		glColor3f(0.8, 0.8, 0.8);

		glBegin(GL_LINE_STRIP);
		glVertex3f(x_from, y_from, z_from);
		glVertex3f(x_to, y_to, z_to);
		glEnd();
	}
}


void display_atom(GLFWwindow* window, const Mat &img_bgr, Marker* markers){

	glMatrixMode(GL_MODELVIEW);

    for (int i = 0; i < 6; i++){
        if(markers[i].seen > 0) {
            glLoadTransposeMatrixf(markers[i].marker_matrix.data());
            markers[i].type.render_atom();

            for (int j = 0; j < 6; j++) {
                if (j != i) {
                    render_bond(markers[i].marker_matrix, markers[j].marker_matrix);
                }
            }
        }
	}

}

void display_reference(GLFWwindow* window){
	render_text("Hydrogen", 20, 20, white, 48);
	render_text("Oxygen", 20, 80, red, 48);
    render_text("Carbon", 20, 140, black, 48);
    render_text("Nitrogen", 20, 200, darkblue, 48);
}


int main(int argc, char* argv[])
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	// initialize the window system
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(camera_width, camera_height, "Combine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	int window_width, window_height;
	glfwGetFramebufferSize(window, &window_width, &window_height);
    glViewport(0, 0, window_width, window_height);

    //initialize glew
    glewExperimental = GL_TRUE;
    glewInit();

	// initialize the GL library
	initGL(argc, argv);

	//set up text rendering
	init_resources();

	// setup OpenCV
	Mat img_bgr;
	VideoCapture cap;
	initVideoStream(cap);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(virtual_camera_angle, (double)window_width/(double)window_height, 0.01, 100);


	Marker markers[6];
	init_markers(markers);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		cap >> img_bgr;

        flip(img_bgr, img_bgr, 1);

		if (img_bgr.empty()){
			std::cout << "Could not query frame. Trying to reinitialize." << std::endl;
			initVideoStream(cap);
			cv::waitKey(1000); // Wait for one sec.
			continue;
		}

		/* Find the markers in the frame */
		MarkerTracker mt;
        mt.find(img_bgr, markers, 6);

        display(window, img_bgr);

		display_reference(window);

		display_atom(window, img_bgr, markers);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}


	glfwTerminate();

	return 0;
}
