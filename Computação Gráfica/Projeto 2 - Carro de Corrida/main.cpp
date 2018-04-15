//------------------------------------------------------------------------------
//
// UNIVERSIDADE GAMA FILHO - UGF
//
// COMPUTAÇÃO GRÁFICA
//
// Prof. Cláudio M. N. A. Pereira
//
// Transformações 2D - Trabalho A1 - Carro de Corrida
//
// Aluno Ruan Pedro Dias Seraphim Mat. 20101075779
//
// Aluno Sérgio da Silva Pereira  Mat. 20101609418
// 
//------------------------------------------------------------------------------

#include <windows.h>
#include <stdlib.h>
#include <math.h>
//#include <iostream.h> 
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glut.h>

#define PI 3.1415926535898 

float Tx=-3.5, Ty=-30, R=0, S=3, z=0.15, m=0, k=0;
int v=0, vmax=20, vmin=-20, vscale=10, tm=0, tmin=1;

char texto1[52]="UNIVERSIDADE GAMA FILHO - UGF";
char texto2[52]="COMPUTAÇÃO GRÁFICA";
char texto3[52]="Prof. Cláudio M. N. A. Pereira";
char texto4[52]="Transformações 2D - Trabalho A1 - Carro de Corrida";
char texto5[52]="Aluno Ruan Pedro Dias Seraphim Mat. 20101075779";
char texto6[52]="Aluno Sérgio da Silva Pereira  Mat. 20101609418";
char texto7 [4]="UGF";

//------------------------------------------------------------------------------
// Timer
//------------------------------------------------------------------------------
void Timer(int value) {
         
   // Cálculo de aceleração
   tm=abs(abs(v*vscale)-(vmax*vscale));
   
   //Impede que se dê imprensão que inprensão que o sentido de movimento inverso
   if(tm<tmin)tm=tmin;
   
   // Configura o timer com tempo de rechamada
   glutTimerFunc(tm, Timer, 1);
   
   //Atualiza posição da faixa central da pista de rolamento simulando movimento
   if(v > 0) if(m >  0) m--; else m=12;
   if(v < 0) if(m < 12) m++; else m=0;  
   
   // Redesenha a tela
   glutPostRedisplay();    
}

//------------------------------------------------------------------------------
// Desenha Texto
//------------------------------------------------------------------------------
void DesenhaTexto(float x, float y, char *string) 
{  
    // Posição no universo onde o texto será colocado             
    glRasterPos2f(x,y); 
    glPushMatrix();
    // Exibe caracter a caracter
    while(*string){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
    }
    glPopMatrix();
}

//------------------------------------------------------------------------------
// Desenha Circulo Preenchido
//------------------------------------------------------------------------------
void cirulo(float x, float y, float r) {
    int i=0;
    float a=0; 
    int p = 1000; 
    
    glBegin(GL_POLYGON); 
        for(i=0; i<p; i++) 
        {           
            glVertex2f((cos(a)*r)+x,(sin(a)*r)+y); 
            a+=(360.0/p);
        } 
    glEnd();
}

//------------------------------------------------------------------------------
// Desenha Oval Preenchido
//------------------------------------------------------------------------------
void oval(float x, float y, float w, float h)
{
    float t, a;
    int n = 1000;
    a = PI / n;
    
    glBegin (GL_POLYGON); 
        for (t = 0; t < 360; t += a)
        { 
            glVertex2f (w/2 * cos (t)+x, h/2 * sin (t)+y);
        }
    glEnd ();
}

//------------------------------------------------------------------------------
// Inicializa
//------------------------------------------------------------------------------
void Init () {
    
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glOrtho (-100, 100, -100, 100, -100, 100);
}

//------------------------------------------------------------------------------
// Display
//------------------------------------------------------------------------------
void Display () {
    
	//--------------------------------------------------------------------------
	// Inicializa matrizes
	//--------------------------------------------------------------------------
	Init();

	//--------------------------------------------------------------------------
	// Limpa janela
	//--------------------------------------------------------------------------
    glClearColor (1, 1, 1, 1);								// Cor de fundo
    glClear(GL_COLOR_BUFFER_BIT);							// Limpa janela
 
    //--------------------------------------------------------------------------
	// Desenha os canteiros laterais da Pista de Rolameto
	//--------------------------------------------------------------------------
	glColor3f (0, 1, 0);
    glBegin (GL_QUADS);
       	glVertex2f (-100,-100);
       	glVertex2f ( -50,-100);
       	glVertex2f ( -50, 100);
       	glVertex2f (-100, 100);
       	
       	glVertex2f (  50,-100);
       	glVertex2f ( 100,-100);
       	glVertex2f ( 100, 100);
       	glVertex2f (  50, 100);
    glEnd();
    
   	//--------------------------------------------------------------------------
	// Desenha da Pista de Rolameto
	//--------------------------------------------------------------------------
    glColor3f (0, 0, 0);
    glBegin (GL_QUADS);
       	glVertex2f ( -50,-100);
       	glVertex2f (  50,-100);
       	glVertex2f (  50, 100);
       	glVertex2f ( -50, 100);
    glEnd();
    
    //--------------------------------------------------------------------------
	// Desenho das faixas laterais da pista de rolamento
	//-------------------------------------------------------------------------- 
    glColor3f (1, 1, 1);
    glBegin (GL_QUADS);
       	glVertex2f (-40,-100);
       	glVertex2f (-39,-100);
       	glVertex2f (-39, 100);
       	glVertex2f (-40, 100);
       	
       	glVertex2f (40,-100);
       	glVertex2f (39,-100);
       	glVertex2f (39, 100);
       	glVertex2f (40, 100);
    glEnd();
    
    //--------------------------------------------------------------------------
	// Desenha a dinâmica do movimento da faixa central da pista de rolamento
	//--------------------------------------------------------------------------  
    glBegin (GL_QUADS);   
        for(k=-100; k<100; k=k+12) 
        {        
           	glVertex2f (-0.5, k+m  );
           	glVertex2f ( 0.5, k+m  );
           	glVertex2f ( 0.5, k+m+4);
           	glVertex2f (-0.5, k+m+4);
        }
    glEnd(); 
    
    //--------------------------------------------------------------------------
	// Label
	//--------------------------------------------------------------------------   
    glColor3f (1, 1, 1);
    glBegin (GL_QUADS);
        glColor3f (1, 1, 1);
        glVertex2f (-99, -99);
       	glVertex2f (-30, -99);
       	glVertex2f (-30, -72);
       	glVertex2f (-99, -72); 
   	glEnd(); 
    
    glColor3f (0, 0, 0);
    DesenhaTexto(-95, -76, texto1); 
    DesenhaTexto(-95, -80, texto2); 
    DesenhaTexto(-95, -84, texto3); 
    DesenhaTexto(-95, -88, texto4); 
    DesenhaTexto(-95, -92, texto5); 
    DesenhaTexto(-95, -96, texto6);
    
  	//--------------------------------------------------------------------------
	// Escala
	//--------------------------------------------------------------------------
  	glScalef(S, S, S);
  	
  	//--------------------------------------------------------------------------
	// Rotação Carro de Corrida
	//--------------------------------------------------------------------------   
    glTranslatef((Tx+3.5), (Ty+7.5), 0);        // p/ Rotação (centro)
    glRotatef(R, 0, 0, 1);
   	glTranslatef(-(Tx+3.5), -(Ty+7.5), 0);      // p/ Rotação (centro) 	
	
	//--------------------------------------------------------------------------
	// Carro de Corrida - Empilha matriz - para "Double Buffering"
	//--------------------------------------------------------------------------
    glPushMatrix();
        //----------------------------------------------------------------------
    	// Translação
     	//---------------------------------------------------------------------- 
        glTranslatef(Tx, Ty, 0);
    	//----------------------------------------------------------------------
    	// Desenha Carro de Corrida
    	//----------------------------------------------------------------------
        glBegin (GL_QUADS);
        
            glColor3f (1, 1, 1);
            
            glVertex2f (0-z, 3-z);
           	glVertex2f (2+z, 3-z);
           	glVertex2f (2+z, 5+z);
           	glVertex2f (0-z, 5+z);
           	
           	glVertex2f (5-z, 3-z);
           	glVertex2f (7+z, 3-z);
           	glVertex2f (7+z, 5+z);
           	glVertex2f (5-z, 5+z);
           	
           	glVertex2f (0-z, 10-z);
           	glVertex2f (2+z, 10-z);
           	glVertex2f (2+z, 13+z);
           	glVertex2f (0-z, 13+z);
           	
           	glVertex2f (5-z, 10-z);
           	glVertex2f (7+z, 10-z);
           	glVertex2f (7+z, 13+z);
           	glVertex2f (5-z, 13+z);
            
            glColor3f (1, 0, 0);
            
           	glVertex2f (0, 0);
           	glVertex2f (7, 0);
           	glVertex2f (7, 3);
           	glVertex2f (0, 3);
                	
            glVertex2f (0, 14);
           	glVertex2f (7, 14);
           	glVertex2f (7, 16);
           	glVertex2f (0, 16);
           	
           	glColor3f (0, 1, 0);
           	
        	glVertex2f (2, 11);
           	glVertex2f (3, 11);
           	glVertex2f (3, 12);
           	glVertex2f (2, 12);
           	
        	glVertex2f (4, 11);
           	glVertex2f (5, 11);
           	glVertex2f (5, 12);
           	glVertex2f (4, 12);
           	
           	glColor3f (0, 0, 1);
           	
            glVertex2f (2, 3);
           	glVertex2f (5, 3);
           	glVertex2f (5, 10);
           	glVertex2f (2, 10);
        
        	glVertex2f (2, 10);
           	glVertex2f (5, 10);
           	glVertex2f (4, 14);
           	glVertex2f (3, 14);
           	
            glColor3f (0, 0, 0);
           	
        	glVertex2f (0, 3);
           	glVertex2f (2, 3);
           	glVertex2f (2, 5);
           	glVertex2f (0, 5);
           	
           	glVertex2f (5, 3);
           	glVertex2f (7, 3);
           	glVertex2f (7, 5);
           	glVertex2f (5, 5);
           	
           	glVertex2f (0, 10);
           	glVertex2f (2, 10);
           	glVertex2f (2, 13);
           	glVertex2f (0, 13);
           	
           	glVertex2f (5, 10);
           	glVertex2f (7, 10);
           	glVertex2f (7, 13);
           	glVertex2f (5, 13);           	
           	   
        glEnd();
        
        //----------------------------------------------------------------------
    	// Desenha Texto
    	//----------------------------------------------------------------------
        glColor3f (1, 1, 0);
        DesenhaTexto(2, 1, texto7);
                
        //----------------------------------------------------------------------
    	// Desenha Cockpit
    	//----------------------------------------------------------------------
        glColor3f (1, 1, 0);
        
        oval(3.5, 7.5, 2, 3);
           
    //--------------------------------------------------------------------------
    // Carro de Corrida - Desempilha matriz - para "Double Buffering"
    //-------------------------------------------------------------------------- 
    glPopMatrix();
    
    glutSwapBuffers();
    
    glFlush();            // Descarrega buffer
}

//------------------------------------------------------------------------------
// Controle de Teclado
//------------------------------------------------------------------------------
void Keyboard (unsigned char key, int x, int y) {

	switch (key) {
   	case 27:
    {
         exit(0); 
         break;
    }
   	case 'd':  	
    {
        if(Tx < 20) Tx = Tx + 1;            
        break;
    }
   	case 'e':  	
   	{
        if(Tx > -27) Tx = Tx - 1;              
        break;
    }
   	case 'c':  	
   	{
        if(Ty < 40)Ty = Ty + 1; 
        else Ty = -50;
        break;  
    }
   	case 'b':  	
   	{
        if(Ty > -50)Ty = Ty - 1; 
        else Ty = 40;
        break;  
    }
   	case 'r':  	
   	{ 
        R = R + 1; 
        break;
    }
    case 'f':  	
   	{
        R = R - 1; 
        break;
    }
    case 't':  	
   	{
        if(v < vmax) v = v + 1; 
        break;
    }
    case 'g':  	
   	{   
        if(v > vmin) v = v - 1; 
        break;
    }
   	case '-':  	
   	{
        S = S * 0.95; // Zoom Out
        break; 
    }
   	case '+':  	
   	{
        S = S * 1.05; // Zomm In
        break; 
    }
   	case ' ':  	
   	{
        Tx=-3.5, Ty=-30, S=3, R=0, v=0; 
        break; 
    }
	

   }

//   cout << endl << "Tx=" << Tx <<  "  Ty=" << Ty <<  "  R=" << R << endl;

   glutPostRedisplay();
}

//------------------------------------------------------------------------------
// Principal
//------------------------------------------------------------------------------
int main (int argc, char** argv) {
    tm=vscale*vmax;
    
	// Inicializa glut
	glutInit (&argc, argv);

	// Inicializa modos de display (single buffer e cores RGB)
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

   // Tamanho da janela
   glutInitWindowSize (700,700);

   // Posição inicial da janela
   glutInitWindowPosition (50,50);

   // Cria a janela
	glutCreateWindow ("UGF - Carro de Corrida - A1");

   Init();

   // Executa função Display
   glutDisplayFunc (Display);

   // Executa função Display
   glutKeyboardFunc (Keyboard);
   
   //glutIdleFunc(Display);
   
   glutTimerFunc(tm, Timer, 1); 

   // Entra em loop
   glutMainLoop();
}

//------------------------------------------------------------------------------
// Fim
//------------------------------------------------------------------------------
