#include <GLUT/GLUT.h>
#include <iostream>
#include <stdlib.h>
#include "imageLoader.h"

float rotationAngle = 0;
GLuint textureId;
GLUquadric *quad;
float rotate1, alr = 0.5, alg = 0.5, alb = 0.5, dlr = 1.0,  dlg = 1.0, dlb = 1.0, slr = 1.0, slg = 1.0,  slb = 1.0, scale_x = 1.0, scale_y = 1.0, scale_z = 1.0;
bool enableLighting = false;  //keyboard control = 'e'


GLuint loadTexture(Image* image) {
    
    
    
    glGenTextures(1, &textureId); //Make room for our texture
    
    glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
    
    //Map the image to the texture
    
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 
                 0,                            //0 for now
                 
                 GL_RGB,                       //Format OpenGL uses for image
                 
                 image->width, image->height,  //Width and height
                 
                 0,                            //The border of the image
                 
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 
                 //as unsigned numbers
                 
                 image->pixels);               //The actual pixel data
    
    return textureId; //Returns the id of the texture
    
}

// Draw the shere
void drawSphere()
{


    glPushMatrix();
    
  

    // add the earth texture to the sphere
    quad = gluNewQuadric();
    Image* image = loadBMP("/Users/Stephanie/Documents/Xcode_projects/Earth\ Looking\ at\ Itself/Earth\ Looking\ at\ Itself/earth.bmp");
    delete image;
    
    textureId = loadTexture(image);
    glEnable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    
    //Bottom
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    
    glScalef(scale_x, scale_y, scale_z);
    
    // Rotate the globe by the specific angle and vector
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glColor3f( 1.0f, 1.0f, 1.0f );
   
    gluQuadricTexture(quad,1);

    gluSphere(quad, 5.0f, 24, 24);
    glTranslatef(0.0, 3.0, 0.0);

    glPopMatrix();
    
    
    

}

// Draw the mirror
void drawFloor(float width, float length, float alpha)
{
    // Begin drawing the floor
    glBegin(GL_QUADS);
    
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width / 2, 0.0f, length / 2);
    glVertex3f(-width / 2, 0.0f, -length / 2);
    glVertex3f(width / 2, 0.0f, -length / 2);
    glVertex3f(width / 2, 0.0f, length / 2);
    
    glEnd();
}

// Handle keyboard input
void handleKeyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
            // Close on escape key
        case 'q':
            exit(0);
        case 'e':  // turn on the light
            if (enableLighting == false) {
                enableLighting = true;
            }
            break;
            glutPostRedisplay();
        case 'd':
            if (enableLighting == true) {
                enableLighting = false;
            }
            break;
            glutPostRedisplay();
            
        case 'r':
            if (alr < 1.0) {
                alr += 0.1;
            }
            else alr =0.0;
            if (dlr < 1.0) {
                dlr += 0.1;
            }else dlr = 0.0;
            if (slr < 1.0) {
                slr += 0.1;
            }else slr = 0.0;
            break;
            glutPostRedisplay();
        case 'g':
            if (alg < 1.0) {
                alg += 0.1;
            }
            else alg =0.0;
            if (dlg < 1.0) {
                dlg += 0.1;
            }else dlg= 0.0;
            if (slg < 1.0) {
                slg += 0.1;
            }else slg = 0.0;
            break;
            glutPostRedisplay();
        case 'b':
            if (alb < 1.0) {
                alb += 0.1;
            }
            else alb =0.0;
            if (dlb < 1.0) {
                dlb += 0.1;
            }else dlb= 0.0;
            if (slb < 1.0) {
                slb += 0.1;
            }else slb = 0.0;
            break;
            glutPostRedisplay();
        case 'x':
            scale_x += 0.01;
            if (scale_x >= 3.0) {
                scale_x = 1.0;
            }
            scale_y += 0.01;
            scale_y += 0.01;
            break;
            glutPostRedisplay();
        case 'z':
            scale_x -= 0.01;
            if (scale_x < 1.0) {
                scale_x = 1.0;
            }
            scale_y -= 0.01;
            if (scale_y < 1.0) {
                scale_y = 1.0;
            }
            
            scale_z -= 0.01;
            if (scale_z < 1.0) {
                scale_z = 1.0;
            }

            break;
            glutPostRedisplay();

        
    }
}

void initRendering(){
    GLfloat lightAmbient[] = {alr, alg ,alb, 1.0f};
    GLfloat lightDiffuse[] = {dlr, dlg, dlb, 1.0f};
    GLfloat lightSpecular[] = {slr, slg, slb, 1.0f};
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 1000.0);
}

void drawScene()
{
    if (enableLighting == true) {
        initRendering();
    }
   // Clear the stencil buffer
    glClearStencil(0);
    // Clear depth
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);  //specify modelview matrix is the current matrix
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, -45.0f);
    glRotatef(45, 1.0f, 0.0f, 0.0f);
    
    // Set light position
    GLfloat lightPosition[] = {0.0f, 10.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    
    // Draw sphere
    glPushMatrix();  //pushes the current matrix stack down by one, duplicating the current matrix
    glTranslatef(0.0f, 5.0f, 0.0f);
    drawSphere();
    glPopMatrix();   //pops the current matrix stack, replacing the current matrix with the one below it on the stack.
    
    // Enable the stencil buffer
    glEnable(GL_STENCIL_TEST); //stencil buffer is an optional extension of the depth buffer that gives you more control over the question of which fragments should be drawn and which shouldn't
    
    // Disable drawing colors
    glColorMask(0, 0, 0, 0);     //Specify whether red, green, blue, and alpha can or cannot be written into the frame buffer.
    // Disable depth testing
    glDisable(GL_DEPTH_TEST);
    // Make the stencil test always pass
    glStencilFunc(GL_ALWAYS, 1, 1);
    // Make pixels in the stencil buffer be set to 1 when the stencil test passes
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    // Set all of the pixels covered by the floor to be 1 in the stencil buffer
    drawFloor(30.0f, 30.f, 1.0f);
    
    // Enable drawing colors to the screen
    glColorMask(1, 1, 1, 1);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Make the stencil test pass only when the pixel is 1 in the stencil buffer
    glStencilFunc(GL_EQUAL, 1, 1);
    // Make the stencil buffer not change
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    
    //Draw the sphere, reflected vertically, at all pixels where the stencil
    //buffer is 1
    glPushMatrix();
    glScalef(1, -1, 1);  //produces a nonuniform scaling along the x, y, and z axes
    glTranslatef(0, 5.0f, 0);
    drawSphere();
    glPopMatrix();
    
    // Disable using the stencil buffer
    glDisable(GL_STENCIL_TEST);
    
    // Blend the floor onto the screen
    glEnable(GL_BLEND);
    drawFloor(30.0f, 30.f, 0.8f);
    glDisable(GL_BLEND);
    
    glutSwapBuffers();
}

void update(int value)
{
    rotationAngle += 1.0f;
    if (rotationAngle > 360)
        rotationAngle = 0;
    
    glutPostRedisplay();
    glutTimerFunc(25, update, 0);
}


int main(int argc, char *argv[])
{
    // Initialize Glut
    glutInit(&argc, argv);
    // Initialize display mode and use stencil
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
    // Initialize a Glut window
    glutInitWindowSize(800, 600);
    // Create glut window
    glutCreateWindow("Earth Looking at Itself");
  
   
    // Set display function
    glutDisplayFunc(drawScene);
    // Initialize rendering
    
    // Set timer function
    glutTimerFunc(25, update, 0);
    // Set keyPress function
    glutKeyboardFunc(handleKeyPress);
    // Set resize function
    glutReshapeFunc(handleResize);
    // Start OpenGL loop
    glutMainLoop();
    
    return 0;
}