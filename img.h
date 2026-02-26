#include <cstdint>
#include "sokol/sokol_gfx.h"

typedef struct img_data {
	int width;	
	int height;	
	int channels;

	unsigned char* data;
} img_data;

img_data load_img_data_from_file(const char* path);
sg_image load_img_from_data(img_data data);
