#version 120
uniform sampler2D myTexture;
uniform sampler2D mytexture2;
varying float a;

void main (void)
{
    vec4 col = texture2D(myTexture, vec2(gl_TexCoord[0]));
    //col *= gl_Color;
	gl_FragColor =  col ;
	/*if(a >= -0.5){
		gl_FragColor =  col ;
	}
	if(a < -0.5){
		gl_FragColor = texture2D(myTexture2, vec2(gl_TexCoord[0]));
	}*/


}
