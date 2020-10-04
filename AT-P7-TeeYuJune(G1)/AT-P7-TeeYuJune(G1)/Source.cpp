#include <Windows.h> 
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <string>

using namespace std;

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);
void createPyramid();
void createCube();

GLUquadricObj *myQuadriObj = gluNewQuadric();

GLuint texture = 0;
BITMAP BMP;
HBITMAP hBMP = NULL;

float radius = 0.25;
int slices = 20;
int stacks = 20;
int questionNum = 1;

float baseRadius = 0.01;
float topRadius = 0.3;
float height = 0.8;

float rotateX = 0;
float rotateY = 0;
float rotateZ = 0;

string type("Box.bmp");

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
			rotateY -= 2;
			break;

		case VK_UP:
			rotateX += 2;
			break;

		case VK_DOWN:
			rotateX -= 2;
			break;

		case VK_RIGHT:
			rotateY += 2;
			break;

		case VK_SPACE:
			break;

		case VK_NUMPAD1:
			rotateZ += 2;
			break;

		case VK_NUMPAD2:
			rotateZ -= 2;
			break;

		case 'W':
			type = "Box.bmp";
			break;

		case 'M':
			type = "metal.bmp";
			break;

		case 'B':
			type = "brick.bmp";
			break;

		case 0x31: {
			questionNum = 1;
			break;
		}
			

		case 0x32: {
			questionNum = 2;
			break;

		}
			
		case 0x33: {
			questionNum = 3;
			break;

		}
		
		case 0x34:
			questionNum = 4;
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
	switch (questionNum)
	{
	case 1: {

		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "brick.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		glPushMatrix();
		glTranslatef(0, 0, -1);

		glPushMatrix();
		//glColor3f(1, 0, 0);
		glRotatef(rotateX, 1, 0, 0);
		glRotatef(rotateY, 0, 1, 0);
		glRotatef(rotateZ, 0, 0, 1);
		glTranslatef(-0.1, 0, 0);

		createPyramid();

		glPopMatrix();

		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);


		break;
	}
	case 2: {

		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		LPCTSTR typ = type.c_str();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), typ, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		glPushMatrix();
		glTranslatef(0, 0, -1);

		glPushMatrix();
		//glColor3f(1, 0, 0);
		glRotatef(rotateX, 1, 0, 0);
		glRotatef(rotateY, 0, 1, 0);
		glRotatef(rotateZ, 0, 0, 1);
		glTranslatef(-0.1, 0, 0);

		createCube();

		glPopMatrix();

		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);

		break;
	}
	case 3: {

		glMatrixMode(GL_MODELVIEW);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		glTranslatef(0, -0.8, -2);
		glRotatef(rotateY, 0, 1, 0);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP3 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "cone.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP3, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		//cone
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(0.6, 0.3, 0.2);
		glRotatef(270, 1, 0, 0);
		gluCylinder(myQuadriObj, baseRadius, topRadius, height, slices, stacks);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP3);
		glDeleteTextures(1, &texture);

		////cone line
		//glPushMatrix();
		//glLineWidth(4);
		//gluQuadricDrawStyle(myQuadriObj, GLU_LINE);
		////glColor3f(0.65, 0.35, 0.25);
		//glRotatef(270, 1, 0, 0);
		//gluCylinder(myQuadriObj, baseRadius*1.001, topRadius*1.001, height,
		//	slices, stacks);
		//glPopMatrix();

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "vanila.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		//ice cream scoop 1
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		gluQuadricTexture(myQuadriObj, GL_TRUE);
		//glColor3f(1, 1, 0.7);
		glTranslatef(0, 0.8, 0);
		glRotatef(270, 1, 0, 0);
		gluSphere(myQuadriObj, radius, slices, stacks);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP);
		glDeleteTextures(1, &texture);


		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "strawberry.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP2, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


		//ice cream scoop 2
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(1, 0.6, 0.7);
		glRotatef(270, 1, 0, 0);
		glTranslatef(0, 0, 1); // something tricky
		gluSphere(myQuadriObj, radius*0.9, slices, stacks);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP2);
		glDeleteTextures(1, &texture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP5 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "cherry.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP5, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits); 

		//cherry
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(1, 0.2, 0.3);
		glTranslatef(0, 1.2, -0.1); // something tricky
		glRotatef(270, 1, 0, 0);
		gluSphere(myQuadriObj, radius*0.3, slices, stacks);
		glPopMatrix();

		//cherry stem 1
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(0.9, 0.2, 0.3);
		glTranslatef(0, 1.2, -0.1);
		glRotatef(240, 1, 0, 0);
		glTranslatef(0, 0, 0.07);
		gluCylinder(myQuadriObj, 0.005, 0.005, 0.1, slices, stacks);
		glPopMatrix();

		//cherry stem 2
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(0.9, 0.2, 0.3);
		glTranslatef(0, 1.295, -0.1);
		glRotatef(210, 1, 0, 0);
		glTranslatef(0, 0, 0.09);
		gluCylinder(myQuadriObj, 0.005, 0.007, 0.1, slices, stacks);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP5);
		glDeleteTextures(1, &texture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP4 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "stick.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP4, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		//chocolate love letter
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(0.9, 0.3, 0.2);
		glTranslatef(-0.1, 1, 0);
		glRotatef(300, 1, 0, 0);
		gluCylinder(myQuadriObj, 0.05, 0.05, 0.5, slices, stacks);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP4);
		glDeleteTextures(1, &texture);


		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		HBITMAP hBMP6 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "choc.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		GetObject(hBMP6, sizeof(BMP), &BMP);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

		//chocolate biscuit
		glPushMatrix();
		gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
		//glColor3f(0.6, 0.3, 0.1);
		glTranslatef(0.15, 1.25, 0);
		//glRotatef(300, 1, 0, 0);
		gluDisk(myQuadriObj, 0.1, 0.2, 4, 1);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		DeleteObject(hBMP6);
		glDeleteTextures(1, &texture);


		glPopMatrix();

		break;
	}
	
	default:
		break;
	}

}


void createPyramid()
{

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, 0.2f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.1f, 0.2f, 0.0f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();
}

void createCube()
{

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();
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