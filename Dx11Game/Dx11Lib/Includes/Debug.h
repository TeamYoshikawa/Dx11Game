#ifndef _DEBUGLOG_ 
#define _DEBUGLOG_

#define DebugLog(lpszformat, ...) Debug::GetInstance().Log(__FUNCTION__,lpszformat,__VA_ARGS__)

#include<fstream>
#include<windows.h>


class Debug{
private:
	Debug() = default;
	~Debug() = default;
	static FILE *fp;

public:
	Debug(const Debug&) = delete;
	Debug& operator=(const Debug) = delete;

	static Debug& GetInstance();
	static bool Create();
	static bool Destroy();

	void Log(char *,char *, ...);

private:
	static Debug* debuglog;
};


#endif