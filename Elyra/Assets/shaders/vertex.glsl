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