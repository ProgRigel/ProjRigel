


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
	o.position = float4(v.position.xy, 0, 1.0);
	return o;
}