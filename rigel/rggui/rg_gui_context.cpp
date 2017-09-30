#include "rggui.h"

#include "rg_gui_context.h"
#include "rg_gui_draw_buffer.h"
#include "rg_gui_glyph.h"
#include <map>

namespace rg {
	void RgGUIContext::Release()
	{
		if (m_pDrawBuffer != nullptr) {
			delete m_pDrawBuffer;
			m_pDrawBuffer = nullptr;
		}

		if (m_pTextBuffer != nullptr) {
			delete m_pTextBuffer;
			m_pTextBuffer = nullptr;
		}

		if (m_pGlyph != nullptr) {
			m_pGlyph->Release();
			m_pGlyph = nullptr;
		}

		m_pWindowInput = nullptr;
	}
	void RgGUIContext::Reset()
	{
		m_pDrawBuffer->ResetBuffer();
		m_pTextBuffer->ResetBuffer();
	}
	void RgGUIContext::SetDirty(bool dirty)
	{
		m_bDirty = dirty;
	}
	bool RgGUIContext::IsDirty()
	{
		return m_bDirty;
	}

#pragma region GUILayout
	void RgGUIContext::GUILayoutText()
	{
	}
	void RgGUIContext::GUILayoutButton()
	{
	}
	void RgGUIContext::GUILayoutGroupBegin()
	{
	}
	void RgGUIContext::GUILayoutGroupEnd()
	{
	}
	void RgGUIContext::GUILayoutRect()
	{
	}
#pragma endregion


	void RgGUIContext::BeginGUI(const RgWindowEvent& e)
	{
		m_pWindowInput = e.Input;
		m_pDrawBuffer->ResetBuffer();
		m_pTextBuffer->ResetBuffer();
		m_state.Reset();
		m_state.contextMenuReset();
		m_state.WindowGroupRect.z = m_pWindowInput->WindowRect.z;
		m_state.WindowGroupRect.w = m_pWindowInput->WindowRect.w;

		//mouseclick check
		m_state.mouseLeftClick = false;
		if (m_pWindowInput->LButton && m_state.mouseLeftDown == false) {
			m_state.mouseLeftDown = true;
		}

		m_state.eventMouseLeftDown = e.Input->LButton;
		m_state.eventMousePos = e.Input->MousePos;

		m_stateWindow.ongui(m_state);
	}
	void RgGUIContext::EndGUI()
	{
		SetDirty(true);

		//contextmenu
		{
			if (!m_state.stateContextMenu.menuMap.empty()) {
				auto pair = *m_state.stateContextMenu.menuMap.begin();

				bool mousedown = m_state.mouseLeftDown;
				if (mousedown && !m_state.stateContextMenu.newMenuContext) {
					RgLogD() << "clear";
					m_state.contextMenuClear();
					return;
				}
				GUIRect(pair.second,RgGUIColors::Alizarin, false);
			}
		}

		m_pDrawBuffer->ApplyBuffer();
		m_pTextBuffer->ApplyBuffer();


	}



	////////////////


	void RgGUIContext::GUIText(std::string content, const RgVec4 & rect)
	{
		RgVec4 pos = rect;
		for (char c : content) {
			pos.x += GUIText(c, pos).x;
			m_pTextBuffer->ExtendBufferCheck();
		}
		m_state.RectZInc();
	}

	const RgVec2 RgGUIContext::GUIText(const char & c, const RgVec4 & rect)
	{
		auto color = m_state.Color;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy(), m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->color = color;
		m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 0);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c,1), m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->color = color;
		m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 1);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c, 2), m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->color = color;
		m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 2);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + m_pGlyph->GetCharPos(c, 3), m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->color = color;
		m_pTextBuffer->m_pPos->uv = m_pGlyph->GetCharUV(c, 3);
		m_pTextBuffer->m_pPos++;

		return m_pGlyph->GetCharPos(c, 2);
	}

	void RgGUIContext::GUITextDebug(const RgVec4 & rect)
	{
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.x, rect.y, m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->uv = RgVec2(0,0);
		m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.x + rect.z, rect.y, m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->uv = RgVec2(1, 0);
		m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.xy() + rect.zw(), m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->uv = RgVec2(1, 1);
		m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		m_pTextBuffer->m_pPos++;
		m_pTextBuffer->m_pPos->pos = RgVec4(rect.x, rect.y + rect.w, m_state.RectZ, 1.0);
		m_pTextBuffer->m_pPos->uv = RgVec2(0, 1);
		m_pTextBuffer->m_pPos->color = RgVec4(1.0f);
		m_pTextBuffer->m_pPos++;
		m_state.RectZInc();
	}

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
			rect.setxy(lp + m_state.GroupRectStack.top().xy());
			UtilClipRect(rect, m_state.GroupRectStack.top());
		}

		auto& color = m_state.Color;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x, rect.y, m_state.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x + rect.z, rect.y, m_state.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.xy() + rect.zw(),m_state.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;
		m_pDrawBuffer->m_pPos->pos = RgVec4(rect.x, rect.y + rect.w, m_state.RectZ, 1.0);
		m_pDrawBuffer->m_pPos->color = color;
		m_pDrawBuffer->m_pPos++;

		m_pDrawBuffer->ExtendBufferCheck();
		m_state.RectZInc();
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
		auto&stack = m_state.GroupRectStack;
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
		GUIRect(m_state.GroupRectStack.top(),false);
		DropColor();
	}

	void RgGUIContext::GUIGroupEnd()
	{
		if (!m_state.GroupRectStack.empty()) m_state.GroupRectStack.pop();
	}

	void RgGUIContext::GUIMenuBarBegin(const RgVec4 & rect)
	{
		GUIGroupBegin(rect, m_style.MenuBarBackgroudColor);
		m_state.guiMenuBar = true;
		m_state.guiMenuBarOffset = 0;
		m_state.guiMenuBarHeight = rect.w;
	}

	void RgGUIContext::GUIMenuBarEnd()
	{
		m_state.guiMenuBar = false;
		GUIGroupEnd();
		
	}

	bool RgGUIContext::GUIMenuItem(RgFloat width)
	{
		bool clicked = GUIButton(RgVec2(m_state.guiMenuBarOffset, 0.0f), RgVec2(width, m_state.guiMenuBarHeight));
		m_state.guiMenuBarOffset += width;
		return clicked;
	}

	void RgGUIContext::GUIMenuListBegin(RgStr label, RgFloat width)
	{
		bool clicked = GUIMenuItem(width);
		if (clicked) {
			SetColor(RgGUIColors::Alizarin);

			RgVec4 rect(400, 400, 100, 200);
			int ctxmenu = UtilGetHash(label, RgGUIControllerType::ContextMenu, rect);
			m_state.contextMenuAdd(ctxmenu, rect);
		}
	}

	void RgGUIContext::GUIMenuListEnd()
	{
	}

	void RgGUIContext::GUIMenuBar(const RgGUIGenericMenu * _menu, const RgVec4 & _rect)
	{

	}

	bool RgGUIContext::UtilIsInGroup() const
	{
		return !m_state.GroupRectStack.empty();
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
		m_state.Color = color;
	}

	bool RgGUIContext::UtilCheckMousePos(const RgVec2 & lp, const RgVec2 & size,bool grouped)
	{
		if (m_pWindowInput == nullptr) return false;

		if (m_state.mouseLeftChecked) return false; //hack optimize
		
		RgVec4 rect(lp, size);
		const RgVec2& mousepos = m_pWindowInput->MousePos;
		if (grouped && UtilIsInGroup()) {
			rect.setxy(lp + m_state.GroupRectStack.top().xy());
			if (!UtilClipRect(rect, m_state.GroupRectStack.top())) return false;
		}

		if (rect.x < mousepos.x && mousepos.x < rect.x + rect.z && rect.y < mousepos.y && mousepos.y < rect.y + rect.w) {
			
			m_state.SetMouseDownCheck(0,grouped? UtilGetOriginPos(lp):lp);// hack optimize. may cause bugs
			return true;
		}
		return false;
	}

	const RgVec4 RgGUIContext::UtilGetOriginRect(const RgVec4 & rect) const
	{
		if (!UtilIsInGroup()) return rect;

		RgVec4 grect = rect;
		grect.setxy(rect.xy() + m_state.GroupRectStack.top().xy());
		UtilClipRect(grect, m_state.GroupRectStack.top());

		return grect;
	}

	const RgVec2 RgGUIContext::UtilGetOriginPos(const RgVec2 & lp) const
	{
		if (m_state.GroupRectStack.empty()) return lp;
		return lp + m_state.GroupRectStack.top().xy();
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
		m_state.ColorRestored = m_state.Color;
	}

	void RgGUIContext::RestoreColor(const RgVec4 & tempcolor)
	{
		RestoreColor();
		m_state.Color = tempcolor;
	}

	void RgGUIContext::DropColor()
	{
		m_state.Color = m_state.ColorRestored;
	}

	bool RgGUIContext::_GroupClip(RgVec2 & pos, RgVec2 & sz) const
	{
		if (m_state.GroupRectStack.empty()) return true;
		
		return Clip(m_state.GroupRectStack.top(),pos,sz);

	}

	const RgVec2 RgGUIContext::_GetWindowSize() const
	{
		return m_pWindowInput->WindowRect.zw();
	}

	const RgVec4 RgGUIContext::_GetGroupRect() const
	{
		if (m_state.GroupRectStack.empty()) return m_state.WindowGroupRect;

		return m_state.GroupRectStack.top();
	}

	bool RgGUIContext::GUIWindowBegin(RgGUIWindow* win)
	{
		if (win == nullptr) return false;

		//check focus
		if (win->_initdraw == false) {
			m_stateWindow.register_win(win);
			win->_initdraw = true;
		}
		else {
			if (win->enabled == false) return false;
			if (m_stateWindow.verify_valid(win->winid) == false) return false;
		}
		
		//do draw
		GUIRect(win->windowrect,m_style.ColorBg);
		return true;
	}

	void RgGUIContext::GUIWindowEnd()
	{
	}

	RgGUIDrawBuffer * RgGUIContext::GetDrawBuffer()
	{
		return m_pDrawBuffer;
	}

	RgGUIDrawBuffer * RgGUIContext::GetTextBuffer()
	{
		return m_pTextBuffer;
	}

	RgImage * RgGUIContext::GetFontImage()
	{
		return m_pGlyph->GetImage();
	}


	RgGUIContext::RgGUIContext(const RgGUISettings & settings)
	{
		m_pDrawBuffer = new RgGUIDrawBuffer();
		m_pTextBuffer = new RgGUIDrawBuffer();
		m_style = settings.Style;
		m_pGlyph = new RgGUIGlyph(settings.Font);
	}

	RgGUIContext::RgGUIContext()
	{
		m_pDrawBuffer = new RgGUIDrawBuffer();
		m_pTextBuffer = new RgGUIDrawBuffer();
		m_pGlyph = new RgGUIGlyph();
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
		eventMouseLeftDown = false;
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


	void RgGUIStateWindow::ongui(const RgGUIState & state)
	{
		bool mousedown = state.eventMouseLeftDown;
		if (mousedown == false) {
			return;
		}
		RgGUIWindow * focusedWin = nullptr;
		long maxorder = 0;

		for (auto pair : windowMap) {
			auto win = pair.second;
			maxorder = win->order > maxorder ? win->order : maxorder;
			if (win->windowrect.rect_contain(state.eventMousePos)) {
				if (focusedWin == nullptr) {
					focusedWin = pair.second;
					focusedWin->_mouseover = true;
				}
				else
				{
					if (focusedWin->order < win->order) {
						focusedWin->_mouseover = false;
						focusedWin = pair.second;
						focusedWin->_mouseover = true;
					}
				}
			}
		}
		if (focusedWin != nullptr) {
			focusedWin->order = maxorder + 1;
			RgLogW() << "focused win:" << focusedWin->winid;
		}

		
	}

	void RgGUIStateWindow::register_win(RgGUIWindow* win)
	{
		if (win == nullptr) return;

		int ordernext = 0;

		if (windowMap.size() > 0) {
			auto iter = windowMap.end();
			iter--;
			ordernext = (*iter).second->order+1;
		}
		win->order = ordernext;
		windowMap.insert(std::make_pair(win->winid,win));
	}

	bool RgGUIStateWindow::verify_valid(long winid)
	{
		auto iter = windowMap.find(winid);
		if (iter == windowMap.end()) {
			RgLogE() << "window check focused error";
			return false;
		}

		return (*iter).second->_mouseover;
	}

}

