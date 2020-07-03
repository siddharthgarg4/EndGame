#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
uniform mat4 u_viewProjection;
uniform mat4 u_transform;
out vec3 vecPosition;
void main() {
    vecPosition = attrPosition;
    gl_Position = u_viewProjection * u_transform * vec4(vecPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 vecPosition;
uniform vec3 u_flatColor;
void main() {
    color = vec4(u_flatColor, 1.0);
}