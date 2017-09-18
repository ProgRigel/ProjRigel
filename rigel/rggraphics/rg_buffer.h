#pragma once

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

	enum class RgGraphicsBufferMap {
		Read = 1,
		Write = 2,
		ReadWrite = 3,
		WriteDiscard = 4,
		WriteNoOverride = 5
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
		virtual void SetData(RgRenderContext *renderctx, void *pdata, unsigned int size, RgGraphicsBufferMap maptype = RgGraphicsBufferMap::WriteDiscard) = 0;

		RgBufferSettings& GetSettings();

	protected:
		RgBuffer(const RgBuffer&) = delete;
		RgBuffer& operator=(const RgBuffer&) = delete;
		RgBufferSettings m_setting;
	public:
		friend class RgGraphicsContext;
	};
}