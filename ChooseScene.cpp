#include "ChooseScene.h"  
#include "CardSprite.h"  
#include "GameMain.h"  
#include "MainMenu.h"
#include "res.h"

USING_NS_CC;

Scene* ChooseScene::createScene()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		//修改屏幕大小
		glview = GLView::create("2048");
		director->setOpenGLView(glview);
	}
	glview->setFrameSize(480, 640);
	//分辨率适应
	glview->setDesignResolutionSize(480, 640, ResolutionPolicy::SHOW_ALL);
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this  
	director->setAnimationInterval(1.0 / 60);
	// 'scene' is an autorelease object  
	auto scene = Scene::create();

	// 'layer' is an autorelease object  
	auto layer = ChooseScene::create();

	// add layer as a child to scene  
	scene->addChild(layer);

	// return the scene  
	return scene;
}

// on "init" you need to initialize your instance  
bool ChooseScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

// 加入游戏的背景
	CCSprite *select = CCSprite::create("selectLevel.png");
	auto size = Director::getInstance()->getWinSize();
	// 计算缩放比例
	float scaleX = size.width / select->getContentSize().width;
	float scaleY = size.height / select->getContentSize().height;
	// 设置背景的缩放
	select->setScaleX(scaleX);
	select->setScaleY(scaleY);
	// 设置背景的位置
	select->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(select);


	//结束按钮
	auto closeItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png", CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
	closeItem->setTag(-1);

	//新增菜单目录
	MenuItemFont::setFontSize(60);
	
	Dictionary *strings = CCDictionary::createWithContentsOfFile("strings.xml");

	auto ChooseItem = MenuItemFont::create(((String*)strings->objectForKey("Choose Model"))->getCString(), CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	auto color_action = TintBy::create(0.5f, 0, -255, -255);
	auto color_back = color_action->reverse();
	auto seq = Sequence::create(color_action, color_back, NULL);
	ChooseItem->runAction(RepeatForever::create(seq));
	ChooseItem->setEnabled(false); 
	ChooseItem->setTag(0);

	CCMenuItemFont::setFontSize(30);
	
	auto FourItem = MenuItemFont::create(((String*)strings->objectForKey("Senior"))->getCString(), CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	FourItem->setTag(4);
	auto FiveItem = MenuItemFont::create(((String*)strings->objectForKey("Intermediate"))->getCString(), CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	FiveItem->setTag(5);
	auto SixItem = MenuItemFont::create(((String*)strings->objectForKey("Junior"))->getCString(), CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	SixItem->setTag(6);
	auto BackItem = MenuItemFont::create(((String*)strings->objectForKey("Back"))->getCString(), CC_CALLBACK_1(ChooseScene::menuCloseCallback, this));
	BackItem->setTag(10);

	ChooseItem->setPosition(Point(origin.x + visibleSize.width / 2, 500));
	FourItem->setPosition(Point(origin.x + visibleSize.width / 2, 260));
	FiveItem->setPosition(Point(origin.x + visibleSize.width / 2, 320));
	SixItem->setPosition(Point(origin.x + visibleSize.width / 2, 380));
	BackItem->setPosition(Point(visibleSize.width / 2, 200));

	//ChooseItem->setColor(Color3B::WHITE);
	FourItem->setColor(Color3B::BLUE);
	FiveItem->setColor(Color3B::BLUE);
	SixItem->setColor(Color3B::BLUE);
	BackItem->setColor(Color3B::BLUE);

	auto menu = Menu::create(closeItem, ChooseItem, FourItem, FiveItem, SixItem, BackItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 1);

	return true;
}

//按钮
void ChooseScene::menuCloseCallback(Ref* pSender)
{
	int tag = ((MenuItem *)pSender)->getTag();
	switch (tag)
	{
	case -1:
		Director::getInstance()->end();
		break;
	case 4:case 5:case 6:
		level = tag;
		Director::sharedDirector()->replaceScene(TransitionPageTurn::create(1, GameMain::createScene(), false));//翻页式切换
		break;
	case 10:
		Director::sharedDirector()->replaceScene(TransitionCrossFade::create(1, MainMenu::createScene()));//交叉消退式跳转
		break;
	}
}