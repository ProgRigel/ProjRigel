#include "rggui.h"

#include "rg_gui_context.h"
#include "rg_gui_draw_buffer.h"

namespace rg {
	void RgGUIContext::Release()
	{
		if (m_pDrawBuffer != nullptr) {
			delete m_pDrawBuffer;
			m_pDrawBuffer = nullptr;
		}
	}
	void RgGUIContext::Reset()
	{
		m_pDrawBuffer->ResetBuffer();
	}
	void RgGUIContext::DrawLine()
	{
	}
	void RgGUIContext::DrawRect(const RgVec2& lp, const RgVec2& size) const
	{
		m_pDrawBuffer->m_pPos->pos = lp;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec2(lp.x + size.x, lp.y);
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = lp + size;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec2(lp.x, lp.y + size.y);
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();
	}

	RgGUIDrawBuffer * RgGUIContext::GetDrawBuffer()
	{
		return m_pDrawBuffer;
	}


	RgGUIContext::RgGUIContext()
	{
		m_pDrawBuffer = new RgGUIDrawBuffer();
	}

	RgGUIContext::~RgGUIContext()
	{
		Release();
	}

}

