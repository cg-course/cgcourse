#version 130

in vec4 pos;
out vec2 uv;
out vec3 normal;

uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 NormalMatrix;
uniform vec3 LightPos;

float f(float x, float y) {
    return sin(x * y);
}

float df_dx(float x, float y, float z) {
    return 0;
}

float df_dy(float x, float y, float z) {
    return 0;
}

float df_dz(float x, float y, float z) {
    return -1;
}

void main(void)
{
    float x = pos.x*4.0f;
    float y = pos.y*4.0f;
    float z = f(x, y);
    vec4 posf = vec4(pos.x, pos.y, z/10.0f, 1.0f);
    gl_Position = MVP * posf;
    uv = pos.xy*4.0f;

    normal = -normalize(vec3(df_dx(x, y, z),
                            df_dy(x, y, z),
                            df_dz(x, y, z)));
}

