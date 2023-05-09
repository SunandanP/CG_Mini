#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416

float theta = 0;

struct point
{
    GLfloat x, y, z;
};

void display();
void bezierPlot(point*, int, int);
int factorial(int);
void BezierTakeControl(float, point*, int , point*, int*);
void nCr(int,int*);

void BezierTakeControl(float t,
                       point *bezierPoints,
                       int numberOfControlPoints,
                       point *controlPoints,
                       int *ncrValues)
{
    int i, n = numberOfControlPoints - 1;

    float breinsteinPolynomial;

    bezierPoints -> x = 0;
    bezierPoints -> y = 0;
    bezierPoints -> z = 0;

    for(i=0; i < numberOfControlPoints; i++)
    {
        breinsteinPolynomial = ncrValues[i] * pow(t, i) * pow(1 - t, n - i);

        bezierPoints -> x += breinsteinPolynomial * controlPoints[i].x;
        bezierPoints -> y += breinsteinPolynomial * controlPoints[i].y;
        bezierPoints -> z += breinsteinPolynomial * controlPoints[i].z;
    }
}

void bezierPlot(point *controlPoints, int numberOfControlPoints, int numberOfBezierPoints)
{
    point bezierPoint;
    float t;
    int *ncrValues, i;

    ncrValues = new int[numberOfControlPoints]; // to hold the nCr values

    nCr(numberOfControlPoints - 1, ncrValues); // call nCr function to calculate nCr values

    glBegin(GL_LINE_STRIP);
        for(i=0; i <= numberOfBezierPoints; i++)
        {
            t=float(i)/float(numberOfBezierPoints);
            BezierTakeControl(t, &bezierPoint, numberOfControlPoints, controlPoints, ncrValues);
            glVertex2f(bezierPoint.x, bezierPoint.y);
        }
    glEnd();

    delete[] ncrValues;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int number_of_control_points = 4, number_of_bezier_points = 20;

    point control_points_array[4] = {{100, 400, 0}, {150, 450, 0}, {250, 350, 0},{300, 400, 0}};

    control_points_array[1].x += 50*sin(theta * PI/180.0);
    control_points_array[1].y += 25*sin(theta * PI/180.0);

    control_points_array[2].x -= 50*sin((theta+30) * PI/180.0);
    control_points_array[2].y -= 50*sin((theta+30) * PI/180.0);

    control_points_array[3].x -= 25*sin((theta-30) * PI/180.0);
    control_points_array[3].y += sin((theta-30) * PI/180.0);

    theta += 2;

    glPushMatrix();

    glPointSize(5);

    glColor3f(1, 0.4, 0.2); //Indian flag: Saffron color code
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0 );
        bezierPlot(control_points_array, number_of_control_points, number_of_bezier_points);
    }

    glColor3f(1, 1, 1); //Indian flag: white color code
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezierPlot(control_points_array, number_of_control_points, number_of_bezier_points);
    }

    glColor3f(0, 1, 0); //Indian flag: green color code
    for(int i=0; i<50; i++)
    {
        glTranslatef(0, -0.8, 0);
        bezierPlot(control_points_array, number_of_control_points, number_of_bezier_points);
    }

    glPopMatrix();

    glLineWidth(5);

    glColor3f(0.7, 0.5,0.3); //pole colour
    glBegin(GL_LINES);
        glVertex2f(100,400);
        glVertex2f(100,40);
    glEnd();

    glutPostRedisplay();
    glutSwapBuffers();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
}

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n= n * factorial(n-1);
    return n;
}

void nCr(int n, int *hold_ncr_values)
{
    int r;
    for(r=0; r <= n; r++) //start from nC0, then nC1, nC2, nC3 till nCn
    {
        hold_ncr_values[r] = factorial(n) / (factorial(n-r) * factorial(r));
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Flag using Bazier Curve");

    init();

    glutDisplayFunc(display);
    glutMainLoop();
}
