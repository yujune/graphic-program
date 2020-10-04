#include <Windows.h> 
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void createPyramid();

GLUquadricObj *myQuadriObj = gluNewQuadric();


float radius = 0.25;
int slices = 20;
int stacks = 20;

float baseRadius = 0.01;
float topRadius = 0.3;
float height = 0.8;

float rotateY = 0;
float rotateZ = 0;

float lightx = 0;
float lighty = 3;
float lightz = 0;

float lightx1 = 0;
float lighty1 = 3;
float lightz1 = 0;

float posX = 0;
float posY = 1;
float posZ = 5;

int num = 1;

int onoff = 0;

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {

		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_UP:
			lightz1 -= 0.1;
			break;

		case VK_DOWN:
			lightz1 += 0.1;
			break;

		case VK_RIGHT:
			lightx -= 0.1;
			break;

		case VK_LEFT:
			lightx += 0.1;
			break;

		case VK_SPACE:
			if (onoff == 0) {
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHTING);
				onoff = 1;
			}
			else {
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHTING);
				onoff = 0;
			}

			break;

		case 'W':
			lighty += 0.1;
			lighty1 += 0.1;
			break;

		case 'S':
			lighty -= 0.1;
			lighty1 -= 0.1;
			break;

		case 'A':
			lightx1 -= 0.1;
			break;

		case 'D':
			lightx1 += 0.1;
			break;

		case 'E':
			lightz -= 0.1;
			break;

		case 'Q':
			lightz += 0.1;
			break;

		default:
			break;
		}

	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc) //ensure OpenGL can draw to your window
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--------------------------------------------------------------------

void display()
{

		glMatrixMode(GL_MODELVIEW);

		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT0);

		GLfloat lightposition[] = { lightx, lighty, lightz,0 };
		GLfloat lightposition2[] = { lightx1, lighty1, lightz1,0 };

		GLfloat lightdiffusecolor[] = { 1, 1, 1 ,1 };
		GLfloat lightdiffusecolor2[] = { 1, 1, 1 ,1 };

		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiffusecolor);
		glLightfv(GL_LIGHT0, GL_POSITION, lightposition);

		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightdiffusecolor2);
		glLightfv(GL_LIGHT1, GL_POSITION, lightposition2);

		glLoadIdentity();
		gluLookAt(posX, posY, posZ, 0, 0, 0, 0, 1, 0);

		//sphere 1
		glPushMatrix();
		glTranslatef(0, 1, 0);
		GLfloat spherediffusecolor[] = { 1, 1,1 ,0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, spherediffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();


		//sphere 2
		glPushMatrix();
		glTranslatef(1, 1, 0);
		//GLfloat spherediffusecolor[] = { 1, 1,1 ,0 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, spherediffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();


		//floor
		glBegin(GL_QUADS);

		glNormal3f(0, 1, 0);
		glVertex3f(-2,0,2);
		glVertex3f(2, 0, 2);
		glVertex3f(2, 0, -2);
		glVertex3f(-2, 0, -2);

		glEnd();

		//shadow obj 1
		glPushMatrix();
		glTranslatef(0, 0.01, 0);
		GLfloat matrix[16] = {lighty,0,0,0,-lightx,0,-lightz,-1,0,0,lighty,0,0,0,0,lighty};
		glMultMatrixf(matrix);
		glTranslatef(0.0f, 1.0f, 0.0f);
		GLfloat shadowdiffusecolor[] = { 0, 0, 0 ,1 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shadowdiffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();


		//shadow obj 1.2
		glPushMatrix();
		glTranslatef(0, 0.01, 0);
		GLfloat matrix2[16] = { lighty1,0,0,0,-lightx1,0,-lightz1,-1,0,0,lighty1,0,0,0,0,lighty1 };
		glMultMatrixf(matrix2);
		glTranslatef(0.0f, 1.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shadowdiffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();


		//shadow obj 2
		glPushMatrix();
		glTranslatef(0, 0.01, 0);
		// matrix[16] = { lighty,0,0,0,-lightx,0,-lightz,-1,0,0,lighty,0,0,0,0,lighty };
		glMultMatrixf(matrix);
		glTranslatef(1.0f, 1.0f, 0.0f);
		//GLfloat shadowdiffusecolor[] = { 0, 0, 0 ,1 };
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shadowdiffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();


		//shadow obj 2.2
		glPushMatrix();
		glTranslatef(0, 0.01, 0);
		//GLfloat matrix2[16] = { lighty1,0,0,0,-lightx1,0,-lightz1,-1,0,0,lighty1,0,0,0,0,lighty1 };
		glMultMatrixf(matrix2);
		glTranslatef(1.0f, 1.0f, 0.0f);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shadowdiffusecolor);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();

}


void createPyramid()
{
	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();
}

//--------------------------------------------------------------------

// 1st parameter id number for the launched window
// second -> refer to previous instance, child window send thing to father window, this is not used now due to privacy
// third -> long pointer to a string
// last -> not so important, just define how your window should show
// but who is calling this function???
// Answer: when program is run, it will auto run this function
// E.g. Os itself is the one who call this function and pass the parameters
// the parameters pass from window, window give the parameters.
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow)
{
	WNDCLASSEX wc; // window class , abstract class
	ZeroMemory(&wc, sizeof(WNDCLASSEX)); // clean leftover data

	wc.cbSize = sizeof(WNDCLASSEX); // recipe of window class
	wc.hInstance = GetModuleHandle(NULL); // ask OS for ID
	wc.lpfnWndProc = WindowProcedure; // long pointer function window procedure, handle mouse move, click
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW; //redraw what is inside the window when window size change

	if (!RegisterClassEx(&wc)) return false; // pass in recipe

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 800,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, 0, 1);
	gluPerspective(45, 1, 0.1, 10);
	//glFrustum(-0.2, 0.2, -0.2, 0.2, 0.1, 10);
	//--------------------------------
	//	End initialization
	//--------------------------------

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------