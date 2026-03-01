#define SOKOL_IMPL
#define SOKOL_GLCORE
#include "img.h"
#include "sokol/sokol_app.h"
#include "sokol/sokol_glue.h"
#include "sokol/sokol_log.h"
#include "shaders/simple.glsl.h"

// this is problem but i fix tomorrow
// it is now today so i fix problem


static struct {
	sg_pipeline pip;
	sg_bindings bind;
	sg_pass_action pass_action;
} state;

static void init(void) {
	sg_setup(&(sg_desc){
		.environment = sglue_environment(),
		.logger.func = slog_func,
			});

	img_data data = load_img_data_from_file("test_assets/ptsd_meme.png");
	sg_image img = load_img_from_data(data);
	img_data_free(data);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,  1.0f, 1.0f, 0.0f,   0.0f, 1.0f 
	};

	state.bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc){
		.data = SG_RANGE(vertices), // just found out you can do this btw
		.size = sizeof(vertices),
			});

	uint16_t indices[] = {
		0, 1, 3,
		1, 2, 3 
	};

	state.bind.index_buffer = sg_make_buffer(&(sg_buffer_desc){
		.size = sizeof(indices),
		.data = SG_RANGE(indices),
	});

	state.pip = sg_make_pipeline(&(sg_pipeline_desc){
		.shader = sg_make_shader(simple_shader_desc(sg_query_backend())),
		.index_type = SG_INDEXTYPE_UINT16,
		.layout = {
			.attrs = {
				[ATTR_simple_position].format = SG_VERTEXFORMAT_FLOAT3,
				[ATTR_simple_aColor].format = SG_VERTEXFORMAT_FLOAT3,
				[ATTR_simple_aTexCoords].format = SG_VERTEXFORMAT_FLOAT2
			}
		},
	});

	state.pass_action = (sg_pass_action) {
		.colors[0] = { .load_action=SG_LOADACTION_CLEAR, .clear_value={0.2f, 0.3f, 0.3f, 1.0f} }
	};
}

void frame(void) {
	sg_begin_pass(&(sg_pass){ .action = state.pass_action, .swapchain = sglue_swapchain() });
	sg_apply_pipeline(state.pip);
	sg_apply_bindings(&state.bind);

	sg_draw(0, 4, 1);
	sg_end_pass();
	sg_commit();
}

void cleanup(void) {
	sg_shutdown();
}

sapp_desc sokol_main(int argc, char* argv[]) {
	(void)argc; (void)argv;
	return (sapp_desc){
		.init_cb = init,
		.frame_cb = frame,
		.cleanup_cb = cleanup,
		.width = 640,
		.height = 480,
		.window_title = "img test",
		.icon.sokol_default = true,
		.logger.func = slog_func,
	};
}
