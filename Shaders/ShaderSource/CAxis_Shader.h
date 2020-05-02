#pragma once

static const char *VertexShader_CAxis =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"uniform vec3 PointWorldPosition;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"
	"void main()"
	"{"

	"vec3 vertexWorldPosition = vertexPosition +PointWorldPosition; "
	"gl_Position =  Projection* View * Model* vec4(vertexWorldPosition ,1.0) ;"
	"};"
};

static const char *GeomShader_CAxis =
{
	"#version 410 core\n"
	"layout(lines) in;"
	"layout(triangle_strip,max_vertices = 4) out;"

	"void main()"
	"{"

		"vec2 LineDirection =  gl_in[1].gl_Position.xy -  gl_in[0].gl_Position.xy;"

		//Orthogonal vector to the line direction
		"vec4 Ortho = normalize(vec4(LineDirection.y,-LineDirection.x,0.0,0.0));"
		//"vec4 Ortho = vec4(0.4,0.3,0.0,0.0);"
		
		"float size = 0.1f;"

		"gl_Position =  gl_in[1].gl_Position +Ortho * size ;"
		"EmitVertex();"

		"gl_Position =  gl_in[0].gl_Position +Ortho* size ;"
		"EmitVertex();"
		
		"gl_Position =  gl_in[1].gl_Position - Ortho * size;"
		"EmitVertex();"
	
		"gl_Position =  gl_in[0].gl_Position -Ortho* size;"
		"EmitVertex();"

		"EndPrimitive();"
	"}"
};

static const char *FragmentShader_CAxis =
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