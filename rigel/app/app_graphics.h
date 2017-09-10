#pragma once
#include <rgcore\rgcore.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rgcore\rg_window.h>
#include <rggraphics\rg_buffer.h>
#include <rggraphics\rg_shader.h>
#include <rggraphics\rg_inputlayout.h>

using namespace rg;

class RigelAppGraphics {

public:
	RigelAppGraphics();
	~RigelAppGraphics();

	void Release();
	void Init(rg::RgWindow *window);
	void Render();

private:

public:
	rg::RgGraphicsContext * m_pRgGraphicsCtx = nullptr;

private:
	std::shared_ptr<RgShader> m_pShaderUIvertex;
	std::shared_ptr<RgShader> m_pShaderUIfragment;

	RgBuffer* m_pBufferUIvertex = nullptr;
	RgBuffer* m_pBufferUIindices = nullptr;
	RgBuffer* m_pBufferUIconst = nullptr;

	RgInputLayout * m_pInputlayout = nullptr;

};