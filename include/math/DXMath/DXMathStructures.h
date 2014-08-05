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

#ifndef DX_MATH_STRUCTURES_
#define DX_MATH_STRUCTURES_

typedef DirectX::XMFLOAT2		NLE_FLOAT2;
typedef DirectX::XMFLOAT2A		NLE_FLOAT2A;
typedef DirectX::XMFLOAT3		NLE_FLOAT3;
typedef DirectX::XMFLOAT3A		NLE_FLOAT3A;
typedef DirectX::XMFLOAT3X3		NLE_FLOAT3X3;
typedef DirectX::XMFLOAT4		NLE_FLOAT4;
typedef DirectX::XMFLOAT4A		NLE_FLOAT4A;
typedef DirectX::XMFLOAT4X3		NLE_FLOAT4X3;
typedef DirectX::XMFLOAT4X3A	NLE_FLOAT4X3A;
typedef DirectX::XMFLOAT4X4		NLE_FLOAT4X4;
typedef DirectX::XMFLOAT4X4A	NLE_FLOAT4X4A;
typedef DirectX::XMINT2			NLE_INT2;
typedef DirectX::XMINT3			NLE_INT3;
typedef DirectX::XMINT4			NLE_INT4;

typedef DirectX::XMMATRIX		NLE_MATRIX;
typedef DirectX::FXMMATRIX		NLE_FMATRIX;
typedef DirectX::CXMMATRIX		NLE_CMATRIX;

typedef DirectX::XMUINT2		NLE_UINT2;
typedef DirectX::XMUINT3		NLE_UINT3;
typedef DirectX::XMUINT4		NLE_UINT4;

typedef DirectX::XMVECTOR		NLE_VECTOR;
typedef DirectX::FXMVECTOR		NLE_FVECTOR;
typedef DirectX::GXMVECTOR		NLE_GVECTOR;
typedef DirectX::HXMVECTOR		NLE_HVECTOR;
typedef DirectX::CXMVECTOR		NLE_CVECTOR;

#if defined(_XM_VECTORCALL_)
#define _NLE_CALLCONV_ __vectorcall
#else
#define _NLE_CALLCONV_ __fastcall
#endif

#endif