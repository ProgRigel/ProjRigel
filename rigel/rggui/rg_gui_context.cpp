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
		m_sState.WindowGroupRect.z = m_pWindowInput->WindowRect.z;
		m_sState.WindowGroupRect.w = m_pWindowInput->WindowRect.w;

	}
	void RgGUIContext::EndGUI()
	{
		SetDirty(true);
	}

	void RgGUIContext::BeginGroup(RG_PARAM_RECT)
	{
		BeginGroup(lp, size, m_style.ColorBg);
	}

	void RgGUIContext::BeginGroup(RG_PARAM_RECT, RgVec4 color)
	{
		auto& stack = m_sState.GroupRectStack;
		if (stack.empty()) {
			stack.push(RgVec4(lp, lp + size));

			RestoreColor(color);
			DrawRect(RgVec2(),size);
			DropColor();
		}
		else
		{
			
			RgVec4 rect = stack.top();
			rect.x += lp.x;
			rect.y += lp.y;
			rect.z = size.x > rect.z ? rect.z : size.x;
			rect.w = size.y > rect.y ? rect.y : size.y;
			stack.push(rect);

			RestoreColor(color);
			DrawRect(RgVec2(),rect.zw());
			DropColor();
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
	void RgGUIContext::DrawRect(const RgVec2& lp, const RgVec2& sz)
	{
		RgVec2 point = lp;
		RgVec2 size = sz;

		bool d = _GroupClip(point, size);

		//RgLogW()<< lp.toStr() << size.toStr();

		if (d == false) return;

		auto color = m_sState.Color;
		m_pDrawBuffer->m_pPos->pos = RgVec4(point.x, point.y,m_sState.RectZ,1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(point.x + size.x, point.y, m_sState.RectZ,1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos =RgVec4(point + size, m_sState.RectZ,1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(point.x, point.y + size.y, m_sState.RectZ,1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();

		m_sState.RectZInc();
	}

	bool RgGUIContext::DrawButton(const RgVec2 & lp, const RgVec2 & size)
	{
		DrawRect(lp, size);

		RgVec2 cliplp, clipsz;
		_GroupClip(cliplp, clipsz);
		if (m_pWindowInput->LButton && CheckMousePos(cliplp, clipsz)) {
			return true;
		}
		return false;
	}

	void RgGUIContext::GUIMenuBarBegin(bool horizontal)
	{
		m_sState.guiMenuBar = true;
		m_sState.guiMenuBarHorizontal = horizontal;
		m_sState.guiMenuBarOffset = 0;

		RestoreColor(m_style.MenuBarBackgroudColor);

		auto groupr = _GetGroupRect();
		DrawRect(RgVec2(), RgVec2(groupr.z - groupr.x, m_style.MenuBarHeight));
		DropColor();
	}

	void RgGUIContext::GUIMenuBarEnd()
	{
		m_sState.guiMenuBar = false;
	}

	bool RgGUIContext::GUIMenuItem()
	{
		RgFloat offset = m_sState.guiMenuBarOffset;
		m_sState.guiMenuBarOffset += m_style.MenuBarItemWdith;
		return DrawButton(RgVec2(offset, 0.0f), RgVec2(m_style.MenuBarItemWdith, m_style.MenuBarHeight));
	}

	void RgGUIContext::GUIMenuItemList()
	{
	}

	void RgGUIContext::GUIMenuItemListBegin()
	{
	}

	void RgGUIContext::GUIMenuItemListEnd()
	{
	}


	bool RgGUIContext::GUIButton(const RgVec2 & lp, const RgVec2 & sz)
	{
		GUIRect(lp, sz);
		return (m_pWindowInput->LButton && CheckMousePos(lp, sz));
	}

	void RgGUIContext::GUIRect(const RgVec2 & lp, const RgVec2 & sz)
	{

		RgVec4 rect(lp, sz);
		if (UtilIsInGroup()) {
			if (!UtilClipRect(rect, m_sState.GroupRectStack.top())) {
				return;
			}
		}

		auto& color = m_sState.Color;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x, rect.y, m_sState.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x + rect.z, rect.y, m_sState.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.xy() + rect.zw(),m_sState.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x, rect.y + rect.w, m_sState.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();
		m_sState.RectZInc();
	}

	void RgGUIContext::GUIRect(const RgVec4 & rect)
	{
		GUIRect(rect.xy(), rect.zw());
	}

	void RgGUIContext::GUIRect(const RgVec4 & rect, const RgVec4 & color)
	{
		RestoreColor(color);
		GUIRect(rect);
		DropColor();
	}

	void RgGUIContext::GUIGroupBegin(const RgVec2 & lp, const RgVec2 & sz)
	{
		auto&stack = m_sState.GroupRectStack;
		if (stack.empty()) {
			stack.push(RgVec4(lp, sz));
		}
		else {
			RgVec4 rect = stack.top();
			rect.setxy(rect.xy() + lp);
			rect.setzw(min(lp + sz, rect.zw()) - lp);

			stack.push(rect);
		}
	}

	void RgGUIContext::GUIGroupBegin(const RgVec4 & rect, const RgVec4 & color)
	{
		GUIGroupBegin(rect.xy(), rect.zw(), color);
	}

	void RgGUIContext::GUIGroupBegin(const RgVec2 & lp, const RgVec2 & sz, const RgVec4 & color)
	{
		GUIGroupBegin(lp,sz);
		RestoreColor(color);
		GUIRect(m_sState.GroupRectStack.top());
		DropColor();
	}

	void RgGUIContext::GUIGroupEnd()
	{
		if (!m_sState.GroupRectStack.empty()) m_sState.GroupRectStack.pop();
	}

	bool RgGUIContext::UtilIsInGroup()
	{
		return !m_sState.GroupRectStack.empty();
	}

	bool RgGUIContext::UtilClipRect(RgVec4 & content, const RgVec4 & rect)
	{
		auto cxy = content.xy();
		auto rxy = rect.xy();

		RgVec2 lt = max(cxy, rxy);
		RgVec2 rb = min(cxy + content.zw(), rxy + rect.zw());

		if (lt.x > rb.x || lt.y > rb.y) return false;

		content.setxy(lt);
		content.setzw(rb - lt);
		return true;
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

	//pos sz in related to group root
	bool RgGUIContext::Clip(const RgVec4 & rect, RgVec2 & pos, RgVec2 & sz) const
	{
		RgVec2 rroot = max(RgVec2(), pos);
		RgVec2 rtail = pos + sz;
		rtail = min(rtail, rect.zw());

		if (rtail.x < rroot.x || rtail.y < rroot.y) return false;

		sz = rtail - rroot;
		pos = rroot + rect.xy();
		

		return true;
	}

	void RgGUIContext::RestoreColor()
	{
		m_sState.ColorRestored = m_sState.Color;
	}

	void RgGUIContext::RestoreColor(const RgVec4 & tempcolor)
	{
		RestoreColor();
		m_sState.Color = tempcolor;
	}

	void RgGUIContext::DropColor()
	{
		m_sState.Color = m_sState.ColorRestored;
	}

	bool RgGUIContext::_GroupClip(RgVec2 & pos, RgVec2 & sz) const
	{
		if (m_sState.GroupRectStack.empty()) return true;
		
		return Clip(m_sState.GroupRectStack.top(),pos,sz);

	}

	const RgVec2 RgGUIContext::_GetWindowSize() const
	{
		return m_pWindowInput->WindowRect.zw();
	}

	const RgVec4 RgGUIContext::_GetGroupRect() const
	{
		if (m_sState.GroupRectStack.empty()) return m_sState.WindowGroupRect;

		return m_sState.GroupRectStack.top();
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
		std::stack<RgVec4>().swap(GroupRectStack);
		RectZ = 1.0f;
	}

	void RgGUIState::RectZInc()
	{
		RectZ += 1.0f;
	}

}

