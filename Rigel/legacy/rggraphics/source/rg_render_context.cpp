#include "rggraphics.h"
#include "rg_render_context.h"


namespace rg {

	RgRenderContext::RgRenderContext()
	{
	}

	RgRenderContext::~RgRenderContext()
	{
		Release();
	}

	void RgRenderContext::Release()
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

	void RgRenderContext::DrawIndexed(unsigned int count, unsigned int startpos, int vertexstart)
	{
	}

	void RgRenderContext::Draw()
	{
	}


	void RgRenderContext::SetViewPort(const RgViewPort *)
	{
	}

	void RgRenderContext::SetRasterizerState(RgRasterizerState *)
	{
	}

	void RgRenderContext::SetDepthStencilState(RgDepthStencilState *)
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
