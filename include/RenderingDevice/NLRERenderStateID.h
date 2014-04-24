#ifndef NLRE_RENDER_STATE_ID_
#define NLRE_RENDER_STATE_ID_

namespace NLRE_RenderStateId
{
	
	enum Usage
	{
		DEFAULT,
		IMMUTABLE,
		DYNAMIC,
		STAGING
	};

	enum BufferType
	{
		UNKNOWN,
		CONSTANT,
		INDEX,
		VERTEX
	};

	enum PipelineStage
	{
		VShader,
		PShader,
		GShader
	};

	enum VS
	{
		VS_DeferredGBuff_TextNormal_BlinnPhong
	};

	enum PS
	{
		PS_DeferredGBuff_TextNormal_BlinnPhong
	};

	enum IL
	{

	};
}


#endif