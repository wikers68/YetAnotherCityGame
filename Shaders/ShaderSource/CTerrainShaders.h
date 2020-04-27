#pragma once

static const char *VertexShader_CTerrain =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"
	"uniform vec4 SizePosition;"
	"out vec2 uv;"
	"void main()"
	"{"
	"float longitude =  (vertexPosition.x - 0.5f) * SizePosition.x + SizePosition.z;  "
	"float latitude =  (vertexPosition.y - 0.5f) * SizePosition.y + SizePosition.w;  "
	"uv = vertexPosition.xy;"
	"gl_Position =  Projection* View * Model* vec4(longitude, latitude, 0.0 ,1.0) ;"
	"};"
};

static const char *FragmentShader_CTerrain =
{
	"#version 420 core\n"
	"in vec2 uv;"
	"uniform sampler2D baseColor;"
	"layout (location = 0) out vec4 color;"
	"layout (location = 2) out int MaterialID;"
	"void main()"
	"{"
	"MaterialID = 230;"
	"color = vec4(uv.x,uv.y,0.0,1.0f);"
	//"color = texture(baseColor,uv);"
	"};"
};