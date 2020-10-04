#include <Windows.h> 
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library
#pragma comment (lib, "GLU32.lib")

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void create3DCone();

void createCube();

void createRoad();

void createPyramid();

void createTower();

void createUpperBridge();

void createLowerBridge();

void createVirtualWorld();

void createMount();

void createBoatHead();

void createBoat();

void createMovingBoat1();

void createLightTower();

void createTowerSupport();

void createMovingBoat2();

GLUquadricObj *myQuadriObj = gluNewQuadric();

float radius = 0.25;
int slices = 20;
int stacks = 20;

float baseRadius = 0.01;
float topRadius = 0.3;
float height = 0.8;

float rotateY = 0;
float rotateX = 0;
float moveZ = -3;

float moveRightBridge = 180;
float moveLeftBridge = 0;

float moveBoat = 3.5;
float moveBoat2 = -3.5;

float line1 = -1;
float line2 = -0.9;

int chgView = 0;

GLuint texture = 1, textureLand = 1, texturelTowerroofhBMP = 1, texturelTower = 1, texturemount, textureSky = 1, textureSea = 1;
BITMAP BMP, BMPrland, BMPlTowerroofhBMP, BMPlTower, BMPmount, BMPsky, BMPsea;
HBITMAP hBMP = NULL, hBMPrland = NULL, hBMPlTowerroofhBMP = NULL, lTowerhBMP = NULL, hBMPmount = NULL, hBMPsky = NULL, hBMPsea = NULL;


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
			rotateX += 1;
			break;

		case VK_DOWN:
			rotateX -= 1;
			break;

		case VK_RIGHT:
			rotateY += 2;
			break;

		case VK_SPACE:
			moveBoat -= 0.1;
			break;

		case VK_ADD:
			moveZ += 0.1;
			break;

		case VK_NUMPAD1:
			moveRightBridge += 1;
			break;

		case VK_NUMPAD3:
			moveRightBridge -= 1;
			chgView = 1;
			break;

		case VK_SUBTRACT:
			moveZ -= 0.1;
			break;

		case 'O': {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(-1, 1, -0.7, 1, 0.2, 10);
			break;
		}

		case 'P': {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(55, 1, 0.1, 10);
			break;
		}


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

	glPushMatrix();
	glTranslatef(0, 0, moveZ);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateX, 1, 0, 0);

	//virtual world
	glPushMatrix();
	glTranslatef(-5, -0.75, 0);
	glScalef(40, 30, 30);
	createVirtualWorld();
	glPopMatrix();

	//left land to tower
	glPushMatrix();
	glTranslatef(-5, -0.49, -0.2);
	glScalef(20, 0.1, 2);
	createRoad();
	glPopMatrix();

	//right land to tower
	glPushMatrix();
	glTranslatef(0.0, -0.49, -0.2);
	glScalef(15, 0.1, 2);
	createRoad();
	glPopMatrix();

	//left land
	glPushMatrix();
	glTranslatef(-5, -0.75, 0);
	glScalef(10, 1.2, 30);
	glColor3f(0.803, 0.807, 0.752);
	createCube();
	glPopMatrix();

	//left house
	glColor3f(0.662, 0.662, 0.635);
	glPushMatrix();
	glTranslatef(-5, -0.5, 2);
	glScalef(7, 1, 10);
	createCube();
	glPopMatrix();

	//left house upper
	glColor3f(0.662, 0.662, 0.635);
	glPushMatrix();
	glTranslatef(-5, -0.4, 2);
	glScalef(5, 1, 8);
	createCube();
	glPopMatrix();

	//right land
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(1, -0.75, 0);
	glScalef(10, 1.2, 30);


	glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D, textureLand);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPrland.bmWidth, BMPrland.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPrland.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
	//DeleteObject(hBMPrland);
	glDeleteTextures(1, &textureLand);

	//moutain 1
	glPushMatrix();
	glTranslatef(1.5, -0.49, -1);
	glRotatef(30, 0, 1, 0);
	glScalef(5, 5, 5);
	createMount();
	glPopMatrix();

	//moutain 4
	glPushMatrix();
	glTranslatef(1.8, -0.59, -2.5);
	glRotatef(30, 0, 1, 0);
	glScalef(9, 10, 8);
	createMount();
	glPopMatrix();

	//moutain 2
	glPushMatrix();
	glTranslatef(1.5, -0.49, 1);
	glRotatef(30, 0, 1, 0);
	glScalef(5, 5, 5);
	createMount();
	glPopMatrix();

	//moutain 3
	glPushMatrix();
	glTranslatef(1.8, -0.49, 2.5);
	glRotatef(30, 0, 1, 0);
	glScalef(8, 8, 8);
	createMount();
	glPopMatrix();

	//moutain 5
	glPushMatrix();
	glTranslatef(1.25, -0.49, 1.7);
	glRotatef(50, 0, 1, 0);
	glScalef(3, 3, 3);
	createMount();
	glPopMatrix();

	glDeleteTextures(1, &texturemount);

	//boat 1
	createBoat();

	//boat 2
	glPushMatrix();
	glTranslatef(0, 0, 0.5);
	createBoat();
	glPopMatrix();

	//boat 3
	glPushMatrix();
	glTranslatef(0, 0, 1);
	createBoat();
	glPopMatrix();

	//boat 4
	glPushMatrix();
	glTranslatef(0, 0, 1.5);
	createBoat();
	glPopMatrix();

	//boat 5
	glPushMatrix();
	glTranslatef(0, 0, 2);
	createBoat();
	glPopMatrix();

	//moving boat 1
	moveBoat -= 0.01;

	createMovingBoat1();

	//moving boat 2
	createMovingBoat2();

	glColor3f(0, 1, 0);
	//right tower
	createTower();

	//right front tower and road support
	createTowerSupport();

	//right back tower and road support
	glPushMatrix();
	glTranslatef(0, 0, -0.30);
	createTowerSupport();
	glPopMatrix();

	//left front tower and road support
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(1, 0, 0.1);
	createTowerSupport();
	glPopMatrix();

	//left back tower and road support
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(1, 0, 0.4);
	createTowerSupport();
	glPopMatrix();

	//left tower
	glPushMatrix();
	glTranslatef(-1.3, 0, 0);
	createTower();
	glPopMatrix();

	//upper front bridge
	createUpperBridge();

	//upper back bridge
	glPushMatrix();
	glTranslatef(0, 0, -0.18);
	createUpperBridge();
	glPopMatrix();

	//lower right bridge
	glPushMatrix();
	glTranslatef(0.03, 0, 0);
	createLowerBridge();
	glPopMatrix();

	//lower left bridge
	glPushMatrix();
	glTranslatef(-1.03, 0, -0.4);
	glRotatef(180, 0, 1, 0);
	createLowerBridge();
	glPopMatrix();

	//light tower
	glPushMatrix();
	glTranslatef(-3.5, 0.5, -2);
	createLightTower();
	glPopMatrix();


	////tower wings
	//glPushMatrix();
	//glBegin();
	//glEnd();
	//glPopMatrix();

	glPopMatrix();

}

void createTowerSupport()
{

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	//HBITMAP hBMPRoadSupport = (HBITMAP)LoadImage(GetModuleHandle(NULL), "support.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	//GetObject(hBMPRoadSupport, sizeof(BMP), &BMP);

	//glEnable(GL_TEXTURE_2D);
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(0.462, 0.454, 0.454);
	//right 1st tiang
	glPushMatrix();
	glTranslatef(0.7, 0.1, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	//glColor3f(0.682, 0.4, 0.117);
	gluCylinder(myQuadriObj, 0.015, 0.015, 0.6, 30, 30);
	glPopMatrix();

	//right 2nd tiang
	glPushMatrix();
	glTranslatef(1.1, -0.1, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	//glColor3f(0.682, 0.4, 0.117);
	gluCylinder(myQuadriObj, 0.015, 0.015, 0.4, 30, 30);
	glPopMatrix();

	//glDisable(GL_TEXTURE_2D);
	//DeleteObject(hBMPRoadSupport);
	//glDeleteTextures(1, &texture);

	glLineWidth(5);
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex3f(0.3, 0.29, -0.05);
	glVertex3f(1.9, -0.5, -0.05);
	glEnd();
	glPopMatrix();

	float j = 0.3;
	float z = 0.3;
	glColor3f(0.792, 0.768, 0.768);
	for (int i = 0;i < 100;i++) {

		if (j < 1.8) {
			glLineWidth(1);
			glPushMatrix();
			glBegin(GL_LINES);
			glVertex3f(j, z, -0.05);
			glVertex3f(j, -0.5, -0.05);
			glEnd();
			glPopMatrix();
			j += 0.02;
			z -= 0.01;
		}
		else {
			j = 0.3;
			z = 0.3;
		}
	}


}

void createLightTower()
{
	//light tower roof

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texturelTowerroofhBMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPlTowerroofhBMP.bmWidth, BMPlTowerroofhBMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPlTowerroofhBMP.bmBits);

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.2);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.858, 0.650, 0.262);
	gluCylinder(myQuadriObj, 0.001, 0.1, 0.2, 30, 30);
	glPopMatrix();

	/*glDisable(GL_TEXTURE_2D);
	DeleteObject(lTowerroofhBMP);*/
	glDeleteTextures(1, &texturelTowerroofhBMP);


	//light tower body




	glBindTexture(GL_TEXTURE_2D, texturelTower);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPlTower.bmWidth, BMPlTower.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPlTower.bmBits);


	glPushMatrix();
	glTranslatef(0.0, -0.2, 0.2);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.796, 0.588, 0.203);
	gluCylinder(myQuadriObj, 0.08, 0.08, 0.6, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, -0.8, 0.2);
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.858, 0.650, 0.262);
	gluCylinder(myQuadriObj, 0.1, 0.1, 0.2, 30, 30);
	glPopMatrix();

	/*glDisable(GL_TEXTURE_2D);
	DeleteObject(lTowerhBMP);*/
	glDeleteTextures(1, &texturelTower);
}

void createMovingBoat1()
{
	glPushMatrix();

	if (moveBoat < -3.6) {
		moveBoat = 3.5;
	}

	glTranslatef(-0.7, -0.75, moveBoat);
	//glRotatef(90, 0, 1, 0);

	glColor3f(0.796, 0.588, 0.203);
	glPushMatrix();
	glScalef(0.5, 0.3, 1);
	createCube();
	createBoatHead();

	////boat pole
	glPushMatrix();
	glLineWidth(0.5);
	glBegin(GL_LINES);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glEnd();
	glPopMatrix();

	////boat fan
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, -0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glPopMatrix();

	glPopMatrix();
}

void createBoat()
{

	//create boat
	glPushMatrix();
	glTranslatef(-2, -0.75, 0.5);
	glRotatef(90, 0, 1, 0);

	glColor3f(0.796, 0.588, 0.203);
	glPushMatrix();
	glScalef(0.5, 0.3, 1);
	createCube();
	createBoatHead();

	////boat pole
	glPushMatrix();
	glLineWidth(0.5);
	glBegin(GL_LINES);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glEnd();
	glPopMatrix();

	////boat fan
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, -0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glPopMatrix();

	glPopMatrix();
}

void createMovingBoat2()
{
	//create boat
	moveBoat2 += 0.01;

	glPushMatrix();

	if (moveBoat2 > 3.6) {
		moveBoat2 = -3.5;
	}

	glTranslatef(-0.3, -0.75, moveBoat2);
	glRotatef(180, 0, 1, 0);

	glColor3f(0.796, 0.588, 0.203);
	glPushMatrix();
	glScalef(0.5, 0.3, 1);
	createCube();
	createBoatHead();

	////boat pole
	glPushMatrix();
	glLineWidth(0.5);
	glBegin(GL_LINES);
	glVertex3f(0.1f, 0.2f, 0.0f);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glEnd();
	glPopMatrix();

	////boat fan
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, 0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0.1f, 1.0f, 0.0f);
	glVertex3f(0.1f, 0.3f, -0.2f);
	glVertex3f(0.1f, 0.3f, 0.0f);
	glEnd();

	glPopMatrix();

	glPopMatrix();
}

void createBoatHead()
{
	//head boat
	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.2f, -0.2f);
	glVertex3f(0.1f, 0.0f, -0.2f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.1f, 0.0f, -0.2f);
	glVertex3f(0.1f, 0.2f, -0.2f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.2f, -0.2f);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.1f, 0.0f, -0.2f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glEnd();
}

void createMount()
{


	glColor3f(0.823, 0.423, 0.215);
	//glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texturemount);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPmount.bmWidth, BMPmount.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPmount.bmBits);

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


	////glDisable(GL_TEXTURE_2D);
	////DeleteObject(hBMPmount);
	////glDeleteTextures(1, &texture);


	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glEnd();


}

void createVirtualWorld()
{



	glColor3f(1, 1, 1);
	//glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, textureSky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPsky.bmWidth, BMPsky.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPsky.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();


	/*glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMPsky);*/
	glDeleteTextures(1, &textureSky);


	glBindTexture(GL_TEXTURE_2D, textureSea);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMPsea.bmWidth, BMPsea.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMPsea.bmBits);

	//glColor3f(0.270, 0.568, 0.988);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

	//glDisable(GL_TEXTURE_2D);
	//DeleteObject(hBMPsea);
	glDeleteTextures(1, &textureSea);

}

void createLowerBridge()
{
	if (moveBoat <1 && moveBoat >-1 && moveRightBridge > 100) {
		moveRightBridge -= 0.2;
	}
	else if (moveBoat < -1.5 && moveRightBridge < 180) {
		moveRightBridge += 0.2;
	}

	//lower right bridge
	glPushMatrix();
	glTranslatef(-0.05, -0.48, 0.0);
	glRotatef(moveRightBridge, 0, 0, 1);
	glTranslatef(-0.02, -0.01, -0.2);

	glPushMatrix();
	glScalef(2.5, 0.1, 2);
	createRoad();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5, 0.05, 0);
	glRotatef(170, 0, 0, 1);
	glPushMatrix();
	glScalef(2.5, 0.1, 2);
	createCube();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.48, 0, 0);
	glScalef(0.1, 0.25, 2);
	createCube();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0, 0);
	glScalef(0.1, 0.6, 2);
	createCube();
	glPopMatrix();

	////bridge line
	glColor3f(0.898, 0.901, 0.898);
	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.49, 0.05, 0.19);
	glVertex3f(0.49, 0.01, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.49, 0.05, 0.19);
	glVertex3f(0.4, 0.01, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.01, 0.19);
	glVertex3f(0.4, 0.06, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.06, 0.19);
	glVertex3f(0.3, 0.01, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.3, 0.01, 0.19);
	glVertex3f(0.3, 0.07, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.3, 0.07, 0.19);
	glVertex3f(0.2, 0.01, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.2, 0.01, 0.19);
	glVertex3f(0.2, 0.08, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.2, 0.08, 0.19);
	glVertex3f(0.1, 0.01, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.1, 0.01, 0.19);
	glVertex3f(0.1, 0.1, 0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.1, 0.1, 0.19);
	glVertex3f(0.0, 0.01, 0.19);
	glEnd();

	////bridge line
	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.49, 0.05, -0.19);
	glVertex3f(0.49, 0.01, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.49, 0.05, -0.19);
	glVertex3f(0.4, 0.01, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.01, -0.19);
	glVertex3f(0.4, 0.06, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.4, 0.06, -0.19);
	glVertex3f(0.3, 0.01, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.3, 0.01, -0.19);
	glVertex3f(0.3, 0.07, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.3, 0.07, -0.19);
	glVertex3f(0.2, 0.01, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.2, 0.01, -0.19);
	glVertex3f(0.2, 0.08, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.2, 0.08, -0.19);
	glVertex3f(0.1, 0.01, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.1, 0.01, -0.19);
	glVertex3f(0.1, 0.1, -0.19);
	glEnd();

	glLineWidth(6);
	glBegin(GL_LINES);
	glVertex3f(0.1, 0.1, -0.19);
	glVertex3f(0.0, 0.01, -0.19);
	glEnd();

	glPopMatrix();
}

void createUpperBridge()
{
	//upper 1st bridge
	glPushMatrix();
	glColor3f(0.466, 0.270, 0.074);
	glTranslatef(-1, 0.15, -0.11);
	glScalef(5, 0.1, 0.3);
	createCube();
	glPopMatrix();

	//upper 2nd bridge
	glPushMatrix();
	glTranslatef(-1, 0.05, -0.11);
	glScalef(5, 0.1, 0.3);
	createCube();
	glPopMatrix();

	for (int i = 0;i < 100;i++) {

		if (line1 <= 0.1) {
			glLineWidth(5);
			glColor3f(0.733, 0.741, 0.745);
			glBegin(GL_LINES);
			glVertex3f(line1, 0.15, -0.09);
			glVertex3f(line2, 0.05, -0.09);
			glEnd();

			glLineWidth(5);
			glBegin(GL_LINES);
			glVertex3f(line2, 0.15, -0.09);
			glVertex3f(line1, 0.05, -0.09);
			glEnd();

			glLineWidth(5);
			glBegin(GL_LINES);
			glVertex3f(line1, 0.15, -0.13);
			glVertex3f(line2, 0.05, -0.13);
			glEnd();

			glLineWidth(5);
			glBegin(GL_LINES);
			glVertex3f(line2, 0.15, -0.13);
			glVertex3f(line1, 0.05, -0.13);
			glEnd();

			line1 += 0.1;
			line2 += 0.1;

		}
		else {
			line1 = -1;
			line2 = -0.9;
		}

	}
}

void createTower()
{
	//pyramid roof stick
	glPushMatrix();
	glTranslatef(0.15, 0.6, -0.2);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.976, 0.501, 0.023);
	gluCylinder(myQuadriObj, 0.001, 0.02, 0.25, 30, 30);
	glPopMatrix();

	//pyramid roof

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP7 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "roofs.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP7, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glPushMatrix();
	glColor3f(0.792, 0.749, 0.749);
	glTranslatef(0, 0.2, -0.2);
	glScalef(1.5, 1.5, 1.5);


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

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP7);
	glDeleteTextures(1, &texture);

	//body

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP6 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "wall.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP6, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glColor3f(0.792, 0.560, 0.305);
	glPushMatrix();
	glTranslatef(0, -0.5, -0.2);
	glScalef(1.5, 3.5, 1.5);


	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(0.5f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(0.5f, 0.5f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 0.5f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP6);
	glDeleteTextures(1, &texture);

	//base

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "wall.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);


	glPushMatrix();
	glTranslatef(0.15, -0.5, -0.2);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluQuadricTexture(myQuadriObj, GL_TRUE);
	//glColor3f(0.466, 0.270, 0.074);
	gluCylinder(myQuadriObj, 0.3, 0.3, 0.25, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP);
	glDeleteTextures(1, &texture);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMP2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), "support.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMP2, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	//right front side cyclinder support
	glPushMatrix();
	glTranslatef(0.3, 0.3, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	//glColor3f(0.682, 0.4, 0.117);
	gluCylinder(myQuadriObj, 0.04, 0.04, 0.8, 30, 30);
	glPopMatrix();

	//left front side cyclinder support
	glPushMatrix();
	glTranslatef(0.0f, 0.3, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.04, 0.04, 0.8, 30, 30);
	glPopMatrix();

	//left back side cyclinder support
	glPushMatrix();
	glTranslatef(0.0f, 0.3, -0.35);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.04, 0.04, 0.8, 30, 30);
	glPopMatrix();

	//right back side cyclinder support
	glPushMatrix();
	glTranslatef(0.3f, 0.3, -0.35);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.04, 0.04, 0.8, 30, 30);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMP2);
	glDeleteTextures(1, &texture);


	//right front support cone roof
	glPushMatrix();
	glTranslatef(0.3, 0.5, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.001, 0.04, 0.2, 30, 30);
	glPopMatrix();

	//left front support cone roof
	glPushMatrix();
	glTranslatef(0.0f, 0.5, -0.05);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.001, 0.04, 0.2, 30, 30);
	glPopMatrix();

	//left front support cone roof
	glPushMatrix();
	glTranslatef(0.0f, 0.5, -0.35);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.001, 0.04, 0.2, 30, 30);
	glPopMatrix();

	//left front support cone roof
	glPushMatrix();
	glTranslatef(0.3f, 0.5, -0.35);
	glRotatef(90, 1, 0, 0);
	//glScalef(1.5, 3.5, 1.5);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	gluCylinder(myQuadriObj, 0.001, 0.04, 0.2, 30, 30);
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

void createCube()
{

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.2f, 0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glVertex3f(0.2f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();
}

void createRoad()
{

	glColor3f(0.776, 0.803, 0.756);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glEnd();

	glColor3f(0.776, 0.803, 0.756);
	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.2f, -0.1f);
	glVertex3f(0.2f, 0.0f, -0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.2f, 0.2f, 0.1f);
	glEnd();

	glColor3f(0.776, 0.803, 0.756);
	glBegin(GL_POLYGON);
	glVertex3f(0.2f, 0.2f, 0.1f);
	glVertex3f(0.2f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glColor3f(0.776, 0.803, 0.756);
	glBegin(GL_POLYGON);
	glVertex3f(0.0f, 0.2f, 0.1f);
	glVertex3f(0.0f, 0.0f, 0.1f);
	glVertex3f(0.0f, 0.0f, -0.1f);
	glVertex3f(0.0f, 0.2f, -0.1f);
	glEnd();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	HBITMAP hBMProad = (HBITMAP)LoadImage(GetModuleHandle(NULL), "road.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMProad, sizeof(BMP), &BMP);

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.2f, 0.2f, -0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.2f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.2f, 0.1f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	DeleteObject(hBMProad);
	glDeleteTextures(1, &texture);

	glColor3f(0.337, 0.345, 0.333);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, -0.1f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.1f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.2f, 0.0f, 0.1f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.2f, 0.0f, -0.1f);
	glEnd();

}

void create3DCone()
{
	//cone
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	gluQuadricDrawStyle(myQuadriObj, GLU_FILL);
	glColor3f(0.6, 0.3, 0.2);
	gluCylinder(myQuadriObj, baseRadius, topRadius, height, slices, stacks);
	glPopMatrix();
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
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();

	//glOrtho(-10, 10, -10, 10, -10, 10);
	//gluPerspective(55, 1, 0.1, 10);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);


	hBMPrland = (HBITMAP)LoadImage(GetModuleHandle(NULL), "grass.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMPrland, sizeof(BMPrland), &BMPrland);
	glGenTextures(1, &textureLand);

	hBMPlTowerroofhBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "roofs.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMPlTowerroofhBMP, sizeof(BMPlTowerroofhBMP), &BMPlTowerroofhBMP);
	glGenTextures(1, &texturelTowerroofhBMP);

	lTowerhBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), "support.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(lTowerhBMP, sizeof(BMPlTower), &BMPlTower);
	glGenTextures(1, &texturelTower);

	hBMPmount = (HBITMAP)LoadImage(GetModuleHandle(NULL), "mount.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMPmount, sizeof(BMPmount), &BMPmount);
	glGenTextures(1, &texturemount);

	hBMPsky = (HBITMAP)LoadImage(GetModuleHandle(NULL), "sky.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMPsky, sizeof(BMPsky), &BMPsky);
	glGenTextures(1, &textureSky);

	hBMPsea = (HBITMAP)LoadImage(GetModuleHandle(NULL), "sea.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	GetObject(hBMPsea, sizeof(BMPsea), &BMPsea);
	glGenTextures(1, &textureSea);


	//if (chgView == 0) {
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	gluPerspective(55, 1, 0.1, 10);
	//}
	//else if(chgView == 1){
	//	glLoadIdentity();
	//	glOrtho(-1, 1, -0.7, 1, 0.2, 10);
	//}

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	//glOrtho(-1, 1, -1, 1, 0.1, 10);

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