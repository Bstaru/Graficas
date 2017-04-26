#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Matrices.h"


Matriz* auxMat;

class Billy
{
public:

	float color[4];
	float local_p[4];
	float width;
	float height;
	GLuint texture;

	Billy(GLuint tex, float w, float h, float posx, float posy, float posz){
		texture = tex;
		width = w / 2.0;
		height = h / 2.0;
		local_p[0] = posx;
		local_p[1] = posy;
		local_p[2] = posz;
		local_p[3] = 1.0;
		color[0] = 1;
		color[1] = 1;
		color[2] = 1;
		color[3] = 1;
		auxMat = new Matriz();
	}
	~Billy() {};

	void draw(){


	

		float modelview[16];
		int i, j;
		
		
		// undo all rotations
		// beware all scaling is lost as well 
		for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) {
			if (i == j)
				modelview[i * 4 + j] = 1.0;
			else
				modelview[i * 4 + j] = 0.0;
		}

		// get the current modelview matrix
		glGetFloatv(GL_MODELVIEW_MATRIX, modelview);

		glLoadMatrixf(modelview);
		// save the current modelview matrix
		glPushMatrix();
		
		
		glBindTexture(GL_TEXTURE_2D, texture);

		GLfloat vert1[3];
		GLfloat vert2[3];
		GLfloat vert3[3];
		GLfloat vert4[3];

		// bottom left corner
		vert1[0] = local_p[0] - width;
		vert1[1] = local_p[1] - height;
		vert1[2] = local_p[2];

		// top left corner  
		vert2[0] = local_p[0] - width;
		vert2[1] = local_p[1] + height;
		vert2[2] = local_p[2];

		// bottom right corner
		vert3[0] = local_p[0] + width;
		vert3[1] = local_p[1] - height;
		vert3[2] = local_p[2];

		// top right corner
		vert4[0] = local_p[0] + width;
		vert4[1] = local_p[1] + height;
		vert4[2] = local_p[2];

		
		glColor4fv(color);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3fv(vert1);
		glTexCoord2f(1, 0);
		glVertex3fv(vert3);
		glTexCoord2f(1, 1);
		glVertex3fv(vert4);
		glTexCoord2f(0, 1);
		glVertex3fv(vert2);
		glEnd();
		

	
		

		glPopMatrix();


	}
	

};
