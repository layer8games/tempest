#version 430 core
		
layout(points) in;
layout(triangle_strip, max_vertices = 6) out;

in vec4 gs_color[];
in vec4 gs_dimensions[];
in vec2 gs_bottomTop[];
in vec2 gs_leftRight[];

out vec4 fs_color;
out vec2 fs_uvs;

void main()
{
	fs_color = gs_color[0];
//Right Bottom
	fs_uvs = vec2(gs_leftRight[0].y, gs_bottomTop[0].x);
	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, -gs_dimensions[0].y, 0, 0);
 	EmitVertex();
//Right Top
	fs_uvs = vec2(gs_leftRight[0].y, gs_bottomTop[0].y);
	gl_Position = gl_in[0].gl_Position + vec4(-gs_dimensions[0].x, gs_dimensions[0].y, 0.0, 0.0);
	EmitVertex();
//Left Bottom
	fs_uvs = vec2(gs_leftRight[0].x, gs_bottomTop[0].x);
 	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, -gs_dimensions[0].y, 0.0, 0.0);
	EmitVertex();
//Left Top
	fs_uvs = vec2(gs_leftRight[0].x, gs_bottomTop[0].y);
	gl_Position = gl_in[0].gl_Position + vec4(gs_dimensions[0].x, gs_dimensions[0].y, 0, 0);
	EmitVertex();

	EndPrimitive();
}