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
		m_sState.Reset();
	}
	void RgGUIContext::EndGUI()
	{
		SetDirty(true);
	}

	void RgGUIContext::BeginGroup(RG_PARAM_RECT)
	{
		auto& stack = m_sState.GroupRectStack;
		if (stack.empty()) {
			stack.push(RgVec4<RgFloat>(lp, lp + size));
		}
		else
		{
			RgVec4<RgFloat> rect = stack.top();
			rect.x += lp.x;
			rect.y += lp.y;
			rect.z = size.x > rect.z ? rect.z : size.x;
			rect.w = size.y > rect.y ? rect.y : size.y;
			stack.push(rect);
		}
	}

	void RgGUIContext::EndGroup()
	{
		auto& stack = m_sState.GroupRectStack;
		if (!stack.empty()) stack.pop();
	}

	void RgGUIContext::DrawLine()
	{

	}
	void RgGUIContext::DrawRect(const RgVec2<RgFloat>& lp, const RgVec2<RgFloat>& sz) const
	{
		RgVec2<RgFloat> point = lp;
		RgVec2<RgFloat> size = sz;

		bool d = _GroupClip(point, size);

		auto color = m_sState.Color;
		m_pDrawBuffer->m_pPos->pos = RgVec4<RgFloat>(point.x, point.y,1.0f,0.0f);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4<RgFloat>(point.x + size.x, point.y,1.0f,0.0f);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos =RgVec4<RgFloat>(point + size,1.0,0.0f);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4<RgFloat>(point.x, point.y + size.y,1.0,0.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();
	}

	bool RgGUIContext::GUIButton(const RgVec2<RgFloat> & lp, const RgVec2<RgFloat> & size) const
	{
		DrawRect(lp, size);
		if (m_pWindowInput->LButton && CheckMousePos(lp, size)) {
			return true;
		}
		return false;
	}

	void RgGUIContext::SetColor(RgVec4<RgFloat> color)
	{
		m_sState.Color = color;
	}

	bool RgGUIContext::CheckMousePos(const RgVec2<RgFloat> & lp, const RgVec2<RgFloat> & size) const
	{
		if (m_pWindowInput == nullptr) return false;
		
		const RgVec2<RgFloat>& mousepos = m_pWindowInput->MousePos;
		if (lp.x < mousepos.x && mousepos.x < size.x + lp.x && lp.y < mousepos.y && mousepos.y < lp.y + size.y) {
			return true;
		}
		return false;
	}

	bool RgGUIContext::Clip(const RgVec4<RgFloat> & rect, RgVec2<RgFloat> & pos, RgVec2<RgFloat> & sz) const
	{
		RgVec2<RgFloat> rb(rect.x + rect.z, rect.y + rect.w);
		if (pos.x > rb.x || pos.y > rb.y) return false;

		RgVec2<RgFloat> lb = pos + sz + RgVec2<RgFloat>(rect.x,rect.y);
		if (lb.x < rect.x || lb.y < rect.y) return false;

		pos.x = pos.x < rect.x ? rect.x : pos.x;
		pos.y = pos.y < rect.y ? rect.y : pos.y;

		sz = lb - pos;

		return true;
	}

	bool RgGUIContext::_GroupClip(RgVec2<RgFloat> & pos, RgVec2<RgFloat> & sz) const
	{
		if (m_sState.GroupRectStack.empty()) return true;
		
		return Clip(m_sState.GroupRectStack.top(),pos,sz);

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

	void RgGUIState::Reset()
	{
		std::stack<RgVec4<RgFloat>>().swap(GroupRectStack);
	}

}

