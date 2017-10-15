#include "rggraphics.h"
#include "rg_inputlayout.h"

rg::RgInputLayout::RgInputLayout(const RgInputLayoutElement * elements, const unsigned size)
{
	for (size_t i = 0; i < size; i++)
	{
		Elements.push_back(elements[i]);
	}
}

rg::RgInputLayout::~RgInputLayout()
{
	std::vector<RgInputLayoutElement>().swap(Elements);
}
