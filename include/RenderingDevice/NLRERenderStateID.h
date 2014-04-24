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
		DeferredGBuff_TextNormal_BlinnPhong
	};

	enum PS
	{
		DeferredGBuff_TextNormal_BlinnPhong
	};

	
}


#endif