#pragma once
#include <rgcore\rg_window.h>
#include "rg_gui_style.h"
#include <stack>
namespace rg {

#define RG_PARAM_RECT const RgVec2&lp,const RgVec2& size

	class RgGUI;
	class RgGUIDrawBuffer;

	struct RgGUIState {
		RgVec4 ColorBg;
		RgVec4 ColorFont;
		RgVec4 Color;
		RgVec4 ColorRestored;
		
		//group lp,sz
		std::stack<RgVec4> GroupRectStack;
		RgFloat RectZ = 1.0f;
		RgFloat GroupWidthMax;
		RgVec4 WindowGroupRect = RgVec4::Zero;

		bool guiMenuBar = false;
		bool guiMenuBarHorizontal = false;
		RgFloat guiMenuBarOffset = 0;
		RgFloat guiMenuBarHeight = 0;

		void Reset();
		void RectZInc();
	};

	class RgGUIContext {

	public:
		void Release();
		void Reset();

		void SetDirty(bool dirty);
		bool IsDirty();
	public:

		//logic
		void BeginGUI(const RgWindowEvent&);
		void EndGUI();

		void BeginGroup(RG_PARAM_RECT);
		void BeginGroup(RG_PARAM_RECT,RgVec4 color);
		void EndGroup();

		

		bool Clip(const RgVec4& rect, RgVec2& pos, RgVec2& sz) const;

		void RestoreColor(const RgVec4& tempcolor);
		void RestoreColor();
		void DropColor();
		



		
		void GUIMenuItemList();
		void GUIMenuItemListBegin();
		void GUIMenuItemListEnd();

		////////////////////////
		bool GUIButton(const RgVec2& lp, const RgVec2& sz);
		void GUIRect(const RgVec2& lp, const RgVec2& sz,bool grouped =true);
		void GUIRect(const RgVec4& rect,bool grouped = true);
		void GUIRect(const RgVec4& rect, const RgVec4& color);
		void GUIGroupBegin(const RgVec2&lp, const RgVec2& sz);
		void GUIGroupBegin(const RgVec4& rect);
		void GUIGroupBegin(const RgVec4& rect,const RgVec4& color);
		void GUIGroupBegin(const RgVec2&lp, const RgVec2& sz,const RgVec4& color);
		void GUIGroupEnd();

		void GUIMenuBarBegin(const RgVec4& rect);
		void GUIMenuBarEnd();
		bool GUIMenuItem(RgFloat width);

		/////////////////////
		bool UtilIsInGroup() const;
		bool UtilClipRect(RgVec4& content, const RgVec4& rect) const;		//return false is no need to draw
		bool UtilCheckMousePos(const RgVec2& lp, const RgVec2& size,bool grouped = true) const;
		//////////////////
		

		//state
		void SetColor(RgVec4 color);

		RgGUIDrawBuffer * GetDrawBuffer();

	private:
		bool _GroupClip(RgVec2& pos, RgVec2& sz) const;
		const RgVec2 _GetWindowSize() const;
		const RgVec4 _GetGroupRect() const;

	private:
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		bool m_bDirty = false;
		RgGUIState m_sState;
		RgGUIDrawBuffer * m_pDrawBuffer = nullptr;
		const RgWindowInput * m_pWindowInput = nullptr;

		RgGUIStyle m_style;

	public:
		friend class RgGUI;
	};
}