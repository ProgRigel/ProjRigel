#pragma once
#include "rggraphics_inc.h"


namespace rg {

	class RgGraphicsContext;
	class RgBuffer;
	class RgShader;
	class RgMaterial;
	class RgInputLayout;
	class RgCommandList;
	class RgRasterizerState;
	class RgDepthStencilState;
	class RgRenderTarget;
	class RgTexture;
	class RgGraphicsSampler;
	class RgBlendState;

	class RgRenderContext {

	public:
		virtual ~RgRenderContext();
		virtual void Release();
	protected:
		RgRenderContext();
		

		RgRenderContext(const RgRenderContext&) = delete;
		RgRenderContext& operator=(const RgRenderContext&) = delete;


	public:
		virtual void InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage = (RgGraphicsPipelineStage)0);
		virtual void InputSetMaterial(std::shared_ptr<RgMaterial> material);
		virtual void InputSetShader(std::shared_ptr<RgShader> shader);
		virtual void InputSetPrimitiveTopology();
		virtual void InputSetInputLayout(RgInputLayout * layout);

		virtual void DrawIndexed(unsigned int size);
		virtual void DrawIndexed(unsigned int count, unsigned int startpos, int vertexstart);
		virtual void Draw();

		virtual void SetRenderTarget(RgRenderTarget * rtarget) = 0;
		virtual void ClearRenderTarget(RgVec4 color, RgRenderTarget * rtarget) = 0;
		virtual void ClearDepthStencil(RgRenderTarget * rtarget) = 0;

		virtual void SetViewPort(const RgViewPort*) = 0;

		virtual void SetRasterizerState(RgRasterizerState*) = 0;
		virtual void SetDepthStencilState(RgDepthStencilState *) = 0;
		virtual void SetBlendState(RgBlendState *) = 0;

		virtual void SetShaderTexture(std::shared_ptr<RgTexture> texture, RgGraphicsPipelineStage stage) = 0;
		virtual void SetSampler(RgGraphicsSampler * sampler) = 0;


		virtual void ClearState();
		virtual bool FinishCommandList(bool restorectx, RgCommandList ** pcommandlist);
		virtual void ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx);
	public:
		friend class RgGraphicsContext;
	};
}