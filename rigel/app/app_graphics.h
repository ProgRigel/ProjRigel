#pragma once
#include <rgcore\rgcore.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rgcore\rg_window.h>
#include <rggraphics\rg_buffer.h>
#include <rggraphics\rg_shader.h>

using namespace rg;

class RigelAppGraphics {

public:
	RigelAppGraphics();
	~RigelAppGraphics();

	void Release();
	void Init(rg::RgWindow *window);
	void Render();

public:
	rg::RgGraphicsContext * m_pRgGraphicsCtx = nullptr;

private:
	std::shared_ptr<RgShader> m_pShaderUIvertex;
	std::shared_ptr<RgShader> m_pShaderUIfragment;

	std::shared_ptr<RgBuffer> m_pBufferUIvertex;
	std::shared_ptr<RgBuffer> m_pBufferUIindices;
	std::shared_ptr<RgBuffer> m_pBufferUIconst;


};