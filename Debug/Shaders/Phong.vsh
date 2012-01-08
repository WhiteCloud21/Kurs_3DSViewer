//позиция фрагмента
varying vec3 position;

//нормаль
varying vec3 normal;

void main (void)
{
	//позиция точки
	position=vec3(gl_ModelViewMatrix*gl_Vertex);

	//нормаль
	normal=vec3(gl_NormalMatrix*gl_Normal);
	
	// текстурные координаты
	gl_TexCoord[0]=gl_MultiTexCoord0;
	
	//положение в пространстве наблюдения
	gl_Position=ftransform();
}
