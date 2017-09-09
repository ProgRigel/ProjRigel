struct VertexInput
{
	float2 position:POSITION;
};

struct PixelInput
{
	float4 position:SV_POSITION;
	float2 uv:TEXCOORD0;
	float4 color :COLOR;
};


PixelInput main(VertexInput v)
{
	PixelInput o;

	//o.position = float4(v.position, 0.5, 1.0);

	o.color = v.color;
	o.uv = v.uv;
	o.position = mul(worldMatrix,float4(v.position.xy,0,1.0f));
	//o.position = mul(o.position, viewMatrix);
	//o.position = mul(o.position, projectionMatrix);

	return o;
}