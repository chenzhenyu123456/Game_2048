#include "MainMenu.h"
#include "CardSprite.h"
#include "ChooseScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setFrameSize(480, 640);
	//分辨率适应
	glview->setDesignResolutionSize(480, 640, ResolutionPolicy::SHOW_ALL);

	auto scene = Scene::create();

	auto layer = MainMenu::create();

	scene->addChild(layer);

	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite *homepage = Sprite::create("homepage.png");
	auto size = Director::getInstance()->getWinSize();
	// 计算缩放比例
	float scaleX = size.width / homepage->getContentSize().width;
	float scaleY = size.height / homepage->getContentSize().height;
	// 设置背景的缩放
	homepage->setScaleX(scaleX);
	homepage->setScaleY(scaleY);
	homepage->setPosition(Point(size.width / 2, size.height / 2));
	this->addChild(homepage);

	auto StartItem = MenuItemImage::create("start_normal.png",
		"start_select.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	auto ExitItem = MenuItemImage::create("exit_normal.png",
		"exit_select.png", CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

	StartItem->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.5));
	ExitItem->setPosition(Point(visibleSize.width / 2, visibleSize.height * 0.3));
	
	StartItem->setScale(1.5,1.5);
	ExitItem->setScale(1.5, 1.5);

	StartItem->setTag(1);
	ExitItem->setTag(2);

	auto menu = Menu::create(StartItem, ExitItem, NULL);

	menu->setPosition(Point::ZERO);
	//设置为垂直对齐
	//menu->alignItemsVertically();
	this->addChild(menu);
	return true;
}

//按钮
void MainMenu::menuCloseCallback(Ref* pSender)
{
	int tag = ((MenuItem *)pSender)->getTag();
	switch (tag)
	{
		case 1:
			Director::getInstance()->replaceScene(TransitionCrossFade::create(1, ChooseScene::createScene()));
			break;
		case 2:
			Director::getInstance()->end();
			break;
	}
}
