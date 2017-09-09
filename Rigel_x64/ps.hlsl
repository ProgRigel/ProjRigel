struct PixelInput
{
	float4 position:SV_POSITION;
};

float4 main(PixelInput i):SV_TARGET
{
	float4 col = float4(0.2,0.4,0.8,1.0);
	return col;
}