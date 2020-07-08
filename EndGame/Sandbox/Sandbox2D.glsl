#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;
void main() {
    gl_Position = u_viewProjection * u_transform * vec4(attrPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_color;
void main() {
    color = vec4(u_color);
}