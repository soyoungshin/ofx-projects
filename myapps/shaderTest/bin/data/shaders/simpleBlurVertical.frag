#extension GL_ARB_texture_rectangle : enable
uniform sampler2DRect src_tex_unit0;
uniform float blurAmnt;

void main( void )
{  
	vec2 st = gl_TexCoord[0].st;
	
	//vertical blur 
	//from http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
	
	vec4 color;
	
	color		+= 1.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * 4.0));
	color		+= 2.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * 3.0));
	color		+= 3.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * 2.0));
	color		+= 4.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * 1.0));	
		
	color		+= 5.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt) );
	
	color		+= 4.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * -1.0));
	color		+= 3.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * -2.0));
	color		+= 2.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * -3.0));
	color		+= 1.0 * texture2DRect(src_tex_unit0, st + vec2(0.0, blurAmnt * -4.0));
	
	color /= 25.0;
	gl_FragColor = color;
}