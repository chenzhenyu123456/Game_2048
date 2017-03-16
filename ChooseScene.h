#ifndef __CHOOSESCENE_SCENE_H__  
#define __CHOOSESCENE_SCENE_H__  

#include "cocos2d.h"  
#include "CardSprite.h"  

class ChooseScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(ChooseScene);

private:
	cocos2d::LabelTTF *labelTTFCardNumber;
};

#endif // __CHOOSESCENE_SCENE_H__ 