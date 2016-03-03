#pragma once
#include"Singleton.h"

class ResultData
{

private:
	
	int LifePointCounter;
	int SoumatouCounter;

public:

	int LifePointGet();
	int SoumatouCountGet();
	void LifePointSet(int);
	void SoumatouCountSet(int);

	void Reset();

	ResultData();
	~ResultData();
};

