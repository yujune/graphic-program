#include <Windows.h> 
#include <gl/GL.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);

int questionNumber;
float posX = 0.0f, posY = 0.0f;
float scaleX =1.0f, scaleY=1.0f;
float red = 1.0f, green = 1.0f, blue = 1.0f;
int angle = 0;
float scaleAmount = 0.001f;

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

		case VK_LEFT:
			posX -= 0.01;
			break;

		case VK_UP:
			posY += 0.01;
			break;

		case VK_DOWN:
			posY -= 0.01;
			break;

		case VK_RIGHT:
			posX += 0.01;
			break;

		case VK_SPACE:
			posX = 0.0f;
			posY = 0.0f;
			red = 1.0f;
			green = 1.0f;
			blue = 1.0f;
			break;

		case 0x52:
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
			break;

		case 0x47:
			red = 0.0f;
			green = 1.0f;
			blue = 0.0f;
			break;

		case 0x42:
			red = 0.0f;
			green = 0.0f;
			blue = 1.0f;
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

	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(posX, posY, 0);
	glColor3f(red, green, blue);
	glBegin(GL_QUADS);
	glVertex2f(-0.1f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, -0.1f);
	glVertex2f(-0.1f, -0.1f);
	glEnd();


	
	switch (questionNumber) {

	case 1:

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		red += 0.001;
		green += 0.002;
		blue += 0.003;

		if (red > 1.0) {
			red = 0.0f;
		}

		if (green > 1.0) {
			green = 0.0f;
		}

		if (blue > 1.0) {
			blue = 0.0f;
		}

		glLoadIdentity();
		glColor3f(red,green,blue);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2,0);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0.5);
		glEnd();

		glLoadIdentity();
		glRotatef(72,0.0f,0.0f,1.0f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2, 0);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0.5);
		glEnd();

		glLoadIdentity();
		glRotatef(144, 0.0f, 0.0f, 1.0f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2, 0);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0.5);
		glEnd();

		glLoadIdentity();
		glRotatef(216, 0.0f, 0.0f, 1.0f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2, 0);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0.5);
		glEnd();

		glLoadIdentity();
		glRotatef(288, 0.0f, 0.0f, 1.0f);
		//glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex2f(-0.2, 0);
		glVertex2f(0.2, 0);
		glVertex2f(0, 0.5);
		glEnd();


		//glColor3f(1.0f, 1.0f, 1.0f);
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(5);
		glBegin(GL_LINE_STRIP);
		
		for (int i = 0;i < 180;i++) {
			glVertex2f(cos(i*3.142/180)*0.02 + (-0.1), sin(i*3.142 / 180)*0.02 + (0.1));
		}
		glEnd();

		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 0;i < 180;i++) {
			glVertex2f(cos(i*3.142 / 180)*0.02 + (0.1), sin(i*3.142 / 180)*0.02 + (0.1));
		}
		glEnd();

		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_STRIP);

		for (int i = 180;i < 360;i++) {
			glVertex2f(cos(i*3.142 / 180)*0.06 + (0.0), sin(i*3.142 / 180)*0.06 + (-0.06));
		}
		glEnd();

		break;

	case 2:

		angle++;
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
		glRotatef(angle,0.0f,0.0f,1.0f);
		glTranslatef(-0.5f, 0.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex2f(-0.1f, 0.1f);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, -0.1f);
		glVertex2f(-0.1f, -0.1f);
		glEnd();
		
		break;

	case 3:

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		if (scaleX > 10 || scaleX < 1) {
			scaleAmount *= -1;
		}

		scaleX += scaleAmount;
		scaleY += scaleAmount;



		glLoadIdentity();
		glColor3f(1, 1, 1);
		glScalef(scaleX, scaleY, 1);

		glBegin(GL_QUADS);
		glVertex2f(-0.1f, 0.1f);
		glVertex2f(0.1f, 0.1f);
		glVertex2f(0.1f, -0.1f);
		glVertex2f(-0.1f, -0.1f);
		glEnd();

		break;

	case 4:
	{
		
		break;

	}

	case 5:

	break;
	case 6:
		break;

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