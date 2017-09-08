#pragma once


namespace rg {

	enum class RG_TEXTURE_FORMAT {
		DEFAULT,
		R8G8B8A8_UNORM,
	};

	enum class RG_TEXTURE_USAGE {
		DEFAULT,
		DYNAMIC,
		STAGE,
	};

	struct RgTextureSettings {
		unsigned int Width;
		unsigned int Height;
		RG_TEXTURE_FORMAT Format = RG_TEXTURE_FORMAT::DEFAULT;
		RG_TEXTURE_USAGE Usage = RG_TEXTURE_USAGE::DEFAULT;
	};


	class RgTexture {

	public:
		RgTexture() {};
		RgTexture(RgTextureSettings settings):m_sSettings(settings){}

		void SetRawData(void* data, unsigned int length);

	private:
		RgTexture(const RgTexture&) = delete;
		RgTexture& operator=(const RgTexture&) = delete;

	protected:
		RgTextureSettings m_sSettings;
	};
}