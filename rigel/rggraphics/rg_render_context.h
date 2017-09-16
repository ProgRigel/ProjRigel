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

	class RgRenderContext {

	protected:
		RgRenderContext();
		virtual ~RgRenderContext();

		RgRenderContext(const RgRenderContext&) = delete;
		RgRenderContext& operator=(const RgRenderContext&) = delete;


	public:
		virtual void InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage = (RgGraphicsPipelineStage)0);
		virtual void InputSetMaterial(std::shared_ptr<RgMaterial> material);
		virtual void InputSetShader(std::shared_ptr<RgShader> shader);
		virtual void InputSetPrimitiveTopology();
		virtual void InputSetInputLayout(RgInputLayout * layout);

		virtual void DrawIndexed(unsigned int size);
		virtual void Draw();

		virtual void SetRenderTarget();
		virtual void SetRenderTargetDefault();
		virtual void SetDepthStencilStateDefault();
		virtual void SetViewPort(const RgViewPort*);
		virtual void SetRasterizerState(RgRasterizerState*);
		virtual void ClearRenderTarget(RgVec4 color);
		virtual void ClearDepthStencil();


		virtual void ClearState();
		virtual bool FinishCommandList(bool restorectx, RgCommandList ** pcommandlist);
		virtual void ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx);
	public:
		friend class RgGraphicsContext;
	};
}