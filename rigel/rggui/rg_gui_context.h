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

#include "rg_gui_state.h"
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
		void GUIBegin(const RgWindowEvent&);
		void GUIEnd();
		

		bool Clip(const RgVec4& rect, RgVec2& pos, RgVec2& sz) const;

		void RestoreColor(const RgVec4& tempcolor);
		void RestoreColor();
		void DropColor();
		
		////////////////////////
		void GUIText(std::string content, const RgVec4& rect);
		const RgVec2 GUIText(const char& c, const RgVec4& rect);
		void GUITextDebug(const RgVec4& rect);

		void GUIMenuBarBegin(const RgVec4& rect);
		void GUIMenuBarEnd();
		bool GUIMenuItem(RgFloat width);
		void GUIMenuListBegin(RgStr label,RgFloat width);
		void GUIMenuListEnd();

		void GUIMenuBar(const RgGUIGenericMenu * _menu, const RgVec4& _rect);

		////////////////////////////////// new
		bool GUIWindowBegin(RgGUIWindow* win);//return true if focused
		void GUIWindowEnd();

		void GUIRect(const RgVec2&lp, const RgVec2&sz, const RgVec4& color);

		const RgVec2 GUIChar(const char& c, const RgVec4& rect, const RgVec4& color);
		void GUIText(std::string str, const RgVec4& rect, const RgVec4& color);

		void GUIGroupBegin(const RgVec2&lp, const RgVec2&sz);
		void GUIGroupEnd();

		//state
		void SetColor(RgVec4 color);

		RgImage * GetFontImage();

		//buffer
		RgGUIVertexBuffer * GetVertexBufferPtr();
		RgGUIVertexBuffer * GetTextBufferPtr();
		RgGUIIndicesBuffer * GetIndicesBufferPtr();

		//utility
		bool UtilIsInGroup() const;
		bool UtilClipRect(RgVec4& content, const RgVec4& rect) const;		//return false is no need to draw
		const RgVec4 UtilGetOriginRect(const RgVec4& rect) const;
		const RgVec2 UtilGetOriginPos(const RgVec2& lp) const;
		int UtilGetHash(RgStr label, const RgGUIControllerType type, const RgVec4& rect);

		bool UtilRectContain(const RgVec4& rect, const RgVec2& pos);
		bool UtilRectContain(const RgVec2& lp, const RgVec2&sz, const RgVec2& pos);
		
		unsigned char UtilMouseDrag(const RgVec2& lp, const RgVec2& sz);
		unsigned char UtilMouseDrag(const RgVec4& rect);

		void UtilEventUse();
		bool UtilIsEventUsed() const;


	private:
		bool _GroupClip(RgVec2& pos, RgVec2& sz) const;
		const RgVec2 _GetWindowSize() const;
		const RgVec4 _GetGroupRect() const;
		const RgFloat _GetDrawOrder();

		void _DrawRect(const RgVec2& lp, const RgVec2& sz,const RgVec4& color,RgFloat order);
		void _GroupBegin(const RgVec2&lp, const RgVec2& sz);
		void _GroupEnd();

		const RgVec2 _DrawChar(const char& c, const RgVec4& rect, const RgVec4& color, RgFloat order);
		void _DrawText(std::string content, const RgVec4& rect,const RgVec4& color,RgFloat order);
		void _DrawLineAxis(const RgVec2& from, const RgVec2& to, const RgVec4& color, RgFloat width,RgFloat order);
		void _DrawBorder(const RgVec2& lp, const RgVec2& sz, const RgVec4& color,RgFloat width, RgFloat order);

		

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