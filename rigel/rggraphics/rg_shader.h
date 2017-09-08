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

	class RgShaderOptions {
		RG_SHADER_TYPE ShaderType = RG_SHADER_TYPE_DEFAULT;
		std::wstring EntryPoint = nullptr;
		std::wstring ShaderTarget = nullptr;
		void * ShaderInclude = nullptr;
		unsigned int ShaderIncludeCount = 0;
		unsigned int Flag1 = 0;
		unsigned int Flag2 = 0;
		void * Other = nullptr;
	};

	class RgShader {
		RgShaderOptions m_sShaderOptions;
	};
}