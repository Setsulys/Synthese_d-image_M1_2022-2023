#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 1000;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD03 Ex01";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 20.;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

void onWindowResized(GLFWwindow* window, int width, int height)
{
	aspectRatio = width / (float) height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if( aspectRatio > 1)
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
	}
	else
	{
		gluOrtho2D(
		-GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
		-GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
	}
	glMatrixMode(GL_MODELVIEW);

}

void onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {
		switch(key) {
			case GLFW_KEY_A :
			case GLFW_KEY_ESCAPE :
				glfwSetWindowShouldClose(window, GLFW_TRUE); 
				break;
			case GLFW_KEY_L :
				glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
				break;
			case GLFW_KEY_P :
				glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
				break;
			default: fprintf(stdout,"Touche non gérée\n");
		}
	}
}


void drawSquare(float size,float offsetx, float offsety){
	size = size / 2.0;
	glBegin(GL_LINE_STRIP);
	glVertex2f(size + offsetx,size + offsety);
	glVertex2f(-size + offsetx,size + offsety);
	glVertex2f(-size + offsetx,-size + offsety);
	glVertex2f(size + offsetx,-size + offsety);
	glVertex2f(size + offsetx,size + offsety);
	glEnd();
}

void drawCircle(int x,float size,float offsetx,float offsety){

	glBegin(GL_LINE_STRIP);
	for(int i = 0; i <x ; i++){
		float line = M_PI *2*i/x;
		glVertex2f(offsetx + cos(line)*size,offsety+sin(line)*size);
	}
	glVertex2f(offsetx + cos(0)*size,offsety + sin(0)*size);
	glEnd();
}

void drawFirstArm(){

	drawCircle(200,2,0,0);
	glBegin(GL_LINES);
	glVertex2f(0,2);
	glVertex2f(6,1);
	glVertex2f(0,-2);
	glVertex2f(6,-1);
	glEnd();
	drawCircle(200,1,6,0);
}

void drawRoundedSquare(float offsetx, float offsety){
	drawCircle(200,.25,-0.25+offsetx,0.25+offsety);
	drawCircle(200,.25,0.25+offsetx,0.25+offsety);
	drawCircle(200,.25,-0.25+offsetx,-0.25+offsety);
	drawCircle(200,.25,0.25+offsetx,-0.25+offsety);
	glBegin(GL_LINES);
	glVertex2f(-.25+offsetx,0.5+offsety);
	glVertex2f(.25+offsetx,0.5+offsety);
	glVertex2f(-.25+offsetx,-0.5+offsety);
	glVertex2f(.25+offsetx,-0.5+offsety);
	glVertex2f(-0.5+offsetx,.25+offsety);
	glVertex2f(-0.5+offsetx,-.25+offsety);
	glVertex2f(0.5+offsetx,-.25+offsety);
	glVertex2f(0.5+offsetx,.25+offsety);
	glEnd();

}

void drawRectangle(float height,float width,float offsetx, float offsety){
	height = height/2;
	width = width/2;
	glBegin(GL_QUADS);
	glVertex2f(width + offsetx,height+ offsety);
	glVertex2f(-width + offsetx,height+ offsety);
	glVertex2f(-width + offsetx,-height+ offsety);
	glVertex2f(width + offsetx,-height + offsety);
	glEnd();
}

void drawSecondArm(float rectangleHeight,float rectangleWidth, float offsetx, float offsety){
	drawRoundedSquare(0,0);
	drawRectangle(rectangleHeight,rectangleWidth,offsetx + rectangleWidth / 2.0,offsety);
	drawRoundedSquare(offsetx *2+ rectangleWidth,0);
}

void drawThirdArm(float rectangleHeight,float rectangleWidth,float circleDiameter,float offsetx,float offsety){
	drawSquare(0.6,0,0);
	drawRectangle(rectangleHeight,rectangleWidth,offsetx + rectangleWidth / 2.0,offsety);
	drawCircle(200,circleDiameter/2.0,rectangleWidth + offsetx*2,offsety);
}


void drawFullArm(float alpha,float beta,float delta){

		float SecondArmOffsetx = -0.25;
		float SecondArmOffsety = 0;
		float SecondArmRectangleHeight = 0.6;
		float SecondArmRectangleWidth =4.6;

		float ThirdArmOffsetx =-0.2;
		float ThirdArmOffsety =0;
		float ThirdArmRectangleHeight = 0.4;
		float ThirdArmRectangleWidth = 4.0;
		float ThirdArmCircleDiameter = 0.8;

		float SecondArmMargin =1;
		float ThirdArmMargin = 0.3;

		glPushMatrix();
		glTranslatef(-5,0,0);
		glRotatef(alpha,0,0,1);
		drawFirstArm();
		glTranslatef(5 + SecondArmMargin,0,0);
		glRotatef(beta,0,0,1);
		drawSecondArm(SecondArmRectangleHeight,SecondArmRectangleWidth,SecondArmOffsetx,SecondArmOffsety);
		glTranslatef(SecondArmRectangleWidth -ThirdArmMargin ,0,0);
		glRotatef(delta,0,0,1);
		drawThirdArm(ThirdArmRectangleHeight,ThirdArmRectangleWidth,ThirdArmCircleDiameter,ThirdArmOffsetx,ThirdArmOffsety);
		glRotatef(20,0,0,1);
		drawThirdArm(ThirdArmRectangleHeight,ThirdArmRectangleWidth,ThirdArmCircleDiameter,ThirdArmOffsetx,ThirdArmOffsety);
		glRotatef(20,0,0,1);
		drawThirdArm(ThirdArmRectangleHeight,ThirdArmRectangleWidth,ThirdArmCircleDiameter,ThirdArmOffsetx,ThirdArmOffsety);
		glPopMatrix();
}




float Alpha = 0;
float Beta = 0;
float Gammmma = 0;
int ReverseAlpha =0;
int ReverseBeta =0;
int ReverseGamma =0;


void rotate(){

	if(Alpha < 45 && ReverseAlpha ==0){
		Alpha++;
		if(Alpha==45){
			ReverseAlpha= 1;
		}
	}
	else if(Alpha > -45 && ReverseAlpha == 1){
		Alpha--;
		if(Alpha ==-45 ){
			ReverseAlpha =0;
		}
	}

	// if(Beta < 5 && ReverseBeta ==0){
	// 	Beta++;
	// 	if(Beta==5){
	// 		ReverseBeta= 1;
	// 	}
	// }
	// else if(Beta > -5 && ReverseBeta == 1){
	// 	Beta--;
	// 	if(Beta ==-5 ){
	// 		ReverseBeta =0;
	// 	}
	// }
	Beta++;
	Gammmma++;
}

int main(int argc, char** argv) 
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);

	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Cleaning buffers and setting Matrix Mode */
		glClearColor(0.2,0.0,0.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();


		rotate();
		drawFullArm(Alpha,Beta,Gammmma);
		/* RENDER HERE */


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		double elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		if(elapsedTime < FRAMERATE_IN_SECONDS) 
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS-elapsedTime);
		}
	}

	glfwTerminate();
	return 0;
}
