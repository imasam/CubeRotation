#include "stdafx.h"
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <SOIL.h>

static GLfloat xrot = 0.0;
static GLfloat yrot = 0.0;
static GLfloat zrot = 0.0;

static GLfloat xtrans = 0.0;
static GLfloat ytrans = 0.0;
static GLfloat ztrans = 0.0;

static GLfloat size = 1.0;

GLuint texture[6];

int LoadGLTextures()
{	
	// 加载各个面的图片
	int getImage;
	char *image[6] = { "info1.bmp","info2.bmp","info3.bmp",
		"info4.bmp","info5.bmp","info6.bmp" };

	// 加载纹理
	for (int i = 0; i < 6; ++i)
	{
		texture[i] = SOIL_load_OGL_texture(image[i], SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
		if (texture[i] == 0)
			getImage = 0;

		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	return getImage;
}

// 绘制立方体
void cube()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0, 0.0); glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(1.0, 1.0, -1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 0.0); glVertex3f(1.0, -1.0, 1.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, -1.0);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -5);

	glTranslatef(xtrans, 0, 0); // 沿x轴平移
	glTranslatef(0, ytrans, 0);	// 沿y轴平移
	glTranslatef(0, 0, ztrans);	// 沿z轴平移

	glRotatef(xrot, 0.5, 0, 0);	// 绕x轴旋转
	glRotatef(yrot, 0, 0.5, 0);	// 绕y轴旋转
	glRotatef(zrot, 0, 0, 0.5);	// 绕z轴旋转

	glScalef(size, size, size); // 缩放

	cube();	// 绘制立方体

	glutSwapBuffers();
	glPopMatrix();

	// 自转
	/*
	xrot += 0.5;
	yrot += 0.5;
	zrot += 0.5;
	*/

	// 控制频率
	// Sleep(20);
}

// 重新绘制窗口
void reshape(int w, int h) 
{
	if (h == 0) h = 1;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int init()
{
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);    // 剔除背面  
	glEnable(GL_CULL_FACE);

	if (!LoadGLTextures())
		return 0;

	glShadeModel(GL_SMOOTH); // 平滑着色  
	glClearColor(1.0, 0.75, 0.80, 1.0);	// 设置背景色
	glClearDepth(1.0);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return 1;
}

void keyboard(unsigned char key, int w, int h)
{
	switch (key)
	{
	// 基本操作
	case 27:exit(0); break; // ESC退出

	case 'o':glutFullScreen(); break; //全屏
	case 'p': // 退出全屏
		glutReshapeWindow(640, 480); // 设置窗口大小
		glutPositionWindow(400, 100); // 设置窗口位置
		break;

	// 平移
	case 'a':xtrans += 0.1; break; // 沿x轴正方向平移
	case 's':xtrans -= 0.1; break; // 沿x轴负方向平移

	case 'd':ytrans += 0.1; break; // 沿y轴正方向平移
	case 'f':ytrans -= 0.1; break; // 沿y轴负方向平移

	case 'g':ztrans += 0.1; break; // 沿z轴正方向平移
	case 'h':ztrans -= 0.1; break; // 沿z轴负方向平移

	// 旋转
	case 'q':xrot += 10; break; // 绕x轴逆时针旋转
	case 'w':xrot -= 10; break; // 绕x轴顺时针旋转

	case 'e':yrot += 10; break; // 绕y轴逆时针旋转
	case 'r':yrot -= 10; break; // 绕y轴顺时针旋转

	case 't':zrot += 10; break; // 绕z轴逆时针旋转
	case 'y':zrot -= 10; break; // 绕z轴顺时针旋转

	default:break;
	}
}

void mouse(int button, int dir, int x, int y)
{
	// GLUT_WHEEL_UP、GLUT_WHEEL_DOWN未定义标识符？
	switch (button)
	{
	case GLUT_LEFT_BUTTON:size += 0.05; break;
	case GLUT_RIGHT_BUTTON:size -= 0.05; break;
	}
}

void CreateMenu(int value)
{
	switch (value)
	{
	case 1:system("Instructions.txt"); break;//打开操作
	default:break;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(350, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("2014301550147");

	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	//创建菜单
	int mainMenu = glutCreateMenu(CreateMenu);
	glutAddMenuEntry("Open Instructions", 1);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);// 设置单击滚轮弹出菜单

	init();
	glutMainLoop();
	return 0;
}