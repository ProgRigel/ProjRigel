#include "app_graphics.h"

using namespace rg;

RigelAppGraphics::RigelAppGraphics()
{
}

RigelAppGraphics::~RigelAppGraphics()
{
	Release();
}

void RigelAppGraphics::Release()
{
	RgGraphicsAPI::ReleaseAPI(m_pRgGraphicsCtx);
	m_pRgGraphicsCtx = nullptr;
}

void RigelAppGraphics::Init(RgWindow * window)
{
	RG_GRAPHICS_INIT_SETTINGS settings;
	settings.BufferHeight = window->getHeight();
	settings.BufferWidth = window->getWidth();
	settings.OutputWindow =(HWND) window->getHandler();
	settings.Windowed = true;

	m_pRgGraphicsCtx = RgGraphicsAPI::InitAPI(RG_GRAPHICS_API::RG_GRAPHICS_APY_DX11, &settings);

	//init draws
	RgBufferSettings bufferVertexDesc;
	bufferVertexDesc.ByteWidth = 3 * sizeof(float) * 2;
	bufferVertexDesc.BindFlag = RgBufferBind::VertexBuffer;
	bufferVertexDesc.Usage = RgBufferUsage::Dynamic;
	m_pBufferUIvertex = m_pRgGraphicsCtx->CreateBuffer(bufferVertexDesc);

	RgBufferSettings bufferIndicesDesc;
	bufferIndicesDesc.ByteWidth = 3 * sizeof(unsigned int);
	bufferIndicesDesc.BindFlag = RgBufferBind::IndexBuffer;
	bufferIndicesDesc.Usage = RgBufferUsage::Dynamic;
	m_pBufferUIindices = m_pRgGraphicsCtx->CreateBuffer(bufferIndicesDesc);
}

void RigelAppGraphics::Render()
{
	m_pRgGraphicsCtx->render();
}
