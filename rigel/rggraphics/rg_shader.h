#pragma once
#include "rggraphics.h"


namespace rg {

	enum RG_SHADER_TYPE
	{
		RG_SHADER_TYPE_DEFAULT,
		RG_SHADER_TYPE_HLSL,
		RG_SHADER_TYPE_GLSL,
		RG_SAHDER_TYPE_EFFECT,
	};

	enum class RG_SHADER_ENTRY {
		Default,
		Vertex,
		Pixel,
	};

	struct RgShaderOptions {
		RG_SHADER_TYPE ShaderType = RG_SHADER_TYPE_DEFAULT;
		RG_SHADER_ENTRY ShaderEntry = RG_SHADER_ENTRY::Default;
		std::string EntryPoint;
		std::string ShaderTarget;
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

		RG_SHADER_ENTRY GetShaderEntry();
	};
}