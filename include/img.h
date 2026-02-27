#ifndef IMG_H
#define IMG_H

#include <stdint.h>
#include "sokol_gfx.h"
#include "stb_image.h"

typedef struct img_data {
	int width;	
	int height;	
	int channels;

	unsigned char* data;
} img_data;

//static inline img_data load_img_data_from_file(const char* path);
//static inline sg_image load_img_from_data(img_data data);

static inline img_data load_img_data_from_file(const char *path) {
	img_data data;
	data.data = stbi_load(path, &data.width, &data.height, &data.channels, 4);
	return data;
}

static inline sg_image load_img_from_data(img_data data) {
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


#endif
