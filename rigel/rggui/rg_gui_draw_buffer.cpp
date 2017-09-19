#include "rggui.h"
#include "rg_gui_draw_buffer.h"

namespace rg {
	RgGUIDrawBuffer::RgGUIDrawBuffer()
	{
		m_pData = new RgGUIVertex[BUFFER_SIZE_INIT];
		m_pPos = m_pData;

		ExtendIndicesBuffer(0, INDICES_QUAD_INIT);
	}

	RgGUIDrawBuffer::~RgGUIDrawBuffer()
	{
		delete[] m_pData;
		m_pData = nullptr;
		m_pPos = nullptr;

		if (m_pIndicesBufferData != nullptr) {
			delete[] m_pIndicesBufferData;
			m_pIndicesBufferData = nullptr;
			m_pIndicesBufferQuadSize = 0;
		}
	}


	void RgGUIDrawBuffer::ExtendIndicesBuffer(unsigned int lastQuad, unsigned int newQuad)
	{
		auto temp = m_pIndicesBufferData;
		m_pIndicesBufferData = new unsigned int[newQuad * 6];
		if (lastQuad != 0) {
			memcpy(m_pIndicesBufferData, temp, lastQuad * 6* sizeof(unsigned int));
		}

		auto diff = newQuad - lastQuad;

		unsigned int tm = lastQuad * 6;
		unsigned int tn = lastQuad * 4;
		for (size_t i = 0; i < diff; i++)
		{
			m_pIndicesBufferData[tm] = tn;
			m_pIndicesBufferData[tm+1] = tn+1;
			m_pIndicesBufferData[tm+2] = tn+2;
			m_pIndicesBufferData[tm+3] = tn;
			m_pIndicesBufferData[tm+4] = tn+2;
			m_pIndicesBufferData[tm+5] = tn+3;
			tm += 6;
			tn += 4;
		}

		RgLogW() << "resize indices" << newQuad;

		m_pIndicesBufferQuadSize = newQuad;
	}

	void RgGUIDrawBuffer::ExtendBufferCheck()
	{
		
		if ((m_pPos - m_pData) < m_sBufferSize - BUFFER_SIZE_THRES) return;
		size_t offset = (m_pPos - m_pData);
		RgGUIVertex * n = new RgGUIVertex[m_sBufferSize* BUFFER_SIZE_SCALE];
		memcpy(n, m_pData, m_sBufferSize * VERTEX_SIZE);
		delete[] m_pData;
		m_pData = n;
		m_pPos = m_pData + offset;
		m_sBufferSize = m_sBufferSize * BUFFER_SIZE_SCALE;

		RgLogD() << "resize rggui buffer :" <<(unsigned int)m_sBufferSize;

	}

	void RgGUIDrawBuffer::ResetBuffer()
	{
		m_pLastIndicesQuadSize = m_pIndicesQuadCount;
		m_pPos = m_pData;
		ZeroMemory(m_pData, m_sBufferSize * VERTEX_SIZE);
	}

	unsigned int RgGUIDrawBuffer::GetBufferSize()
	{
		return m_sBufferSize;
	}

	unsigned int RgGUIDrawBuffer::GetVertexCount()
	{
		return (unsigned int)(m_pPos - m_pData);
	}

	void * RgGUIDrawBuffer::GetDataPtr()
	{
		return m_pData;
	}

	unsigned int * RgGUIDrawBuffer::GetIndicesPtr()
	{
		unsigned int quadcount =(unsigned int)(m_pPos - m_pData)/4;
		if (quadcount > m_pIndicesBufferQuadSize) {
			auto scale = quadcount / m_pIndicesBufferQuadSize + 1;
			ExtendIndicesBuffer(m_pIndicesBufferQuadSize, m_pIndicesBufferQuadSize*scale);
		}
		m_pIndicesQuadCount = quadcount;

		return m_pIndicesBufferData;
	}

	unsigned int RgGUIDrawBuffer::GetIndicesSize()
	{
		return m_pIndicesQuadCount *6;
	}

	bool RgGUIDrawBuffer::IsIndicesChanged()
	{
		return m_pIndicesQuadCount != m_pLastIndicesQuadSize;
	}


}

