#include "includes.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define PI 3.1415926535898

int option = 0;
int line = 0;
float r, g, b;

//Set lines for default layout
void setline(x1, x2, y1, y2){
    glBegin(GL_LINES);
    glLineWidth(line);
    glColor3f(r, g, b);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

//Set point for bresenham algorithm
void setpoint(x, y, line){
    glPointSize(line);
    glBegin(GL_POINTS);
        glColor3f(r, g, b);
        glVertex2i(x, y);
    glEnd();
}

//Bresenham algorithm present in the classroom
void bresenham(GLfloat x1, GLfloat x2, GLfloat y1, GLfloat y2){

    glLineWidth(line);
    glColor3f(r, g, b);
    GLfloat dx,dy,incE,incNE,d;

    int x, y, i;

    dx = x2 - x1;
    dy = y2 - y1;
    d = (2 * dy) - dx;
    incE = 2 * dy;
    incNE = 2 * (dy - dx);
    x = x1;
    y = y1;

    setpoint(x, y, line);

    if (dx == 0) {
        for(i = y1; i <= y2; i++) {
            setpoint(x, i, line);
        }
    } else if (dy == 0) {
        for (i = x1; i <= x2; i++){
            setpoint(i, y, line);
        }
    } else {
        while (x <= x2) {
            if (d <= 0) {
                d += incE;
                x = x + 1;
            } else {
                d += incNE;
                x = x + 1;
                y = y + 1;
            }
            setpoint(x, y, line);
        }
    }
}

//Classifies the type of circle using a flag.
void classifyCircle(int x, int y, int valor, int xc, int yc, int option) {
    switch (option){
        case 1: //full circle
            setpoint(x + xc, y + yc, valor); // top right
            setpoint(y + xc, x + yc, valor); // top2 right
            setpoint(y + xc, -x + yc, valor); //bottom right
            setpoint(x + xc, -y + yc, valor); //bottom 2 right
            setpoint(-x + xc, -y + yc, valor); //bottom left
            setpoint(-y + xc, -x + yc, valor); //bottom 2 left
            setpoint(-y + xc, x + yc, valor); //top left
            setpoint(-x + xc, y + yc, valor); //top2 left
        break;

        case 2: //semi circle left
            setpoint(x + xc, y + yc, valor);
            setpoint(y + xc, x + yc, valor);
            setpoint(y + xc, -x + yc, valor);
            setpoint(x + xc, -y + yc, valor);
        break;

        case 3: //semi circle right
            setpoint(-x + xc, -y + yc, valor);
            setpoint(-y + xc, -x + yc, valor);
            setpoint(-y + xc, x + yc, valor);
            setpoint(-x + xc, y + yc, valor);
        break;

        case 4: //corner top right
            setpoint(x + xc, y + yc, valor);
            setpoint(y + xc, x + yc, valor);
        break;

        case 5: //corner bottom right
            setpoint(y + xc, -x + yc, valor);
            setpoint(x + xc, -y + yc, valor);
        break;

        case 6: //corner top left
            setpoint(-y + xc, x + yc, valor);
            setpoint(-x + xc, y + yc, valor);
        break;

        case 7: //corner bottom left
            setpoint(-x + xc, -y + yc, valor);
            setpoint(-y + xc, -x + yc, valor);
        break;
    }
}

//Function to draw a circle
void bresenhamCircle(int r, int value, int xc, int yc, int option){

    int x = 0 ;
    int y = r;
    double d = 1.25 - r;

    classifyCircle(x, y, value, xc, yc, option);

    while(y > x){
        if (d < 0) {
            d += 2.0 * x + 1.0;
        } else {
            d += 2 * (x - y) + 1;
            y--;
        }
        x++;
        classifyCircle(x, y, value, xc, yc, option);
    }
}

//Draw dots
void dots(void) {
    bresenhamCircle(4.0f, line, 384.0f, 300.0f, 1); //central
    bresenhamCircle(2.0f, line, 210.0f, 375.0f, 1); //left top
    bresenhamCircle(2.0f, line, 558.0f, 225.0f, 1); //left bottom
    bresenhamCircle(2.0f, line, 312.0f, 375.0f, 1); //left top center
    bresenhamCircle(2.0f, line, 312.0f, 225.0f, 1); //left bottom center
    bresenhamCircle(2.0f, line, 456.0f, 375.0f, 1); //right top center
    bresenhamCircle(2.0f, line, 456.0f, 225.0f, 1); //right bottom center
    bresenhamCircle(2.0f, line, 558.0f, 375.0f, 1); //right top
    bresenhamCircle(2.0f, line, 210.0f, 225.0f, 1); //right bottom
}

//Draw circles
void circles(void) {
    bresenhamCircle(45.0f, line, 384.0f, 300.0f, 1); //central circle
    bresenhamCircle(35.0f, line, 210.0f, 375.0f, 1); //Left Top Circle
    bresenhamCircle(35.0f, line, 210.0f, 225.0f, 1); //Left Bottom Circle
    bresenhamCircle(35.0f, line, 558.0f, 375.0f, 1); //Right Top Circle
    bresenhamCircle(35.0f, line, 558.0f, 225.0f, 1); //Right Bottom Circle
}

//Draw semicircles
void semicircles(void) {
    bresenhamCircle(26.0f,line,140.0f,300.0f,2); //semicircle left
    bresenhamCircle(26.0f,line,628.0f,300.0f,3); //semicircle right
    bresenhamCircle(50.0f,line,618.0f,400.0f,4); //corner top right
    bresenhamCircle(50.0f,line,618.0f,200.0f,5); //corner bottom right
    bresenhamCircle(50.0f,line,150.0f,400.0f,6); //corner top left
    bresenhamCircle(50.0f,line,150.0f,200.0f,7); //corner bottom left
}

//Draw lines
void lines(void) {

    if(option == 1){
        //main lines
        bresenham(100,100,190,410); //left
        bresenham(668,668,190,410); //right
        bresenham(140,625,450,200); //top
        bresenham(140,628,150,150); //bottom

        //vertical lines
        bresenham(140,140,150,450); //left
        bresenham(300,300,150,450); //left center
        bresenham(384,384,150,450); //center
        bresenham(468,468,150,450); //right center
        bresenham(628,628,150,450); //right

        //top left circle details
        bresenham(220,220,410,419);
        bresenham(200,200,410,419);
        bresenham(220,220,332,342);
        bresenham(200,200,332,342);

        //bottom left circle details
        bresenham(220,220,260,269);
        bresenham(200,200,260,269);
        bresenham(220,220,182,192);
        bresenham(200,200,182,192);

        //bottom right circle details
        bresenham(570,570,260,269);
        bresenham(550,550,260,269);
        bresenham(570,570,182,192);
        bresenham(550,550,182,192);

        //top right circle details
        bresenham(570,570,410,419);
        bresenham(550,550,410,419);
        bresenham(570,570,332,342);
        bresenham(550,550,332,342);
    } else {
        printf("aqui");
        //main lines
        setline(100,100,190,410); //left
        setline(668,668,190,410); //right
        setline(140,625,450,450); //top
        setline(140,628,150,150); //bottom

        //vertical lines
        setline(140,140,150,450); //left
        setline(300,300,150,450); //left center
        setline(384,384,150,450); //center
        setline(468,468,150,450); //right center
        setline(628,628,150,450); //right

        //top left circle details
        setline(220,220,410,419);
        setline(200,200,410,419);
        setline(220,220,332,342);
        setline(200,200,332,342);

        //bottom left circle details
        setline(220,220,260,269);
        setline(200,200,260,269);
        setline(220,220,182,192);
        setline(200,200,182,192);

        //bottom right circle details
        setline(570,570,260,269);
        setline(550,550,260,269);
        setline(570,570,182,192);
        setline(550,550,182,192);

        //top right circle details
        setline(570,570,410,419);
        setline(550,550,410,419);
        setline(570,570,332,342);
        setline(550,550,332,342);
    }

}

//Layout based in bresenham algorithm
void bresenhamLayout(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(line);
    glColor3f(r, g, b);

    lines(); //display all lines
    circles(); //display all circles
    dots(); //display all dots
    semicircles(); //display all semicircles

    glFlush();
}

//Default Layout
void defaultLayout(void) {

    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(line);
    glColor3f(r, g, b);
    GLfloat circle_points = 1000;
    GLfloat angle = 0;
    GLfloat radio = 45.0f;
    int i;

    lines(); //display all lines

    /*
     * Circles
     */
    glBegin(GL_LINE_LOOP); //central circle
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 384.0f, (sin(angle) * radio) + 300.0f);
        }
    glEnd();

    radio = 35.0f;

    glBegin(GL_LINE_LOOP); //Left Top Circle
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 210.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //Left Bottom Circle
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 210.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //Right Top Circle
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 558.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //Right Bottom Circle
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 558.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    /*
     * Dots
     */
    radio = 4.0f;

    glBegin(GL_LINE_LOOP); //center
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 384.0f, (sin(angle) * radio) + 300.0f);
        }
    glEnd();

    radio = 2.0f;

    glBegin(GL_LINE_LOOP); //left top
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 210.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //left bottom
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 558.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //left top center
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 312.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //left bottom center
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 312.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //right top center
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 456.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //right bottom center
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 456.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //right top
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 558.0f, (sin(angle) * radio) + 375.0f);
        }
    glEnd();

    glBegin(GL_LINE_LOOP); //right bottom
        for (i = 0; i < circle_points; i++) {
            angle = (2 * PI * i / circle_points);
            glVertex2i((cos(angle) * radio) + 210.0f, (sin(angle) * radio) + 225.0f);
        }
    glEnd();

    /*
     * Semicircles
     */
    radio = 26.0f;

    glBegin(GL_LINE_LOOP); //semicircle left
    for (i = (-1) * (circle_points / 4); i < circle_points / 4; i++) {
        angle = (2 * PI * i / circle_points);
        glVertex2i((cos(angle) * radio) + 140.0f, (sin(angle) * radio) + 300.0f);
    }
    glEnd();

    glBegin(GL_LINE_LOOP); //semicircle right
    for (i = 3 * (circle_points / 4); i > circle_points / 4; i--) {
        angle = (2 * PI * i / circle_points);
        glVertex2i((cos(angle) * radio) + 628.0f, (sin(angle) * radio) + 300.0f);
    }
    glEnd();

    radio = 50.0f;

    glBegin(GL_LINE_STRIP); //corner top right
        for (i = 0; i <= circle_points; i++) {
            angle = (PI / 2.0f) * i /circle_points;
            glVertex2f((0.5+cos(angle)*radio) + 618.0f, (0.5+sin(angle)*radio) + 400.0f );
        }
    glEnd();

    glBegin(GL_LINE_STRIP); //corner top left
        for (i = 2 * (circle_points); i >= circle_points; i--) {
            angle = (PI / 2.0f) * i /circle_points;
            glVertex2f((0.5+cos(angle)*radio) + 149.0f, (0.5+sin(angle)*radio) + 400.0f );
        }
    glEnd();

    glBegin(GL_LINE_STRIP); //corner bottom right
    for (i = 0; i <= circle_points; i++) {
        angle = (PI / -2) * i /circle_points;
        glVertex2f((0.5+cos(angle)*radio) + 618.0f, (0.5+sin(angle)*radio) + 200.0f );
    }
    glEnd();

    glBegin(GL_LINE_STRIP); //corner bottom left
        for (i = 2 * (circle_points); i >= circle_points; i--) {
            angle = (PI / -2) * (i) /circle_points;
            glVertex2f((0.5+cos(angle)*radio) + 149.0f, (0.5+sin(angle)*radio) + 200.0f );
        }
    glEnd();

    glFlush();
}

//Init
void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 760, 0, 600);
}

//Main
int main(int argc, char **argv) {

    printf("Colors:\n");
    printf("R: ");
    scanf("%f",&r);
    printf("G: ");
    scanf("%f",&g);
    printf("B: ");
    scanf("%f",&b);

    printf("\nLine Size: ");
    scanf("%d",&line);

    printf("\nPress 1 for BRESENHAM and 2 for DEFAULT\n");
    scanf("%d",&option);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(760, 500);
    glutCreateWindow("Computer graphics: Ice hockey court");
    init();

    if(option == 1){
        glutDisplayFunc(bresenhamLayout);
    } else {
        glutDisplayFunc(defaultLayout);
    }

    glutMainLoop();

    return 0;
}