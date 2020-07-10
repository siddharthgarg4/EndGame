#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
layout(location = 1) in vec2 attrTextureCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;
 
out vec2 vecTextureCoord;

void main() {
    vecTextureCoord = attrTextureCoord;
    gl_Position = u_viewProjection * u_transform * vec4(attrPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec2 vecTextureCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
    color = texture(u_texture, vecTextureCoord) * u_color;
}