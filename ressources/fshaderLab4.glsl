#version 330

uniform sampler2D texId;

in vec3 fColor;
in vec2 texCoord;

out vec4 fragColor;

void main()
{
    fragColor = texture2D(texId, texCoord);
    //fragColor = vec4(texCoord, 0., 1.);
}
