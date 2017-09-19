cbuffer ConstBuffer:register(b0)
{
	float4 Color;
	float4x4 Mtx;
};

struct PixelInput
{
	float4 position:SV_POSITION;
	float4 color : COLOR0;
};

float4 main(PixelInput i):SV_TARGET
{
	return float4(i.color.xyz,1.0);
}