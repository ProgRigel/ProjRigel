#pragma once
#include "rg_graphicsAPI.h"

namespace rg {

	enum class RG_TEXTURE_FORMAT {
		DEFAULT,
		R8G8B8A8_UNORM,
	};

	enum class RgGraphicsUsage {
		DEFAULT,
		DYNAMIC,
		STAGE,
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
		RG_TEXTURE_FORMAT Format = RG_TEXTURE_FORMAT::DEFAULT;
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
		void SetRawData(void* data, unsigned int length);

	private:
		RgTexture(const RgTexture&) = delete;
		RgTexture& operator=(const RgTexture&) = delete;

	protected:
		const RgTextureSettings m_sSettings;
	};
}