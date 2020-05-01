// HonoursProjectFinal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "glm/glm/glm.hpp"
#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include "glut.h"
#include <vector>
#include "OBJ_Loader.h"

//All Variables needed for the system
GLint WindowWidth, WindowHeight;
GLfloat CameraZoom = 50.0;
float PanningX = 0.f;
GLfloat Radius = 10.0;
GLfloat PhiEquation = 0.0;
GLfloat ThetaEquation = 0.0;
GLfloat CameraX = 0.0;
GLfloat CameraY = 0.0;
GLfloat CameraZ = 0.0;
GLfloat TempX = 0.0;
GLfloat TempY = 0.0;
GLfloat TempZ = 0.0;
GLfloat VectorX = 0.0;
GLfloat VectorY = 0.0;
GLfloat VectorZ = 0.0;

std::vector<glm::vec3> Vertices;
std::vector<glm::vec3> Indices;



void InitGL(GLvoid) { //Sets up the window using OpenGL functions
	glClearColor(0.0, 0.0, 0.0, 0.0); //Makes the window background black
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT); //Makes all sides of the object render all the time and uses the ambient light effect(solid colours)
}

void CreateXYZ(void) {
	glTranslatef(0.0, 0.0, 0.0); //Sets middle point for the coordinates
	glLineWidth(5.0); //States the size of the Axis lines

	glBegin(GL_LINES); //Starts creation of axis

	glColor3f(1.0, 0.0, 0.0); //Sets colour for X axis (Red)
	glVertex3f(0.0, 0.0, 0.0); //Sets start point for X axis
	glVertex3f(5.0, 0.0, 0.0); //Sets end point for X axis

	glColor3f(0.0, 1.0, 0.0); //Sets colour for Y axis (Green)
	glVertex3f(0.0, 0.0, 0.0); //Sets start point for Y axis
	glVertex3f(0.0, 5.0, 0.0); //Sets end point for Y axis

	glColor3f(0.0, 0.0, 1.0); //Sets colour for Z axis (Blue)
	glVertex3f(0.0, 0.0, 0.0); //Sets start point for Z axis
	glVertex3f(0.0, 0.0, 5.0); //Sets end point for Z axis

	glEnd(); //Stops creation of axis

}





void WindowDisplay(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(CameraZoom, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.1, 100);
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(CameraX, CameraY, CameraZ, PanningX, 0, 0, VectorX, VectorY, VectorZ);

	CreateXYZ();
	ImageDraw();

	glFlush();
	glutSwapBuffers();
}

void FileLoader() {
	bool Test = LoadFile("Test.obj", Vertices, Indices);

}

void ImageDraw(void) {

	glBegin(GL_POINTS);

	for (int i = 0; i < Indices.size(); i++) {

		glNormal3f(Vertices[Indices[i].x - 1].x, Vertices[Indices[i].x - 1].y, Vertices[Indices[i].x - 1].z);
		glVertex3f(Vertices[Indices[i].x - 1].x, Vertices[Indices[i].x - 1].y, Vertices[Indices[i].x - 1].z);
	}
	glEnd();
}


void MouseControl(int x, int y) {
	
	WindowWidth = glutGet(GLUT_WINDOW_WIDTH); //Gets current window width position
	WindowHeight = glutGet(GLUT_WINDOW_HEIGHT); //Gets current window height position

	PhiEquation = (360.0 / WindowWidth) * x * 2.0; //Sets the window to allow 2 rotations either going left or right

	ThetaEquation = (360.0 / WindowHeight) * y * 2.0; // Sets the window to allow 2 rotations either going up or down

	CameraX = Radius * sin(ThetaEquation * 0.01745) * sin(PhiEquation * 0.01745); //Converts Spherical coordinates into Cartesian coordinates on the X axis

	CameraY = Radius * cos(ThetaEquation * 0.01745); //Converts Spherical coordinates into Cartesian coordinates on the Y axis

	CameraZ = Radius * sin(ThetaEquation * 0.01745) *cos(PhiEquation * 0.01745); //Converts Spherical coordinates into Cartesian coordinates on the Z axis

	GLfloat Temp = 1.0; 

	TempX = Radius * sin(ThetaEquation * 0.01745 - Temp) * sin(PhiEquation * 0.01745); //Axis converstion on X minus 1 

	TempY = Radius * cos(ThetaEquation * 0.01745 - Temp); //Axis converstion on Y minus 1 

	TempZ = Radius * sin(ThetaEquation * 0.01745 - Temp) * cos(PhiEquation * 0.01745); //Axis converstion on Z minus 1 

	VectorX = TempX - CameraX; //Finds the Up vector for X

	VectorY = TempY - CameraY; //Finds the Up vector for Y

	VectorZ = TempZ - CameraZ; //Finds the Up vector for Z

	glutPostRedisplay(); //Forces the window to update to new angle


}




void main(int argc, char** argv) {

	glutInit(&argc, argv); //Links GLUT with windows
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //Sets up the display for the window
	glutInitWindowSize(1000, 800); //Sets the window size here in 1000x1000 pixels
	glutCreateWindow("Ross McGregor Honours S1510552"); //Sets Name of the window at the top
	InitGL(); //Calls the function to start OpenGL functions
	FileLoader(); //Calls the function to open the .obj file
	glutDisplayFunc(WindowDisplay); //Calls the function to display the Program
	glutMotionFunc(MouseControl); //Calls the function to activate mouse inputs
	glutMainLoop(); //Calls for the program to run all checks continuously
}

