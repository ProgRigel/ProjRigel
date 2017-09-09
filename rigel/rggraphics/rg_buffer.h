#pragma once
#include "rg_graphicsAPI.h"

namespace rg {

	class RgGraphicsContext;

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
		RgBufferBind BindFlag = RgBufferBind::ConstBuffer;
		unsigned Flag = 0;
		unsigned DX_AccessFlag = 0;

	};

	class RgBuffer {

	public:
		RgBuffer();
		~RgBuffer();
		RgBuffer(RgBufferSettings setting);

	protected:
		RgBuffer(const RgBuffer&) = delete;
		RgBuffer& operator=(const RgBuffer&) = delete;
	public:
		friend class RgGraphicsContext;
	};
}