#version 130

in vec2 uv;
in vec3 normal;
in vec3 view_dir;
in vec3 l;
in vec3 v;
in vec3 n;
out vec4 color;
uniform vec3 LightPos;

void main()
{
    vec4 albedo = vec4(0.4f, 0.8f, 0.5f, 1.0f);
    vec4 ambient = vec4(0.1f, 0.1f, 0.1f, 1.0f);

    float marker_grid = step( abs(sin(uv.x * 4)), 0.5f) + step( abs(sin(uv.y * 4)), 0.5f);

    color = ambient + (albedo * marker_grid + (vec4(0.0f, 0.4f, 0.5f, 1.0f) * (1 - marker_grid)));
}
