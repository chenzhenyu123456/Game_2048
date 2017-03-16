#ifndef __GAME_MAIN_H__
#define __GAME_MAIN_H__

#include "cocos2d.h"
#include "CardSprite.h"

class GameMain : public cocos2d::Layer
{

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameMain);

	// 加入手势识别的事件
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// 上下左右的函数
	bool doLeft();
	bool doRight();
	bool doUp();
	bool doDown();
	// 自动卡片生成
	void autoCreateCardNumber();
	// 判断游戏是否还能继续运行下去
	void doCheckGameOver();
	int levelNum;

	// 点击的元素位置
	int firstX, firstY, endX, endY;

	// 定义一个二维数组
	CardSprite *cardArr[20][20];

	// 创建卡片
	void createCardSprite(cocos2d::Size size);

	// 整体游戏的分数
	int score;
	// 定义显示数据的控件
	cocos2d::LabelTTF *labelTTFCardNumber;
};

#endif
