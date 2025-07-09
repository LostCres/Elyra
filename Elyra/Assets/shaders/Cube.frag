#version 330 core

out vec4 color;
in vec3 v_Normal;

void main() {
    vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));
    vec3 normal = normalize(v_Normal);
    float diff = max(dot(normal, -lightDir), 0.0);

    vec3 baseColor = vec3(1.0, 0.3, 0.6);
    vec3 shadedColor = baseColor * diff;

    color = vec4(shadedColor, 1.0);
}
