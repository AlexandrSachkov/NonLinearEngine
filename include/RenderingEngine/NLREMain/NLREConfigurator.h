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

#if defined(NLRE_CONFIGURATOR_) || defined (NLE_CONFIGURATOR_)
#else
#define NLRE_CONFIGURATOR_



/*
	Platform
	1. Windows Vista:				_WINDOWS_VISTA_
	2. Windows 7:					_WINDOWS_7_
	3. Windows 8:					_WINDOWS_8_
	4. Windows 8.1:					_WINDOWS_8_1_
*/
#define _WINDOWS_7_

/*
	Graphics API
	1. DirectX 11:					_DX11_
*/
#define _DX11_	

/*
	Task Management
	1. Parallel Patterns Library:	_PPL_
	2. Threading Building Blocks:	_TBB_			<= Unsupported
*/

#define _PPL_

/*
	SIMD Math library:
	1. DirectX Math:				_DXMATH_
*/
#define _DXMATH_

/*
	SIMD Collision Library:
	1. DirectX Collision			_DXCOLLISION_
*/
#define _DXCOLLISION_

/*
	Log message character max size
*/
#define _LOG_MSG_MAX_SIZE	256

#endif