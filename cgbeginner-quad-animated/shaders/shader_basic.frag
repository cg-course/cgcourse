#version 130

out vec4 color;
in vec2 outuv;

uniform vec2 screenSize;
uniform float time;

void main()
{
    vec2 p = screenSize * outuv / 10;

    float col = abs(sin(p.x + sin(p.y + time)) * sin(p.y));
    color = vec4(col, col, col, 1.0);
}
