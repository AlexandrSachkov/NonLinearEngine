#ifndef NLRE_CONFIGURATOR_
#define NLRE_CONFIGURATOR_

/*
	Rendering Device
	1. DirectX 11:					_DX11
	2. OpenGl 4.2:					_OPENGL4.2		<= Unsupported
*/
#define _DX11	

/*
	Task Management
	1. Parallel Patterns Library:	_PPL
	2. Threading Building Blocks:	_TBB			<= Unsupported
*/
#define _PPL

/*
	SIMD Math library:
	1. DirectX Math:				_DXMATH
*/
#define _DXMATH

/*
	SIMD Collision Library:
	1. DirectX Collision			_DXCOLLISION
*/
#define _DXCOLLISION

#endif