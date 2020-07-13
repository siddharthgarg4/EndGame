#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
layout(location = 1) in vec4 attrColor;
layout(location = 2) in vec2 attrTextureCoord;

uniform mat4 u_viewProjection;
 
out vec4 vecColor;
out vec2 vecTextureCoord;

void main() {
    vecColor = attrColor;
    vecTextureCoord = attrTextureCoord;
    gl_Position = u_viewProjection * vec4(attrPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec4 vecColor;
in vec2 vecTextureCoord;

uniform sampler2D u_texture;

void main() {
    color = vecColor;
    // color = texture(u_texture, vecTextureCoord) * u_color;
}