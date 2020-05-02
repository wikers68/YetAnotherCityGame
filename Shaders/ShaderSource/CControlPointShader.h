#pragma once

static const char *VertexShader_CControlPoint =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"uniform vec3 WorldPosition;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"
	"void main()"
	"{"
	"vec3 vWorlPosition = vertexPosition * WorldPosition;"
	"gl_Position =  Projection* View * Model* vec4(vWorlPosition ,1.0) ;"
	"};"
};

static const char *GeomShader_CControlPoint =
{
	"#version 410 core\n"
	"layout(points) in;"
	"layout(triangle_strip,max_vertices = 4) out;"
	/*"in inVertex{"
	"vec4 gl_Position;"
	"} gl_in[];"*/
	"void main()"
	"{"
	//gl_in[0].gl_Position +

		"float size = 0.2f;"

		"gl_Position =  gl_in[0].gl_Position +vec4(size,size,0.0,0.0);"
		"EmitVertex();"

		"gl_Position =  gl_in[0].gl_Position + vec4(-size,size,0.0,0.0);"
		"EmitVertex();"
		
		"gl_Position = gl_in[0].gl_Position + vec4(size,-size,0.0,0.0);"
		"EmitVertex();"

		"gl_Position = gl_in[0].gl_Position + vec4(-size,-size,0.0,0.0);"
		"EmitVertex();"

		"EndPrimitive();"
	"}"
};

static const char *FragmentShader_CControlPoint =
{
	"#version 420 core\n"
	"layout (location = 1) out vec4 color;"
	"layout (location = 2) out int MaterialID;"
	"layout (location = 3) out int Object_ID;"
	"uniform int ID;"
	"uniform vec3 Color;"
	"void main()"
	"{"
	"Object_ID = ID;"
	"MaterialID = 145;"
	"color = vec4(Color,1.0f);"
	//"color = texture(baseColor,uv);"
	"};"
};