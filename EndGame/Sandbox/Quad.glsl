#type vertex
#version 330 core
layout(location = 0) in vec3 attrPosition;
layout(location = 1) in vec4 attrColor;
layout(location = 2) in vec2 attrTextureCoord;
layout(location = 3) in float attrTextureIndex;
layout(location = 4) in float attrTilingFactor;

uniform mat4 u_viewProjection;
 
out vec4 vecColor;
out vec2 vecTextureCoord;
out float vecTextureIndex;
out float vecTilingFactor;

void main() {
    vecColor = attrColor;
    vecTextureCoord = attrTextureCoord;
    vecTextureIndex = attrTextureIndex;
    vecTilingFactor = attrTilingFactor;
    gl_Position = u_viewProjection * vec4(attrPosition, 1.0);
}

#type fragment
#version 330 core
layout(location = 0) out vec4 color;

in vec4 vecColor;
in vec2 vecTextureCoord;
in float vecTextureIndex;
in float vecTilingFactor;

uniform sampler2D u_textures[16];

void main() {
    vec4 texColor = vecColor;
    switch(int(vecTextureIndex)) {
        case  0: texColor *= texture(u_textures[0],  vecTextureCoord * vecTilingFactor); break;
        case  1: texColor *= texture(u_textures[1],  vecTextureCoord * vecTilingFactor); break;
        case  2: texColor *= texture(u_textures[2],  vecTextureCoord * vecTilingFactor); break;
        case  3: texColor *= texture(u_textures[3],  vecTextureCoord * vecTilingFactor); break;
        case  4: texColor *= texture(u_textures[4],  vecTextureCoord * vecTilingFactor); break;
        case  5: texColor *= texture(u_textures[5],  vecTextureCoord * vecTilingFactor); break;
        case  6: texColor *= texture(u_textures[6],  vecTextureCoord * vecTilingFactor); break;
        case  7: texColor *= texture(u_textures[7],  vecTextureCoord * vecTilingFactor); break;
        case  8: texColor *= texture(u_textures[8],  vecTextureCoord * vecTilingFactor); break;
        case  9: texColor *= texture(u_textures[9],  vecTextureCoord * vecTilingFactor); break;
        case 10: texColor *= texture(u_textures[10], vecTextureCoord * vecTilingFactor); break;
        case 11: texColor *= texture(u_textures[11], vecTextureCoord * vecTilingFactor); break;
        case 12: texColor *= texture(u_textures[12], vecTextureCoord * vecTilingFactor); break;
        case 13: texColor *= texture(u_textures[13], vecTextureCoord * vecTilingFactor); break;
        case 14: texColor *= texture(u_textures[14], vecTextureCoord * vecTilingFactor); break;
        case 15: texColor *= texture(u_textures[15], vecTextureCoord * vecTilingFactor); break;
        //default attach to white texture
        default: texColor *= texture(u_textures[0],  vecTextureCoord * vecTilingFactor); break;
    }
    color = texColor;
}