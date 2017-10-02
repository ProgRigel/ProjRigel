#pragma once
#include <rgcore\rg_math.h>
namespace rg {

	

	//flat ui colors http://flatuicolors.com/
	class RgGUIColors{
	public:
		static const RgVec4 Wetasphalt;	//dark
		static const RgVec4 MidnightBlue;
		static const RgVec4 Concrete;	//grey
		static const RgVec4 Asbestos;
		static const RgVec4 Amethyst;	//purpe
		static const RgVec4 Wisteria;
		static const RgVec4 Clouds;		//white
		static const RgVec4 Sliver;
		static const RgVec4 PeterRiver;	//blue
		static const RgVec4 BelizeHole;
		static const RgVec4 Alizarin;	//red
		static const RgVec4 Pomegranate;
		static const RgVec4 Emerald;	//green
		static const RgVec4 Nephritis;
		static const RgVec4 Carrot;		//orange
		static const RgVec4 Pumpkin;
		static const RgVec4 Turquoise;	//cyan
		static const RgVec4 GreenSea;
		static const RgVec4 SunFlower;	//yello
		static const RgVec4 Orange;

		static const RgVec4 White;
		static const RgVec4 Black;
	};



	struct RgGUIStyle
	{
		RgVec4 colorBg = RgGUIColors::MidnightBlue;
		RgVec4 colorFont = RgGUIColors::White;

		//menu
		RgFloat MenuBarHeight = 17.0f;
		RgVec4 MenuBarBackgroudColor = RgGUIColors::BelizeHole;
		RgFloat MenuBarItemWdith = 40.0f;

		//guiwindow
		RgFloat WindowHeaderHeight = 20.0f;
		RgVec4 WindowHeaderColor = RgGUIColors::BelizeHole;
		RgVec4 WindowHeaderTitleColor = RgGUIColors::White;
	};
}