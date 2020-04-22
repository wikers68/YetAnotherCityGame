#include "stdafx.h"
#include "FinalRenderPass.h"

CFinalRenderPass::CFinalRenderPass()
{
	HasBeenInit = false;
}


CFinalRenderPass::~CFinalRenderPass()
{
}

void CFinalRenderPass::Draw(PBR_Texture renderPass, float delta_t)
{
	if (HasBeenInit)
	{
		//glDisable(GL_DEPTH_TEST);

		/*
		*	Set default framebuffer to draw last render pass on screen
		*/
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		
		/*
		*	Clear buffer linked to screen
		*/
		glClearColor(0.0f, 0.2f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(_vertexArray);
		glUseProgram(_shader->getShaderProgram());

		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(_shader->getShaderProgram(), "_TextureColor"), 0);
		glBindTexture(GL_TEXTURE_2D, renderPass._ObjectColor);	

		glActiveTexture(GL_TEXTURE1);
		glUniform1i(glGetUniformLocation(_shader->getShaderProgram(), "_GuiColor"), 1);
		glBindTexture(GL_TEXTURE_2D, renderPass._GuiColor);

		glActiveTexture(GL_TEXTURE2);
		glUniform1i(glGetUniformLocation(_shader->getShaderProgram(), "_TextureMaterialID"), 2);
		glBindTexture(GL_TEXTURE_2D, renderPass._textureMaterialID);
		
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void CFinalRenderPass::Init(void)
{
		glGenVertexArrays(1, &_vertexArray);
		glBindVertexArray(_vertexArray);

		float Vertex[12] =
		{
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,
			0.0f, 0.0f
		};

		glGenBuffers(1, &_bufferVertex);	//allocate on free buffer name
		glBindBuffer(GL_ARRAY_BUFFER, _bufferVertex);	//Create the buffer
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex), &Vertex, GL_STATIC_DRAW);
																							
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);


		const char *VertexShaderString =
		{
			"#version 410 core\n"
			"layout( location = 0) in vec2 vertexPosition;"
			"out vec2 UV;"
			"void main()"
			"{"
			//upper left corner position in screen space
			"float Xposition = -1 + 2*vertexPosition.x ;"
			"float Yposition =  1 - 2*vertexPosition.y;"

			"UV = vec2(vertexPosition.x ,1-vertexPosition.y);"
			"gl_Position = vec4( Xposition,Yposition,0.5f,1);"
			"};"
		};

		const char *FragmentShaderString =
		{
			"#version 420 core\n"
			"in vec2 UV;"
			//"layout(binding=0) uniform isampler2D _TextureMaterialID;"
			"uniform sampler2D _TextureColor;"
			"uniform sampler2D _GuiColor;"
			"uniform isampler2D _TextureMaterialID;"
			"layout( location = 0) out vec4 color;"
			"void main()"
			"{"
			"vec4 result;"
			"int ID = texture(_TextureMaterialID,UV).x;"
			
			/*
			*	Render the gui on top, we draw it always on front screen
			*/
			"float alpha_GUI =texture(_GuiColor,UV).w; "

			"if(alpha_GUI == 1.0f)"
			"{"
				"color = vec4(texture(_GuiColor,UV).xyz,1.0f); "
			"}else{"

			"color = texture(_TextureColor,UV);}"

			"};"
		};

		_shader = new CShader();
		_shader->Compile(VertexShaderString, FragmentShaderString);

		//glGenSamplers(1, &_TextureSampler);

		HasBeenInit = true;

		glBindVertexArray(0);
}
