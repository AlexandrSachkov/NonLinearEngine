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

#ifndef NLRE_SCENE_MANAGER_
#define NLRE_SCENE_MANAGER_

class NLRERenderingDevice;
class NLREDeviceController;
class NLRETextureLoader;
class NLRECamera;

class NLRESceneManager
{
public:
	NLRESceneManager(
		std::shared_ptr<NLREDeviceController> deviceController, 
		std::shared_ptr<NLRERenderingDevice> renderingDevice, 
		std::shared_ptr<NLRETextureLoader> textureLoader,
		int width, 
		int height);
	~NLRESceneManager();

	void NLRESceneManager::printFloat4x4(NLE_FLOAT4X4& matrix);

	void render();
	void addAssets(std::vector<std::shared_ptr<NLRE_RenderableAsset>>& assets);

	void cameraReset();
	void cameraUpdate();

	void cameraRotate(float yaw, float pitch);
	void cameraPitchUp();
	void cameraPitchDown();
	void cameraYawLeft();
	void cameraYawRight();

	void cameraMoveForward();
	void cameraMoveBackward();
	void cameraMoveLeft();
	void cameraMoveRight();
	void cameraMoveUp();
	void cameraMoveDown();

private:
	bool initialize();

	std::shared_ptr<NLREDeviceController> _deviceController;
	std::shared_ptr<NLRERenderingDevice> _renderingDevice;
	std::shared_ptr<NLRETextureLoader> _textureLoader;

	std::shared_ptr<NLRECamera> _activeCamera;
	std::vector<std::shared_ptr<NLRE_RenderableAsset>> _assets;
};

#endif