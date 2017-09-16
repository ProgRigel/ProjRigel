#include "rggraphics.h"
#include "rg_render_context.h"


namespace rg {

	RgRenderContext::RgRenderContext()
	{
	}

	RgRenderContext::~RgRenderContext()
	{
	}


	void RgRenderContext::InputSetBuffer(RgBuffer* buffer,RgGraphicsPipelineStage tarstage)
	{
	}

	void RgRenderContext::InputSetMaterial(std::shared_ptr<RgMaterial> material)
	{
	}

	void RgRenderContext::InputSetShader(std::shared_ptr<RgShader> shader)
	{
	}

	void RgRenderContext::InputSetPrimitiveTopology()
	{
	}

	void RgRenderContext::InputSetInputLayout(RgInputLayout * layout)
	{
	}

	void RgRenderContext::DrawIndexed(unsigned int size)
	{
	}

	void RgRenderContext::Draw()
	{
	}

	void RgRenderContext::SetRenderTarget()
	{
	}

	void RgRenderContext::SetRenderTargetDefault()
	{
	}

	void RgRenderContext::SetDepthStencilStateDefault()
	{
	}

	void RgRenderContext::SetViewPort(const RgViewPort *)
	{
	}

	void RgRenderContext::SetRasterizerState(RgRasterizerState *)
	{
	}

	void RgRenderContext::ClearRenderTarget(RgVec4 color)
	{
	}

	void RgRenderContext::ClearDepthStencil()
	{
	}

	void RgRenderContext::ClearState()
	{
	}

	bool RgRenderContext::FinishCommandList(bool restorectx, RgCommandList ** pcommandlist)
	{
		return false;
	}

	void RgRenderContext::ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx)
	{
	}

}
