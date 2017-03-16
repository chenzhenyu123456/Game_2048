#ifndef __GAME_OVER_H__
#define __GAME_OVER_H__

#include "cocos2d.h"

class GameOver : public cocos2d::LayerColor
{
public:
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameOver);

	cocos2d::LabelTTF *gameOverLabel;
};

#endif // __GAME_OVER_H__
