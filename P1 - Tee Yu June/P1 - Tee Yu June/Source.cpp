#include <Windows.h> 
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);

int questionNumber;

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

		case 0x31:
			questionNumber = 1;
			break;

		case 0x32:
			questionNumber = 2;
			break;

		case 0x33:
			questionNumber = 3;
			break;

		case 0x34:
			questionNumber = 4;
			break;

		case 0x35:
			questionNumber = 5;
			break;

		case 0x36:
			questionNumber = 6;
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

	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.7f, 0.4f);
	glVertex2f(0.7f, 0.4f);
	glVertex2f(0.7f, 0.0f);
	glVertex2f(-0.7f, 0.0f);

	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2f(0.7f, 0.0f);
	glVertex2f(-0.7f, 0.0f);
	glVertex2f(-0.7f, -0.4f);
	glVertex2f(0.7f, -0.4f);
	glEnd();

	switch (questionNumber) {

	case 1:

		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 0.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(0.7f, 0.4f);
		glVertex2f(0.7f, -0.4f);
		glVertex2f(-0.7f, -0.4f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(0.0f, 0.4f);
		glVertex2f(0.0f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(-0.7f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glEnd();

		break;

	case 2:

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(0.7f, 0.4f);
		glVertex2f(0.7f, -0.4f);
		glVertex2f(-0.7f, -0.4f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.6f, 0.0f, 0.0f);
		glVertex2f(-0.7f, 0.1f);
		glVertex2f(0.7f, 0.1f);
		glVertex2f(0.7f, -0.1f);
		glVertex2f(-0.7f, -0.1f);
		glEnd();

		glBegin(GL_QUADS);
		glColor3f(0.6f, 0.0f, 0.0f);
		glVertex2f(-0.1f, 0.4f);
		glVertex2f(0.1f, 0.4f);
		glVertex2f(0.1f, -0.4f);
		glVertex2f(-0.1f, -0.4f);
		glEnd();

		break;

	case 3:

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(0.7f, 0.4f);
		glVertex2f(0.7f, -0.4f);
		glVertex2f(-0.7f, -0.4f);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.6f, 0.4f);
		glVertex2f(0.6f, 0.4f);
		glVertex2f(0.0f, 0.1f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.6f, -0.4f);
		glVertex2f(0.6f, -0.4f);
		glVertex2f(0.0f, -0.1f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.7f, 0.3f);
		glVertex2f(-0.7f, -0.3f);
		glVertex2f(-0.1f, 0.0f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.7f, 0.3f);
		glVertex2f(0.7f, -0.3f);
		glVertex2f(0.1f, 0.0f);
		glEnd();

		break;

	case 4:
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS);
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f(-0.7f, 0.4f);
		glVertex2f(0.7f, 0.4f);
		glVertex2f(0.7f, -0.4f);
		glVertex2f(-0.7f, -0.4f);
		glEnd();

		float radius = 0.25;

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);

		for (int angle = 0; angle <= 360; angle++) {

			glVertex2f(cos(angle * 3.142 / 180)* radius, sin(angle * 3.142 / 180)* radius);

		}

		glEnd();

		break;

	}

	case 5:
	{

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//straw hat
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.4f);
		drawCircle(0.4f, 0.4f, 360, 0.0f, 0.3f);
		glEnd();

		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 0.2f);
		drawCircle(0.6f, 0.35f, 360, 0.0f, 0.2f);
		glEnd();


		//hair
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.4f, 0.4f, 180, 0.0f, 0.0f);
		glEnd();

		//face
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.9f, 0.7f);
		drawCircle(0.35, 0.35, 360, 0.0f, 0.0f);
		glEnd();

		//left ear
		glBegin(GL_POLYGON);
		drawCircle(0.08f, 0.1f, 360, -0.35f, 0.0f);
		glEnd();

		//right ear
		glBegin(GL_POLYGON);
		drawCircle(0.08f, 0.1f, 360, 0.35f, 0.0f);
		glEnd();

		//nose
		glLineWidth(1);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, 0.0f);
		glVertex2f(-0.01f, -0.06f);
		glVertex2f(0.03f, -0.06f);
		glEnd();

		//mouth
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 1.0f, 1.0f);
		for (int angle = 180; angle <= 360; angle++) {

			glVertex2f(cos(angle * 3.142 / 180)* 0.28 + 0, sin(angle * 3.142 / 180)* 0.23 - 0.1);

		}

		glEnd();

		glLineWidth(1);
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex2f(-0.25f, -0.2f);
		glVertex2f(0.25f, -0.2f);
		glEnd();

		//left eye
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.07f, 0.07f, 180, -0.165f, 0.0f);
		glEnd();

		//right eye
		glLineWidth(2);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.07f, 0.07f, 180, 0.165f, 0.0f);
		glEnd();

		//left eye
		glLineWidth(1.5);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.09f, 0.06f, 180, -0.165f, 0.08f);
		glEnd();

		//right eye
		glLineWidth(1.5);
		glBegin(GL_LINE_STRIP);
		glColor3f(0.0f, 0.0f, 0.0f);
		drawCircle(0.09f, 0.06f, 180, 0.165f, 0.08f);
		glEnd();

		//hair triangle (below)
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.32f, 0.2f);
		glVertex2f(-0.24f, 0.27f);
		glVertex2f(-0.25f, 0.05f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.23f, 0.32f);
		glVertex2f(-0.10f, 0.38f);
		glVertex2f(-0.20f, 0.02f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.08f, 0.36f);
		glVertex2f(-0.03f, 0.38f);
		glVertex2f(-0.10f, -0.01f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.36f);
		glVertex2f(0.05f, 0.38f);
		glVertex2f(0.10f, 0.08f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.1f, 0.36f);
		glVertex2f(0.21f, 0.32f);
		glVertex2f(0.2f, 0.08f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.26f, 0.30f);
		glVertex2f(0.33f, 0.22f);
		glVertex2f(0.26f, 0.08f);
		glEnd();

		//mouth stick
		glBegin(GL_LINES);
		glVertex2f(0.05f, -0.2f);
		glVertex2f(0.25f, -0.06f);
		glEnd();

		//hair triangle (up)
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.32f, 0.18f);
		glVertex2f(-0.24f, 0.27f);
		glVertex2f(-0.5f, 0.15f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.28f, 0.2f);
		glVertex2f(-0.22f, 0.3f);
		glVertex2f(-0.36f, 0.32f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.23f, 0.32f);
		glVertex2f(-0.10f, 0.38f);
		glVertex2f(-0.35f, 0.38f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.10f, 0.35f);
		glVertex2f(0.0f, 0.38f);
		glVertex2f(-0.15f, 0.50f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.28f, 0.28f);
		glVertex2f(0.33f, 0.20f);
		glVertex2f(0.45f, 0.18f);
		glEnd();

		glBegin(GL_TRIANGLES);
		glVertex2f(0.25f, 0.30f);
		glVertex2f(0.30f, 0.25f);
		glVertex2f(0.40f, 0.30f);
		glEnd();


	}

	break;
	case 6:
		break;

	default:
		break;
	}
	//glClearColor(1.0f,1.0f,1.0f,0.0f);
	//glEnable(GL_LINE_STIPPLE);
	//glLineStipple(2, 0x7733);
	//glLineWidth(10);
	//glPointSize(10);
	//glShadeModel(GL_SMOOTH);
	//glClear(GL_COLOR_BUFFER_BIT); //screen clear

	//glBegin(GL_LINE_STRIP);
	//glColor3f(1.0f, 1.0f, 0.0f);
	//glVertex2f(0, 0);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glVertex2f(0, 0.5);
	////glColor3f(0.0f, 0.0f, 1.0f);
	//glVertex2f(0.5, 0.5);
	//glDisable(GL_LINE_STIPPLE);
	//glEnd();
	//--------------------------------
	//	OpenGL drawing
	//--------------------------------
	// code to draw triangle here
	//--------------------------------
	//	End of OpenGL drawing
	//--------------------------------
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