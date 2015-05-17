#ifndef GRAPHICMANAGER_H
#define GRAPHICMANAGER_H

#include <wx/glcanvas.h>
#include <GL/glu.h>
#include <math.h>
#include <wx/image.h>
#include <iostream>

class GraphicManager {
    public:
        GraphicManager();
        static GLuint* loadTexture(char * path);
        static void drawRectangle(GLfloat x1,GLfloat x2,GLfloat y1,GLfloat y2,GLfloat z);
        static void drawTexturedQuad(GLfloat quadCoords[5], GLfloat texCoords[4]);
        static GLuint* texture; // Texture of all game objects. :-)


    protected:


    private:


};

#endif //GRAPHICMANAGER_H
