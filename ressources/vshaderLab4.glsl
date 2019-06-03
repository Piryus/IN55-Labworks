#version 330

uniform mat4 mvp;

in vec3 position;
in vec3 color;
in vec2 uv;

out vec3 fColor;
out vec2 texCoord;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4( position, 1.0 );

    fColor = color;
    texCoord = uv;
}
