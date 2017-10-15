#pragma once


namespace rg {

	class RgGraphicsContext;

	enum class RgRasterizerCullMode {
		CULL_NONE = 1,
		CULL_FRONT = 2,
		CULL_BACK = 3,
	};

	enum class RgRasterizerFillMode
	{
		FILL_WIREFRAME = 2,
		FILL_SOLID = 3
	};

	struct RgRasterizerSettings {
		RgRasterizerFillMode FillMode = RgRasterizerFillMode::FILL_SOLID;
		RgRasterizerCullMode CullMode = RgRasterizerCullMode::CULL_NONE;
		int DepthBias = 0;
		float DepthBiasClamp = 0;
		float SlopeScaledDepthBias = 0;
		bool DepthClipEnable = true;
		bool ScissorEnable = false;
		bool MultisampleEnable = false;
		bool AntialiasedLine = false;
		bool FrontCounterClockwise = false;
	};

	class RgRasterizerState {

	public:
		virtual ~RgRasterizerState();
		virtual void Release();
		const RgRasterizerSettings& GetSettings()const;
	protected:
		RgRasterizerState(const RgRasterizerSettings settings):m_sSettings(settings){}

		
	private:
		RgRasterizerState(const RgRasterizerState&) = delete;
		RgRasterizerState& operator=(const RgRasterizerState&) = delete;

	protected:
		const RgRasterizerSettings m_sSettings;

		friend class RgGraphicsContext;
	};
}