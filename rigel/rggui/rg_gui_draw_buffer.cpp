#include "rggui.h"
#include "rg_gui_draw_buffer.h"

namespace rg {

#pragma region RgGUIIndicesBuffer
	RgGUIIndicesBuffer::RgGUIIndicesBuffer()
	{
		m_pIndicesBufferData = new unsigned int[m_indiceQuadSize * 6];

		unsigned int tm = 0;
		unsigned int tn = 0;
		for (size_t i = 0; i < m_indiceQuadSize; i++)
		{
			m_pIndicesBufferData[tm] = tn;
			m_pIndicesBufferData[tm + 1] = tn + 1;
			m_pIndicesBufferData[tm + 2] = tn + 2;
			m_pIndicesBufferData[tm + 3] = tn;
			m_pIndicesBufferData[tm + 4] = tn + 2;
			m_pIndicesBufferData[tm + 5] = tn + 3;

			tm += 6;
			tn += 4;
		}
	}

	RgGUIIndicesBuffer::~RgGUIIndicesBuffer()
	{
		delete[] m_pIndicesBufferData;
	}
	unsigned int RgGUIIndicesBuffer::ExtenBuffer()
	{
		unsigned int * newbuf = new unsigned int[m_indiceQuadSize *INDICES_EXTEN_TIMES * 6];
		memcpy(newbuf, m_pIndicesBufferData, sizeof(unsigned int) * m_indiceQuadSize * 6);
		delete[] m_pIndicesBufferData;
		m_pIndicesBufferData = newbuf;

		auto diff = m_indiceQuadSize *(INDICES_EXTEN_TIMES -1);

		unsigned int tm = m_indiceQuadSize * 6;
		unsigned int tn = m_indiceQuadSize * 4;
		for (size_t i = 0; i < diff; i++)
		{
			m_pIndicesBufferData[tm] = tn;
			m_pIndicesBufferData[tm + 1] = tn + 1;
			m_pIndicesBufferData[tm + 2] = tn + 2;
			m_pIndicesBufferData[tm + 3] = tn;
			m_pIndicesBufferData[tm + 4] = tn + 2;
			m_pIndicesBufferData[tm + 5] = tn + 3;
			tm += 6;
			tn += 4;
		}

		m_indiceQuadSize = m_indiceQuadSize * INDICES_EXTEN_TIMES;

		return m_indiceQuadSize;
	}
	unsigned int * RgGUIIndicesBuffer::GetPtr()
	{
		return m_pIndicesBufferData;
	}
	unsigned int RgGUIIndicesBuffer::GetQuadSize()
	{
		return m_indiceQuadSize;
	}
	size_t RgGUIIndicesBuffer::GetBufferSize()
	{
		return m_indiceQuadSize*6;
	}
	size_t RgGUIIndicesBuffer::GetBufferSize(unsigned int quadcount)
	{
		RG_CHECK_RET(quadcount <= m_indiceQuadSize, "rggui indices buffer overflow", return 0;);
		return quadcount * 6;
	}
	size_t RgGUIIndicesBuffer::GetBufferBytes()
	{
		return GetBufferSize() * sizeof(unsigned int);
	}
	size_t RgGUIIndicesBuffer::GetBufferBytes(unsigned int quadcount)
	{
		return GetBufferSize(quadcount) * sizeof(unsigned int);
	}
#pragma endregion


#pragma region RgGUIVertexBuffer
	RgGUIVertexBuffer::RgGUIVertexBuffer()
	{
		m_pVertexData = new RgGUIVertex[m_vertexBufferSize];
		ZeroMemory(m_pVertexData, GetVertxBufferBytes());

		ptrFloater = m_pVertexData;
	}
	RgGUIVertexBuffer::~RgGUIVertexBuffer()
	{
		delete[] m_pVertexData;
	}
	unsigned int RgGUIVertexBuffer::GetVertexSize()
	{
		return (unsigned int)(ptrFloater - m_pVertexData);
	}
	unsigned int RgGUIVertexBuffer::GetVertexBufferSize()
	{
		return m_vertexBufferSize;
	}
	size_t RgGUIVertexBuffer::GetVertexDataBytes()
	{
		return (ptrFloater - m_pVertexData) * sizeof(RgGUIVertex);
	}
	size_t RgGUIVertexBuffer::GetVertxBufferBytes()
	{
		return m_vertexBufferSize * sizeof(RgGUIVertex);
	}
	RgGUIVertex * RgGUIVertexBuffer::GetPtr()
	{
		return m_pVertexData;
	}
	bool RgGUIVertexBuffer::ExtendVertexBufferCheck()
	{
		unsigned int vertexcount = (unsigned int)(ptrFloater - m_pVertexData);
		unsigned int newsize = m_vertexBufferSize * VERTEX_EXTEN_TIMES;

		if (((unsigned long long)vertexcount) < m_vertexBufferSize - VERTEX_EXTEN_TOLERANCE) return false;
		RgGUIVertex * newbuffer = new RgGUIVertex[newsize];
		ZeroMemory(newbuffer, m_vertexBufferSize * VERTEX_EXTEN_TIMES * sizeof(RgGUIVertex));
		memcpy(newbuffer, m_pVertexData, GetVertxBufferBytes());

		delete [] m_pVertexData;
		m_pVertexData = newbuffer;

		m_vertexBufferSize = newsize;
		ptrFloater = m_pVertexData + vertexcount;
		return true;
	}
	bool RgGUIVertexBuffer::IsDirty()
	{
		return m_bIsDirty;
	}
	void RgGUIVertexBuffer::SetDirty(bool d)
	{
		m_bIsDirty = d;
	}
#pragma endregion


	

}

