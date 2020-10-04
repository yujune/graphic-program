#include <Windows.h> 
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);

float rotate1 = 0;
float rotate2 = 0;
float rotate3 = 0;

float urotate1 = 0;
float urotate2 = 0;
float urotate3 = 0;

float xrotate1 = 0;
float xrotate2 = 0;
float xrotate3 = 0;
int questionNumber = 0;

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

		case VK_LEFT:
			//rotate1+=5;
			rotate3 += 5;
			break;

		case VK_UP:
			//rotate3 += 5;
			urotate3 += 5;
			break;

		case VK_DOWN:
			//urotate1 += 5;
			urotate3 -= 5;
			break;

		case VK_RIGHT:
			//rotate2 += 5;
			rotate3 -= 5;
			break;

		case VK_SPACE:
			urotate3 = 0;
			rotate3 = 0;
			break;

		case VK_ADD:
			urotate3 += 5;
			break;

		case 0x31:
			questionNumber = 1;
			break;

		case 0x32:
			questionNumber = 2;
			break;

		case 0x33:
			questionNumber = 3;
			break;

		case 0x58:
			xrotate1 -= 5;
			break;

		case 0x59:
			xrotate2 -= 5;
			break;

		case 0x5A:
			xrotate3 += 5;
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(xrotate1, 1, 0, 0);
	glRotatef(xrotate2, 0, 1, 0);
	glRotatef(xrotate3, 0, 0, 1);

	glColor3f(0,1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0,0.3,0);
	glVertex3f(-0.1, 0, 0.1);
	glVertex3f(0.1, 0, 0.1);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.1, 0, 0.1);
	glVertex3f(0.1, 0, -0.1);
	glVertex3f(0, 0.3, 0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0, 0.3, 0);
	glVertex3f(0.1, 0, -0.1);
	glVertex3f(-0.1, 0, -0.1);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0, -0.1);
	glVertex3f(-0.1, 0, 0.1);
	glVertex3f(0, 0.3, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-0.1, 0, 0.1);
	glVertex3f(0.1, 0, 0.1);
	glVertex3f(0.1, 0, -0.1);
	glVertex3f(-0.1, 0, -0.1);
	glEnd();
	glPopMatrix();

	switch (questionNumber)
	{

	case 1: {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//lower arm
		glPushMatrix();
		glRotatef(rotate1, 1, 0, 0);
		glRotatef(rotate2, 0, 1, 0);
		glRotatef(rotate3, 0, 0, 1);

		glColor3f(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0.2);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0.5, 0, 0.2);
		glVertex3f(0.5, 0.2, 0.2);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.5, 0.2, 0.2);
		glVertex3f(0.5, 0, 0.2);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 0.2, 0);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.5, 0.2, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0.2, 0);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0, 0.2, 0.2);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0.2);
		glVertex3f(0, 0.2, 0);
		glVertex3f(0.5, 0.2, 0);
		glVertex3f(0.5, 0.2, 0.2);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 0, 0.2);
		glEnd();

		//uppper arm
		glPushMatrix();
		glTranslatef(0.4, 0.1, 0.0);
		glRotatef(urotate1, 1, 0, 0);
		glRotatef(urotate2, 0, 1, 0);
		glRotatef(urotate3, 0, 0, 1);
		glTranslatef(-0.1, -0.1, 0.0);

		glColor3f(0, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0.2);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0.5, 0, 0.2);
		glVertex3f(0.5, 0.2, 0.2);
		glEnd();

		glColor3f(1, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.5, 0.2, 0.2);
		glVertex3f(0.5, 0, 0.2);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 0.2, 0);
		glEnd();

		glColor3f(0, 1, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0.5, 0.2, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0.2, 0);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0, 0.2, 0.2);
		glEnd();

		glColor3f(0, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0.2, 0.2);
		glVertex3f(0, 0.2, 0);
		glVertex3f(0.5, 0.2, 0);
		glVertex3f(0.5, 0.2, 0.2);
		glEnd();

		glColor3f(0, 0, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0.2);
		glVertex3f(0, 0, 0);
		glVertex3f(0.5, 0, 0);
		glVertex3f(0.5, 0, 0.2);
		glEnd();
		glPopMatrix();

		glPopMatrix();
		break;
	}

	case 2: {
		break;
	}

	default:
		break;
	}

	
}

void drawCircle(float radiusX, float radiusY, int totalAngle, float offsetX, float offsetY) {

	for (int angle = 0; angle <= totalAngle; angle++) {

		glVertex2f(cos(angle * 3.142 / 180)* radiusX + offsetX, sin(angle * 3.142 / 180)* radiusY + offsetY);

	}
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

	//--------------------------------
	//	End initialization
	//--------------------------------

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