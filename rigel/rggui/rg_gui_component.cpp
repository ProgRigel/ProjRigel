#include "rggui.h"
#include "rg_gui_component.h"

namespace rg {


	void RgGUIMenuItemList::AddMenuItem(const RgGUIMenuItem & item)
	{
		subitems.push_back(item);
	}


}
