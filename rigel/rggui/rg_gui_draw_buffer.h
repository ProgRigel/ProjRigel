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

		static const unsigned int INDICES_QUAD_INIT_COUNT = 128;
		static const unsigned int INDICES_EXTEN_TIMES = 2;
	private:
		RgGUIIndicesBuffer(const RgGUIIndicesBuffer&) = delete;
		RgGUIIndicesBuffer& operator=(const RgGUIIndicesBuffer&) = delete;

		unsigned int * m_pIndicesBufferData = nullptr;
		unsigned int m_indiceQuadSize = INDICES_QUAD_INIT_COUNT;

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
		bool IsDirty();
		void SetDirty(bool d);

		static const unsigned int VERTEX_SIZE_INIT = 512;
		static const unsigned int VERTEX_EXTEN_TIMES = 2;
		static const unsigned int VERTEX_EXTEN_TOLERANCE = 32;

	private:
		RgGUIVertexBuffer(const RgGUIVertexBuffer&) = delete;
		RgGUIVertexBuffer& operator=(const RgGUIVertexBuffer&) = delete;

		unsigned int m_vertexBufferSize = VERTEX_SIZE_INIT;

		RgGUIVertex * m_pVertexData = nullptr;
		bool m_bIsDirty = false;
	};

}