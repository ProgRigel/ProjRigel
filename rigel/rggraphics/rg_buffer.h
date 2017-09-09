#pragma once
#include "rg_graphicsAPI.h"

namespace rg {

	class RgGraphicsContext;
	class RgRenderContext;

	enum class RgBufferUsage
	{
		Default,
		Dynamic,
	};

	enum class RgBufferBind
	{
		IndexBuffer,
		VertexBuffer,
		ConstBuffer,
	};

	struct RgBufferSettings {
		RgBufferUsage Usage = RgBufferUsage::Default;
		unsigned int ByteWidth = 0;
		unsigned int Stride = 0;
		RgBufferBind BindFlag = RgBufferBind::ConstBuffer;
		unsigned Flag = 0;
		unsigned DX_AccessFlag = 0;
	};

	class RgBuffer {

	public:
		RgBuffer();
		virtual ~RgBuffer();
		RgBuffer(RgBufferSettings setting);

		virtual void Release() = 0;
		virtual void SetData(RgRenderContext *renderctx, void *pdata, unsigned int size) = 0;

		RgBufferSettings& GetSettings();

	protected:
		RgBuffer(const RgBuffer&) = delete;
		RgBuffer& operator=(const RgBuffer&) = delete;
		RgBufferSettings m_setting;
	public:
		friend class RgGraphicsContext;
	};
}