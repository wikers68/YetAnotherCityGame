#pragma once

static const char *VertexShader_CTerrainCells_Heightmap =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	/*
	*	vec2(longitude,latitude)
	*/
	"uniform vec2 TerrainCell_Position;"
	"uniform vec2 TerrainCell_Size;"

	"out float altitude;"

	"void main()"
	"{"
	"float longitude = ( vertexPosition.x - TerrainCell_Position.x) / 0.5* TerrainCell_Size.x  ;  "
	"float latitude =  (vertexPosition.y - TerrainCell_Position.y) / 0.5*TerrainCell_Size.y ;  "

	"altitude = vertexPosition.z ;"
	"gl_Position =   vec4(longitude, latitude,altitude ,1.0) ;"
	"};"
};

static const char *FragmentShader_CTerrainCells_Heightmap =
{
	"#version 420 core\n"
	"layout (location = 0) out float height;"
	"in float altitude;"
	"void main()"
	"{"
			"height = altitude;"
	"};"
};

static const char *VertexShader_CTerrainCells_Heightmap_3D =
{
	"#version 410 core\n"
	"layout( location = 0) in vec3 vertexPosition;"
	"uniform mat4 Model;"
	"uniform mat4 View;"
	"uniform mat4 Projection;"
	"out float altitude;"
	"void main()"
	"{"
	"altitude = vertexPosition.z;"
	"gl_Position =  Projection* View * Model* vec4(vertexPosition,1.0) ;"
	"};"
};

static const char *FragmentShader_CTerrainCells_Heightmap_3D =
{
	"#version 420 core\n"
	"in float altitude;"
	"layout (location = 0) out vec4 color;"
	//"layout (location = 2) out int MaterialID;"
	"void main()"
	"{"
	//"MaterialID = 60;"
	"color = vec4(0.0,altitude / 2.0f,0.0,1.0);"
	"};"
};