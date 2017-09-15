#pragma once
#include <rgcore\rg_math.h>

namespace rg {

	struct RgGUIVertex
	{
		RgVec3 pos;
		RgVec3 color;
		RgVec2 uv;

	};

	class RgGUIDrawBuffer {

	public:
		RgGUIDrawBuffer();
		~RgGUIDrawBuffer();

		void ResetBuffer();
		unsigned int GetBufferSize();
		unsigned int GetVertexCount();
		void * GetDataPtr();

	private:
		RgGUIDrawBuffer(const RgGUIDrawBuffer&) = delete;
		RgGUIDrawBuffer& operator=(const RgGUIDrawBuffer&) = delete;


		void ExtendBufferCheck();
	public:
		static const unsigned int BUFFER_SIZE_INIT = 1024;
		static const unsigned int BUFFER_SIZE_SCALE = 4;
		static const unsigned int BUFFER_SIZE_THRES = 32;
		static const unsigned int VERTEX_SIZE = sizeof(RgGUIVertex);

	private:

		RgGUIVertex * m_pData = nullptr;
		RgGUIVertex * m_pPos = nullptr;
		unsigned int m_sBufferSize = BUFFER_SIZE_INIT;

		friend class RgGUIContext;
	};
}