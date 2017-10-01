#pragma once
#include <rgcore\rg_math.h>

namespace rg {

	struct RgGUIVertex
	{
		RgVec4 pos;
		RgVec4 color;
		RgVec2 uv;

	};

	class RgGUIIndicesBuffer {
	public:
		RgGUIIndicesBuffer();
		~RgGUIIndicesBuffer();

		unsigned int ExtenBuffer();
		unsigned int * GetPtr();
		unsigned int GetQuadSize();
		size_t GetBufferSize();
		size_t GetBufferSize(unsigned int quadcount);
		size_t GetBufferBytes();
		size_t GetBufferBytes(unsigned int quadcount);
	private:
		RgGUIIndicesBuffer(const RgGUIIndicesBuffer&) = delete;
		RgGUIIndicesBuffer& operator=(const RgGUIIndicesBuffer&) = delete;

		unsigned int * m_pIndicesBufferData = nullptr;
		unsigned int m_indiceQuadSize = INDICES_QUAD_INIT_COUNT;

		static const unsigned int INDICES_QUAD_INIT_COUNT = 128;
		static const unsigned int INDICES_EXTEN_TIMES = 2;


	};

	class RgGUIVertexBuffer {
	public:
		RgGUIVertexBuffer();
		~RgGUIVertexBuffer();


		unsigned int GetVertexSize();
		unsigned int GetVertexBufferSize();
		size_t GetVertexDataBytes();
		size_t GetVertxBufferBytes();

		RgGUIVertex * GetPtr();
		RgGUIVertex * ptrFloater = nullptr;

		bool ExtendVertexBufferCheck();

	private:
		RgGUIVertexBuffer(const RgGUIVertexBuffer&) = delete;
		RgGUIVertexBuffer& operator=(const RgGUIVertexBuffer&) = delete;

		
		
		static const unsigned int VERTEX_SIZE_INIT = 64;
		static const unsigned int VERTEX_EXTEN_TIMES = 2;
		static const unsigned int VERTEX_EXTEN_TOLERANCE = 32;
		
		unsigned int m_vertexBufferSize = VERTEX_SIZE_INIT;

		RgGUIVertex * m_pVertexData = nullptr;
	};

	class RgGUIDrawBuffer {

	public:
		RgGUIDrawBuffer();
		~RgGUIDrawBuffer();

		void ResetBuffer();
		void ApplyBuffer(); //caculate indices size and prepare for draw
		unsigned int GetBufferSize();
		unsigned int GetVertexCount();
		void * GetDataPtr();

		unsigned int * GetIndicesPtr();
		unsigned int GetIndicesSize();

		bool IsIndicesChanged();

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

		unsigned int m_pLastIndicesQuadSize = 0;


		friend class RgGUIContext;
	};
}