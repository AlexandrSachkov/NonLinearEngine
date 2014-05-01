cbuffer cbPerObject
{
	float4x4 WVP;
};


float4 VSMain(float4 inPos : POSITION) : SV_POSITION
{
	return mul(inPos, WVP);
}