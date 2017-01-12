#include <GL\glut.h>
#include <math.h>
#include <GL\glaux.h>
#include <stdio.h>

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

int n = 50;
const GLfloat R = 0.5f;
const GLfloat Pi = 3.1415926536f;

void drawCircle(void)
{
	int i = 1;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	for (i = 0; i < n; ++i)
	{
		GLfloat x = R*cos(2 * Pi / n*i);
		GLfloat y = R*sin(2 * Pi / n*i);
		glVertex2f(x, y);
	}
	glEnd();
	glFlush();
}

void drawLine(void)
{
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.0f);
	glEnd();
	glFlush();
}

void drawStar(void)
{
	GLfloat a = 1 / (2 - 2 * cos(72 * Pi / 180));
	GLfloat bx = a * cos(18 * Pi / 180);
	GLfloat by = a * sin(18 * Pi / 180);
	GLfloat cy = -a * cos(18 * Pi / 180);
	GLfloat
		PointA[2] = { 0, a },
		PointB[2] = { bx, by },
		PointC[2] = { 0.5, cy },
		PointD[2] = { -0.5, cy },
		PointE[2] = { -bx, by };

	glClear(GL_COLOR_BUFFER_BIT);
	// 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出
	glBegin(GL_LINE_LOOP);
	glVertex2fv(PointA);
	glVertex2fv(PointC);
	glVertex2fv(PointE);
	glVertex2fv(PointB);
	glVertex2fv(PointD);
	glEnd();
	glFlush();
}

const GLfloat factor = 0.1f;
void drawSin(void)
{
	GLfloat x;
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);         // 以上两个点可以画x轴
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);         // 以上两个点可以画y轴
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (x = -1.0f / factor; x < 1.0f / factor; x += 0.01f)
	{
		glVertex2f(x*factor, sin(x)*factor);
	}
	glEnd();
	glFlush();
}

void drawStipple(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2, 0x0F0F);
	glLineWidth(10.0f);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glEnd();
	glutSwapBuffers();
}

void drawPoint(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(20.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.5f, 0.5f);
	glEnd();
	glFlush();
}

static GLubyte Mask[128] =

{

	0x00, 0x00, 0x00, 0x00,    //   这是最下面的一行

	0x00, 0x00, 0x00, 0x00,

	0x03, 0x80, 0x01, 0xC0,    //   麻

	0x06, 0xC0, 0x03, 0x60,    //   烦

	0x04, 0x60, 0x06, 0x20,    //   的

	0x04, 0x30, 0x0C, 0x20,    //   初

	0x04, 0x18, 0x18, 0x20,    //   始

	0x04, 0x0C, 0x30, 0x20,    //   化

	0x04, 0x06, 0x60, 0x20,    //   ，

	0x44, 0x03, 0xC0, 0x22,    //   不

	0x44, 0x01, 0x80, 0x22,    //   建

	0x44, 0x01, 0x80, 0x22,    //   议

	0x44, 0x01, 0x80, 0x22,    //   使

	0x44, 0x01, 0x80, 0x22,    //   用

	0x44, 0x01, 0x80, 0x22,

	0x44, 0x01, 0x80, 0x22,

	0x66, 0x01, 0x80, 0x66,

	0x33, 0x01, 0x80, 0xCC,

	0x19, 0x81, 0x81, 0x98,

	0x0C, 0xC1, 0x83, 0x30,

	0x07, 0xE1, 0x87, 0xE0,

	0x03, 0x3F, 0xFC, 0xC0,

	0x03, 0x31, 0x8C, 0xC0,

	0x03, 0x3F, 0xFC, 0xC0,

	0x06, 0x64, 0x26, 0x60,

	0x0C, 0xCC, 0x33, 0x30,

	0x18, 0xCC, 0x33, 0x18,

	0x10, 0xC4, 0x23, 0x08,

	0x10, 0x63, 0xC6, 0x08,

	0x10, 0x30, 0x0C, 0x08,

	0x10, 0x18, 0x18, 0x08,

	0x10, 0x00, 0x00, 0x08    // 这是最上面的一行

};

#include <stdio.h>
void drawFrontFace(void)
{
	FILE *fp;
	fp = fopen("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\Mask.bmp", "rb");
	if (!fp)
		exit(0);
	if (fseek(fp, -(int)sizeof(Mask), SEEK_END))
		exit(0);
	if (!fread(Mask, sizeof(Mask), 1, fp))
		exit(0);
	fclose(fp);

	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(&Mask);
	glBegin(GL_POLYGON);
	glVertex2f(-0.5f, -0.5f);
	glVertex2f(0.0f, -0.5f);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(-0.5f, 0.0f);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(0.0f, 0.5f);
	glVertex2f(0.5f, 0.5f);
	glVertex2f(0.5f, 0.0f);
	glEnd();
	glDisable(GL_CULL_FACE);
	glDisable(GL_POLYGON_STIPPLE);
	glFlush();
}

void drawColor(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 1.0f, 1.0f);
	glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
	glFlush();
}

// no effect.
#include <math.h>
#include <gl\glaux.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glaux.lib")
void drawColorIndex(void)
{
	int i;
	for (i = 0; i < 8; ++i)
		auxSetOneColor(i, (float)(i & 0x04), (float)(i & 0x02), (float)(i & 0x01));
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i <= 8; ++i)
	{
		glIndexi(i);
		glVertex2f(cos(i*Pi / 4), sin(i*Pi / 4));
	}
	glEnd();
	glFlush();
}

void drawClearColor(void)
{
	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void drawShadeModel(void)
{
	int i;
	glShadeModel(GL_FLAT);
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0.0f, 0.0f);
	for (i = 0; i < 8; ++i)
	{
		glColor3f(i & 0x04, i & 0x02, i & 0x01);
		glVertex2f(cos(i*Pi / 4), sin(i*Pi / 4));
	}
	glEnd();
	glFlush();
}

#include <time.h>
double CalFrequency()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 50)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLK_TCK;
	save = 50.0 / timegap;
	return save;
}

static int day = 200;
static int viewingAngle = 75;
static int viewingAngleRise = 1;
static int viewingXIncrementalFactor = 0;
static int viewingYIncrementalFactor = 0;
static int viewingZIncrementalFactor = 0;
static int incremental = 2000000;
static int incrementalRise = 1;
void drawSolarSystem(void)
{
	double FPS = CalFrequency();
	printf("FPS = %f\n", FPS);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(viewingAngle, 1, 1, 400000000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0 + viewingXIncrementalFactor * incremental, -200000000 + viewingYIncrementalFactor * incremental, 200000000 + viewingZIncrementalFactor * incremental, 0, 0, 0, 0, 0, 1);

	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
	}
	// draw red sun
	//glColor3f(1.0f,0.0f,0.0f);
	glutSolidSphere(69600000, 100, 100);

	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
	}
	// draw blue earth
	//glColor3f(0.0f,0.0f,1.0f);
	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(150000000, 0.0f, 0.0f);
	glutSolidSphere(15945000, 100, 100);

	// draw yellow moon
	glColor3f(1.0f, 1.0f, 0.0f);
	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
	glTranslatef(38000000, 0.0f, 0.0f);
	glutSolidSphere(4345000, 100, 100);

	glFlush();
	glutSwapBuffers();
}

void Idle2(void)
{
	if (++day >= 360)
		day = 0;
	if (viewingAngleRise)
	{
		if (++viewingAngle >= 100)
			viewingAngleRise = 0;
	}
	else
	{
		if (--viewingAngle <= 50)
			viewingAngleRise = 1;
	}
	if (incrementalRise)
	{
		if (++viewingXIncrementalFactor > 8)
			incrementalRise = 0;
		if (--viewingYIncrementalFactor < -20)
			incrementalRise = 0;
		if (++viewingZIncrementalFactor > 8)
			incrementalRise = 0;
	}
	else
	{
		if (--viewingXIncrementalFactor < -8)
			incrementalRise = 1;
		if (++viewingYIncrementalFactor > 20)
			incrementalRise = 1;
		if (--viewingYIncrementalFactor < -8)
			incrementalRise = 1;

	}
	drawSolarSystem();
}

void doNothing(void)
{

}

#define WIDTH 400
#define HEIGHT 400
static GLfloat angle = 0.0f;
void drawLight(void)
{
	static int list0 = 0;
	static int list1 = 0;
	static int list2 = 0;
	static int list3 = 0;

	if (list0 == 0)
	{
		list0 = glGenLists(1);
		glNewList(list0, GL_COMPILE);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Create a perspective view
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
		glEndList();
	}

	// define the white light of the sun .
	if (list1 == 0)
	{
		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		list1 = glGenLists(1);
		glNewList(list1, GL_COMPILE);
		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		glEndList();
	}

	// define the material of the sun and draw it.
	if (list2 == 0)
	{
		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_mat_shininess = 0.0f;

		list2 = glGenLists(1);
		glNewList(list2, GL_COMPILE);
		glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);
		glutSolidSphere(2.0, 40, 32);
		glEndList();
	}

	// define the material of the earth and draw it.
	if (list3 == 0)
	{
		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		GLfloat earth_mat_shininess = 30.0f;

		list3 = glGenLists(1);
		glNewList(list3, GL_COMPILE);
		glMaterialfv(GL_FRONT, GL_AMBIENT, earth_mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, earth_mat_specular);
		glMaterialfv(GL_FRONT, GL_EMISSION, earth_mat_emission);
		glMaterialf(GL_FRONT, GL_SHININESS, earth_mat_shininess);
		glTranslatef(5.0f, 0.0f, 0.0f);
		glutSolidSphere(2.0, 40, 32);
		glEndList();
	}

	// projection and model view transformation. 
	glCallList(list0);

	// define light.
	glCallList(list1);

	// draw sun.
	glCallList(list2);

	// draw earth.
	glRotatef(angle, 0.0f, -1.0f, 0.0f);
	glCallList(list3);

	glutSwapBuffers();
}

void Idle(void)
{
	angle += 1.0f;
	if (angle >= 360.0f)
		angle = 0.0f;
	drawLight();
}

#include <math.h>
GLfloat angle2 = 0.0f;
#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v);}while(0)

void setNormal(GLfloat* Point1, GLfloat* Point2, GLfloat* Point3)
{
	GLfloat normal[3];
	int i;
	for (i = 0; i < 3; ++i)
		normal[i] = (Point1[i] + Point2[i] + Point3[i]) / 3;
	glNormal3fv(normal);
}

void drawList()
{
	static int list = 0;
	if (list == 0)
	{

		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };
		GLfloat
			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		{
			// set material.
			GLfloat obj_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_specular[] = { 0.0f, 0.0f, 0.5f, 1.0f };
			GLfloat obj_mat_emission[] = { 0.0f, 0.0f, 0.3f, 1.0f };
			GLfloat obj_mat_shininess = 50.0f;

			glMaterialfv(GL_FRONT, GL_AMBIENT, obj_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, obj_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, obj_mat_shininess);
		}
		// Plane ABC
		setNormal(PointA, PointB, PointC);
		/*ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);*/
		glVertex3fv(PointA);
		glVertex3fv(PointB);
		glVertex3fv(PointC);
		{
			// set material.
			GLfloat obj_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_specular[] = { 0.0f, 0.5f, 0.5f, 1.0f };
			GLfloat obj_mat_emission[] = { 0.0f, 0.3f, 0.3f, 1.0f };
			GLfloat obj_mat_shininess = 60.0f;

			glMaterialfv(GL_FRONT, GL_AMBIENT, obj_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, obj_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, obj_mat_shininess);
		}
		// Plane ACD
		setNormal(PointA, PointC, PointD);
		/*ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);*/
		glVertex3fv(PointA);
		glVertex3fv(PointC);
		glVertex3fv(PointD);
		{
			// set material.
			GLfloat obj_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_specular[] = { 0.5f, 0.0f, 0.5f, 1.0f };
			GLfloat obj_mat_emission[] = { 0.3f, 0.0f, 0.3f, 1.0f };
			GLfloat obj_mat_shininess = 70.0f;

			glMaterialfv(GL_FRONT, GL_AMBIENT, obj_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, obj_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, obj_mat_shininess);
		}
		// Plane CBD
		setNormal(PointC, PointB, PointD);
		/*ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);*/
		glVertex3fv(PointC);
		glVertex3fv(PointB);
		glVertex3fv(PointD);
		{
			// set material.
			GLfloat obj_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
			GLfloat obj_mat_specular[] = { 0.5f, 0.5f, 0.0f, 1.0f };
			GLfloat obj_mat_emission[] = { 0.3f, 0.3f, 0.0f, 1.0f };
			GLfloat obj_mat_shininess = 80.0f;

			glMaterialfv(GL_FRONT, GL_AMBIENT, obj_mat_ambient);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, obj_mat_diffuse);
			glMaterialfv(GL_FRONT, GL_SPECULAR, obj_mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, obj_mat_emission);
			glMaterialf(GL_FRONT, GL_SHININESS, obj_mat_shininess);
		}
		// Plane BAD
		setNormal(PointB, PointA, PointD);
		/*ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);*/
		glVertex3fv(PointB);
		glVertex3fv(PointA);
		glVertex3fv(PointD);
		glEnd();
		glEndList();

		glEnable(GL_DEPTH_TEST);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0, 1.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// set light
	{
		GLfloat light_position[] = { 2.0f, 2.0f, 2.0f, 2.0f };
		GLfloat light_ambient[] = { 1.0f, 0.3f, 0.3f, 1.0f };
		GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
	}

	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	glRotatef(angle2, 1, 0.5, 0);
	glCallList(list);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1.0f, -1.0f, -1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidSphere(0.2, 40, 40);
	glPopMatrix();

	glutSwapBuffers();
}

void Idle3(void)
{
	if (++angle2 >= 360.0f)
		angle2 = 0.0f;
	drawList();
}

GLfloat angle3 = 0.0f;
void rotatingTriangle(void)
{
	static int list = 0;
	if (list == 0)
	{
		GLfloat
			PointA[] = { 0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointB[] = { -0.5f, -sqrt(6.0f) / 12, -sqrt(3.0f) / 6 },
			PointC[] = { 0.0f, -sqrt(6.0f) / 12, sqrt(3.0f) / 3 },
			PointD[] = { 0.0f, sqrt(6.0f) / 4, 0 };
		GLfloat
			ColorR[] = { 1, 0, 0 },
			ColorG[] = { 0, 1, 0 },
			ColorB[] = { 0, 0, 1 },
			ColorY[] = { 1, 1, 0 };

		list = glGenLists(1);
		glNewList(list, GL_COMPILE);
		glBegin(GL_TRIANGLES);
		// flat ABC
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorB, PointC);
		// flat ACD
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorY, PointD);
		// flat CBD
		ColoredVertex(ColorB, PointC);
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorY, PointD);
		// flat BAD
		ColoredVertex(ColorG, PointB);
		ColoredVertex(ColorR, PointA);
		ColoredVertex(ColorY, PointD);
		glEnd();
		glEndList();
		glEnable(GL_DEPTH_TEST);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle3, 1, 0.5, 0);
	glCallList(list);
	glPopMatrix();
	glutSwapBuffers();
}

void Idle4(void)
{
	if (++angle3 >= 360.0f)
		angle3 = 0.0f;
	Sleep(50);
	rotatingTriangle();
}

GLfloat angle5 = 0.0f;
void drawPyramid(float x, float y, float z, int n){
	if (n == 0)return;
	//画一个三菱锥
	glBegin(GL_TRIANGLES);
	//画背面
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, y, z);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x + 1.0f, y - 1.63f, z - 0.57f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x - 1.0f, y - 1.63f, z - 0.57f);
	//画底面
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, y - 1.63f, z + 1.15f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - 1.0f, y - 1.63f, z - 0.57f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x + 1.0f, y - 1.63f, z - 0.57f);
	//画左侧面
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, y, z);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x - 1.0f, y - 1.63f, z - 0.57f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x, y - 1.63f, z + 1.15f);
	//画右侧面
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, y, z);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x, y - 1.63f, z + 1.15f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x + 1.0f, y - 1.63f, z - 0.57f);
	glEnd();
	//递归调用，画多个三菱锥
	drawPyramid(x, y - 1.63f, z + 1.15f, n - 1);
	drawPyramid(x - 1.0f, y - 1.63f, z - 0.57f, n - 1);
	drawPyramid(x + 1.0f, y - 1.63f, z - 0.57f, n - 1);
}

// rotate the pyramid.
void Idle5(void)
{
	if (++angle5 >= 360.0f)
		angle5 = 0.0f;
	Sleep(50);

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 投影矩阵
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//设置窗口比例和透视图
	gluPerspective(60, (float) 1.0f, 0.1f, 50);

	//选择模型观察矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
	glLoadIdentity();
	{ // light
		GLfloat sun_light_position[] = { 5.0f, 0.0f, 0.0f, 1.0f };
		GLfloat sun_light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		GLfloat sun_light_diffuse[] = { 0.5f, 0.5f, 0.0f, 1.0f };
		GLfloat sun_light_specular[] = { 1.0f, 0.0f, 0.0f, 1.0f };

		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0f);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();

	glRotatef(angle5, 0, 1, 0);

	//调用递归函数，绘制三菱锥矩阵
	drawPyramid(0, 4, 0, 4);

	glPushMatrix();
	glTranslatef(6.0f, 0.0f, 0.0f);
	glutSolidSphere(0.5f, 50, 50);
	glPopMatrix();

	glutSwapBuffers();
}

void drawBlendColor()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glColor4f(1, 0, 0, 0.5);
	glRectf(-1, -1, 0.5, 0.5);
	glColor4f(0, 1, 0, 0.5);
	glRectf(-0.5, -0.5, 1, 1);

	glutSwapBuffers();
}

void setLight(void)
{
	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void setMaterial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
{
	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
}

void drawBlendBalls()
{
	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	setLight();
	setMaterial(red_color, 30.0);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.5f);
	glutSolidSphere(0.3, 30, 30);
	glPopMatrix();

	glDepthMask(GL_FALSE);

	setMaterial(blue_color, 30.0);
	glPushMatrix();
	glTranslatef(0.2f, 0.0f, -0.5f);
	glutSolidSphere(0.2, 30, 30);
	glPopMatrix();

	setMaterial(green_color, 30.0);
	glPushMatrix();
	glTranslatef(0.1, 0, 0);
	glutSolidSphere(0.15, 30, 30);
	glPopMatrix();

	glDepthMask(GL_TRUE);

	glutSwapBuffers();
}

#define BMP_Header_Length 54
#define WindowWidth 400
#define WindowHeight 400
void grab(void)
{
	FILE* pDummyFile;
	FILE* pWritingFile;
	GLubyte* pPixelData;
	GLubyte* BMP_Header[BMP_Header_Length];
	GLint i, j;
	GLint PixelDataLength;

	i = WindowWidth * 3;
	while (i % 4 != 0)
		++i;
	PixelDataLength = i * WindowHeight;

	pPixelData = (GLubyte*)malloc(PixelDataLength);
	if (pPixelData == 0)
		exit(0);

	pDummyFile = fopen("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\dummy.bmp", "rb");
	if (pDummyFile == 0)
		exit(0);

	pWritingFile = fopen("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\grab.bmp", "wb");
	if (pWritingFile == 0)
		exit(0);

	glReadBuffer(GL_FRONT);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, WindowWidth, WindowHeight,
		GL_BGR_EXT,
		GL_UNSIGNED_BYTE,
		pPixelData);

	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
	fseek(pWritingFile, 0x0012, SEEK_SET);
	i = WindowWidth;
	j = WindowHeight;
	fwrite(&i, sizeof(i), 1, pWritingFile);
	fwrite(&j, sizeof(j), 1, pWritingFile);

	fseek(pWritingFile, 0, SEEK_END);
	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);

	fclose(pDummyFile);
	fclose(pWritingFile);
	free(pPixelData);
}

void drawTriangleZoomAndCopy()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.5f, 1.0f);
	glEnd();

	glPixelZoom(-0.5f, -0.5f);
	glRasterPos2i(0, 0);
	glCopyPixels(WindowWidth / 2, WindowHeight / 2,
		200, 200, GL_COLOR);

	glutSwapBuffers();
	grab();
}

#define FileName "dummy24位.bmp"
static GLint ImageWidth;
static GLint ImageHeight;
static GLint PixelLength;
static GLubyte* PixelData;

void showPicFile(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawPixels(ImageWidth, ImageHeight,
		GL_BGR_EXT,
		GL_UNSIGNED_BYTE,
		PixelData);

	glutSwapBuffers();
}

void DrawPic(int argc, char *argv[])
{
	FILE* pFile = fopen("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\dummy24位.bmp", "rb");
	if (pFile == 0)
		exit(0);

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&ImageWidth, sizeof(ImageWidth), 1, pFile);
	fread(&ImageHeight, sizeof(ImageHeight), 1, pFile);

	PixelLength = ImageWidth * 3;
	while (PixelLength % 4 != 0)
		++PixelLength;
	PixelLength *= ImageHeight;

	PixelData = (GLubyte*)malloc(PixelLength);
	if (PixelData == 0)
		exit(0);

	fseek(pFile, 54, SEEK_SET);
	fread(PixelData, PixelLength, 1, pFile);

	fclose(pFile);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ImageWidth, ImageHeight);
	glutCreateWindow(FileName);
	glutDisplayFunc(&showPicFile);
	glutMainLoop();

	free(PixelData);
}

#define WindowWidth 400
#define WindowHeight 400
#define WindowTitle "OpenGL纹理测试"

int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLint last_texture_ID, texture_ID = 0;

	FILE* pFile = fopen(file_name, "rb");
	if (pFile == 0)
		return 0;

	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256;
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, last_texture_ID);

	free(pixels);
	return texture_ID;
}

GLuint texGround;
GLuint texWall;

void showTextures()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(75, 1, 1, 21);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);

	glBindTexture(GL_TEXTURE_2D, texGround);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texWall);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	glRotatef(-90, 0, 0, 1);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
	grab();
}

void DrawTextures(int argc, char* argv[])
{
	// GLUT初始化
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow(WindowTitle);
	glutDisplayFunc(&showTextures);

	// 在这里做一些初始化
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	texGround = load_texture("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\ground.bmp");
	texWall = load_texture("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\wall.bmp");

	glutMainLoop();
}

void texture_colorkey(GLubyte r, GLubyte g, GLubyte b, GLubyte absolute)
{
	GLint width, height;
	GLubyte* pixels = 0;

	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

	pixels = (GLubyte*)malloc(width * height * 4);
	if (pixels == 0)
		return;
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);

	{
		GLint i;
		GLint count = width * height;
		for (i = 0; i < count; ++i)
		{
			if (abs(pixels[i * 4] - b) <= absolute
				&& abs(pixels[i * 4 + 1] - g) <= absolute
				&& abs(pixels[i * 4 + 2] - r) <= absolute)
				pixels[i * 4 + 3] = 0;
			else
				pixels[i * 4 + 3] = 255;
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_BGRA_EXT, GL_UNSIGNED_BYTE, pixels);
	free(pixels);
}

void showPicAndWindow()
{
	static int initialized = 0;
	static GLuint texWindow = 0;
	static GLuint texPicture = 0;

	/*glMatrixMode(GL_PROJECTION);
	gluPerspective(60, 1, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(1,1,4, 0,0,0, 0,1,0);*/
	if (!initialized)
	{
		texPicture = load_texture("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\pic.bmp");
		texWindow = load_texture("D:\\Users\\llyang\\Documents\\Work\\Plot\\FirstGL\\Pic\\window.bmp");
		glBindTexture(GL_TEXTURE_2D, texWindow);
		texture_colorkey(255, 255, 255, 10);
		glEnable(GL_TEXTURE_2D);
		initialized = 1;
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texPicture);
	glDisable(GL_ALPHA_TEST);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texWindow);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(0, 1); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1, 1); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1, 0); glVertex2f(1.0f, -1.0f);
	glEnd();

	glutSwapBuffers();
}

void draw_sphere()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{
		GLfloat pos[] = { 5.0f, 5.0f, 0.0f, 1.0f },
			ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	}

	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(0, 0, 2);
	glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
}

void drawMirrorByStencil()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 5, 25);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 0, 6.5, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);

	glDisable(GL_STENCIL_TEST);
	draw_sphere();

	glClearStencil(0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glEnable(GL_STENCIL_TEST);

	glDisable(GL_LIGHTING);
	glColor3f(0.5f, 0.5f, 0.5f);
	glDepthMask(GL_FALSE);
	glRectf(-1.5f, -1.5f, 1.5f, 1.5f);
	glDepthMask(GL_TRUE);

	glStencilFunc(GL_EQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glScalef(1.0f, 1.0f, -1.0f);
	draw_sphere();

	glutSwapBuffers();
	grab();
}

static const GLfloat vertex_list[][3] = {
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	-0.5f, 0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
	-0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	-0.5f, 0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
};

static const GLint index_list[][4] = {
	0, 2, 3, 1,
	0, 4, 6, 2,
	0, 1, 5, 4,
	4, 5, 7, 6,
	1, 3, 7, 5,
	2, 6, 7, 3,
};

void drawCube()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 1, 1, 0, 0, 0, 0, 1, 0);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	{
		int i, j;
		glBegin(GL_QUADS);
		for (i = 0; i < 6; ++i)
		for (j = 0; j < 4; ++j)
			glVertex3fv(vertex_list[index_list[i][j]]);
		glEnd();
	}
	glutSwapBuffers();
}

void drawCubeWithVertexPointer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 1, 1, 0, 0, 0, 0, 1, 0);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertex_list);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list);

	glutSwapBuffers();
}

void drawCubeWithBuffersARB()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 1, 1, 0, 0, 0, 0, 1, 0);

	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//if( GLEE_ARB_vertex_buffer_object ) {
	//    // 如果支持顶点缓冲区对象
	//static int isFirstCall = 1;
	//static GLuint vertex_buffer;
	//static GLuint index_buffer;
	//if( isFirstCall ) {
	//    // 第一次调用时，初始化缓冲区
	//    isFirstCall = 0;

	//    // 分配一个缓冲区，并将顶点数据指定到其中
	//    glGenBuffersARB(1, &vertex_buffer);
	//    glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
	//    glBufferDataARB(GL_ARRAY_BUFFER_ARB,
	//    sizeof(vertex_list), vertex_list, GL_STATIC_DRAW_ARB);

	//    // 分配一个缓冲区，并将序号数据指定到其中
	//    glGenBuffersARB(1, &index_buffer);
	//    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);
	//    glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,
	//    sizeof(index_list), index_list, GL_STATIC_DRAW_ARB);
	//}
	//glBindBufferARB(GL_ARRAY_BUFFER_ARB, vertex_buffer);
	//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, index_buffer);

	//// 实际使用时与顶点数组非常相似，只是在指定数组时不再指定实际的数组，改为指定NULL即可
	//glEnableClientState(GL_VERTEX_ARRAY);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);
	//} 
	//else 
	{
		// 不支持顶点缓冲区对象
		// 使用顶点数组
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertex_list);
		glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, index_list);
	}

	glutSwapBuffers();
}

#define MAX_CHAR 120
void drawString(const char* str)
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall)
	{
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}

	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}

void selectFont(int size, int charset, const char* face)
{
	HFONT hFont = CreateFontA(
		size,
		0,
		0,
		0,
		FW_MEDIUM,
		0,
		0,
		0,
		charset,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		face
		);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}

void drawCNString(const char* str)
{
	int len, i;
	wchar_t* wstring;
	HDC hdc = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	for (i = 0; i < len; ++i)
	{
		wglUseFontBitmapsW(hdc, wstring[i], 1, list);
		glCallList(list);
	}

	free(wstring);
	glDeleteLists(list, 1);
}

void displayString(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(-1.0f, 0.8f);
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	drawString("Hello, World!");

	glColor3f(0.0f, 1.0f, 0.0f);
	glRasterPos2f(-1.0f, 0.5f);
	selectFont(48, GB2312_CHARSET, "楷体_GB2312");
	drawCNString("Hello, 中国！");

	glutSwapBuffers();
}

#define FONT_SIZE 64
#define TEXTURE_SIZE FONT_SIZE

GLuint drawChar_To_Texture(const char* s)
{
	wchar_t w;
	HDC hdc = wglGetCurrentDC();
	selectFont(FONT_SIZE, DEFAULT_CHARSET, "");
	glColor3f(1.0f, 1.0f, 1.0f);

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, s, 2, &w, 1);
	{
		int width, x, y;
		GetCharWidth32W(hdc, w, w, &width);
		x = (TEXTURE_SIZE - width) / 2;
		y = FONT_SIZE / 8;
	}

	{
		GLuint list = glGenLists(1);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glDisable(GL_FOG);
		glDisable(GL_TEXTURE_2D);

		wglUseFontBitmaps(hdc, w, 1, list);
		glCallList(list);
		glDeleteLists(list, 1);
	}

	{
		GLuint texID;
		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);
		glCopyTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_LUMINANCE4,
			0,
			0,
			TEXTURE_SIZE,
			TEXTURE_SIZE,
			0);
		glTexParameteri(
			GL_TEXTURE_2D,
			GL_TEXTURE_MIN_FILTER,
			GL_LINEAR);
		return texID;
	}
}

void setNormal1(const GLfloat v1[3],
	const GLfloat v2[3],
	const GLfloat v3[3])
{
	const GLfloat s1[] = {
		v2[0] - v1[0], v2[1] - v1[1], v2[2] - v1[2]
	};
	const GLfloat s2[] = {
		v3[0] - v1[0], v3[1] - v1[1], v3[2] - v3[2]
	};
	GLfloat n[] = {
		s1[1] * s2[2] - s1[2] * s2[1],
		s1[2] * s2[0] - s1[0] * s2[2],
		s1[0] * s2[1] - s1[1] * s2[0]
	};
	GLfloat abs = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	n[0] /= abs;
	n[1] /= abs;
	n[2] /= abs;
	glNormal3fv(n);
}

#define PI (3.1415926f)
#define MIN_X (-0.5f)
#define MAX_X (0.5f)
#define MIN_Y (-0.5f)
#define MAX_Y (0.5f)
#define SEGS ((int)((MAX_X - MIN_X) * (512/2)))
#define RANGE (0.05f)
#define CIRCLES (2.0f)
#define SPEED (5.0f)

GLfloat theta = 0.0f;

void drawFlag(void)
{
	int i;
	const GLfloat x_inc = (MAX_X - MIN_X) / SEGS;
	const GLfloat t_inc = 1.0f / SEGS;
	const GLfloat theta_inc = 2 * PI * CIRCLES / SEGS;
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= SEGS; ++i)
	{
		const GLfloat z = RANGE * sin(i * theta_inc + theta);
		const GLfloat
			v1[] = { i*x_inc + MIN_X, MAX_Y, z },
			v2[] = { i*x_inc + MIN_X, MIN_Y, z },
			v3[] = {
			(i + 1)*x_inc + MIN_X,
			MAX_Y,
			RANGE * sin((i + 1)*theta_inc + theta) };
		setNormal1(v1, v2, v3);
		glTexCoord2f(i*t_inc, 1.0f);
		glVertex3fv(v1);
		glTexCoord2f(i*t_inc, 0.0f);
		glVertex3fv(v2);
	}
	glEnd();
}

void displayFlag(void)
{
	static int isFirstCall = 1;
	static GLuint texID = 0;

	if (isFirstCall)
	{
		isFirstCall = 0;
		texID = drawChar_To_Texture("杨");

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		{
			GLfloat color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
			glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, color);
		}

		{
			GLfloat
				light_position[] = { 2.0f, 3.0f, 5.0f, 0.0f },
				light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f },
				light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f },
				mat_ambient[] = { 0.0f, 0.0f, 1.0f, 1.0f },
				mat_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f },
				mat_emission[] = { 0.0f, 0.0f, 0.3f, 1.0f };
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glLightfv(GL_LIGHT0, GL_POSITION, light_position);
			glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, light_ambient);
			glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
			glMaterialf(GL_FRONT, GL_SHININESS, 64.0f);
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_ambient);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

			glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, 1.0, 0.1, 5.0);
		glMatrixMode(GL_MODELVIEW);
		gluLookAt(1.0, -1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	drawFlag();
	glutSwapBuffers();
}

void drawSolarSystem2(void)
{
	glDepthFunc(GL_LEQUAL);
}

void Idle6(void)
{
	theta += (SPEED * PI / 180.0f);
	glutPostRedisplay();
}

typedef struct __ctitem__
{
	char valid;
	wchar_t c;
	GLfloat texcoord_x;
	GLfloat texcoord_y;
} ctitem_t;
static GLuint g_texID = 0;
static ctitem_t* g_items = 0;
static int g_count = 0;
static int g_total = 0;
static int g_fontsize = 0;
static int g_texturesize = 0;
void ctbuf_destroy(void);
void ctbuf_init(int fontsize, int texturesize, const char* font)
{
	int i;
	ctbuf_destroy();

	g_count = texturesize / fontsize;
	g_total = g_count * g_count;
	g_fontsize = fontsize;
	g_texturesize = texturesize;

	glGenTextures(1, &g_texID);
	glBindTexture(GL_TEXTURE_2D, g_texID);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_LUMINANCE4,
		texturesize, texturesize, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, NULL
		);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	g_items = (ctitem_t*)malloc(g_total * sizeof(ctitem_t));
	for (i = 0; i < g_total; ++i)
	{
		g_items[i].valid = 0;
		g_items[i].texcoord_x = (i%g_count * fontsize) / (GLfloat)texturesize;
		g_items[i].texcoord_y = (i / g_count * fontsize) / (GLfloat)texturesize;
	}

	selectFont(fontsize, DEFAULT_CHARSET, font);
}

void ctbuf_destroy(void)
{
	glDeleteTextures(1, &g_texID);
	free(g_items);
	g_items = NULL;
	g_count = 0;
	g_total = 0;
	g_fontsize = 0;
	g_texturesize = 0;
}

void ctbuf_bind(void)
{
	glBindTexture(GL_TEXTURE_2D, g_texID);
}

const ctitem_t* ctbuf_find(wchar_t c)
{
	int i;
	for (i = 0; i < g_total; ++i)
	if (g_items[i].valid && g_items[i].c == c)
		return &g_items[i];

	for (i = 0; i < g_total; ++i)
	if (!g_items[i].valid)
		break;

	if (i == g_total)
	{
		i = rand() % g_total;
	}

	g_items[i].valid = 1;
	g_items[i].c = c;
	/*   drawChar_To_SubTexture(
		   c,
		   (int)(g_items[i].texcoord_x * g_texturesize),
		   (int)(g_items[i].texcoord_y * g_texturesize));*/

	return &g_items[i];
}

void ctbuf_drawString(const char* str, GLfloat cwidth, GLfloat cheight)
{
	int i, len;
	wchar_t* wstring;
	GLfloat texinc;
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	ctbuf_bind();

	texinc = (GLfloat)g_fontsize / g_texturesize;
	for (i = 0; i < len; ++i)
	{
		const ctitem_t* pItem = ctbuf_find(wstring[i]);
		glBegin(GL_QUADS);
		glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y);
		glVertex2f(cwidth * i, 0.0f);
		glTexCoord2f(pItem->texcoord_x + texinc, pItem->texcoord_y + texinc);
		glVertex2f(cwidth * (i + 1), cheight);
		glTexCoord2f(pItem->texcoord_x, pItem->texcoord_y + texinc);
		glVertex2f(cwidth * i, cheight);
		glEnd;
	}

	free(wstring);
}

void displayTextArea(void)
{
	static int isFirstCall = 1;
	if (isFirstCall)
	{
		isFirstCall = 0;
		ctbuf_init(32, 256, "黑体");
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-1.0f, 0.0f, 0.0f);
	ctbuf_drawString("Best is yet to come", 0.1f, 0.15f);
	glPopMatrix();

	glutSwapBuffers();
}

void DrawGraph(int argc, char *argv[])
{
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("The first OpenGL programe");
	glutDisplayFunc(&myDisplay);
	//glutDisplayFunc(&drawCircle);
	//glutDisplayFunc(&drawLine);
	//glutDisplayFunc(&drawStar);
	//glutDisplayFunc(&drawSin);
	//glutDisplayFunc(drawStipple);
	//glutDisplayFunc(drawPoint);
	//glutDisplayFunc(drawFrontFace);
	//glutDisplayFunc(drawColor);
	//glutDisplayFunc(drawColorIndex);
	//glutDisplayFunc(drawClearColor);
	//glutDisplayFunc(drawShadeModel);

	// Solar system.
	{
		/*glutDisplayFunc(drawSolarSystem);
		glutIdleFunc(Idle);*/
	}

	// Solar system 2.
	{
		/*glutDisplayFunc(&drawSolarSystem);
		glutIdleFunc(Idle2); */
	}


	// rotate triangle with light.
	{
		/*glutDisplayFunc(drawList);
		glutIdleFunc(Idle3);*/
	}

	// rotate triangle.
	{
		/*glutDisplayFunc(rotatingTriangle);
		glutIdleFunc(Idle4);*/
	}

	// rotate pyramid.
	{
		//glutDisplayFunc(Idle5);
		//glutIdleFunc(Idle5); // rotate pyramid.
	}

	// Gone with the wind.
	{
		//glutDisplayFunc(&displayFlag);
		//glutIdleFunc(&Idle6); // Gone with the wind.
	}

	//glutDisplayFunc(drawBlendColor);
	//glutDisplayFunc(drawBlendBalls);
	//glutDisplayFunc(drawTriangleZoomAndCopy);
	//glutDisplayFunc(showPicAndWindow);
	//glutDisplayFunc(drawMirrorByStencil);
	//glutDisplayFunc(&drawCube);
	//glutDisplayFunc(drawCubeWithVertexPointer);
	//glutDisplayFunc(drawCubeWithBuffersARB);
	//glutDisplayFunc(displayString);
	//glutDisplayFunc(&doNothing);

	glutMainLoop();
}

int main(int argc, char *argv[])
{
	const char* version = (const char*)glGetString(GL_EXTENSIONS);
	printf("OpenGL 版本：%s\n", version);

	DrawGraph(argc, argv);
	//DrawPic(argc, argv);
	//DrawTextures(argc, argv);

	return 0;
}
