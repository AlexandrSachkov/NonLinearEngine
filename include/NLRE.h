#ifndef NLRE_
#define NLRE_

class NLRE
{
public:
	NLRE();
	~NLRE();

	void registerDebugCallback			(void(*callback)(char msg[]));
	void registerConsoleCallback		(void(*callback)(char msg[]));
	void registerErrorCallback			(void(*callback)(NLRE_Log::ErrorFlag,char msg[]));

	void unregisterDebugCallback		(void(*callback)(char msg[]));
	void unregisterConsoleCallback		(void(*callback)(char msg[]));
	void unregisterErrorCallback		(void(*callback)(NLRE_Log::ErrorFlag,char msg[]));

	void unregisterDebugCallbackAll		();
	void unregisterConsoleCallbackAll	();
	void unregisterErrorCallbackAll		();
private:
	
};
#endif