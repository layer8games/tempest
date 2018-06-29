#version 430 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 dimensions;
layout (location = 3) in vec2 bottomTop;
layout (location = 4) in vec2 leftRight;

uniform mat4 projection_mat;
uniform mat4 translation_mat;
//uniform mat4 transform_mat;

out vec4 gs_color;
out vec4 gs_dimensions;
out vec2 gs_bottomTop;
out vec2 gs_leftRight;

void main(void)
{
	gl_Position = projection_mat * position;
//	gl_Position = perspective_mat * modelView_mat * position;
	gs_color = color;
//Because the geometry shader just applies the dimensions directly, the dimensions 
//have to be transformed by the projection_matrix. Maybe this could be done better.
	gs_dimensions = projection_mat * vec4(dimensions.x, dimensions.y, 0.0, 0.0);
	gs_bottomTop = bottomTop;
	gs_leftRight = leftRight;
}