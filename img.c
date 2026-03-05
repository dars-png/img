#include "img.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

//temporary
#include <unistd.h>

img_data load_img_data_from_file(const char* path) {
	img_data data;

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("Working Directory: %s\n", cwd);
	printf("Given Path: %s\n", path);

	stbi_set_flip_vertically_on_load(1);
	data.data = stbi_load(path, &data.width, &data.height, &data.channels, 4);
	if (!data.data) {
		printf("ERROR LOADING IMAGE FILE: %s\n", stbi_failure_reason());
		exit(-2);
	}
	return data;
}

void load_img_from_data(sg_image img, img_data data) {
	if (!data.data) {
		return;
	}

	printf("DATA FOR IMAGE\n");
	printf("Width: %d\n", data.width);
	printf("Height: %d\n", data.height);

	sg_init_image(img, &(sg_image_desc){
		.type = SG_IMAGETYPE_2D,
		.width = data.width,
		.height = data.height,
		.data.mip_levels[0] = {
			.ptr = data.data,
			.size = (size_t) (data.width * data.height * 4)},
		.pixel_format = SG_PIXELFORMAT_RGBA8,
			});
}

void img_data_free(img_data data) {
	stbi_image_free(data.data);
}
