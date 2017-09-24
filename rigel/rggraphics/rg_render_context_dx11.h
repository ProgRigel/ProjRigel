#pragma once
#include "rg_render_context.h"
#include <d3d11.h>

namespace rg {
	class RgGraphicsContextDX11;
	class RgCommandList;
	class RgRenderTarget;
	class RgTexture;

	class RgRenderContextDX11 : public RgRenderContext {

	public:
		~RgRenderContextDX11();
		void Release();
	public:
		void InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage = (RgGraphicsPipelineStage)0);
		void InputSetShader(std::shared_ptr<RgShader> shader);
		void InputSetPrimitiveTopology();
		void InputSetInputLayout(RgInputLayout * layout);


		void SetRenderTarget(RgRenderTarget * rtarget);
		void ClearRenderTarget(RgVec4 color,RgRenderTarget * rtarget);
		void ClearDepthStencil(RgRenderTarget * rtarget);

		void SetViewPort(const RgViewPort*);

		void SetRasterizerState(RgRasterizerState*);
		void SetDepthStencilState(RgDepthStencilState *);
		
		void SetShaderTexture(std::shared_ptr<RgTexture> texture, RgGraphicsPipelineStage stage);

		void DrawIndexed(unsigned int size);
		void Draw();

		void ClearState();
		bool FinishCommandList(bool restorectx, RgCommandList ** pcommandlist);
		void ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx);

	protected:
		RgRenderContextDX11(bool immedctx);

		bool m_bIsImmediateContext = true;
		ID3D11DeviceContext *m_pDeviceContext = nullptr;
	public:
		friend class RgGraphicsContextDX11;
		friend class RgBufferDX11;
	};
}