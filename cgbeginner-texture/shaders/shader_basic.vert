#version 130

in vec4 pos;
in vec2 uv;

out vec2 outuv;

void main(void)
{
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
    outuv = uv;
}

