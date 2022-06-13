#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

const int width = 800;
const int height = 800;
//const float ratio_ = 1.0 * width / height;
GLfloat eye[3] = {5,8,-26};
GLfloat look[3] = {5,9,0};
float theta = 0.0, controller = 16.0;

bool light1_flag = true, light2_flag = false, light3_flag = false;
bool ambient_flag = true, diffuse_flag = true, specular_flag = true;

static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLfloat v_ac[8][3] =
{
    {0,0.2,0},
    {0,0,1},
    {0,0.6,0},
    {0,1,1},

    {1,0.2,0},
    {1,0,1},
    {1,0.6,0},
    {1,1,1}
};

static GLfloat v_lshade[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0.2,1,0.2},
    {0.2,1,0.8},

    {1,0,0},
    {1,0,1},
    {0.8,1,0.2},
    {0.8,1,0.8}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(float colR=0.5, float colG=0.5, float colB=0.5, float shine=30, bool emit=false, bool emit1=false)
{
    GLfloat no_material[] = {0,0,0,1};
    GLfloat m_ambient[] = {colR/2.0,colG/2.0,colB/2.0,1};
    GLfloat m_diffuse[] = {colR,colG,colB,1};
    GLfloat m_specular[] = {colR,colG,colB,1};
    GLfloat m_shine[] = {shine};
    GLfloat m_emit[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_shine);

    if(emit & light1_flag) glMaterialfv(GL_FRONT, GL_EMISSION, m_emit);
    else if(emit1 & light3_flag) glMaterialfv(GL_FRONT, GL_EMISSION, m_emit);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_material);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void sphere(){
    GLfloat no_material[] = {0,0,0,1};
    GLfloat m_ambient[] = {0.5,0,0,1};
    GLfloat m_diffuse[] = {1.0,0,0,1};
    GLfloat m_specular[] = {1.0,0,0,1};
    GLfloat m_shine[] = {60};
    GLfloat m_emit[] = {1,1,1,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_shine);

    glutSolidSphere(1,20,16);
}

void ac(float colR=0.5, float colG=0.5, float colB=0.5, float shine=30)
{
    GLfloat m_ambient[] = {colR/2.0,colG/2.0,colB/2.0,1};
    GLfloat m_diffuse[] = {colR,colG,colB,1};
    GLfloat m_specular[] = {colR,colG,colB,1};
    GLfloat m_shine[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_shine);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_ac[c_ind[i][0]][0], v_ac[c_ind[i][0]][1], v_ac[c_ind[i][0]][2],
                    v_ac[c_ind[i][1]][0], v_ac[c_ind[i][1]][1], v_ac[c_ind[i][1]][2],
                    v_ac[c_ind[i][2]][0], v_ac[c_ind[i][2]][1], v_ac[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_ac[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void lampShade(float colR=0.5, float colG=0.5, float colB=0.5, float shine=30,bool emit=false)
{
    GLfloat no_material[] = {0,0,0,1};
    GLfloat m_ambient[] = {colR,colG,colB,1};
    GLfloat m_diffuse[] = {colR,colG,colB,1};
    GLfloat m_specular[] = {1,0,0,1};
    GLfloat m_shine[] = {shine};
    GLfloat m_emit[] = {colR,colG,colB,1};

    glMaterialfv(GL_FRONT, GL_AMBIENT, m_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, m_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, m_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, m_shine);

    if(emit & light2_flag) glMaterialfv(GL_FRONT, GL_EMISSION, m_emit);
    else glMaterialfv(GL_FRONT, GL_EMISSION, no_material);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_lshade[c_ind[i][0]][0], v_lshade[c_ind[i][0]][1], v_lshade[c_ind[i][0]][2],
                    v_lshade[c_ind[i][1]][0], v_lshade[c_ind[i][1]][1], v_lshade[c_ind[i][1]][2],
                    v_lshade[c_ind[i][2]][0], v_lshade[c_ind[i][2]][1], v_lshade[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_lshade[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

void axisSystem()
{
    float length = 10;
    float width = 0.3;

    // X-axis
    glPushMatrix();
    glTranslatef(length/2,0,0);
    glScalef(length,width,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.8,0.1,0.1);
    glPopMatrix();

    // Y-axis
    glPushMatrix();
    glTranslatef(0,length/2,0);
    glScalef(width,length,width);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.8,0.1);
    glPopMatrix();

    // Z-axis
    glPushMatrix();
    glTranslatef(0,0,length/2);
    glScalef(width,width,length);
    glTranslatef(-0.5,-0.5,-0.5);
    cube(0.1,0.1,0.8);
    glPopMatrix();
}

void windowWall()
{
    glPushMatrix();
    glTranslatef(20,0,0);
    ///wall pieces
    glPushMatrix();
    glTranslatef(0,0,-10);
    glScalef(0.5,20,7);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,3);
    glScalef(0.5,20,7);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    ///upper and lower panel
    glPushMatrix();
    glTranslatef(0,14,-10);
    glScalef(0.5,6,20);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,-10);
    glScalef(0.5,6,20);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    ///grills
    glPushMatrix();
    glTranslatef(0.25,8,-3);
    glScalef(0.25,0.25,6);
    cube(0.92,0.85,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25,10,-3);
    glScalef(0.25,0.25,6);
    cube(0.92,0.85,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25,12,-3);
    glScalef(0.25,0.25,6);
    cube(0.92,0.85,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,6,0);
    glScalef(0.25,8,0.25);
    cube(0.92,0.85,0.39);
    glPopMatrix();

    glPopMatrix();
}

void clock()
{
    glPushMatrix();
    glTranslatef(-10,11.5,0);
    ///frame
    glPushMatrix();
    glScalef(0.25,4,4);
    cube(0,0,0);
    glPopMatrix();
    ///screen
    glPushMatrix();
    glTranslatef(0.0625,0.5,0.5);
    glScalef(0.25,3,3);
    cube(1.0,1.0,1.0);
    glPopMatrix();
    ///arms
    glPushMatrix();
    glTranslatef(0.125,2,0.6);
    glScalef(0.25,0.25,1.8);
    cube(0,0,0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.125,0.8,2);
    glScalef(0.25,1.5,0.25);
    cube(0,0,0);
    glPopMatrix();

    glPopMatrix();
}

void photoFrame()
{
    glPushMatrix();
    glTranslatef(8,9,9.5);
    ///frame
    glPushMatrix();
    glScalef(3,4,0.25);
    cube(0.32,0.03,0.1);
    glPopMatrix();
    ///screen
    glPushMatrix();
    glTranslatef(0.5,0.5,-0.0625);
    glScalef(2,3,0.25);
    cube(0.94,1.0,0.5);
    glPopMatrix();
    ///photo
    glPushMatrix();
    glTranslatef(0.5,0.75,-0.125);
    glRotatef(-33,0,0,1);
    glScalef(0.25,3,0.25);
    cube(0.25,0.7,0.07);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(2,0.75,-0.125);
    glRotatef(33,0,0,1);
    glScalef(0.25,1.5,0.25);
    cube(0.25,0.7,0.07);
    glPopMatrix();

    glPopMatrix();
}

void aircon()
{
    glPushMatrix();
    glTranslatef(0,14,7);
    glScalef(10,2,3);
    ac(0.3,0.33,0.41);
    glPopMatrix();
}

void doormat()
{
    glPushMatrix();
    glTranslatef(-4,0,-3);
    ///the whole doormat
    glPushMatrix();
    glScalef(6,0.125,3);
    cube(0.27,0.07,0.74);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,1);
    glScalef(6,0.13,1);
    cube(1.0,0,0);
    glPopMatrix();

    glPopMatrix();
}

void room()
{
    ///floor
    glPushMatrix();
    glTranslatef(-10,-1,-10);
    glScalef(30,1,20);
    cube(0.45,0.45,0.45);
    glPopMatrix();
    ///a doormat on the floor
    doormat();
    ///left wall with window
    windowWall();
    ///right wall
    glPushMatrix();
    glTranslatef(-10.5,0,-10);
    glScalef(0.5,20,20);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    ///a tube light on the right wall
    glPushMatrix();
    glTranslatef(-10, 16.5, -5);
    glScalef(0.25,0.5,10);
    cube(1,1,1,60,true);
    glPopMatrix();
    ///a clock on the right wall
    clock();
    aircon();
    ///back wall
    glPushMatrix();
    glTranslatef(-10,0,10);
    glScalef(30,20,0.5);
    cube(0.25,0.44,0.64);
    glPopMatrix();
    ///a photo and an ac on the back wall
    photoFrame();
    ///ceiling
    glPushMatrix();
    glTranslatef(-10,18,-10);
    glScalef(30,1,20);
    cube(0.87,0.91,0.95);
    glPopMatrix();
}

void tool()
{
    glPushMatrix();
    glTranslatef(-3,0,1);
    ///base
    glPushMatrix();
    glTranslatef(0,2.5,0);
    glScalef(4,0.5,3);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///legs
    glPushMatrix();
    glScalef(0.5,2.5,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.5,0,0);
    glScalef(0.5,2.5,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3.5,0,2.5);
    glScalef(0.5,2.5,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,0,2.5);
    glScalef(0.5,2.5,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();

    glPopMatrix();
}

void bed()
{
    glPushMatrix();
    glTranslatef(3,0,-4);
    ///frame
    glPushMatrix();
    glScalef(12,3,13);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///drawer
    glPushMatrix();
    glTranslatef(-0.125,0.5,0.5);
    glScalef(12,2,5);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.125,0.5,6);
    glScalef(12,2,5);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    ///mattress
    glPushMatrix();
    glTranslatef(0,3,0);
    glScalef(12,0.5,13);
    cube(0.3, 0.52, 0.15);
    glPopMatrix();
    ///pillows
    glPushMatrix();
    glTranslatef(0.5,3.5,9);
    glScalef(5,0.4,3);
    cube(0.92,0.37,0.08);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(6.5,3.5,9);
    glScalef(5,0.4,3);
    cube(0.92,0.37,0.08);
    glPopMatrix();
    ///back stand
    glPushMatrix();
    glTranslatef(0,0,13);
    glScalef(12,7,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///quilt
    glPushMatrix();
    glTranslatef(1,3.5,1);
    glScalef(10,0.2,5);
    cube(0.32,0.03,0.1);
    glPopMatrix();

    glPopMatrix();
}

void lamp()
{
    ///lamp stand and base
    glPushMatrix();
    glTranslatef(2,4.5,1.5);
    glScalef(0.25,2,0.25);
    cube(0.2,0.2,0.2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.6,4.25,1);
    glScalef(1,.25,1);
    cube(0.1,0.1,0.1);
    glPopMatrix();
    ///lamp shade
    glPushMatrix();
    glTranslatef(1,6,0.5);
    glScalef(2,3,2);
    lampShade(1,0,0,1);
    glPopMatrix();
}

void bedside()
{
    glPushMatrix();
    glTranslatef(15.5,0,6);
    ///frame
    glPushMatrix();
    glScalef(4,4,3);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///drawers
    glPushMatrix();
    glTranslatef(0.25,0.25,-0.125);
    glScalef(3.5,1.75,3);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25,2.25,-0.125);
    glScalef(3.5,1.7,3);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    ///handles
    glPushMatrix();
    glTranslatef(1.5,1.5,-0.13);
    glScalef(1,0.25,3);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,3.5,-0.13);
    glScalef(1,0.25,3);
    cube(1,1,1);
    glPopMatrix();
    ///top base
    glPushMatrix();
    glTranslatef(-0.25,4,-0.25);
    glScalef(4.5,0.25,3.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///a lamp on the table
    lamp();

    glPopMatrix();
}

void dressingTable()
{
    glPushMatrix();
    glTranslatef(-5.5,0,6);
    ///body
    glPushMatrix();
    glScalef(8,4.5,3);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///drawers
    glPushMatrix();
    glTranslatef(0.5,0.5,-0.25);
    glScalef(2,3.5,3);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3,0.5,-0.25);
    glScalef(2,3.5,3);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(5.5,0.5,-0.25);
    glScalef(2,3.5,3);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    ///handles
    glPushMatrix();
    glTranslatef(2,2,-0.3);
    glScalef(0.25,1,3);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4.5,2,-0.3);
    glScalef(0.25,1,3);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(7,2,-0.3);
    glScalef(0.25,1,3);
    cube(1,1,1);
    glPopMatrix();
    ///mirror
    glPushMatrix();
    glTranslatef(1,0,3);
    glScalef(6,10,0.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.5,0,2.75);
    glScalef(5,9.5,0.5);
    cube(1,1,1);
    glPopMatrix();

    glPopMatrix();
}

void wardrobe()
{
    glPushMatrix();
    glTranslatef(-9.4,0,-4.25);
    ///body
    glPushMatrix();
    glScalef(3,8,10);
    cube(0.3,0.18,0.09);
    glPopMatrix();
    ///pulling door with handle
    glPushMatrix();
    glTranslatef(0.25,0.5,0.25);
    glScalef(3,7,3.25);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.35,4,3);
    glScalef(3,1,0.25);
    cube(1,1,1);
    glPopMatrix();
    ///other drawers
    glPushMatrix();
    glTranslatef(0.25,0.5,3.75);
    glScalef(3,2,6);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25,3,3.75);
    glScalef(3,2,6);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.25,5.5,3.75);
    glScalef(3,2,6);
    cube(0.89,0.55,0.39);
    glPopMatrix();
    ///handles
    glPushMatrix();
    glTranslatef(0.3,2,6.5);
    glScalef(3,0.25,1);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3,4.5,6.5);
    glScalef(3,0.25,1);
    cube(1,1,1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.3,7,6.5);
    glScalef(3,0.25,1);
    cube(1,1,1);
    glPopMatrix();
    ///top base
    glPushMatrix();
    glTranslatef(-0.25,8,-0.25);
    glScalef(3.5,0.25,10.5);
    cube(0.3,0.18,0.09);
    glPopMatrix();

    glPopMatrix();
}

void fan()
{
    glPushMatrix();
    glTranslatef(8,15,0);
    ///stick
    glPushMatrix();
    glTranslatef(-0.125,.25,-0.125);
    glScalef(0.25,3,0.25);
    cube(0.27,0.1,0.1);
    glPopMatrix();
    ///wall base
    glPushMatrix();
    glTranslatef(-0.5,2.5,-0.5);
    glScalef(1,.5,1);
    cube(0.34,0.24,0.11);
    glPopMatrix();
    glRotatef(theta, 0,1,0);
    ///spotlight
    glPushMatrix();
    glTranslatef(-0.5,-0.19,-0.5);
    glScalef(1,.4,1);
    cube(1,1,1,30,false,true);
    glPopMatrix();
    ///blade_1
    glPushMatrix();
    glTranslatef(-5,0,-0.5);
    glScalef(10,.125,1);
    cube(0.26, 0.7, 0.6);
    glPopMatrix();
    ///blade_2
    glPushMatrix();
    glTranslatef(-.5,0,-5);
    glScalef(1,.125,10);
    cube(0.26, 0.7, 0.6);
    glPopMatrix();
    ///bottom base
    glPushMatrix();
    glTranslatef(-0.75,-0.15,-0.75);
    glScalef(1.5,.4,1.5);
    cube(0.02,0.32,0.31);
    glPopMatrix();

    glPopMatrix();
}

void light(){
    GLfloat no_light[] = {0, 0, 0, 1.0};
    ///ambients
    GLfloat l_ambient0[] = {0.25, 0.25, 0.25, 1.0};
    GLfloat l_ambient1[] = {0.1, 0, 0, 1.0};
    GLfloat l_ambient2[] = {0.5, 0.5, 0.5, 1.0};
    ///diffuse and specular
    GLfloat l_diffuse[] = {1,1,1,1};
    GLfloat l_specular[] = {1,1,1,1};
    GLfloat l_diffuse1[] = {0.5,0,0,1};
    GLfloat l_specular1[] = {0.5,0,0,1};
    ///positions
    GLfloat l_position0[] = {-9, 16.5, -5, 1};
    GLfloat l_position1[] = {15, 7.5, 6, 1};
    GLfloat l_position2[] = {8,14,0, 1};

    ///tube light
    glEnable(GL_LIGHT0);
    ///table lamp light
    glEnable(GL_LIGHT1);
    ///spotlight
    glEnable(GL_LIGHT2);

    ///control on light properties
    if(ambient_flag){
            glLightfv(GL_LIGHT0, GL_AMBIENT, l_ambient0);
            glLightfv(GL_LIGHT1, GL_AMBIENT, l_ambient1);
            glLightfv(GL_LIGHT2, GL_AMBIENT, l_ambient2);
    }
    else {
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT2, GL_AMBIENT, no_light);
    }
    if(diffuse_flag) {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, l_diffuse);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, l_diffuse1);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, l_diffuse);
    }
    else {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light);
    }
    if(specular_flag) {
            glLightfv(GL_LIGHT0, GL_SPECULAR, l_specular);
            glLightfv(GL_LIGHT1, GL_SPECULAR, l_specular1);
            glLightfv(GL_LIGHT2, GL_SPECULAR, l_specular);
    }
    else {
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
            glLightfv(GL_LIGHT2, GL_SPECULAR, no_light);
    }

    ///position of the lights
    glLightfv(GL_LIGHT0, GL_POSITION, l_position0);
    glLightfv(GL_LIGHT1, GL_POSITION, l_position1);
    glLightfv(GL_LIGHT2, GL_POSITION, l_position2);

    ///for the spotlight
    GLfloat spot_direction[] = {0,-1,-0.75,1};
    GLfloat cut_off[] = {35};
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, cut_off);

    ///control on lights
    if(light1_flag) glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
    if(light2_flag) glEnable(GL_LIGHT1);
    else glDisable(GL_LIGHT1);
    if(light3_flag) glEnable(GL_LIGHT2);
    else glDisable(GL_LIGHT2);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 5.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye[0],eye[1],eye[2], look[0],look[1],look[2], 0,1,0);
    glViewport(0, 0, width, height);

    //axisSystem();
    //photoFrame();
    //clock();
    //aircon();
    //doormat();
    tool();
    fan();
    wardrobe();
    dressingTable();
    bed();
    bedside();
    room();
    ///a sphere for a better intuition
    glPushMatrix();
    glTranslatef(8,5,0);
    sphere();
    glPopMatrix();
    light();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case 'h':
        eye[0]-=0.2;
        break;
    case 'f':
        eye[0]+=0.2;
        break;
    case 't':
        eye[1]+=0.2;
        break;
    case 'g':
        eye[1]-=0.2;
        break;
    case '+':
        eye[2]+=0.2;
        look[2]+=0.2;
        break;
    case '-':
        eye[2]-=0.2;
        look[2]-=0.2;
        break;
    case 'l':
        look[0]-=0.2;
        break;
    case 'j':
        look[0]+=0.2;
        break;
    case 'i':
        look[1]+=0.2;
        break;
    case 'k':
        look[1]-=0.2;
        break;
    case 'r':
        controller-=2;
        break;
    case 'e':
        controller+=2;
        break;
    case '1':
        light1_flag =! light1_flag;
        break;
    case '2':
        light2_flag =! light2_flag;
        break;
    case '3':
        light3_flag =! light3_flag;
        break;
    case 'a':
        ambient_flag =! ambient_flag;
        break;
    case 'd':
        diffuse_flag =! diffuse_flag;
        break;
    case 's':
        specular_flag =! specular_flag;
        break;
    }

    glutPostRedisplay();
}

void animate()
{
    theta+=controller;
    //if(theta>=360) theta = 0.0;
    glutPostRedisplay();
}

//static void reset(int width, int height)
//{
//    glViewport(0, 0, width, height/ratio_);
//}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(400,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("project");

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);


    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    printf("\t\t------Key Guide------\n\n");
    printf("\t---CAMERA MOVEMENT---\n");
    printf("T->Up\nG->Down\nF->Left\nH->Right\n'+'->Zoom In\n'-'->Zoom Out\n");
    printf("\t---LOOKING POINT MOVEMENT---\n");
    printf("I>Up\nK->Down\nJ->Left\nL->Right\n");
    printf("\t---FAN CONTROL---\n");
    printf("E->Increase Speed\nR->Decrease Speed\n");
    printf("N.B: Once stopped, decreasing the speed will cause the fan to rotate backwards.\nAnd the controls will be reverted.\n\n");
    printf("\t---LIGHT CONTROL---\n");
    printf("1->Tube Light\n2->Table Lamp\n3->Spot Light\n");
    printf("A->Ambient\nS->Specular\nD->Diffuse\n");

    glutMainLoop();

    return EXIT_SUCCESS;
}
