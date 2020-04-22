// YetAnotherCityGame.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "SDL.h"
#pragma comment(lib,"SDL2.lib")
#pragma comment(lib,"SDL2main.lib")

#include "GL/glew.h"
#pragma comment(lib,"glew32.lib")

#include <gl/GL.h>
#pragma comment(lib,"opengl32.lib")

//use only once before including stb_image.h in other file
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#pragma comment(lib,"freetype.lib")

#include "./Context/ContextManager.h"
#include "./Context/MainMenu.h"
#include "Option.h"
#include "./GUI/Font/FontManager.h"
#include "./Shaders/ShaderManager.h"
#include "./Render/FinalRenderPass.h"

SDL_Window * _MainWindow = nullptr;
SDL_GLContext _glContext;
SDL_Event _SdlEvent;

CMainMenu *_MainMenuContext = nullptr;

unsigned int startFrameTime = 0;
unsigned int endFrameTime = 0;
float delta_t = 0.0;

int main(int argc, char* args[])
{
	/*
	*	Initialize AFX module that will be used later, as CFileDialiog...
	*/
	if (!AfxWinInit(GetModuleHandle(nullptr),nullptr,GetCommandLine(),0))
	{
		std::cout << "can't initialize AFX" << std::endl;
		return 0;
	}

	//read option from hard drive 
	if (!COption::getInstance().Read_Option())
	{
		//if something goes wrong during option loading, display error message
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();

		return -1;
	}

	_MainWindow = SDL_CreateWindow("YetAnotherCityGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	//opengl set-up

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	_glContext = SDL_GL_CreateContext(_MainWindow);

	if (_glContext == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(_MainWindow);
		SDL_Quit();
		return -2;
	}

	/*
	* Load OpenGL 4.2 extension for Windows
	*/
	GLenum initialisationGlew = glewInit();
	if (initialisationGlew != GLEW_OK)
	{
		std::cout << glewGetErrorString(initialisationGlew) << std::endl;
		return -3;
	}

	/*
	*	FontManager initialisation
	*/
	if (!CFontManager::getInstance().Init_FontManager())
	{
		return -4;
	}

	/*
	*	Load and compile shaders
	*/
	if (!CShaderManager::getInstance().InitializeShader())
	{
		return -5;
	}

	//create the main menu
	_MainMenuContext = new CMainMenu();
	_MainMenuContext->CreateContext();
	_MainMenuContext->ActivateContext();

	//glViewport(-1.0, -1.0, COption::getInstance().Get_Horizontal_Resolution(), COption::getInstance().Get_Vertical_Resolution());

	//http://www.songho.ca/opengl/gl_fbo.html
	
	/*
	*	Error tracking
	*/
	GLenum status = glGetError();

	
	/*
	*	We create the framebuffer to hold all texture that will be used in PB rendering
	*/
	GLuint PBR_FrameBuffer, ColorBufferTexture,GUI_Color, MaterialID;
	glGenFramebuffers(1, &PBR_FrameBuffer);

	/*
	*	Color texture
	*/
	glGenTextures(1, &ColorBufferTexture);
	glBindTexture(GL_TEXTURE_2D, ColorBufferTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0, GL_RGBA,  GL_UNSIGNED_BYTE, (void*)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1, &GUI_Color);
	glBindTexture(GL_TEXTURE_2D, GUI_Color);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glBindTexture(GL_TEXTURE_2D, 0);

	/*
	*	One texture with material ID.
	*	Will be used on final rendering pass to select the shading model
	*	Id = nombre entier entre 0 et 255
	*/
	glGenTextures(1, &MaterialID);
	glBindTexture(GL_TEXTURE_2D, MaterialID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0, GL_RED_INTEGER, GL_INT, (void*)0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	status = glGetError();

	
	/*GLuint DepthBufferTExture;
	glGenTextures(1, &DepthBufferTExture);
	glBindTexture(GL_TEXTURE_2D, DepthBufferTExture);
	glTexImage2D(GL_TEXTURE_2D, 1, GL_R32F,
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution(),
		0, GL_R32F, GL_UNSIGNED_BYTE, nullptr);*/
	
	status = glGetError();

	GLuint PBR_RenderDepth;
	glGenRenderbuffers(1, &PBR_RenderDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, PBR_RenderDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 
		COption::getInstance().Get_Horizontal_Resolution(),
		COption::getInstance().Get_Vertical_Resolution());
	
	status = glGetError();
	
	/*
	*	Bind texture and render to th PBR framebuffer
	*/
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, PBR_FrameBuffer);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, ColorBufferTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, GUI_Color, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, MaterialID, 0);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, PBR_RenderDepth);
	//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthBufferTExture, 0);
	glEnable(GL_DEPTH_TEST);

	GLenum b[] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1,GL_COLOR_ATTACHMENT2 };
	glDrawBuffers(3, b);

	status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "not ok..." << std::endl;
	}

	status = glGetError();

	PBR_Texture pbr;
	pbr._ObjectColor = ColorBufferTexture;
	pbr._GuiColor = GUI_Color;
	pbr._textureMaterialID = MaterialID;

	/*
	*	Set Up the final render pass
	*/
	CFinalRenderPass *FinalRenderPass = new CFinalRenderPass();
	FinalRenderPass->Init();

	while (CContextManager::Instance().getRunApplication())
	{
		startFrameTime = SDL_GetTicks();

		/*
		*	Set buffer used to draw PBR data
		*/
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, PBR_FrameBuffer);

		/*
		*	Clear the current DEPTH buffer
		*/
		glClear(GL_DEPTH_BUFFER_BIT);

		/*
		*	Clear the ColorBufferTexture which is at index 0 of glDrawBuffers
		*/
		GLfloat clearColor[] = { 0.0f, 0.0f, 0.4f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, clearColor);

		GLfloat clearColorAlfa[] = { 0.0f, 0.0f, 0.4f, 0.0f };
		glClearBufferfv(GL_COLOR, 1, clearColorAlfa);

		/*
		*	Clear the MaterialID which is at index 1 of glDrawBuffers
		*/
		GLint clear[] = { 0,0,0,0 };
		glClearBufferiv(GL_COLOR, 2, clear);

		if (CContextManager::Instance().GetCurrentActiveContext())
		{
			CContextManager::Instance().GetCurrentActiveContext()->ManageEvent(delta_t);
			CContextManager::Instance().GetCurrentActiveContext()->RunContext(delta_t);
		}

		glBindFramebuffer(GL_READ_FRAMEBUFFER, PBR_FrameBuffer);
		
		FinalRenderPass->Draw(pbr);

		SDL_GL_SwapWindow(_MainWindow);

		endFrameTime = SDL_GetTicks();
		delta_t = (float)(endFrameTime - startFrameTime) / 1000.0;
	}

	SDL_GL_DeleteContext(_glContext);
	SDL_DestroyWindow(_MainWindow);
	SDL_Quit();

    return 0;
}