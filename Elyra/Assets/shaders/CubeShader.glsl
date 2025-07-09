#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Normal;

void main() {
    vec4 worldPosition = u_Transform * vec4(a_Position, 1.0);
    gl_Position = u_ViewProjection * worldPosition;

    // Approximate normal using model transform
    v_Normal = mat3(transpose(inverse(u_Transform))) * a_Position;
}

#type fragment
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
