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
		m_sState.contextMenuReset();
		m_sState.WindowGroupRect.z = m_pWindowInput->WindowRect.z;
		m_sState.WindowGroupRect.w = m_pWindowInput->WindowRect.w;

		//mouseclick check
		m_sState.mouseLeftClick = false;
		if (m_pWindowInput->LButton && m_sState.mouseLeftDown == false) {
			m_sState.mouseLeftDown = true;
		}
		if (m_sState.mouseLeftDown == true && m_pWindowInput->LButton == false) {
			m_sState.mouseLeftDown = false;
			m_sState.mouseLeftClick = true;
		}


	}
	void RgGUIContext::EndGUI()
	{
		SetDirty(true);

		//contextmenu
		{
			if (!m_sState.stateContextMenu.menuMap.empty()) {
				auto pair = *m_sState.stateContextMenu.menuMap.begin();

				bool mousedown = m_sState.mouseLeftDown;
				if (mousedown && !m_sState.stateContextMenu.newMenuContext) {
					RgLogD() << "clear";
					m_sState.contextMenuClear();
					return;
				}
				GUIRect(pair.second,RgGUIColors::Alizarin, false);
			}
		}
		
	}



	////////////////


	bool RgGUIContext::GUIButton(const RgVec2 & lp, const RgVec2 & sz)
	{
		GUIRect(lp, sz);
		return (m_pWindowInput->LButton && UtilCheckMousePos(lp, sz));
	}

	//draw with raw pos
	void RgGUIContext::GUIRect(const RgVec2 & lp, const RgVec2 & sz, bool grouped)
	{

		RgVec4 rect(lp, sz);
		if (grouped && UtilIsInGroup()) {
			rect.setxy(lp + m_sState.GroupRectStack.top().xy());
			UtilClipRect(rect, m_sState.GroupRectStack.top());
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

	void RgGUIContext::GUIRect(const RgVec4 & rect,bool grouped)
	{
		GUIRect(rect.xy(), rect.zw(), grouped);
	}

	void RgGUIContext::GUIRect(const RgVec4 & rect, const RgVec4 & color, bool grouped)
	{
		RestoreColor(color);
		GUIRect(rect,grouped);
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

	void RgGUIContext::GUIGroupBegin(const RgVec4 & rect)
	{
		GUIGroupBegin(rect.xy(), rect.zw());
	}

	void RgGUIContext::GUIGroupBegin(const RgVec4 & rect, const RgVec4 & color)
	{
		GUIGroupBegin(rect.xy(), rect.zw(), color);
	}

	void RgGUIContext::GUIGroupBegin(const RgVec2 & lp, const RgVec2 & sz, const RgVec4 & color)
	{
		GUIGroupBegin(lp,sz);
		RestoreColor(color);
		GUIRect(m_sState.GroupRectStack.top(),false);
		DropColor();
	}

	void RgGUIContext::GUIGroupEnd()
	{
		if (!m_sState.GroupRectStack.empty()) m_sState.GroupRectStack.pop();
	}

	void RgGUIContext::GUIMenuBarBegin(const RgVec4 & rect)
	{
		GUIGroupBegin(rect, m_style.MenuBarBackgroudColor);
		m_sState.guiMenuBar = true;
		m_sState.guiMenuBarOffset = 0;
		m_sState.guiMenuBarHeight = rect.w;
	}

	void RgGUIContext::GUIMenuBarEnd()
	{
		m_sState.guiMenuBar = false;
		GUIGroupEnd();
		
	}

	bool RgGUIContext::GUIMenuItem(RgFloat width)
	{
		bool clicked = GUIButton(RgVec2(m_sState.guiMenuBarOffset, 0.0f), RgVec2(width, m_sState.guiMenuBarHeight));
		m_sState.guiMenuBarOffset += width;
		return clicked;
	}

	void RgGUIContext::GUIMenuListBegin(RgStr label, RgFloat width)
	{
		bool clicked = GUIMenuItem(width);
		if (clicked) {
			SetColor(RgGUIColors::Alizarin);

			RgVec4 rect(400, 400, 100, 200);
			int ctxmenu = UtilGetHash(label, RgGUIControllerType::ContextMenu, rect);
			m_sState.contextMenuAdd(ctxmenu, rect);
		}
	}

	void RgGUIContext::GUIMenuListEnd()
	{
	}

	bool RgGUIContext::UtilIsInGroup() const
	{
		return !m_sState.GroupRectStack.empty();
	}

	bool RgGUIContext::UtilClipRect(RgVec4 & content, const RgVec4 & rect) const
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

	bool RgGUIContext::UtilCheckMousePos(const RgVec2 & lp, const RgVec2 & size,bool grouped)
	{
		if (m_pWindowInput == nullptr) return false;

		if (m_sState.mouseLeftChecked) return false; //hack optimize
		
		RgVec4 rect(lp, size);
		const RgVec2& mousepos = m_pWindowInput->MousePos;
		if (grouped && UtilIsInGroup()) {
			rect.setxy(lp + m_sState.GroupRectStack.top().xy());
			if (!UtilClipRect(rect, m_sState.GroupRectStack.top())) return false;
		}

		if (rect.x < mousepos.x && mousepos.x < rect.x + rect.z && rect.y < mousepos.y && mousepos.y < rect.y + rect.w) {
			
			m_sState.SetMouseDownCheck(0,grouped? UtilGetOriginPos(lp):lp);// hack optimize. may cause bugs
			return true;
		}
		return false;
	}

	const RgVec4 RgGUIContext::UtilGetOriginRect(const RgVec4 & rect) const
	{
		if (!UtilIsInGroup()) return rect;

		RgVec4 grect = rect;
		grect.setxy(rect.xy() + m_sState.GroupRectStack.top().xy());
		UtilClipRect(grect, m_sState.GroupRectStack.top());

		return grect;
	}

	const RgVec2 RgGUIContext::UtilGetOriginPos(const RgVec2 & lp) const
	{
		return lp + m_sState.GroupRectStack.top().xy();
	}

	int RgGUIContext::UtilGetHash(RgStr label,const RgGUIControllerType type, const RgVec4 & rect)
	{
		byte data[64];
		byte* data_ptr = &data[0];
		ZeroMemory(data_ptr, 64);
		size_t labelt = label.size() > 32?32: label.size();
		memcpy(data_ptr, label.data(), labelt);
		data_ptr += 32;
		
		memcpy(data_ptr, &rect, sizeof(RgVec4));
		data_ptr += 16;
		byte t = (unsigned char)type;
		data_ptr[0] = t;

		return RgHash(&data[0], 64);
	}

	bool RgGUIContext::UtilRectContain(const RgVec4 & rect, const RgVec2 & pos)
	{
		if (pos.x > rect.x && pos.y > rect.y && pos.x < rect.x + rect.z && pos.y < rect.y + rect.w) {
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
		
		mouseLeftChecked = false;
	}

	void RgGUIState::RectZInc()
	{
		RectZ += 1.0f;
	}

	void RgGUIState::SetMouseDownCheck(int uihash,const RgVec2& pos)
	{
		mouseLeftChecked = true;
		mouseLeftCheckedPos = pos;
	}

	void RgGUIState::contextMenuReset()
	{
		stateContextMenu.newMenuContext = false;
	}

	void RgGUIState::contextMenuAdd(const int & hash, const RgVec4 rect)
	{
		if (stateContextMenu.menuMap.find(hash) == stateContextMenu.menuMap.end()) {
			std::unordered_map<int, RgVec4>().swap(stateContextMenu.menuMap);
			stateContextMenu.menuMap.insert(std::make_pair(hash, rect));
		}
		else
		{
			stateContextMenu.menuMap[hash] = rect;
		}

		stateContextMenu.newMenuContext = true;
	}

	void RgGUIState::contextMenuClear()
	{
		std::unordered_map<int, RgVec4>().swap(stateContextMenu.menuMap);
	}


}

