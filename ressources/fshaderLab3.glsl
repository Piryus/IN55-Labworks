#version 330

in vec3 fColor;
in vec3 fPosition;

out vec4 fragColor;

void main()
{
    if(length(fPosition) < 0.51) {
        fragColor = vec4(1, 1, 0, 1);
    } else if (length(fPosition) < 0.55) {
        fragColor = vec4(1, 0, 0, 1);
    } else if (length(fPosition) < 0.60) {
        fragColor = vec4(0, 0, 1, 1);
    } else if (length(fPosition) < 0.65) {
        fragColor = vec4(0, 0, 0, 1);
    } else if (length(fPosition) < 1) {
        fragColor = vec4(1, 1, 1, 1);
    }

}
