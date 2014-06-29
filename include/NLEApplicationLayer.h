#ifndef NLE_APPLICATION_LAYER_
#define NLE_APPLICATION_LAYER_

class NLE;

class NLEApplicationLayer
{
public:

	NLEApplicationLayer(HINSTANCE hInstance, NLE* nle);
	NLEApplicationLayer(const NLEApplicationLayer& other);
	~NLEApplicationLayer();

	static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static void debugCallback(char text[]);
	static void consoleCallback(char text[]);
	static void errorCallback(NLE_Log::ErrorFlag flag, char text[]);
	
	void displayErrorBox(std::wstring title, std::wstring message);

	NLEWindowReference& getWindowReference();
	int getScreenWidth();
	int getScreenHeight();
	void updateScreenDimensions();

	int getClientWidth();
	int getClientHeight();
	void updateClientDimensions();

	void setCursorPosition(float x, float y);

	int runMessageLoop();

private:
	bool initialize();
	bool initializeWindow();

	HINSTANCE _hInstance;
	NLE* _nle;
	
	HWND _hwnd;
	int _screenWidth;
	int _screenHeight;
	int _clientWidth;
	int _clientHeight;
};

#endif