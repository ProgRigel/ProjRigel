#include "rggraphics.h"
#include "directx11\rg_command_list_dx11.h"

namespace rg {
	void RgCommandListDX11::Release()
	{
		if (m_pCommandList != nullptr) {
			m_pCommandList->Release();
			m_pCommandList = nullptr;
		}
	}
	rg::RgCommandListDX11::RgCommandListDX11()
	{
	}
	RgCommandListDX11::~RgCommandListDX11()
	{
		Release();
	}
}

