#pragma once
#include <rgcore\rg_inc.h>
#include <rgcore\rg_window.h>
#include "rg_gui_style.h"
#include "rg_gui_component.h"
#include <rgcore\rg_math.h>
#include <stack>
#include <algorithm>
#include <vector>
#include <unordered_map>
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
	struct RgGUIWindow;
	struct RgGUIState;
	class RgGUIContext;

	class RgGUIVertexBuffer;
	class RgGUIIndicesBuffer;

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

	struct RgGUIStateWindow {

		bool skipDraw = false;

		//current drawing window
		RgGUIWindow * stateWindow = nullptr;

		//focus
		RgGUIWindow * windowFocused = nullptr;

		std::map<long, RgGUIWindow *> windowMap;

		RgGUIWindow * GetWindow(long winid);
		void DrawWindow(RgGUIWindow * window,RgGUIContext * ctx);
		void DrawWindowEnd(RgGUIWindow * window,RgGUIContext * ctx);

		void ongui(const RgGUIState& state,RgGUIContext * ctx);
		void endgui(const RgGUIState& state, RgGUIContext * ctx);
		void register_win(RgGUIWindow* win);
		bool verify_valid(long winid);

	};

	struct RgGUIState {
		RgVec4 colorBg;
		RgVec4 colorFont;
		RgVec4 color;
		RgVec4 colorRestored;
		
		//group lp,sz
		std::stack<RgVec4> GroupRectStack;
		RgFloat RectZ = 1.0f;
		RgFloat GroupWidthMax;
		RgVec4 WindowGroupRect = RgVec4::Zero;

		bool guiMenuBar = false;
		bool guiMenuBarHorizontal = false;
		RgFloat guiMenuBarOffset = 0;
		RgFloat guiMenuBarHeight = 0;


		bool eventMouseLeftDown = false;
		RgVec2 eventMousePos;

		void ongui(const RgWindowInput* input);
		void reset();
		void rect_z_inc();


		//contextMenu
	};

	class RgGUIContext {

	public:
		void Release();
		void Reset();

		void SetDirty(bool dirty);
		bool IsDirty();

	public:
		//GUILayout
		void GUILayoutText();
		void GUILayoutButton();
		void GUILayoutGroupBegin();
		void GUILayoutGroupEnd();
		void GUILayoutRect();

	public:

		//logic
		void gui_begin(const RgWindowEvent&);
		void gui_end();
		

		bool Clip(const RgVec4& rect, RgVec2& pos, RgVec2& sz) const;

		void RestoreColor(const RgVec4& tempcolor);
		void RestoreColor();
		void DropColor();
		
		////////////////////////
		void GUIText(std::string content, const RgVec4& rect);
		const RgVec2 GUIText(const char& c, const RgVec4& rect);
		void GUITextDebug(const RgVec4& rect);

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

		bool GUIWindowBegin(RgGUIWindow* win);//return true if focused
		void GUIWindowEnd();

		/////////////////////
		bool UtilIsInGroup() const;
		bool UtilClipRect(RgVec4& content, const RgVec4& rect) const;		//return false is no need to draw
		const RgVec4 UtilGetOriginRect(const RgVec4& rect) const;
		const RgVec2 UtilGetOriginPos(const RgVec2& lp) const;
		int UtilGetHash(RgStr label, const RgGUIControllerType type,const RgVec4& rect);

		bool UtilRectContain(const RgVec4& rect, const RgVec2& pos);
		//////////////////
		

		//state
		void SetColor(RgVec4 color);

		RgImage * GetFontImage();

		RgGUIVertexBuffer * GetVertexBufferPtr();
		RgGUIVertexBuffer * GetTextBufferPtr();
		RgGUIIndicesBuffer * GetIndicesBufferPtr();

	private:
		bool _GroupClip(RgVec2& pos, RgVec2& sz) const;
		const RgVec2 _GetWindowSize() const;
		const RgVec4 _GetGroupRect() const;
		void _drawRect(const RgVec2& lp, const RgVec2& sz,const RgVec4& color);

		

	private:
		RgGUIContext(const RgGUISettings& settings);
		RgGUIContext();
		~RgGUIContext();

		RgGUIContext(const RgGUIContext&) = delete;
		RgGUIContext& operator=(const RgGUIContext&) = delete;

		bool m_bDirty = false;

		RgGUIState m_state;
		RgGUIStateWindow m_stateWindow;
		RgGUIStateContextMenu m_stateContxtMenu;


		RgGUIVertexBuffer * m_pBufferVertex = nullptr;
		RgGUIVertexBuffer * m_pBufferText = nullptr;
		RgGUIIndicesBuffer * m_pBufferIndices = nullptr;

		const RgWindowInput * m_pWindowInput = nullptr;

		RgGUIStyle m_style;
		RgGUIGlyph * m_pGlyph = nullptr;

	public:
		friend class RgGUI;
		friend struct RgGUIStateWindow;
	};
}