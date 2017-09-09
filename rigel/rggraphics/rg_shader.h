#pragma once
#include <string>


namespace rg {

	enum RG_SHADER_TYPE
	{
		RG_SHADER_TYPE_DEFAULT,
		RG_SHADER_TYPE_HLSL,
		RG_SHADER_TYPE_GLSL,
		RG_SAHDER_TYPE_EFFECT,
	};

	enum class RG_SHADER_ENTRY {
		Vertex,
		Pixel,
	};

	struct RgShaderOptions {
		RG_SHADER_TYPE ShaderType = RG_SHADER_TYPE_DEFAULT;
		std::wstring EntryPoint;
		std::wstring ShaderTarget;
		void * ShaderInclude = nullptr;
		unsigned int ShaderIncludeCount = 0;
		unsigned int Flag1 = 0;
		unsigned int Flag2 = 0;
		void * Other = nullptr;
	};

	class RgShader {
	protected:
		RgShaderOptions m_sShaderOptions;

	public:
		RgShader();
		RgShader(RgShaderOptions& options);
		virtual ~RgShader();
	};
}