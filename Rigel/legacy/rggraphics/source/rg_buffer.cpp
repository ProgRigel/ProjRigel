#include "rggraphics.h"
#include "rg_buffer.h"

namespace rg {

	RgBuffer::RgBuffer()
	{
	}

	RgBuffer::~RgBuffer()
	{
	}

	RgBuffer::RgBuffer(RgBufferSettings setting)
	{
		m_setting = setting;
	}

	RgBufferSettings & RgBuffer::GetSettings()
	{
		return m_setting;
	}

}
