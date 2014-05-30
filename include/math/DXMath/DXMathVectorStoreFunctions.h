/*
-----------------------------------------------------------------------------
This source file is part of NLRE
(NonLinear Rendering Engine)
For the latest info, see https://github.com/AlexandrSachkov/NonLinearRenderingEngine

Copyright (c) 2014 NonLinear Rendering Engine Team

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

#ifndef DX_MATH_VECTOR_STORE_FUNCTIONS_
#define DX_MATH_VECTOR_STORE_FUNCTIONS_

namespace NLEMath
{
	void _NLE_CALLCONV_ NLEStoreFloat3(NLE_FLOAT3* destination, NLE_FVECTOR v);
	void _NLE_CALLCONV_ NLEStoreFloat3A(NLE_FLOAT3A* destination, NLE_FVECTOR v);
	void _NLE_CALLCONV_ NLEStoreFloat4(NLE_FLOAT4* destination, NLE_FVECTOR v);
	void _NLE_CALLCONV_ NLEStoreFloat4A(NLE_FLOAT4A* destination, NLE_FVECTOR v);
	void _NLE_CALLCONV_ NLEStoreFloat3x3(NLE_FLOAT3X3* destination, NLE_FMATRIX v);
	void _NLE_CALLCONV_ NLEStoreFloat4x4(NLE_FLOAT4X4* destination, NLE_FMATRIX v);
	void _NLE_CALLCONV_ NLEStoreFloat4x4A(NLE_FLOAT4X4A* destination, NLE_FMATRIX v);
}
#include "math\DXMath\DXMathVectorStoreFunctions.inl"
#endif