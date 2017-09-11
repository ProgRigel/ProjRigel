#include "rg_gui_draw_buffer.h"
#include <memory>
#include <rgcore\rg_log.h>
namespace rg {
	RgGUIDrawBuffer::RgGUIDrawBuffer()
	{
		m_pData = new RgGUIVertex[BUFFER_SIZE_INIT];
	}

	RgGUIDrawBuffer::~RgGUIDrawBuffer()
	{
		delete[] m_pData;
		m_pData = nullptr;
		m_pPos = nullptr;
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
		m_pPos = m_pData;
		ZeroMemory(m_pData, m_sBufferSize * VERTEX_SIZE);
	}

}

