#include "stdafx.h"
#include "editor_gui.h"
#include <rggui\rg_gui.h>
#include <rggui\rg_gui_bind_graphics.h>

using namespace rg;

namespace editor {
	EditorGUI::EditorGUI()
	{
		RgGUI::CreateRgGUIContext(&m_pGUIContext);
	}
	EditorGUI::~EditorGUI()
	{
		Release();
	}
	void EditorGUI::Release()
	{
		if (m_pBindGraphics != nullptr) {
			m_pBindGraphics->Release();
		}
		m_pBindGraphics = nullptr;

		RgGUI::Release(&m_pGUIContext);
		m_pGUIContext = nullptr;
	}
	void EditorGUI::BindGraphics(rg::RgGraphicsContext * graphicsCtx)
	{
		if (m_pBindGraphics != nullptr) {
			m_pBindGraphics->Release();
		}
		m_pBindGraphics = new RgGUIBindGraphics(m_pGUIContext, graphicsCtx);
	}
	void EditorGUI::OnWindowGUI(const rg::RgWindowEvent e)
	{

		auto ctx = m_pGUIContext;

		static bool initResize = false;
		if (e.Type == RgWindowEventType::Resize && initResize) {
			initResize = true;
			return;
		}

		ctx->BeginGUI(e);

		//GUIRect
		{
			ctx->SetColor(RgGUIColors::Concrete);
			ctx->GUIRect(RgVec2(0, 0), RgVec2(40, 30));
		}

		//GUIButton
		{
			ctx->SetColor(RgGUIColors::PeterRiver);
			if (ctx->GUIButton(RgVec2(50, 0), RgVec2(40, 30))) {
				RgLogD() << "GUIButton";
			}
		}
		
		//group
		{
			ctx->GUIGroupBegin(RgVec4(5, 35, 100, 100), RgGUIColors::Orange);

			ctx->GUIRect(RgVec4(0, -10, 30, 30), RgGUIColors::BelizeHole);

			ctx->GUIGroupBegin(RgVec4(50, 5, 100, 40));

			ctx->GUIRect(RgVec4(-15, 10, 30, 30),RgGUIColors::Pomegranate);

			ctx->GUIGroupEnd();

			ctx->GUIGroupEnd();
		}

		//grouped button
		ctx->GUIGroupBegin(RgVec4(230, 5, 100, 100),RgGUIColors::Nephritis);

		ctx->SetColor(RgGUIColors::SunFlower);
		if (ctx->GUIButton(RgVec2(3, 3), RgVec2(50, 30))) {
			RgLogD() << "grouped button";
		}

		ctx->GUIGroupEnd();

		
		//clip
		{
			RgVec4 r1(5, 150, 30, 30);
			RgVec4 r2(25, 170, 30, 30);
			ctx->GUIRect(r1, RgGUIColors::Emerald);
			ctx->GUIRect(r2, RgGUIColors::GreenSea);
			if (ctx->UtilClipRect(r1, r2)) {
				ctx->GUIRect(r1, RgGUIColors::Amethyst);
			}
		}

		//menubar
		{
			ctx->GUIGroupBegin(RgVec4(120, 5, 100, 100),RgGUIColors::Carrot);

			ctx->GUIMenuBarBegin(RgVec4(0, 0, 100, 20));
			if (ctx->GUIMenuItem(20.0f)) {
				RgLogD() << "menubar1 click";
			}
			ctx->SetColor(RgGUIColors::Sliver);
			if (ctx->GUIMenuItem(30.0f)) {
				RgLogD() << "menubar2 click";
			}

			//menuitemlist
			ctx->SetColor(RgGUIColors::Turquoise);
			ctx->GUIMenuListBegin("MenuList",40.0f);


			ctx->GUIMenuListEnd();

			ctx->GUIMenuBarEnd();


			ctx->GUIGroupEnd();
		}
		

		ctx->EndGUI();


	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


