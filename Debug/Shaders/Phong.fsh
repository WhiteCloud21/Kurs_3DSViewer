//позициЯ фрагмента
varying vec3 position;
//нормаль
varying vec3 normal;
//texture using
uniform bool useTex1;
uniform bool useTexSpec;
//texture
uniform sampler2D tex1;
uniform sampler2D texSpec;

void main (void)
{
	//Вычисление нормали
	vec3 n_normal=normalize(normal);
	vec4 FragColor=vec4(0.0,0.0,0.0,0.0);

	// Вектор на камеру
	vec3 n_to_cam = normalize(-position);
	// Правильное отображение нелицевых граней
	if (dot(n_normal,n_to_cam) < 0.0)
		n_normal=-n_normal;

	vec3 n_to_light=normalize(vec3(gl_LightSource[0].position)-position);
	
	if (useTex1)
	{
		//Диффузный цвет
		vec4 diffuse_color=texture2D(tex1,vec2(gl_TexCoord[0]));
		//Диффузный коэффициент
		float Diffuse_coef=max(dot(n_normal,n_to_light),0.0);
		//результирующий диффузный цвет
		diffuse_color=diffuse_color*gl_LightSource[0].diffuse*Diffuse_coef;

		// фоновый цвет
		vec4 ambient_color = texture2D(tex1,vec2(gl_TexCoord[0])) * gl_LightSource[0].ambient;

		// Зеркальный цвет
		vec4 specular_color =  texture2D(tex1,vec2(gl_TexCoord[0])) * gl_LightSource[0].specular;
		vec3 n_reflect = normalize(reflect(-n_to_light,n_normal));

		float spec_coef = pow(max(dot(n_reflect,n_to_cam),0.0),gl_FrontMaterial.shininess);
		specular_color = specular_color * spec_coef;

		FragColor=diffuse_color+ambient_color+specular_color;
	}
	else
	{
		FragColor=gl_FrontMaterial.emission;
		
		//Диффузный цвет
		vec4 diffuse_color=gl_FrontMaterial.diffuse;
		//Диффузный коэффициент
		float Diffuse_coef=max(dot(n_normal,n_to_light),0.0);
		//результирующий диффузный цвет
		diffuse_color=diffuse_color*gl_LightSource[0].diffuse*Diffuse_coef;

		// фоновый цвет
		vec4 ambient_color = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;

		// Зеркальный цвет
		vec4 specular_color;
		if (useTexSpec)
			specular_color = texture2D(texSpec,vec2(gl_TexCoord[0])) * gl_LightSource[0].specular;
		else
			specular_color = gl_FrontMaterial.specular * gl_LightSource[0].specular;	
		vec3 n_reflect = normalize(reflect(-n_to_light,n_normal));
		
		float spec_coef = pow(max(dot(n_reflect,n_to_cam),0.0),gl_FrontMaterial.shininess);
		specular_color = specular_color * spec_coef;
		
		FragColor=FragColor+diffuse_color+ambient_color+specular_color;
		FragColor.a = gl_FrontMaterial.emission.a;
	}
	gl_FragColor=FragColor;
}