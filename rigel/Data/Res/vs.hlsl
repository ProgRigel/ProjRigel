cbuffer ConstBuffer:register(b0)
{
	float4 Color;
	float4x4 Mtx;
};


struct VertexInput
{
	float3 position:POSITION;
	float3 color:COLOR;
	float2 uv:TEXCOORD;
};

struct PixelInput
{
	float4 position:SV_POSITION;
};


PixelInput main(VertexInput v)
{
	PixelInput o;
	float4 vpos = float4(v.position.xyz,1.0);
	vpos = mul(vpos, Mtx);
	vpos.x -= 1.0;
	vpos.y += 1.0;
	o.position = float4(vpos.xy, 0, 1.0);
	return o;
}