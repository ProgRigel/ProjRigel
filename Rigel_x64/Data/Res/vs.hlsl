cbuffer ConstBuffer:register(b0)
{
	float4 Color;
	float3x3 Mtx;
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
	float3 vpos = v.position.xyz;
	vpos.z = 1.0;
	float3x3 mtx = float3x3(0.0025,0,0,
		0,-0.003333,0,
		-1,1.0,1
		);
	float3 pos = vpos;
	pos = mul(pos, mtx);
	o.position = float4(pos.xy, 0, 1.0);
	return o;
}