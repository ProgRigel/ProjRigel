#pragma once
#include <rgcore\rg_window.h>
#include "rg_gui_style.h"
#include "rg_gui_component.h"
#include <stack>
#include <vector>
#include <map>
namespace rg {

#define RG_PARAM_RECT const RgVec2&lp,const RgVec2& size

	class RgGUI;
	class RgGUIDrawBuffer;
	struct RgGUIGenericMenu;
	struct RgGUIMenuItem;
	struct RgGUIMenuItemList;
	class RgGUIGlyph;
	class RgImage;

	struct RgGUISettings {
		std::wstring Font;
		RgGUIStyle Style;
	};

	enum class RgGUIControllerType {
		ContextMenu,
		TextInput,
	};

	struct RgGUIStateContextMenu {
		std::vector<int> menuHashs;
		std::unordered_map<int, RgVec4> menuMap;
		bool newMenuContext = false;
	};

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

		bool mouseLeftChecked = false;
		bool mouseLeftClick = false;
		bool mouseLeftDown = false;
		RgVec2 mouseLeftCheckedPos;

		RgGUIStateContextMenu stateContextMenu;

		void Reset();

		void RectZInc();
		void SetMouseDownCheck(int uihash,const RgVec2& pos);

		void contextMenuReset();
		void contextMenuAdd(const int& hash, const RgVec4 rect);
		void contextMenuClear();

		//contextMenu
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
		

		bool Clip(const RgVec4& rect, RgVec2& pos, RgVec2& sz) const;

		void RestoreColor(const RgVec4& tempcolor);
		void RestoreColor();
		void DropColor();
		
		////////////////////////
		void GUIText(std::string content, const RgVec4& rect);
		void GUIText(const char& c, const RgVec4& rect);

		bool GUIButton(const RgVec2& lp, const RgVec2& sz);
		void GUIRect(const RgVec2& lp, const RgVec2& sz,bool grouped =true);
		void GUIRect(const RgVec4& rect,bool grouped = true);
		void GUIRect(const RgVec4& rect, const RgVec4& color,bool grouped = true);
		void GUIGroupBegin(const RgVec2&lp, const RgVec2& sz);
		void GUIGroupBegin(const RgVec4& rect);
		void GUIGroupBegin(const RgVec4& rect,const RgVec4& color);
		void GUIGroupBegin(const RgVec2&lp, const RgVec2& sz,const RgVec4& color);
		void GUIGroupEnd();

		void GUIMenuBarBegin(const RgVec4& rect);
		void GUIMenuBarEnd();
		bool GUIMenuItem(RgFloat width);
		void GUIMenuListBegin(RgStr label,RgFloat width);
		void GUIMenuListEnd();

		void GUIMenuBar(const RgGUIGenericMenu * _menu, const RgVec4& _rect);

		/////////////////////
		bool UtilIsInGroup() const;
		bool UtilClipRect(RgVec4& content, const RgVec4& rect) const;		//return false is no need to draw
		bool UtilCheckMousePos(const RgVec2& lp, const RgVec2& size,bool grouped = true);
		const RgVec4 UtilGetOriginRect(const RgVec4& rect) const;
		const RgVec2 UtilGetOriginPos(const RgVec2& lp) const;
		int UtilGetHash(RgStr label, const RgGUIControllerType type,const RgVec4& rect);

		bool UtilRectContain(const RgVec4& rect, const RgVec2& pos);
		//////////////////
		

		//state
		void SetColor(RgVec4 color);

		RgGUIDrawBuffer * GetDrawBuffer();
		RgGUIDrawBuffer * GetTextBuffer();
		RgImage * GetFontImage();

	private:
		bool _GroupClip(RgVec2& pos, RgVec2& sz) const;
		const RgVec2 _GetWindowSize() const;
		const RgVec4 _GetGroupRect() const;

	private:
		RgGUIContext(const RgGUISettings& settings);
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		bool m_bDirty = false;
		RgGUIState m_sState;
		RgGUIDrawBuffer * m_pDrawBuffer = nullptr;
		RgGUIDrawBuffer * m_pTextBuffer = nullptr;
		const RgWindowInput * m_pWindowInput = nullptr;

		RgGUIStyle m_style;
		RgGUIGlyph * m_pGlyph = nullptr;

	public:
		friend class RgGUI;
	};
}