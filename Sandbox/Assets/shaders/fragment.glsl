#version 330 core

out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Albedo;
uniform vec3 ambientColor;
uniform vec3 u_BaseColor;
uniform bool u_UseAlbedoTexture;

void main() {
    vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));
    vec3 normal = normalize(v_Normal);
    float diff = max(dot(normal, -lightDir), 0.0);

    vec3 base = u_UseAlbedoTexture 
        ? texture(u_Albedo, v_TexCoord).rgb 
        : u_BaseColor;

    vec3 shadedColor = base * (diff + ambientColor);

    color = vec4(shadedColor, 1.0);
}
