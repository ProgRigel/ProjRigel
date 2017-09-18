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

		unsigned int * GetIndicesPtr();
		unsigned int GetIndicesSize();

	private:
		RgGUIDrawBuffer(const RgGUIDrawBuffer&) = delete;
		RgGUIDrawBuffer& operator=(const RgGUIDrawBuffer&) = delete;

		void ExtendIndicesBuffer(unsigned int lastQuad,unsigned int newQuad);

		void ExtendBufferCheck();
	public:
		static const unsigned int BUFFER_SIZE_INIT = 1024;
		static const unsigned int BUFFER_SIZE_SCALE = 4;
		static const unsigned int BUFFER_SIZE_THRES = 32;
		static const unsigned int VERTEX_SIZE = sizeof(RgGUIVertex);

		static const unsigned int INDICES_QUAD_INIT = 256;

	private:

		RgGUIVertex * m_pData = nullptr;
		RgGUIVertex * m_pPos = nullptr;
		unsigned int m_sBufferSize = BUFFER_SIZE_INIT;


		unsigned int * m_pIndicesBufferData = nullptr;
		unsigned int m_pIndicesBufferQuadSize = INDICES_QUAD_INIT;
		unsigned int m_pIndicesQuadCount = 0;


		friend class RgGUIContext;
	};
}