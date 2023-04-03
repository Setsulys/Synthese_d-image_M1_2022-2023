#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>

/* Window size */
static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;

/* Virtual Windows space*/
static const float GL_VIEW_SIZE = 1;
static float aspectRatio;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Error handling function */
void onError(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}


void onWindowResized(GLFWwindow* window,int width,int height){
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
}

void key_callback(GLFWwindow* window, int key,int scancode,int action,int mods){
	if(key == GLFW_KEY_Q && action == GLFW_PRESS){
		glfwSetWindowShouldClose(window,1);
	}
}

void mouse_button_callback(GLFWwindow* window, int button,int action,int mods){
	double x;
	double y;

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		glfwGetCursorPos(window,&x,&y);
		glClearColor(((int)x%256)/255.0,((int)y%256)/255.0,0,1);	
	}
}

void cursor_pos_callback(GLFWwindow * window, double xpos, double ypos){
	
	glfwGetCursorPos(window,&xpos,&ypos);
	glClearColor(((int)xpos%256)/255.0,0,((int)ypos%256)/255.0,1);


}


int main(int argc, char** argv) 
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);
	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TD 01 Ex 03", NULL, NULL);
	
	/*02b*/
	glfwSetWindowSizeCallback(window,onWindowResized);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}
	onWindowResized(window,WINDOW_WIDTH,WINDOW_HEIGHT);
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	/*Key*/
	glfwSetKeyCallback(window,key_callback);
	/*Mouse*/	
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	glfwSetCursorPosCallback(window,cursor_pos_callback);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		
		

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

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
