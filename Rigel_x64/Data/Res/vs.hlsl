


struct VertexInput
{
	float2 position:POSITION;
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