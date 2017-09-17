cbuffer ConstBuffer:register(b0)
{
	float4 Color;
	float4x4 Mtx;
};

struct PixelInput
{
	float4 position:SV_POSITION;
	float c : TEXCOORD0;
};

float4 main(PixelInput i):SV_TARGET
{
	float4 col = Color;
	return col;
}