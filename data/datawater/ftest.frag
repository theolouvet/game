#version 120
uniform sampler2D myTexture;
uniform sampler2D myTexture2;
uniform sampler2D myTexture3;
uniform float alpha;
uniform vec3 mLightPos;
uniform vec3 mCamPos;
uniform vec3 mLigthColor;
varying vec4 pos;
uniform float Time;
uniform float fragmentation;



vec3 ul;// = normalize(lum -pos);
vec3 t;// = normalize(POS_CAM - pos);
vec3 nt;// =  normalize(texture2D(myTexture, vec2(gl_TexCoord[0]))).rgb * 2.0 -1;

float Ia = 0.2;
float Kd = 0.8;
float ks = 0.2;
float es = 128;
float Is;
float Id;

void main (void)
{
    nt = texture2D(myTexture2, fragmentation * vec2(gl_TexCoord[0]) + fragmentation/10 * Time/100 * vec2(1,1)).rgb *2.0 - 1.0;
    vec3 cailloux = texture2D(myTexture3,  250 * vec2(gl_TexCoord[0])).rgb; 
    vec3 N = normalize(nt);
    ul =  normalize(mLightPos - vec3(pos.x,pos.y,pos.z));
    t = normalize(mCamPos - vec3(pos.x,pos.y,pos.z));
    vec3 s = normalize(reflect(ul, N));


    Id = Kd * clamp(dot(N, ul),0,1);
    Is = ks * pow( clamp(dot(s,t),0,1), es);

    vec3 color = alpha * vec3(78.0/255.0, 131.0/255.0, 169.0/255.0) + (1-alpha) *cailloux;
  
    vec4 c =  vec4(color.xyz, 1.0);

    gl_FragColor =  (Ia + Id) * c + Is* vec4(mLigthColor.rgb,1) ;


    gl_FragColor.a = 1.0;
}
