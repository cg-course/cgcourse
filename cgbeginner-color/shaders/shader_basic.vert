#version 130

in vec4 pos;
in vec3 vcolor;

out vec3 outcolor;

void main(void)
{
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    outcolor = vcolor;
}

