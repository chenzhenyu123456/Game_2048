#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "cocos2d.h"
#include "CardSprite.h"

class MainMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(MainMenu);

private:
	cocos2d::LabelTTF *labelTTFCardNumber;
};

#endif // __MAINMENU_H__
