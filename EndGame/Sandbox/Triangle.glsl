#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
layout(location = 1) in vec4 attrColor;
uniform mat4 u_viewProjection;
uniform mat4 u_transform;
out vec3 vecPosition;
out vec4 vecColor;
void main() {
    vecPosition = attrPosition;
    vecColor = attrColor;
    gl_Position = u_viewProjection * u_transform * vec4(vecPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;
in vec3 vecPosition;
in vec4 vecColor;
void main() {
    color = vecColor;
}