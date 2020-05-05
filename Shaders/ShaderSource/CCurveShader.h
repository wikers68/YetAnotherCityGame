#pragma once

static const char *VertexShader_CTerrainCurve =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"

	"out VS_OUT {"
	"float Height;"
	"} vs_out;"

	"void main()"
	"{"
	"vs_out.Height = vertexPosition.z;"
	"gl_Position =  Projection* View * Model* vec4(vertexPosition ,1.0) ;"
	"};"
};

static const char *GeomShader_CTerrainCurve =
{
	"#version 410 core\n"
	"layout(lines) in;"
	"layout(triangle_strip,max_vertices = 4) out;"

	"in VS_OUT {"
	"float Height;"
	"} gs_in[];"

	"out float fsHeight;"

	"void main()"
	"{"

		"vec2 LineDirection =  gl_in[1].gl_Position.xy -  gl_in[0].gl_Position.xy;"

		//Orthogonal vector to the line direction
		"vec4 Ortho = normalize(vec4(LineDirection.y,-LineDirection.x,0.0,0.0));"
		//"vec4 Ortho = vec4(0.4,0.3,0.0,0.0);"

		"float size = 0.1f;"

		"gl_Position =  gl_in[1].gl_Position +Ortho * size ;"
		"fsHeight = gs_in[1].Height;"
		"EmitVertex();"

		"gl_Position =  gl_in[0].gl_Position +Ortho* size ;"
		"fsHeight = gs_in[0].Height;"
		"EmitVertex();"
		
		"gl_Position =  gl_in[1].gl_Position - Ortho * size;"
		"fsHeight = gs_in[1].Height;"
		"EmitVertex();"
	
		"gl_Position =  gl_in[0].gl_Position -Ortho* size;"
		"fsHeight = gs_in[0].Height;"
		"EmitVertex();"

		"EndPrimitive();"
	"}"
};

static const char *FragmentShader_CTerrainCurve =
{
	"#version 420 core\n"
	"layout (location = 1) out vec4 color;"
	"layout (location = 2) out int MaterialID;"
	"layout (location = 3) out int Object_ID;"
	"uniform int ID;"
	"uniform vec3 Color;"
	"in float fsHeight;"
	"uniform float maxHeight;"
	"void main()"
	"{"
	"Object_ID = ID;"
	"MaterialID = 145;"
	"float HeightRatio = fsHeight / maxHeight;"

	/*
	*	Red is max when altitude = 0 and min when altitude si max
	*/
	"float red = clamp(1 - 2*HeightRatio,0,1);"

	"float green = 0.0f;"
	" if(HeightRatio <= 0.5f) {"
	"green = 2 * HeightRatio; "
	"} else"
	"{"
	"green = 1- 2*(HeightRatio-0.5);"
	"}"
	"float blue = clamp(-1 + 2 * HeightRatio,0,1); "
	"color = vec4(red,green,blue,1.0f);"
	"};"
};