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
layout(binding = 0) uniform texture2D tex;
layout(binding = 0) uniform sampler smp;

in vec3 outColour;
in vec2 TexCoord;

out vec4 frag_color;

void main() {
	frag_color = texture(sampler2D(tex, smp), TexCoord);
}
@end

@program simple vs fs
