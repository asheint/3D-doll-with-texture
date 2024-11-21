#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <SOIL2.h>

constexpr float PI = 3.14159265358979323846;

int width;
int height;
unsigned char* image;
GLuint tex; //texture ID

//variables to move the camera
GLfloat camX = 0.0; GLfloat camY = 0.0; GLfloat camZ = 0.0;

//variables to move the scene
GLfloat sceRX = 0.0; GLfloat sceRY = 0.0; GLfloat sceRZ = 0.0;
GLfloat sceTX = 0.0; GLfloat sceTY = 0.0; GLfloat sceTZ = 0.0;

////variables to move the objects
GLfloat objRX = 0.0; GLfloat objRY = 0.0; GLfloat objRZ = 0.0;
GLfloat objTX = 0.0; GLfloat objTY = 0.0; GLfloat objTZ = 0.0;

//To on/off grids and axes
int gridOn = 0;
int axesOn = 0;

void drawGrid() {
	GLfloat step = 1.0f;
	GLint line;

	glBegin(GL_LINES);
	for (line = -20; line <= 20; line += step) {
		glVertex3f(line, -0.4, 20);
		glVertex3f(line, -0.4, -20);

		glVertex3f(20, -0.4, line);
		glVertex3f(-20, -0.4, line);
	}
	glEnd();
}

void drawAxes() {

	glBegin(GL_LINES);

	glLineWidth(1.5);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-200, 0, 0);
	glVertex3f(200, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, -200, 0);
	glVertex3f(0, 200, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, -200);
	glVertex3f(0, 0, 200);

	glEnd();
}

void loadTextures() {
	image = SOIL_load_image("coattexure.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	if (image == NULL) {
		printf("Error : %s", SOIL_last_result());
	}

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/*
//Read the image to texture image
void loadTextures() {
	//directly loads an image file and generates an OpenGL texture object from it
	tex = SOIL_load_OGL_texture(
		"coattexure.jpg",  // Replace with the path to your texture file
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y
	);

	if (!tex) {
		printf("Texture loading failed: %s\n", SOIL_last_result());
	}

	// Set texture parameters
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
*/

void init(void) {
	glClearColor(0.0, 0.8, 0.8, 1.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	loadTextures();
}

//Doll Components
void eyeright()
{
	//function for the right eye
	glPushMatrix();
	glTranslatef(.17, 1.1, .75);     //Specify the coordinates for the right eye
	glRotatef(-45, 0, 0, 1);
	glScalef(.9, .7, .7);            //Specify the size of the right eye
	glColor3f(1.0, 1.0, 1.0);       //Specify the color of the eye
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}
void eyeleft()
{
	glPushMatrix();
	glTranslatef(-.17, 1.1, .75);     //Specify the position for the left eye
	glRotatef(45, 0, 0, 1);
	glScalef(.9, .7, .7);
	glColor3f(1.0, 1.0, 1.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}

void legleft()
{
	glPushMatrix();
	glTranslatef(.3, -.5, 0);     //Specify the position for the left leg
	glRotatef(-90.0, 1, 0, 0);
	glScalef(.8, .8, .8);
	gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
	glPopMatrix();
}

void legright()
{
	glPushMatrix();
	glTranslatef(-.3, -.5, 0);     //Specify the position for the right leg
	glRotatef(-90.0, 1, 0, 0);
	glScalef(.8, .8, .8);
	gluCylinder(gluNewQuadric(), .5, .5, .5, 30, 6);
	glPopMatrix();
}

void armleft()
{
	glPushMatrix();
	glTranslatef(-.82, 0, .1);     //Specify the position for the left arm
	glRotatef(90, 0, 1, 0);
	glRotatef(-50, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluCylinder(quad, .15, .15, .48, 30, 6);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void armright()
{
	glPushMatrix();
	glTranslatef(.82, 0, .1);      //Specify the position for the right arm
	glRotatef(90, 0, 1, 0);
	glRotatef(-130, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluCylinder(quad, .15, .15, .48, 30, 6);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void handleft()
{
	glPushMatrix();
	glTranslatef(.82, 0, .1);     //Specify the position for the left hand
	glScalef(.4, .3, .3);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}
void handright()
{
	glPushMatrix();
	glTranslatef(-.82, 0, .1);    //Specify the position for the right hand
	glScalef(.4, .3, .3);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}

void mouth()
{
	glPushMatrix();
	glTranslatef(0, .78, .74);
	glScalef(.4, .4, .1);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .4, 100, 100);
	glPopMatrix();
}

void teeth()
{
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-.08, .72, .76);
	glTranslatef(.055, 0, .005);
	glutSolidCube(.045);
	glTranslatef(.055, 0, 0);
	glutSolidCube(.045);
	glPopMatrix();
}
void eyebrowleft()
{
	glPushMatrix();
	glTranslatef(-.3, 1.5, .97);;
	glRotatef(90, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	glColor3f(0.0, 0.0, 0.0);
	gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
	glPopMatrix();
}

void eyebrowright()
{
	glPushMatrix();
	glTranslatef(.3, 1.5, .97);
	glRotatef(270, 0, 1, 0);
	glRotatef(45, 1, 0, 0);
	gluCylinder(gluNewQuadric(), .05, .01, .3, 4, 6);
	glPopMatrix();
}

void neckring()
{
	glPushMatrix();
	glTranslatef(0, .5, 0);
	glScalef(.59, .59, .59);
	glRotatef(90.0, 1, 0, 0);
	glutSolidTorus(.1, 1.0, 20, 20);
	glPopMatrix();
}


void head()
{
	glPushMatrix();
	glTranslatef(0, 1.2, 0);
	glScalef(.9, .9, .9);
	glColor3f(1.0, 0.8, 0.6);
	gluSphere(gluNewQuadric(), 1, 100, 100);
	glPopMatrix();
}

void maintopball()
{
	glPushMatrix();
	glTranslatef(0, 2.2, 0);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .18, 100, 100);
	glPopMatrix();
}

void hatring()
{
	glPushMatrix();
	glTranslatef(0, 1.4, 0);
	glScalef(.84, .84, .84);
	glRotatef(90.0, 1, 0, 0);
	glutSolidTorus(.1, 1.0, 20, 20);
	glPopMatrix();
}

void footleft()
{
	glPushMatrix();
	glTranslatef(-.3, -.5, 0);
	glScalef(1.5, .3, 1.5);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}

void footright()
{
	glPushMatrix();
	glTranslatef(.3, -.5, 0);
	glScalef(1.5, .3, 1.5);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .3, 100, 100);
	glPopMatrix();
}

void bellyCoatbottom()
{
	glPushMatrix();
	glTranslatef(0, -.2, 0);
	glScalef(1, .7, 1);
	glRotatef(90.0, 1, 0, 0);
	gluDisk(gluNewQuadric(), 0, .8, 30, 30);
	glPopMatrix();
}

void BellyCoat()
{
	glPushMatrix();
	glTranslatef(0, .5, 0);
	glScalef(1, .7, 1);
	glRotatef(90.0, 1, 0, 0);

	GLUquadric* quad = gluNewQuadric();
	gluQuadricTexture(quad, GL_TRUE);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluCylinder(quad, .6, .8, 1, 100, 100);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void pupilleft()
{
	glPushMatrix();
	glTranslatef(-.17, 1.1, .88);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .1, 100, 100);
	glPopMatrix();
}

void pupilright()
{
	glPushMatrix();
	glTranslatef(.17, 1.1, .88);
	glScalef(.9, .9, .9);
	gluSphere(gluNewQuadric(), .1, 100, 100);
	glPopMatrix();
}

void topbutton()
{
	glPushMatrix();
	glTranslatef(0, .4, .62);
	glScalef(1.9, 1.9, 1.9);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}
void middlebutton()
{
	glPushMatrix();
	glTranslatef(0, .15, .69);
	glScalef(1.9, 1.9, 1.9);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}
void bottombutton()
{
	glPushMatrix();
	glTranslatef(0, -.1, .76);
	glScalef(1.9, 1.9, 1.9);
	glColor3f(0.0, 0.0, 0.0);
	gluSphere(gluNewQuadric(), .04, 100, 100);
	glPopMatrix();
}

void drawDoll() {
	eyeright();
	eyeleft();
	eyebrowleft();
	eyebrowright();
	glColor3f(0.0, 1.0, 0.0);
	neckring();
	glColor3ub(50, 40, 60);
	legright();
	legleft();
	glColor3ub(255, 90, 0);
	armleft();
	armright();
	BellyCoat();
	bellyCoatbottom();
	glColor3ub(0, 185, 0);
	handleft();
	handright();
	mouth();
	teeth();
	glColor3ub(255, 222, 173);
	head();
	glColor3f(0.0, 0.0, 0.0);
	footleft();
	footright();
	topbutton();
	middlebutton();
	bottombutton();
	pupilleft();
	pupilright();
}

void setLighting() {

	// Lighting set up
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	// Set lighting intensity and color - light 0
	GLfloat qaAmbientLight[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

	// Set the light position - light 0
	GLfloat qaLightPosition[] = { -10.0, 1.0, -.5, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

	// Set lighting intensity and color - light 1
	GLfloat qaAmbientLight1[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat qaDiffuseLight1[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat qaSpecularLight1[] = { 1.0, 1.0, 1.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight1);

	// Set the light position - light 1
	GLfloat qaLightPosition1[] = { 10.0, 1.0, 0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

	GLfloat SpecRef[] = { 0.7,0.7,0.7,1.0 };
	GLint Shine = 128;
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//Set material to follow
	glMaterialfv(GL_FRONT, GL_SPECULAR, SpecRef);//Set specular reflectivity and shine
	glMateriali(GL_FRONT, GL_SHININESS, Shine);
}


void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	// camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	gluLookAt(0.0, 0.0 + camY, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// move the scene (all the rendered environment) using keyboard keys
	glTranslatef(sceTX, sceTY, sceTZ);
	glRotatef(sceRY, 0.0, 1.0, 0.0);

	setLighting();

	//Draw a grid on the xz plane
	glColor3f(0.1, 0.1, 0.1);
	if (gridOn == 1)
		drawGrid();
	//draw the three axes
	if (axesOn == 1)
		drawAxes();

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	drawDoll();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, 3.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	drawDoll();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3.0, -3.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	drawDoll();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, 3.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	drawDoll();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3.0, -3.0, 0.0);
	glScalef(1.0, 1.0, 1.0);
	drawDoll();
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Define the Perspective projection frustum 
	// (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
	gluPerspective(120.0, aspect_ratio, 1.0, 100.0);

}

void keyboardSpecial(int key, int x, int y) {
	if (key == GLUT_KEY_UP)
		camY += 1;

	if (key == GLUT_KEY_DOWN)
		camY -= 1;

	if (key == GLUT_KEY_RIGHT)
		sceTX += 1;

	if (key == GLUT_KEY_LEFT)
		sceTX -= 1;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'l')
		objRY += 1;

	if (key == 'r')
		objRY -= 1;

	if (key == 'Z')
		sceTZ += 1;

	if (key == 'z')
		sceTZ -= 1;

	if (key == 'w')
		sceTX += 1;

	if (key == 's')
		sceTX -= 1;

	if (key == 'y')
		sceRY += 1;

	if (key == 'Y')
		sceRY -= 1;

	if (key == '!')
		glDisable(GL_LIGHT0); // Light at -x

	if (key == '1')
		glEnable(GL_LIGHT0);

	if (key == '@')
		glDisable(GL_LIGHT1); // Light at +x

	if (key == '2')
		glEnable(GL_LIGHT1);

	//Grids and axes
	if (key == 'G')
		gridOn = 1;
	if (key == 'g')
		gridOn = 0;
	if (key == 'A')
		axesOn = 1;
	if (key == 'a')
		axesOn = 0;



	glutPostRedisplay();
}

int main(void) {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("3D Doll - End 202021");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keyboardSpecial);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	init();
	glutMainLoop();
	return 0;
}