#ifndef _Main_Menu_h_
#define _Main_Menu_h_

#include <iostream>
#include "CrossApp.h"

USING_NS_CC;

class MainMenu:public CATabBarController
{
public:
	MainMenu();
	virtual ~MainMenu();
	static CAWindow* createWindow();

protected:
	virtual void viewDidLoad();
	virtual void viewDidUnload();

};

#endif