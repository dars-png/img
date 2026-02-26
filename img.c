#include "img.h"
#include "include/stb_image.h"

img_data load_img_data_from_file(const char* path) {
	img_data data;
	data.data = stbi_load(path, &data.width, &data.height, &data.channels, 4);
	return data;
}

sg_image load_img_from_data(img_data data) {
	if (!data.data) {
		return (sg_image){0};
	}

	sg_image img = sg_alloc_image();

	sg_init_image(img, &(sg_image_desc){
		.width = data.width,
		.height = data.height,
		.pixel_format = SG_PIXELFORMAT_RGBA8,
		.usage.immutable = true,
		.sample_count = 1,
		.data = (sg_range) {
			.ptr = data.data,
			.size = (size_t) (data.width * data.height * 4)
		}
			});


	return img;
}
