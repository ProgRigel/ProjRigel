#include "rggui.h"
#include "rg_gui_component.h"

namespace rg {


	void RgGUIMenuItemList::AddMenuItem(const RgGUIMenuItem & item)
	{
		subitems.push_back(item);
	}


	void RgGUIWindow::focused()
	{
		RgLogD() << "guiwin focused " << winid;
	}

	void RgGUIWindow::lost_focuse()
	{
		RgLogD() << "gui lost focuse" << winid;
	}

	RgGUIWindow::RgGUIWindow()
	{
		static long id = 0;
		id++;
		winid = id;
	}

}
