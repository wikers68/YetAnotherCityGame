#pragma once

#include "GL/glew.h"
#include <gl/GL.h>

#include "../Shaders/Shader.h"

struct PBR_Texture
{
	GLuint _textureMaterialID = 0;
	GLuint _ObjectColor = 0;
	GLuint _GuiColor = 0 ;
	GLuint _ID_Object = 0;
};

class CFinalRenderPass
{
public:
	CFinalRenderPass();
	~CFinalRenderPass();

	void Draw(PBR_Texture renderPass, float delta_t = 0.0f);

	void Init(void);

private:	
	GLuint _vertexArray;
	GLuint _bufferVertex;
	GLuint _TextureSampler;

	bool HasBeenInit;

	CShader *_shader;

};

