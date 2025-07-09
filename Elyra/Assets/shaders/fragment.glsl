#version 330 core

out vec4 color;
in vec3 v_Normal;

uniform vec3 u_BaseColor;

void main() {
    vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));
    vec3 normal = normalize(v_Normal);
    float diff = max(dot(normal, -lightDir), 0.0);

    vec3 shadedColor = u_BaseColor * diff;

    color = vec4(shadedColor, 1.0);
}
