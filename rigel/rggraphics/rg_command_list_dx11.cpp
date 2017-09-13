#include "rggraphics.h"
#include "rg_command_list_dx11.h"

namespace rg {
	rg::RgCommandListDX11::RgCommandListDX11()
	{
	}
	RgCommandListDX11::~RgCommandListDX11()
	{
		delete m_pCommandList;
		m_pCommandList = nullptr;
	}
}

