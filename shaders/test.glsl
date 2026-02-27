@vs vs
in vec3 position;
in vec3 aColor;
in vec2 aTexCoords;

out vec3 outColour;
out vec2 TexCoord;

void main() {
	gl_Position = vec4(position, 1.0);
	outColour = aColor;
	TexCoord = aTexCoords;
}
@end


@fs fs
out vec4 FragColour;

in vec3 outColour;
in vec2 TexCoord;

layout(binding = 0) uniform texture2D _ourTexture;
layout(binding = 0) uniform sampler ourTexture_smp;
#define ourTexture sampler2D(_ourTexture, ourTexture_smp)

void main() {
	FragColour = texture(ourTexture, TexCoord);
}
@end

@program simple vs fs
