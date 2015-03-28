#pragma once

class IInit
{
public:
	virtual void Init() = 0;
	void PreInit();
	void PostInit();

	IInit()
	{

	}
};