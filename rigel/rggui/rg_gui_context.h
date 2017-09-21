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
		
		std::stack<RgVec4> GroupRectStack;
		RgFloat RectZ = 1.0f;

		bool guiMenuBar = false;
		bool guiMenuBarHorizontal = false;

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

		bool CheckMousePos(const RgVec2& lp, const RgVec2& size) const;

		bool Clip(const RgVec4& rect, RgVec2& pos, RgVec2& sz) const;

		void RestoreColor(const RgVec4& tempcolor);
		void RestoreColor();
		void DropColor();
		

		//draw
		void DrawLine();
		void DrawRect(const RgVec2& lp,const RgVec2& size);

		//controller
		bool GUIButton(const RgVec2& lp, const RgVec2& size);
		void GUIMenuBarBegin(bool horizontal = true);
		void GUIMenuBarEnd();

		bool GUIMenuItem();
		void GUIMenuItemList();
		void GUIMenuItemListBegin();
		void GUIMenuItemListEnd();
		

		//state
		void SetColor(RgVec4 color);

		RgGUIDrawBuffer * GetDrawBuffer();

	private:
		bool _GroupClip(RgVec2& pos, RgVec2& sz) const;

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