#pragma once
#include "rg_render_context.h"
#include <d3d11.h>

namespace rg {
	class RgGraphicsContextDX11;
	class RgCommandList;

	class RgRenderContextDX11 : public RgRenderContext {

	public:
		void InputSetBuffer(RgBuffer* buffer, RgGraphicsPipelineStage tarstage = (RgGraphicsPipelineStage)0);
		void InputSetShader(std::shared_ptr<RgShader> shader);
		void InputSetPrimitiveTopology();
		void InputSetInputLayout(RgInputLayout * layout);

		void DrawIndexed(unsigned int size);
		void Draw();

		void ClearState();
		bool FinishCommandList(bool restorectx, RgCommandList ** pcommandlist);
		void ExecuteCommandList(RgCommandList * pcommandlist, bool restorectx);

	protected:
		RgRenderContextDX11(bool immedctx);
		~RgRenderContextDX11();

		bool m_bIsImmediateContext = true;
		ID3D11DeviceContext *m_pDeviceContext = nullptr;
	public:
		friend class RgGraphicsContextDX11;
		friend class RgBufferDX11;
	};
}