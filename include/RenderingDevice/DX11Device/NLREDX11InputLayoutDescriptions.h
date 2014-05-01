#ifndef NLRE_DX11_INPUT_LAYOUT_DESCRIPTIONS_
#define NLRE_DX11_INPUT_LAYOUT_DESCRIPTIONS_

#include "NLREMain\stdafx.h"

class NLREDX11InputLayoutDescriptions
{
public:
	static const NLRE_APIInputLayoutDecs forwardPosNormTanTextDesc[];
	static const NLRE_APIInputLayoutDecs forwardPosTextDesc[];
	static const NLRE_APIInputLayoutDecs forwardPosDesc[];

	static NLRE_InputLayoutDesc forwardPosNormTanText;
	static NLRE_InputLayoutDesc forwardPosText;
	static NLRE_InputLayoutDesc forwardPos;
};

#endif