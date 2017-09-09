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
	data[2] = 0.5f;
	data[3] = 0.0f;
	data[4] = 0.0f;
	data[5] = 0.3f;
	m_pBufferUIvertex->SetData(m_pRgGraphicsCtx->GetRenderContext(), &data, sizeof(data));

	RgBufferSettings bufferIndicesDesc;
	bufferIndicesDesc.ByteWidth = 6 * sizeof(unsigned int);
	bufferIndicesDesc.BindFlag = RgBufferBind::IndexBuffer;
	bufferIndicesDesc.Usage = RgBufferUsage::Dynamic;
	bufferIndicesDesc.Stride = sizeof(unsigned int);
	m_pBufferUIindices = m_pRgGraphicsCtx->CreateBuffer(bufferIndicesDesc);

	unsigned int datai[3]{ 0,1,2};
	m_pBufferUIindices->SetData(m_pRgGraphicsCtx->GetRenderContext(), &datai, sizeof(datai));

	

	//create shader

	RgShaderOptions options;
	options.ShaderEntry = RG_SHADER_ENTRY::Vertex;
	options.EntryPoint = "main";
	options.ShaderTarget = "vs_4_0";
	std::wstring fpath = GetWorkDirectory();
	fpath = fpath.append(L"/vs.hlsl");
	RgLogD() << fpath;
	m_pShaderUIvertex = m_pRgGraphicsCtx->CompileShaderFromFile(fpath, options);

	RgShaderOptions options1;
	options1.ShaderEntry = RG_SHADER_ENTRY::Pixel;
	options1.EntryPoint = "main";
	options1.ShaderTarget = "ps_4_0";
	std::wstring fpath1 = GetWorkDirectory();
	fpath1 = fpath1.append(L"/ps.hlsl");
	RgLogD() << fpath1;
	m_pShaderUIfragment = m_pRgGraphicsCtx->CompileShaderFromFile(fpath1, options1);

	RgInputLayoutElement layoute;
	layoute.SemanticName = "position";
	layoute.SemanticIndex = 0;
	layoute.Format = RgGraphicsFormat::R32G32_FLOAT;
	layoute.InputSlotClass = RgInputSlotClass::PER_VERTEX_DATA;
	layoute.InputSlot = 0;

	m_pInputlayout = m_pRgGraphicsCtx->CreateInputLayout(&layoute, 1, m_pShaderUIvertex);

	auto renderctx = m_pRgGraphicsCtx->GetRenderContext();
	renderctx->InputSetBuffer(m_pBufferUIvertex);
	renderctx->InputSetBuffer(m_pBufferUIindices);

	renderctx->InputSetInputLayout(m_pInputlayout);
	renderctx->InputSetShader(m_pShaderUIvertex);
	renderctx->InputSetShader(m_pShaderUIfragment);

	renderctx->InputSetPrimitiveTopology();
}

void RigelAppGraphics::Render()
{
	m_pRgGraphicsCtx->prerender();


	m_pRgGraphicsCtx->GetRenderContext()->Draw();


	m_pRgGraphicsCtx->render();
}
