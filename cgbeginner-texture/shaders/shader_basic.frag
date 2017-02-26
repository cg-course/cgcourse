#version 130

out vec4 color;
in vec2 outuv;

uniform vec2 screenSize;
uniform sampler2D cat;
uniform float time;

void main()
{
    vec2 p = screenSize * outuv / 10;
    vec4 cat_pix = texture2D (cat, outuv);
//    vec4 cat_pix = texture2D (cat, outuv + time/4);
//    vec4 cat_pix = texture2D (cat, outuv + sin (length(outuv) + time));
//    vec4 cat_pix = texture2D (cat, vec2(outuv.x, outuv.y - (1.5 + sin(outuv.x * 40 + time/10)) * (1.5 + sin(outuv.x * 40 + time/10)) * time/500));
//    vec4 cat_pix = texture2D (cat, outuv + length(texture2D (cat, outuv + sin(outuv.x + time))) * (1 - sin(outuv.x + time)));
//    vec4 cat_pix = texture2D (cat, outuv + length(texture2D (cat, vec2(outuv.x + time/10, outuv.y)))/4); cat_pix = cat_pix * vec4 (abs(sin(time*4-1)), abs(sin(time*8+6)), abs(sin(time)), 1.0);

    color = vec4(cat_pix.rgb, 1.0);
}
