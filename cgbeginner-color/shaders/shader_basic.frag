#version 130

out vec4 color;
in vec3 outcolor;

void main()
{
    color = vec4(outcolor.r, outcolor.g, outcolor.b, 1.0);
}
