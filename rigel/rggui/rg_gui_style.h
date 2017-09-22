#pragma once
#include <rgcore\rg_math.h>
namespace rg {

	

	//flat ui colors http://flatuicolors.com/
	class RgGUIColors{
	public:
		static const RgVec4<RgFloat> Wetasphalt;	//dark
		static const RgVec4<RgFloat> MidnightBlue;
		static const RgVec4<RgFloat> Concrete;	//grey
		static const RgVec4<RgFloat> Asbestos;
		static const RgVec4<RgFloat> Amethyst;	//purpe
		static const RgVec4<RgFloat> Wisteria;
		static const RgVec4<RgFloat> Clouds;		//white
		static const RgVec4<RgFloat> Sliver;
		static const RgVec4<RgFloat> PeterRiver;	//blue
		static const RgVec4<RgFloat> BelizeHole;
		static const RgVec4<RgFloat> Alizarin;	//red
		static const RgVec4<RgFloat> Pomegranate;
		static const RgVec4<RgFloat> Emerald;	//green
		static const RgVec4<RgFloat> Nephritis;
		static const RgVec4<RgFloat> Carrot;		//orange
		static const RgVec4<RgFloat> Pumpkin;
		static const RgVec4<RgFloat> Turquoise;	//cyan
		static const RgVec4<RgFloat> GreenSea;
		static const RgVec4<RgFloat> SunFlower;	//yello
		static const RgVec4<RgFloat> Orange;
		static const RgVec4<RgFloat> White;
		static const RgVec4<RgFloat> Black;
	};



	struct RgGUIStyle
	{
		RgVec4<RgFloat> ColorBg = RgGUIColors::MidnightBlue;
		RgVec4<RgFloat> ColorFont = RgGUIColors::White;
	};
}