#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
layout(location = 1) in vec2 attrTextureCoord;
uniform mat4 u_viewProjection;
uniform mat4 u_transform;
out vec3 vecPosition;
out vec2 vecTextureCoord;
void main() {
    vecPosition = attrPosition;
    vecTextureCoord = attrTextureCoord;
    gl_Position = u_viewProjection * u_transform * vec4(vecPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 vecPosition;
in vec2 vecTextureCoord;
uniform sampler2D u_texture;
void main() {
    color = texture(u_texture, vecTextureCoord);
}