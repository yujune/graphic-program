#include <Windows.h> 
#include <gl/GL.h>
#include <math.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "OpenGL32.lib") // tell visual studio, where is all the code for opengl library

#define WINDOW_TITLE "OpenGL Window" // reserve a word (WINDOW_TITLE) and substitue with "OpenGL Window" values

void drawCircle(float radiousX, float radiusY, int angle, float offsetX, float offsetY);
void createSky();
void createGrass();
void createMount();
void createWindmill();
void createFence(float &fenceTranX);
void drawPigLegs(float pigXTrans, float pigYTrans, float &move, float &pigRoateFac);
void drawPigFrontLegs(float pigXTrans, float pigYTrans, float &moveFront);
void drawLuffy();
void drawLuffyUpperBody();
void drawLuffyLowerBody();
void drawClouds(float cloudScaleX, float cloudScaleY, float cloudTransX, float cloudTransY);
void drawSmallPig();

int questionNumber;

float rotation = 0.0f;
float rotationFactor = 0.0f;
float cloudX1 = 0.0f, cloudX2 = 0.0f, cloudX3 = 0.0f;
float cloudScaleX = 0.0f, cloudScaleY = 0.0f;
float sunY = -0.45f;
float sunDirection = 0.0000f;

int sunFactor = 1;
float sunOrange = 0.0f;
float sunOrangeDensity = 0.0f;

float skyColor = 0.0f;
float skyColor1 = 0.0f;
float skyColor2 = 0.0f;
float pigLegBackMove = -60.0f;
float pigLegBackMove2 = -60.0f;
float pigLegFrontMove = 60.0f;
float pigLegFrontMove2 = 60.0f;

float spigLegBackMove = -60.0f;
float spigLegBackMove2 = -60.0f;
float spigLegFrontMove = 60.0f;
float spigLegFrontMove2 = 60.0f;

float pigRotateFac = 1.0f;
float pigRotateFac1 = 1.0f;
float spigRotateFac = 1.0f;
float spigRotateFac1 = 1.0f;

float movePig = 0.0f;

float fishRoate = 0.0f;


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

		case VK_DOWN: {
			sunOrangeDensity = -0.005;
			sunDirection = -0.005;

			if (sunY < 0.7f && sunY > -0.5f) {
				//sunUp = 0.0001;
				sunY += sunDirection;
				sunOrange += sunOrangeDensity;

				if (sunY > -0.5f && sunY < -0.1) {

					////turn orange
					//if (skyColor < 1.0) {
					//	skyColor += 0.02;

					//}
					//else if (skyColor1 < 0.5) {
					//	skyColor1 += 0.02;
					//}

					//if (skyColor2 < 1.0) {
					//	skyColor2 -= 0.03;
					//}

					//turn black
					if (skyColor >= 0 && skyColor1 >= 0) {
						skyColor -= 0.01;
						skyColor1 -= 0.01;
					}

					if (skyColor2 >= 0) {
						skyColor2 -= 0.01;
					}

				}
				
			}
			else if(sunY >= 0.7f) {
				sunY += sunDirection;
			}
			
			break;
		}

		case VK_UP: {
			sunOrangeDensity = 0.005;
			sunDirection = 0.005;
			//sunY += sunDirection;

			if (sunY < 0.7f && sunY > -0.5f) {
				//sunUp = 0.0001;
				sunY += sunDirection;
				sunOrange += sunOrangeDensity;
				
				if (sunY > -0.3f && sunY < -0.1) {

					//turn orange
					if (skyColor < 1.0) {
						skyColor += 0.02;
					}

					if (skyColor1 < 0.5) {
						skyColor1 += 0.02;
					}

					
				}
				else if (sunY > -0.1) {

					// turn blue
					if (skyColor > 0.4) {
						skyColor -= 0.01;
						
					}else if (skyColor1 > 0.4) {
						skyColor1 -= 0.01;
					}

					if (skyColor2 < 1.0) {
						skyColor2 += 0.03;
					}
				}
			}
			else if (sunY <= 0.5f) {
				sunY += sunDirection;
			}

			


			/*if (sunY >= 0.7f) {
				glColor3f(0.992, sunOrange + sunOrangeDensity, 0);
			}*/

			break;
		}

		case VK_LEFT: {
			rotationFactor-=0.01;
			break;
		}

		case VK_RIGHT: {
			rotationFactor+=0.01;
			break;
		}

		case VK_SPACE: {
			rotationFactor = 0;
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

	float fenceTranX = 0.0;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//sky
	createSky();

	//sun
	glColor3f(0.992, 0.5 + sunOrange, 0);
	glBegin(GL_POLYGON);
	drawCircle(0.15, 0.15, 360, 0.48, sunY);
	glEnd();

	//mountains
	createMount();

	//grass
	createGrass();

	//pond
	glPushMatrix();
	glTranslated(-0.8, -0.3, 0);
	glRotatef(180, 0, 0, 1);
	glColor3f(0.305, 0.670, 0.992);
	glBegin(GL_POLYGON);
	drawCircle(0.7, 0.35, 180,0,0);
	glEnd();
	glPopMatrix();

	//wooden fence
	createFence(fenceTranX);

	//fishy
	fishRoate += 0.2;
	glPushMatrix();
	glTranslatef(-0.7, -0.42, 0);
	glRotated(fishRoate, 0, 0, 1);
	glTranslatef(0.15, 0, 0);
	
	//fish body
	glColor3f(0.980, 0.992, 0.325);
	glBegin(GL_POLYGON);
	drawCircle(0.05, 0.06, 360, 0,0);
	glEnd();

	//fish tail
	glBegin(GL_TRIANGLES);
	glVertex2f(0,-0.06);
	glVertex2f(-0.035, -0.1);
	glVertex2f(0.035, -0.1);
	glEnd();

	//fish eye
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	drawCircle(0.02, 0.02, 360, 0.01, 0.02);
	glEnd();

	//fish eye ball
	glColor3f(0,0,0);
	glBegin(GL_POLYGON);
	drawCircle(0.01, 0.01, 360, 0.01, 0.02);
	glEnd();

	glPopMatrix();

	//pond to cover fish rotation
	glPushMatrix();
	glTranslated(-0.8, -0.35, 0);
	glRotatef(180, 0, 0, 1);
	glColor3f(0.305, 0.670, 0.992);
	glBegin(GL_POLYGON);
	drawCircle(0.6, 0.3, 180, 0, 0);
	glEnd();
	glPopMatrix();

	

	//clouds
	cloudX1 += 0.0001;
	//clouds 1
	glPushMatrix();

	if (cloudX1 < 4.0f) {
		
		glTranslatef(cloudX1, 0.0f, 0.0f);
	}
	else {
		cloudX1 = -1.0f;
		glTranslatef(cloudX1, 0.0f, 0.0f);
	}
	

	glPushMatrix();
	drawClouds(1.0f,1.0f,-1.0f,0.2f);
	glPopMatrix();

	glPushMatrix();
	drawClouds(0.8f, 0.8f, -2.0f, 0.05f);
	glPopMatrix();

	glPopMatrix();

	//clouds 2

	cloudX2 += 0.0001;

	glPushMatrix();

	if (cloudX2 < 5.0f) {

		glTranslatef(cloudX2, 0.0f, 0.0f);
	}
	else {
		cloudX2 = 0.0f;
		glTranslatef(cloudX2, 0.0f, 0.0f);
	}


	glPushMatrix();
	drawClouds(1.0f, 1.0f, -3.0f, 0.2f);
	glPopMatrix();

	glPushMatrix();
	drawClouds(0.8f, 0.8f, -4.0f, 0.05f);
	glPopMatrix();

	glPopMatrix();


	
	//windmill
	createWindmill();
	
	if (movePig > 1.2) {
		movePig = -1.6f;
	}
	movePig += 0.0005;

	glPushMatrix();
	glTranslatef(movePig,0,0);

	//pig
	glPushMatrix();
	drawSmallPig();
	glPopMatrix();

	//pig tail
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 0.847, 0.721);
	glVertex2f(0.3,-0.50);
	glVertex2f(0.27, -0.47);
	glEnd();
	
	//pig left behind legs
	glPushMatrix();
	drawPigLegs(0.32, -0.63,pigLegBackMove, pigRotateFac);
	glPopMatrix();

	//pig right behind legs
	glPushMatrix();
	drawPigLegs(0.38, -0.63, pigLegBackMove2, pigRotateFac);
	glPopMatrix();

	//pig right front legs
	glPushMatrix();
	drawPigLegs(0.48, -0.63, pigLegFrontMove, pigRotateFac1);
	glPopMatrix();

	//pig left front legs
	glPushMatrix();
	drawPigLegs(0.43, -0.63, pigLegFrontMove2, pigRotateFac1);
	glPopMatrix();

	//pig body
	glBegin(GL_POLYGON);
	glColor3f(1, 0.913, 0.839);
	drawCircle(0.12, 0.10, 360, 0.40, -0.55);
	glEnd();

	//draw luffy upper body
	glPushMatrix();
	drawLuffyUpperBody();
	glPopMatrix();


	//pig head
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.13,0.12,360,0.5,-0.5);
	glEnd();

	//pig nose
	glBegin(GL_POLYGON);
	glColor3f(1, 0.913, 0.839);
	drawCircle(0.04, 0.03, 360, 0.5, -0.50);
	glEnd();

	//pig left nosestrill
	glBegin(GL_POLYGON);
	glColor3f(0.996, 0.968, 0.945);
	drawCircle(0.005, 0.01, 360, 0.49, -0.50);
	glEnd();

	//pig right nosestrill
	glBegin(GL_POLYGON);
	glColor3f(0.996, 0.968, 0.945);
	drawCircle(0.005, 0.01, 360, 0.51, -0.50);
	glEnd();

	//pig left eye
	glBegin(GL_POLYGON);
	glColor3f(0.462, 0.439, 0.419);
	drawCircle(0.01, 0.01, 360, 0.45, -0.45);
	glEnd();

	//pig right eye
	glBegin(GL_POLYGON);
	glColor3f(0.462, 0.439, 0.419);
	drawCircle(0.01, 0.01, 360, 0.55, -0.45);
	glEnd();

	//pig left ear
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.03, 0.03, 360, 0.42, -0.40);
	glEnd();

	//pig right ear
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.03, 0.03, 360, 0.58, -0.40);
	glEnd();

	//draw luffy
	glPushMatrix();
	drawLuffy();
	glPopMatrix();

	//draw lower body
	glPushMatrix();
	drawLuffyLowerBody();
	glPopMatrix();

	glPopMatrix();


	switch (questionNumber) {

	case 1: {

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

	
		break;

	}

		
	case 2:

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		
		break;

	default:
		break;
	}

}

void drawLuffyLowerBody()
{

	glTranslatef(0.38, -0.30, 0);
	glScaled(0.3, 0.3, 0);

	//legs
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.7f);
	glVertex2f(0.1, -0.6);
	glVertex2f(-0.05, -0.6);
	glVertex2f(-0.15, -0.7);
	glVertex2f(-0.11, -0.7);
	glEnd();

	//shoes
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(-0.15, -0.7);
	glVertex2f(-0.15, -0.75);
	glVertex2f(-0.05, -0.75);
	glVertex2f(-0.05, -0.7);
	glEnd();


}

void drawLuffyUpperBody()
{

	glTranslatef(0.38, -0.30, 0);
	glScaled(0.3, 0.3, 0);

	//body
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0.15, -0.3);
	glVertex2f(-0.15, -0.3);
	glVertex2f(-0.15, -0.5);
	glVertex2f(0.15, -0.5);
	glEnd();

	//hand
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.7f);
	glVertex2f(-0.15, -0.3);
	glVertex2f(-0.15, -0.35);
	glVertex2f(-0.37, -0.35);
	glVertex2f(-0.37, -0.3);
	glEnd();

	//hand2
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.9f, 0.7f);
	glVertex2f(-0.35, -0.35);
	glVertex2f(-0.35, -0.3);
	glVertex2f(-0.40, -0.2);
	glVertex2f(-0.45, -0.2);
	glEnd();

	//palm
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.9f, 0.7f);
	drawCircle(0.05, 0.05, 360, -0.43, -0.15);
	glEnd();

	//pants
	glBegin(GL_QUADS);
	glColor3f(0, 0, 1);
	glVertex2f(-0.15, -0.5);
	glVertex2f(0.15, -0.5);
	glVertex2f(0.1, -0.6);
	glVertex2f(-0.05, -0.6);
	glEnd();



}

void drawLuffy()
{
	glTranslatef(0.38, -0.30, 0);
	glScaled(0.3,0.3,0);
	
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

void drawPigLegs(float pigXTrans, float pigYTrans,float &move, float &pigRotateFac)
{
	if (move <= -60) {
		pigRotateFac = 1.0;
		move = -59;
	}

	else if (move >= 60) {

		pigRotateFac = -1.0;
		move = 59;
	}

	if (move < 60 && move > -60) {
		move += pigRotateFac;
	}
	
	glTranslatef(pigXTrans, pigYTrans, 0);
	glRotatef(move, 0, 0, 1);
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.025, 0.04, 360, 0, 0);
	glEnd();

}

void drawPigFrontLegs(float pigXTrans, float pigYTrans, float &moveFront)
{
	if (moveFront <= -60) {
		pigRotateFac1 = 1.0;
		moveFront = -59;
	}

	else if (moveFront >= 60) {

		pigRotateFac1 = -1.0;
		moveFront = 59;
	}

	if (moveFront < 60 && moveFront > -60) {
		moveFront += pigRotateFac1;
	}
	
	glTranslatef(pigXTrans, pigYTrans, 0);
	glRotatef(moveFront, 0, 0, 1);

	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.025, 0.04, 360, 0, 0);
	glEnd();

}


void createFence(float &fenceTranX)
{
	//wooden upper horizontal fence
	glBegin(GL_QUADS);
	glColor3f(0.545f, 0.270f, 0.074f);
	glVertex2f(-1.0f, -0.14f);
	glVertex2f(-1.0f, -0.17f);
	glVertex2f(1.0f, -0.17f);
	glVertex2f(1.0f, -0.14f);
	glEnd();

	//wooden lower horizontal fence
	glBegin(GL_QUADS);
	glColor3f(0.545f, 0.270f, 0.074f);
	glVertex2f(-1.0f, -0.20f);
	glVertex2f(-1.0f, -0.23f);
	glVertex2f(1.0f, -0.23f);
	glVertex2f(1.0f, -0.20f);
	glEnd();

	//wooden vertical fence
	for (int i = 0;i < 50; i++) {

		if (fenceTranX < 2.0) {

			glPushMatrix();
			//glLoadIdentity();
			glTranslatef(fenceTranX, 0.0f, 0.0f);
			glBegin(GL_QUADS);
			glColor3f(0.545f, 0.270f, 0.074f);
			glVertex2f(-1.0f, -0.1f);
			glVertex2f(-1.0f, -0.3f);
			glVertex2f(-0.96f, -0.3f);
			glVertex2f(-0.96f, -0.1f);
			glEnd();
			glPopMatrix();
		}
		else {
			fenceTranX = 0.0;
		}

		fenceTranX += 0.1;

	}
}

void createWindmill()
{
	//triangle roof
	glBegin(GL_TRIANGLES);
	glColor3f(0.545f, 0.270f, 0.074f);
	glVertex2f(0.0f, 0.4f);
	glVertex2f(-0.15f, 0.2f);
	glVertex2f(0.15f, 0.2f);
	glEnd();

	//wind mill rect support
	glBegin(GL_QUADS);
	glColor3f(0.870f, 0.521f, 0.247f);
	glVertex2f(-0.13f, 0.2f);
	glVertex2f(0.13f, 0.2f);
	glVertex2f(0.13f, 0.15f);
	glVertex2f(-0.13f, 0.15f);
	glEnd();

	//upper rectangle body
	glBegin(GL_QUADS);
	glColor3f(0.545f, 0.270f, 0.074f);
	glVertex2f(-0.13f, 0.15f);
	glVertex2f(0.13f, 0.15f);
	glVertex2f(0.15f, -0.2f);
	glVertex2f(-0.15f, -0.2f);
	glEnd();

	//lower rectangle body
	glBegin(GL_QUADS);
	glColor3f(0.823f, 0.411f, 0.117f);
	glVertex2f(-0.15f, -0.2f);
	glVertex2f(0.15f, -0.2f);
	glVertex2f(0.16f, -0.3f);
	glVertex2f(-0.16f, -0.3f);
	glEnd();

	//door
	/*glBegin(GL_QUADS);
	glColor3f(0.415, 0.231, 0.003);
	glVertex2f(0.05f, -0.3f);
	glVertex2f(-0.05f, -0.3f);
	glVertex2f(-0.05f, -0.13);
	glVertex2f(0.05f, -0.13);
	glEnd();*/

	//window
	glBegin(GL_QUADS);
	glColor3f(0.6f, 0.737f, 0.941f);
	glVertex2f(0.02f, 0.1f);
	glVertex2f(0.1f, 0.1f);
	glVertex2f(0.1f, 0.0f);
	glVertex2f(0.02f, 0.0f);
	glEnd();

	//center circle
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.01f, 0.01f, 360, 0.0f, 0.2f);
	glEnd();

	glPushMatrix();
	//windmill stick
	rotation += rotationFactor;
	glTranslatef(0.0f, 0.2f, 0.0f);
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);

	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2f(-0.3, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.0, -0.3);
	glVertex2f(0.0, 0.3);
	glEnd();

	//windmill upper blade
	glBegin(GL_QUADS);
	glColor3f(0.898f, 0.933f, 0.980f);
	glVertex2f(0.0, 0.06);
	glVertex2f(0.0, 0.3);
	glVertex2f(0.06, 0.3);
	glVertex2f(0.06, 0.06);
	glEnd();

	//windmill lower blade
	glBegin(GL_QUADS);
	glVertex2f(0.0, -0.06);
	glVertex2f(0.0, -0.3);
	glVertex2f(-0.06, -0.3);
	glVertex2f(-0.06, -0.06);
	glEnd();

	//windmill right blade
	glBegin(GL_QUADS);
	glVertex2f(0.06, 0.0);
	glVertex2f(0.3, 0.0);
	glVertex2f(0.3, -0.06);
	glVertex2f(0.06, -0.06);
	glEnd();

	//windmill left blade
	glBegin(GL_QUADS);
	glVertex2f(-0.06, 0.0);
	glVertex2f(-0.3, 0.0);
	glVertex2f(-0.3, 0.06);
	glVertex2f(-0.06, 0.06);
	glEnd();


	glPopMatrix();
}

void createMount()
{
	//mountains caps
	glBegin(GL_POLYGON);
	glColor3f(0.074f, 0.545f, 0.231f);
	drawCircle(0.18, 0.14, 180, -0.25, 0.12);
	glEnd();

	//mountain body
	glBegin(GL_QUADS);
	glColor3f(0.074f, 0.545f, 0.231f);
	glVertex2f(-1.0f, -0.3f);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(-0.1f, 0.2f);
	glVertex2f(-0.4f, 0.2f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.074f, 0.545f, 0.231f);
	glVertex2f(0.5f, -0.3f);
	glVertex2f(1.0f, -0.3f);
	glVertex2f(1.0f, 0.2f);
	glEnd();
}

void createGrass()
{
	glBegin(GL_QUADS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(-1.0f, -0.3f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(1.0f, -0.3f);

	glColor3f(0.4f, 1.0f, 0.4f);
	glVertex2f(1.0f, -1.0f);

	glColor3f(0.4f, 1.0f, 0.4f);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
}

void createSky()
{

	glBegin(GL_QUADS);
	glColor3f(skyColor, skyColor1, skyColor2);
	glVertex2f(-1.0f, 1.0f);

	glColor3f(skyColor, skyColor1, skyColor2);
	glVertex2f(1.0f, 1.0f);

	glColor3f(0.9f + sunOrangeDensity, 0.9f + sunOrangeDensity, 1.0f);
	glVertex2f(1.0f, -0.3f);

	glColor3f(0.9f + sunOrangeDensity, 0.9f + sunOrangeDensity, 1.0f);
	glVertex2f(-1.0f, -0.3f);

	glEnd();
}

void drawCircle(float radiusX, float radiusY, int totalAngle, float offsetX, float offsetY) {

	for (int angle = 0; angle <= totalAngle; angle++) {

		glVertex2f(cos(angle * 3.142 / 180)* radiusX + offsetX, sin(angle * 3.142 / 180)* radiusY + offsetY);

	}
}

void drawClouds(float cloudScaleX, float cloudScaleY, float cloudTransX, float cloudTransY) {

	glTranslatef(cloudTransX, cloudTransY, 0.0f);
	glScaled(cloudScaleX, cloudScaleY, 0);
	

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.1, 0.08, 360, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.2, 0.1, 360, 0.38, 0.47);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.15, 0.06, 360, 0.3, 0.42);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawCircle(0.16, 0.08, 360, 0.5, 0.42);
	glEnd();
}

void drawSmallPig() {

	glTranslatef(-0.2, -0.4, 0);
	glScalef(0.5, 0.5, 0);

	//pig tail
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3f(1, 0.847, 0.721);
	glVertex2f(0.3, -0.50);
	glVertex2f(0.27, -0.47);
	glEnd();

	//pig left behind legs
	glPushMatrix();
	drawPigLegs(0.32, -0.63, spigLegBackMove, spigRotateFac);
	glPopMatrix();

	//pig right behind legs
	glPushMatrix();
	drawPigLegs(0.38, -0.63, spigLegBackMove, spigRotateFac);
	glPopMatrix();

	//pig right front legs
	glPushMatrix();
	drawPigLegs(0.48, -0.63, spigLegFrontMove, spigRotateFac1);
	glPopMatrix();

	//pig left front legs
	glPushMatrix();
	drawPigLegs(0.43, -0.63, spigLegFrontMove, spigRotateFac1);
	glPopMatrix();

	//pig body
	glBegin(GL_POLYGON);
	glColor3f(1, 0.913, 0.839);
	drawCircle(0.12, 0.10, 360, 0.40, -0.55);
	glEnd();

	//pig head
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.13, 0.12, 360, 0.5, -0.5);
	glEnd();

	//pig nose
	glBegin(GL_POLYGON);
	glColor3f(1, 0.913, 0.839);
	drawCircle(0.04, 0.03, 360, 0.5, -0.50);
	glEnd();

	//pig left nosestrill
	glBegin(GL_POLYGON);
	glColor3f(0.996, 0.968, 0.945);
	drawCircle(0.005, 0.01, 360, 0.49, -0.50);
	glEnd();

	//pig right nosestrill
	glBegin(GL_POLYGON);
	glColor3f(0.996, 0.968, 0.945);
	drawCircle(0.005, 0.01, 360, 0.51, -0.50);
	glEnd();

	//pig left eye
	glBegin(GL_POLYGON);
	glColor3f(0.462, 0.439, 0.419);
	drawCircle(0.01, 0.01, 360, 0.45, -0.45);
	glEnd();

	//pig right eye
	glBegin(GL_POLYGON);
	glColor3f(0.462, 0.439, 0.419);
	drawCircle(0.01, 0.01, 360, 0.55, -0.45);
	glEnd();

	//pig left ear
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.03, 0.03, 360, 0.42, -0.40);
	glEnd();

	//pig right ear
	glBegin(GL_POLYGON);
	glColor3f(1, 0.847, 0.721);
	drawCircle(0.03, 0.03, 360, 0.58, -0.40);
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