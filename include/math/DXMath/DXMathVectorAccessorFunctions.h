/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 Alexandr Sachkov & NonLinear Engine Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/

#ifndef DX_MATH_VECTOR_ACCESSOR_FUNCTIONS_
#define DX_MATH_VECTOR_ACCESSOR_FUNCTIONS_

namespace NLEMath
{
	float _NLE_CALLCONV_ NLEVectorGetByIndex(NLE_FVECTOR v, size_t i);
	uint32_t _NLE_CALLCONV_ NLEVectorGetIntByIndex(NLE_FVECTOR v, size_t i);
	uint32_t _NLE_CALLCONV_ NLEVectorGetIntW(NLE_FVECTOR v);
	uint32_t _NLE_CALLCONV_ NLEVectorGetIntX(NLE_FVECTOR v);
	uint32_t _NLE_CALLCONV_ NLEVectorGetIntY(NLE_FVECTOR v);
	uint32_t _NLE_CALLCONV_ NLEVectorGetIntZ(NLE_FVECTOR v);
	float _NLE_CALLCONV_ NLEVectorGetW(NLE_FVECTOR v);
	float _NLE_CALLCONV_ NLEVectorGetX(NLE_FVECTOR v);
	float _NLE_CALLCONV_ NLEVectorGetY(NLE_FVECTOR v);
	float _NLE_CALLCONV_ NLEVectorGetZ(NLE_FVECTOR v);
}
#include "Math\DXMath\DXMathVectorAccessorFunctions.inl"
#endif