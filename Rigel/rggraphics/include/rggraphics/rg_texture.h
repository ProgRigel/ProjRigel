#pragma once
#include "rg_graphicsAPI.h"

namespace rg {

	class RgRenderContext;

	enum class RgGraphicsUsage {
		DEFAULT,
		DYNAMIC,
		STAGE,
		IMMUTABLE,
	};

	struct RgSampleDesc {
		unsigned int Count = 1;
		unsigned int Quality = 0;
	};

	struct RgTextureSettings {
		unsigned int Width;
		unsigned int Height;
		unsigned int MipLevels = 1;
		unsigned int ArraySize = 1;
		RgGraphicsFormat Format = RgGraphicsFormat::UNKNOWN;
		RgSampleDesc SampleDesc;
		RgGraphicsUsage Usage = RgGraphicsUsage::DEFAULT;
		RgGraphicsBindFlag BindFlags;
		unsigned int DX_CPUAccessFlag = 0;
		unsigned int DX_MiscFlags = 0;
	};


	class RgTexture {

	public:
		RgTexture() {};
		RgTexture(const RgTextureSettings& settings):m_sSettings(settings){}

		virtual void Release();
		virtual void SetRawData(void* data, unsigned int length);
		virtual void SetData(RgRenderContext * renderctx, void * data, size_t size);

	private:
		RgTexture(const RgTexture&) = delete;
		RgTexture& operator=(const RgTexture&) = delete;

	protected:
		const RgTextureSettings m_sSettings;
	};
}