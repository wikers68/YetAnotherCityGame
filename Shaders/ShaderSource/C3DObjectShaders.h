#pragma once

static const char *VertexShader_StaticObject =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"layout( location = 1) in vec2 uv0;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"
	"out vec2 uv;"
	"void main()"
	"{"
	"uv = uv0;"
	"gl_Position =  Projection* View * Model* vec4(vertexPosition,1.0) ;"
	"};"
};

static const char *FragmentShader_StaticObject =
{
	"#version 420 core\n"
	"in vec2 uv;"
	"uniform sampler2D baseColor;"
	"layout (location = 0) out vec4 color;"
	"layout (location = 1) out int MaterialID;"
	"void main()"
	"{"
	"MaterialID = 60;"
	"color = texture(baseColor,uv);"
	"};"
};