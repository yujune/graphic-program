#include <Windows.h> 
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);

GLUquadricObj *myQuadriObj = gluNewQuadric();

float radius = 0.25;
int slices = 20;
int stacks = 20;

float baseRadius = 0.01;
float topRadius = 0.3;
float height = 0.8;

float rotateY = 0;
float rotateZ = -2;

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
		
			break;

		case VK_UP:
			rotateZ += 0.1;
			break;

		case VK_DOWN:
			rotateZ -= 0.1;
			break;

		case VK_RIGHT:
			
			break;

		case VK_SPACE:
			
			break;

		case VK_ADD:
			
			break;

		case VK_NUMPAD1:
			slices--;
			break;

		case VK_NUMPAD4:
			slices++;
			break;

		case VK_NUMPAD5:
			stacks++;
			break;

		case VK_NUMPAD2:
			stacks--;
			break;

		case 0x59:
		
			break;

		case 0x5A:

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rotateY += 0.1;

	glPushMatrix();
	glTranslatef(0, -0.8, rotateZ);
	glRotatef(rotateY, 0, 1, 0);
	//glRotatef(rotateZ, 0, 0, 1);

	//cone
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.6,0.3,0.2);
	glRotatef(270, 1, 0, 0);
	gluCylinder(myQuadriObj, baseRadius, topRadius, height,slices, stacks);
	glPopMatrix();

	//cone line
	glPushMatrix();
	glLineWidth(4);
	gluQuadricDrawStyle(myQuadriObj, GLU_LINE);
	glColor3f(0.65, 0.35, 0.25);
	glRotatef(270, 1, 0, 0);
	gluCylinder(myQuadriObj, baseRadius*1.001, topRadius*1.001, height,
		slices, stacks);
	glPopMatrix();

	//ice cream scoop 1
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(1, 1, 0.7);
	glTranslatef(0, 0.8, 0);
	glRotatef(270, 1, 0, 0);
	/*glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, 0.8); */// something tricky, actually need translate first then rotate
	gluSphere(myQuadriObj, radius,slices, stacks);
	glPopMatrix();

	//ice cream scoop 2
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(1, 0.6, 0.7);
	glRotatef(270, 1, 0, 0);
	glTranslatef(0, 0, 1); // something tricky
	gluSphere(myQuadriObj, radius*0.9, slices, stacks);
	glPopMatrix();

	//cherry
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(1, 0.2, 0.3);
	glTranslatef(0, 1.2, -0.1); // something tricky
	glRotatef(270, 1, 0, 0);
	gluSphere(myQuadriObj, radius*0.3, slices, stacks);
	glPopMatrix();

	//cherry stem 1
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.9, 0.2, 0.3);
	glTranslatef(0, 1.2, -0.1);
	glRotatef(240, 1, 0, 0);
	glTranslatef(0, 0, 0.07);
	gluCylinder(myQuadriObj, 0.005, 0.005, 0.1,slices, stacks);
	glPopMatrix();

	//cherry stem 2
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.9, 0.2, 0.3);
	glTranslatef(0, 1.295, -0.1);
	glRotatef(210, 1, 0, 0);
	glTranslatef(0, 0, 0.09);
	gluCylinder(myQuadriObj, 0.005, 0.007, 0.1, slices, stacks);
	glPopMatrix();

	//chocolate love letter
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.9, 0.3, 0.2);
	glTranslatef(-0.1, 1, 0);
	glRotatef(300, 1, 0, 0);
	gluCylinder(myQuadriObj, 0.05, 0.05, 0.5, slices, stacks);
	glPopMatrix();

	//chocolate biscuit
	glPushMatrix();
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.6, 0.3, 0.1);
	glTranslatef(0.15, 1.25, 0);
	//glRotatef(300, 1, 0, 0);
	gluDisk(myQuadriObj, 0.1, 0.2,4, 1);
	glPopMatrix();

	glPopMatrix();

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, 0, 1);
	gluPerspective(45, 1, 0.1, 10);
	//glFrustum(-0.2, 0.2, -0.2, 0.2, 0.1, 10);
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