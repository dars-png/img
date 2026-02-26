#define STBI_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

#define SOKOL_IMPL
#define SOKOL_GLCORE
#include "img.h"

int main() {
	img_data data = load_img_data_from_file("test_assets/ptsd_meme.png");
	sg_image img = load_img_from_data(data);
	stbi_image_free(data.data);

	return 0;
}
