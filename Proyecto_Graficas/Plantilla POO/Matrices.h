#include<stdio.h> 
#include<math.h>
float angulo;
float cosen = cos(angulo * PI/180.0);
float sen = sin(angulo * PI/180.0);

class Matriz{
public:
void mulMatrix(float _M1[16],float _M2[16],float *_M3)
{
for(int i=0;i<16;i+=4)
{
for(int j=0;j<4;j++)
{
_M3[i+j]=_M1[i]*_M2[0+j] + _M1[i+1]*_M2[4+j] + _M1[i+2]*_M2[8+j] + _M1[i+3]*_M2[12+j];
}
}
}


void escalar(float x, float y, float z){

		float matrix1[16] = {x, 0, 0, 0,
							 0, y, 0, 0,
							 0, 0, z, 0,
							 0, 0, 0, 1};

		float matrix2[16];
		float matrix3[16];

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2); 
		mulMatrix(matrix1, matrix2, matrix3);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix3);
	};

void trasladar(float x, float y, float z){

		float matrix1[16] = {1, 0, 0, 0,
							 0, 1, 0, 0,
							 0, 0, 1, 0,
							 x, y, z, 1};

		float matrix2[16];
		float matrix3[16];

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2); 
		mulMatrix(matrix1, matrix2, matrix3);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix3);
	};

void rotar(float angulo, float x, float y, float z){

		float co = cos(angulo * PI/180.0);
		float se = sin(angulo * PI/180.0);

		

		if (x==1)
		{
		float matrix1x[16] = {1, 0, 0, 0,
							 0, co, se, 0,
							 0, -se, co, 0,
							 0, 0, 0, 1};

		float matrix2[16];
		float matrix3[16];

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2); 
		mulMatrix(matrix1x, matrix2, matrix3);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix3);
		
		}

		if (y==1)
		{
	   float matrix1x[16] = {co, 0, -se, 0,
							 0, 1, 0, 0,
							 se, 0, co, 0,
							 0, 0, 0, 1};

		float matrix2[16];
		float matrix3[16];

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2); 
		mulMatrix(matrix1x, matrix2, matrix3);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix3);
		}

		if (z==1)
		{
		float matrix1z[16] = {co, se, 0, 0,
							 -se, co, 0, 0,
							 0, 0, 1, 0,
							 0, 0, 0, 1};

		float matrix2[16];
		float matrix3[16];
		

		glGetFloatv(GL_MODELVIEW_MATRIX, matrix2); 
		mulMatrix(matrix1z, matrix2, matrix3);
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(matrix3);
		}

		
		
	};
};