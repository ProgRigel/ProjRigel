cbuffer ConstBuffer:register(b0)
{
	float4 Color;
	float4x4 Mtx;
};

struct PixelInput
{
	float4 position:SV_POSITION;
	float4 color : COLOR0;
	float2 uv:TEXCOORD0;
};

sampler TextureSampler;

float4 main(PixelInput i):SV_TARGET
{
	float4 color = tex2D(TextureSampler,i.uv);
	return color;
}