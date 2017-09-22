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
			ctx->GUIGroupBegin(RgVec4(10, 10, 80, 40), RgGUIColors::BelizeHole);
			ctx->GUIGroupEnd();

			ctx->GUIGroupBegin(RgVec4(40, 70, 80, 40), RgGUIColors::Pumpkin);
			ctx->GUIGroupEnd();

			ctx->GUIGroupEnd();
		}
		
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
		

		ctx->EndGUI();


	}
	void EditorGUI::OnRender()
	{
		m_pBindGraphics->OnRender();
	}
}


