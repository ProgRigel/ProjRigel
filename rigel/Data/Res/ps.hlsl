cbuffer ConstBuffer:register(b0)
{
	float4 Ccolor;
};

struct PixelInput
{
	float4 position:SV_POSITION;
};

float4 main(PixelInput i):SV_TARGET
{
	float4 col = Ccolor;
	return col;
}