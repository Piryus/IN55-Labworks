#version 330

uniform mat4 mvp;

in vec3 position;
in vec3 color;

out vec3 fColor;
out vec3 fPosition;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp * vec4(position, 1.0);
    //gl_PointSize = gl_Position.z * 2 ;
    //fColor = vec3(1, 15 / gl_Position.z, 1);
    fPosition = position.xyz;
}
