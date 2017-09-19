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

		m_pWindowInput = nullptr;
	}
	void RgGUIContext::Reset()
	{
		m_pDrawBuffer->ResetBuffer();
	}
	void RgGUIContext::SetDirty(bool dirty)
	{
		m_bDirty = dirty;
	}
	bool RgGUIContext::IsDirty()
	{
		return m_bDirty;
	}
	void RgGUIContext::BeginGUI(const RgWindowEvent& e)
	{
		m_pWindowInput = e.Input;
		m_pDrawBuffer->ResetBuffer();
	}
	void RgGUIContext::EndGUI()
	{
		SetDirty(true);
	}
	void RgGUIContext::DrawLine()
	{
	}
	void RgGUIContext::DrawRect(const RgVec2& lp, const RgVec2& size) const
	{
		
		auto color = m_sState.Color;
		m_pDrawBuffer->m_pPos->pos = RgVec4(lp.x,lp.y,0.0f,0.0f);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(lp.x + size.x, lp.y,0.0f,0.0f);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = lp + size;
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec2(lp.x, lp.y + size.y);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();
	}

	bool RgGUIContext::GUIButton(const RgVec2 & lp, const RgVec2 & size) const
	{
		DrawRect(lp, size);
		if (m_pWindowInput->LButton && CheckMousePos(lp, size)) {
			return true;
		}
		return false;
	}

	void RgGUIContext::SetColor(RgVec4 color)
	{
		m_sState.Color = color;
	}

	bool RgGUIContext::CheckMousePos(const RgVec2 & lp, const RgVec2 & size) const
	{
		if (m_pWindowInput == nullptr) return false;
		
		const RgVec2& mousepos = m_pWindowInput->MousePos;
		if (lp.x < mousepos.x && mousepos.x < size.x + lp.x && lp.y < mousepos.y && mousepos.y < lp.y + size.y) {
			return true;
		}
		return false;
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

