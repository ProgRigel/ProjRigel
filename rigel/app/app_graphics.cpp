#include "app_graphics.h"
#include <rggraphics\rg_render_context.h>
#include <rggraphics\rg_graphicsAPI.h>
#include <rggraphics\rg_graphicscontext.h>
#include <rggraphics\rg_inputlayout.h>
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
	bufferVertexDesc.Stride = sizeof(float);
	m_pBufferUIvertex = m_pRgGraphicsCtx->CreateBuffer(bufferVertexDesc);

	float data[6];
	data[0] = 0.0f;
	data[1] = 0.0f;
	data[2] = 10.0f;
	data[3] = 0.0f;
	data[4] = 30.0f;
	data[5] = 50.0f;
	m_pBufferUIvertex->SetData(m_pRgGraphicsCtx->GetRenderContext(), &data, sizeof(data));

	RgBufferSettings bufferIndicesDesc;
	bufferIndicesDesc.ByteWidth = 6 * sizeof(unsigned int);
	bufferIndicesDesc.BindFlag = RgBufferBind::IndexBuffer;
	bufferIndicesDesc.Usage = RgBufferUsage::Dynamic;
	bufferIndicesDesc.Stride = sizeof(unsigned int);
	m_pBufferUIindices = m_pRgGraphicsCtx->CreateBuffer(bufferIndicesDesc);

	unsigned int datai[6]{ 0,1,2,0,2,3 };
	m_pBufferUIindices->SetData(m_pRgGraphicsCtx->GetRenderContext(), &datai, sizeof(datai));

	auto renderctx = m_pRgGraphicsCtx->GetRenderContext();
	renderctx->InputSetBuffer(m_pBufferUIvertex);
	renderctx->InputSetBuffer(m_pBufferUIindices);


}

void RigelAppGraphics::Render()
{
	m_pRgGraphicsCtx->render();
}
