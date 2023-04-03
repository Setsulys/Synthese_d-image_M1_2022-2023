#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "TD02 Ex01";
static float aspectRatio = 1.0;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Virtual windows space */
// Space is defined in interval -1 and 1 on x and y axes
static const float GL_VIEW_SIZE = 2.;

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
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}
//Mon code
void premier_point(){
	glBegin(GL_POINTS);
	glColor3f(1,1,1); //blanc
	glVertex2f(0.,0.);
	glColor3f(1,0,0); //rouge
	glVertex2f(0.5,0.);
	glColor3f(0,1,0); //vert
	glVertex2f(0.,0.5);
	glColor3f(1,0,1); //violet
	glVertex2f(-0.5,-0.5);
	glEnd();
}

//Exo2
typedef struct vertex{
	float x;
	float y;
	struct vertex *suivant;
}vertex;


void alloc(vertex ** v, float x,float y){
		vertex * element  = malloc(sizeof(vertex));
		if(!element){
			exit(EXIT_FAILURE);
		}
		element->x = x;
		element->y = y;
		element->suivant = *v;
		*v = element;
}

void view(vertex *p){
	printf("---------------\n");
	while(p){
		printf("%f,%f\n",p->x,p->y);
		p = p->suivant;
	}
	printf("---------------\n");
}

void clear(vertex **v){
	vertex *tmp;
	while(*v){
		tmp = (*v)->suivant;
		free(*v);
		*v = tmp;
	}
}


//Global  var
vertex *verlist = NULL;
int enable_line =0;


void mouse_button_callback(GLFWwindow* window, int button,int action,int mods){
	double x;
	double y;

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		glfwGetCursorPos(window,&x,&y);
		alloc(&verlist,x,y);
	}
}

void update_screen(vertex * p){
	glBegin(GL_POINTS);
	glColor3f(0,0,0);
	while(p){
		glVertex2f((p->x * 2.0 /WINDOW_WIDTH) -1 , - ((p->y * 2.0 / WINDOW_HEIGHT) -1));
		p = p->suivant;
	}
	glEnd();
	if(enable_line){
		glColor3f(256.,26.,100.);
		vertex *p = verlist;
		vertex *p2 =verlist;
		glBegin(GL_LINE_STRIP);
		while(p){
			glVertex2f((p->x * 2.0 /WINDOW_WIDTH) -1 , - ((p->y * 2.0 / WINDOW_HEIGHT) -1));
			p = p->suivant;	
		}
		glVertex2f((p2->x * 2.0 /WINDOW_WIDTH) -1 , - ((p2->y * 2.0 / WINDOW_HEIGHT) -1));
		glEnd();
	}
}


void drawOrigin(){
	glBegin(GL_LINES);
	glColor3f(0,1,0);
	glVertex2f(0,0);
	glVertex2f(0,1);
	glColor3f(1,0,0);
	glVertex2f(0,0);
	glVertex2f(1,0);
	glColor3f(1,0,1);
	glVertex2f(0,0);
	glVertex2f(-1,-1);
	glEnd();

}

void drawSquare(){
	glBegin(GL_LINE_STRIP);
	glColor3f(0,0,1);
	glVertex2f(0.5,0.5);
	glVertex2f(-0.5,0.5);
	glVertex2f(-0.5,-0.5);
	glVertex2f(0.5,-0.5);
	glVertex2f(0.5,0.5);
	glEnd();
}

void drawCircle(int x,float r,float g ,float b){
	glBegin(GL_LINE_STRIP);
	glColor3f(r,g,b);
	for(int i = 0; i <x ; i++){
		float line = M_PI *2*i/x;
		glVertex2f(cos(line)/2,sin(line)/2);
	}
	glVertex2f(cos(0)/2,sin(0)/2);
	glEnd();
}

void key_callback(GLFWwindow* window, int key,int scancode,int action,int mods){
	enable_line = 1; /*!enable_line*/
}

int main(int argc, char** argv) 
{
	/*init list*/
	

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

	/*Mouse*/
	glfwSetMouseButtonCallback(window,mouse_button_callback);
	/*Key*/
	glfwSetKeyCallback(window,key_callback);
	glPointSize(4.0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		premier_point();
		drawOrigin();
		drawSquare();
		drawCircle(200,.9,.2,.5);
		update_screen(verlist);
		//drawlines(verlist);
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
	clear(&verlist);
	glfwTerminate();
	return 0;
}
