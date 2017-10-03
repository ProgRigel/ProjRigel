#include "rggui.h"
#include "rg_gui_state.h"
#include "rg_gui_context.h"
#include "rg_gui_draw_buffer.h"
namespace rg {

#pragma region state
	void RgGUIState::PorcessEvent(const RgWindowInput * input)
	{
		WindowGroupRect.z = input->WindowRect.z;
		WindowGroupRect.w = input->WindowRect.w;

		//events
		eventMouseLeftDown = false;
		eventMouseLeftUp = false;

		switch (eventType)
		{
		case rg::RgWindowEventType::None:
			break;
		case rg::RgWindowEventType::Close:
			break;
		case rg::RgWindowEventType::Focus:
			break;
		case rg::RgWindowEventType::LostFocus:
			break;
		case rg::RgWindowEventType::MouseEvent:
			eventMouseLeftDown = input->LButton;
			eventMouseLeftUp = !input->LButton;

			if (eventMouseLeftDown) RgLogD() << "mouse down";
			if (eventMouseLeftUp) RgLogD() << "mouse up";

			break;
		case rg::RgWindowEventType::MouseMove:
			switch (eventDragState)
			{
			case 0:
				if (input->LButton) {
					eventDragState = 1;
					evemtDragStartPos = input->MousePos;
				}
				break;
			case 1:
				eventDragState = 2;
				//RgLogD() << "drag start";
				break;
			case 2:
				if (!input->LButton) {
					eventDragState = 3;
					eventDragEndPos = input->MousePos;
					//RgLogD() << "drag end";
					break;
				}
				eventDragOffsetPos = input->MousePos - eventMousePos;
				//RgLogD() << "drag move";
				break;
			case 3:
				eventDragState = 0;
				break;
			}
			break;
		case rg::RgWindowEventType::MouseWheelEvent:
			break;
		case rg::RgWindowEventType::KeyEvent:
			break;
		case rg::RgWindowEventType::BeginDrag:
			break;
		case rg::RgWindowEventType::EndDrag:
			break;
		case rg::RgWindowEventType::ResizeEnter:
			break;
		case rg::RgWindowEventType::ResizeExit:
			break;
		case rg::RgWindowEventType::Resize:
			break;
		default:
			break;
		}


		eventMousePos = input->MousePos;
		eventMouseLeftButton = input->LButton;
		eventUsed = false;
	}
	void RgGUIState::DrawOrderIncreae()
	{
		currentDrawOrder += 0.0001f;
	}

	void RgGUIState::ResetDrawOrder()
	{
		currentDrawOrder = 0.0f;
	}


#pragma endregion




#pragma region stateWindow
	RgGUIWindow * RgGUIStateWindow::GetWindow(long winid)
	{
		auto iter = windowMap.find(winid);
		if (iter == windowMap.end()) return nullptr;
		return (*iter).second;
	}
	void RgGUIStateWindow::DrawWindow(RgGUIWindow * window, RgGUIContext * ctx)
	{
		window->_buffer_vertex_begin = ctx->GetVertexBufferPtr()->GetVertexSize();
		window->_buffer_text_begin = ctx->GetTextBufferPtr()->GetVertexSize();

		window->_ondraw = true;
		stateWindowOrder = (float)window->order;

		auto& winrect = window->windowrect;
		auto& style = ctx->m_style;
		auto& state = ctx->m_state;

		window->_windowrectNext = winrect;

		ctx->GUIGroupBegin(winrect.xy(), winrect.zw());
		//--------- begin window frame draw ---------//

		//event
		RgVec2 winpos = winrect.xy();

		//windowmove
		if (window->_onWindowMove) {
			if (state.eventDragState == 2) {
				window->_windowrectNext.setxy(winpos + state.eventDragOffsetPos);
			}
			else if (state.eventDragState == 3) {
				window->_onWindowMove = false;
			}
			
			ctx->UtilEventUse();
		}
		else {
			RgVec4 windowMoveStartRect = RgVec4(winpos, RgVec2(winrect.z, style.WindowHeaderHeight));
			if (ctx->UtilMouseDrag(windowMoveStartRect)) {
				RgLogD() << "drag";
				window->_onWindowMove = true;
				window->_onWindowMoveRectStart = windowMoveStartRect;

				ctx->UtilEventUse();
			}
		}

		//windowResize
		if (window->_onWindowResize) {
			if (state.eventDragState == 2) {
				RgLogD() << "resize";
				window->_windowrectNext.w +=state.eventDragOffsetPos.y;
			}
			else if (state.eventDragState == 3) {
				window->_onWindowResize = false;
				RgLogD() << "resize end";
			}
			ctx->UtilEventUse();
		}
		else
		{
			RgVec4 resizerect = winrect;
			resizerect.y += winrect.w - 5;
			resizerect.w = 9;
			if (ctx->UtilMouseDrag(resizerect)) {
				window->_onWindowResize = true;
				window->_onWindowResizeMode = 1;
				RgLogD() << "on resize";
			}
			ctx->UtilEventUse();
		}

		//Background
		ctx->GUIRect(RgVec2::Zero, winrect.zw(), style.WindowBackgroundColor);
		//Header

		ctx->GUIRect(RgVec2::Zero, RgVec2(winrect.z, style.WindowHeaderHeight), style.WindowHeaderColor);
		//Header-Title
		ctx->GUIText(window->title, RgVec4(5.0f, 0.0f, 200.0f, 30.0f), style.WindowHeaderTitleColor);




		//content group
		ctx->GUIGroupBegin(RgVec2(0.0f, style.WindowHeaderHeight), RgVec2(winrect.z, winrect.w - style.WindowHeaderHeight));

		//--------- end window frame draw ---------//
	}
	void RgGUIStateWindow::DrawWindowEnd(RgGUIWindow * window, RgGUIContext * ctx)
	{
		ctx->GUIGroupEnd();		//end content group
		ctx->GUIGroupEnd();		//end window group
		ctx->_DrawBorder(window->windowrect.xy(), window->windowrect.zw(), ctx->m_style.WindowBorderColor, 1.0f, ctx->_GetDrawOrder());	//drawborder

																								//event
		window->windowrect = window->_windowrectNext;
		window->RestrictWindow();

		window->_ondraw = false;
		window->_buffer_vertex_end = ctx->GetVertexBufferPtr()->GetVertexSize();
		window->_buffer_text_end = ctx->GetTextBufferPtr()->GetVertexSize();
	}
	void RgGUIStateWindow::GUIBegin(const RgGUIState & state, RgGUIContext * ctx)
	{
		//check whether to skip draw
		skipDraw = false;

		if (IsSkipUpdate(state)) {
			skipDraw = true;
			return;
		}
		//caculate focused window;
		RgGUIWindow * newfocusedWin = nullptr;
		long maxorder_focused = -1;		//maxorder of current mouseovered window
		long maxorder_window = -1;		//maxorder of all windows
		for (auto pair : windowMap) {
			auto win = pair.second;
			maxorder_window = (win->order > maxorder_window ? win->order : maxorder_window);
			if (!state.eventMouseLeftDown || win->windowrect.rect_contain(state.eventMousePos) == false) continue;
			if (win->order <= maxorder_focused) continue;
			maxorder_focused = win->order;
			win->_isfocused = true;
			if (newfocusedWin != nullptr) {
				newfocusedWin->_isfocused = false;
			}
			newfocusedWin = win;
		}

		if (newfocusedWin == nullptr) {
			//skip unfocus any window
			//if (windowFocused != nullptr) {
			//	windowFocused->_isfocused = false;
			//	windowFocused = nullptr;
			//}
		}
		else {
			if (windowFocused != nullptr) {
				windowFocused->_isfocused = false;

				if (newfocusedWin->order < windowFocused->order) {
					newfocusedWin->order = windowFocused->order + 1;
				}
				windowFocused = newfocusedWin;
				windowFocused->_isfocused = true;
			}
			else
			{
				windowFocused = newfocusedWin;
				windowFocused->_isfocused = true;
				windowFocused->order = maxorder_window + 1;
			}
		}

		if (windowFocused == nullptr) {
			return;
		}

		// every frame will draw focused window and new window
		// so remove lastfocusedWindows's buffer data and
		// set the PtrFloater to the end of the vertex buffer

		auto bufferPtr_vertex = ctx->GetVertexBufferPtr();
		auto windowFocusedSize_vertex = windowFocused->_buffer_vertex_end - windowFocused->_buffer_vertex_begin;
		auto moveBufferOffset_vertex = bufferPtr_vertex->GetVertexSize() - windowFocused->_buffer_vertex_end;

		auto bufferPtr_text = ctx->GetTextBufferPtr();
		auto windowFocusedSize_text = windowFocused->_buffer_text_end - windowFocused->_buffer_text_begin;
		auto moveBufferOffset_text = bufferPtr_text->GetVertexSize() - windowFocused->_buffer_text_end;

		//buffer vertex
		{
			if (moveBufferOffset_vertex > 0) {
				auto movebufferBegin = bufferPtr_vertex->GetPtr() + windowFocused->_buffer_vertex_begin;
				auto movebufferEnd = bufferPtr_vertex->GetPtr() + windowFocused->_buffer_vertex_end;
				memmove(movebufferBegin, movebufferEnd, moveBufferOffset_vertex * sizeof(RgGUIVertex));

				//reset all window bufferpos
				for (auto pair : windowMap) {
					auto win = pair.second;
					if (win == nullptr) {
						RgLogE() << "window null";
						continue;
					}
					if (win->_buffer_vertex_begin >= windowFocused->_buffer_vertex_end) {
						win->_buffer_vertex_begin -= windowFocusedSize_vertex;
						win->_buffer_vertex_end -= windowFocusedSize_vertex;
					}
				}
			}

			bufferPtr_vertex->ptrFloater -= windowFocusedSize_vertex;
			//RgLogD() << "buffersize" << bufferPtr_vertex->GetVertexSize();
		}

		//buffer text
		{
			if (moveBufferOffset_text > 0) {
				auto movebufferBegin = bufferPtr_text->GetPtr() + windowFocused->_buffer_text_begin;
				auto movebufferEnd = bufferPtr_text->GetPtr() + windowFocused->_buffer_text_end;
				memmove(movebufferBegin, movebufferEnd, moveBufferOffset_text * sizeof(RgGUIVertex));

				//reset all window bufferpos
				for (auto pair : windowMap) {
					auto win = pair.second;
					if (win == nullptr) {
						RgLogE() << "window null";
						continue;
					}
					if (win->_buffer_text_begin >= windowFocused->_buffer_text_end) {
						win->_buffer_text_begin -= windowFocusedSize_text;
						win->_buffer_text_end -= windowFocusedSize_text;
					}
				}
			}

			bufferPtr_text->ptrFloater -= windowFocusedSize_text;
		}
	}

	bool RgGUIStateWindow::GUIEnd(const RgGUIState & state, RgGUIContext * ctx)
	{
		if (skipDraw) {
			return false;
		}

		return true;
	}

	void RgGUIStateWindow::register_win(RgGUIWindow* win)
	{
		if (win == nullptr) return;

		int ordernext = 0;

		if (windowMap.size() > 0) {
			auto iter = windowMap.end();
			iter--;
			ordernext = (*iter).second->order + 1;
		}
		win->order = ordernext;
		windowMap.insert(std::make_pair(win->winid, win));
	}

	bool RgGUIStateWindow::verify_valid(long winid)
	{
		if (skipDraw) return false;
		auto iter = windowMap.find(winid);
		if (iter == windowMap.end()) {
			RgLogE() << "window check focused error";
			return false;
		}
		return (*iter).second->_isfocused;
	}
	bool RgGUIStateWindow::IsSkipUpdate(const RgGUIState & state) const
	{
		if (state.eventMouseLeftDown || state.eventMouseLeftUp || state.eventDragState > 0) {
			return false;
		}
		return true;
	}
#pragma endregion
}