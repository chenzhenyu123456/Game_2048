#include "cocos2d.h"
#include "GameOver.h"
#include "MainMenu.h"
#include "string"
using namespace std;
USING_NS_CC;

bool GameOver::init()
{
	if (!LayerColor::initWithColor(Color4B(100, 100, 100, 100)))
	{
		return false;
	}

//添加向下触摸屏蔽
	auto callback = [](Touch *, Event *)
	{
		return true;
	};
	//创建监听器
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callback;
	//监听器状态设置为吞并触摸消息
	listener->setSwallowTouches(true);
	//将监听器与当前节点建立关系并注册到事件分配器
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	
	
	// 获得屏幕可视大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Dictionary *strings = Dictionary::createWithContentsOfFile("strings.xml");

	CCMenuItemFont::setFontSize(40);//设置菜单的字体大小

	// 创建返回键 tag - 1
	auto BackItem = MenuItemFont::create(((String*)strings->objectForKey("Back"))->getCString(), CC_CALLBACK_1(GameOver::menuCloseCallback, this));
	BackItem->setPosition(Point(visibleSize.width/3, visibleSize.height / 2));
	BackItem->setColor(Color3B::RED);
	BackItem->setTag(1);

	// 创建 重新开始游戏键 tag - 2
	auto RestartItem = MenuItemFont::create(((String*)strings->objectForKey("Restart"))->getCString(), CC_CALLBACK_1(GameOver::menuCloseCallback, this));
	RestartItem->setPosition(Point(visibleSize.width-visibleSize.width / 3, visibleSize.height / 2));
	RestartItem->setColor(Color3B::RED);
	RestartItem->setTag(2);


	auto menu = Menu::create(BackItem, RestartItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	return true;
}

//按钮
void GameOver::menuCloseCallback(Ref* pSender)
{
	int tag = ((MenuItem *)pSender)->getTag();
	switch (tag)
	{
		case 1:
			Director::getInstance()->replaceScene(TransitionTurnOffTiles::create(1, MainMenu::createScene()));
			break;
		case 2:
			Director::getInstance()->end();
			break;
	}
}
