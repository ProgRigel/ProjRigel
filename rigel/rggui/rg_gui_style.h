#pragma once
#include <rgcore\rg_math.h>
namespace rg {

	struct RgGUIStyle
	{
		RgVec4 ColorBg = RgGUIColors::MidnightBlue;
		RgVec4 ColorFont = RgGUIColors::White;
	};

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

	const RgVec4 RgGUIColors::White = RgVec4(1, 1, 1, 1);
	const RgVec4 RgGUIColors::Black = RgVec4(0, 0, 0, 1);

	const RgVec4 RgGUIColors::Wetasphalt = RgVec4(0.2039216f, 0.2862745f, 0.3686275f, 1.0f);
	const RgVec4 RgGUIColors::MidnightBlue = RgVec4(0.172549f, 0.2431373f, 0.3137255f, 1.0f);
	const RgVec4 RgGUIColors::Concrete = RgVec4(0.5843138f, 0.6470588f, 0.6509804f, 1.0f);
	const RgVec4 RgGUIColors::Asbestos = RgVec4(0.4980392f, 0.5490196f, 0.5529412f, 1.0f);
	const RgVec4 RgGUIColors::Amethyst = RgVec4(0.6078432f, 0.3490196f, 0.7137255f, 1.0f);
	const RgVec4 RgGUIColors::Wisteria = RgVec4(0.5568628f, 0.2666667f, 0.6784314f, 1.0f);
	const RgVec4 RgGUIColors::Clouds = RgVec4(0.9254902f, 0.9411765f, 0.945098f, 1.0f);
	const RgVec4 RgGUIColors::Sliver = RgVec4(0.7411765f, 0.7647059f, 0.7803922f, 1.0f);
	const RgVec4 RgGUIColors::PeterRiver = RgVec4(0.2039216f, 0.5960785f, 0.8588235f, 1.0f);
	const RgVec4 RgGUIColors::BelizeHole = RgVec4(0.1607843f, 0.5019608f, 0.7254902f, 1.0f);
	const RgVec4 RgGUIColors::Alizarin = RgVec4(0.9058824f, 0.2980392f, 0.2352941f, 1.0f);
	const RgVec4 RgGUIColors::Pomegranate = RgVec4(0.7529412f, 0.2235294f, 0.1686275f, 1.0f);
	const RgVec4 RgGUIColors::Emerald = RgVec4(0.1803922f, 0.8f, 0.4431373f, 1.0f);
	const RgVec4 RgGUIColors::Nephritis = RgVec4(0.1529412f, 0.682353f, 0.3764706f, 1.0f);
	const RgVec4 RgGUIColors::Carrot = RgVec4(0.9019608f, 0.4941176f, 0.1333333f, 1.0f);
	const RgVec4 RgGUIColors::Pumpkin = RgVec4(0.827451f, 0.3294118f, 0.0f, 1.0f);
	const RgVec4 RgGUIColors::Turquoise = RgVec4(0.1019608f, 0.7372549f, 0.6117647f, 1.0f);
	const RgVec4 RgGUIColors::GreenSea = RgVec4(0.08627451f, 0.627451f, 0.5215687f, 1.0f);
	const RgVec4 RgGUIColors::SunFlower = RgVec4(0.945098f, 0.7686275f, 0.05882353f, 1.0f);
	const RgVec4 RgGUIColors::Orange = RgVec4(0.9529412f, 0.6117647f, 0.07058824f, 1.0f);
}