#include "ChooseScene.h"
#include "CardSprite.h"
#include "GameMain.h"
#include "res.h"
#include "MainMenu.h"
#include "GameOver.h"
#include "string"
using namespace std;
USING_NS_CC;

Scene* GameMain::createScene()
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	glview->setFrameSize(480, 640);
	glview->setDesignResolutionSize(480, 640, ResolutionPolicy::SHOW_ALL);
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameMain::create();
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameMain::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->levelNum = level;
	score = 0;

	// 获得屏幕可视大小
	Size visibleSize = Director::getInstance()->getVisibleSize();
	// 加入游戏的背景
	auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(100, 90, 100, 255));
	this->addChild(layerColorBG);

	Dictionary *strings = Dictionary::createWithContentsOfFile("strings.xml");
	// 在上方加入游戏的分数
	auto labelTTFCardNumberName = LabelTTF::create(((String*)strings->objectForKey("Score"))->getCString(), "Consolas", 70);
	labelTTFCardNumberName->setPosition(Point(visibleSize.width/4, visibleSize.height - visibleSize.height / 10));
	addChild(labelTTFCardNumberName);

	labelTTFCardNumber = LabelTTF::create("0", "Consolas", 70);
	labelTTFCardNumber->setPosition(Point(visibleSize.width-visibleSize.width / 4, visibleSize.height - visibleSize.height / 10));
	addChild(labelTTFCardNumber);

	CCMenuItemFont::setFontSize(35);//设置菜单的字体大小

	// 创建返回键 tag - 1
	auto BackItem = MenuItemFont::create(((String*)strings->objectForKey("Back"))->getCString(), CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	BackItem->setPosition(Point(visibleSize.width / 4, visibleSize.height / 10));
	BackItem->setColor(Color3B::BLACK);
	BackItem->setTag(1);

	// 创建 重新开始游戏键 tag - 2
	auto RestartItem = MenuItemFont::create(((String*)strings->objectForKey("Restart"))->getCString(), CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	RestartItem->setPosition(Point(visibleSize.width / 2, visibleSize.height / 10));
	RestartItem->setColor(Color3B::BLUE);
	RestartItem->setTag(2);

	//结束按钮 tag-3
	auto CloseItem = MenuItemImage::create("CloseNormal.png",
		"CloseSelected.png", CC_CALLBACK_1(GameMain::menuCloseCallback, this));
	CloseItem->setPosition(Point(visibleSize.width - visibleSize.width / 4, visibleSize.height / 10));
	CloseItem->setTag(3);

	auto menu = Menu::create(BackItem, RestartItem, CloseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);

	// 创建手势识别的事件监听器
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameMain::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameMain::onTouchEnded, this);
	// 添加事件监听
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	// 调用生成卡片的方法
	createCardSprite(visibleSize);

	// 调用生成随机数
	autoCreateCardNumber();
	autoCreateCardNumber();
	return true;
}

//回调函数
void GameMain::menuCloseCallback(Ref* pSender)
{
	MenuItem *  nowItem = (MenuItem *)pSender;
	switch (nowItem->getTag()) {
	case 1:
		Director::getInstance()->replaceScene(CCTransitionSlideInL::create(1, ChooseScene::createScene()));
		break;
	case 2:
		Director::getInstance()->replaceScene(CCTransitionFadeTR::create(1, GameMain::createScene()));
		break;
	case 3:
		exit(0);
		break;
	}
}

// 游戏是否还能继续运行下去
void GameMain::doCheckGameOver() {
	
	bool Win = false;
	for (int i = 0; i < levelNum; i++) {
		for (int j = 0; j < levelNum; j++) {
			if (cardArr[i][j]->getNumber() == 2048) {
				Win = true;
				break;
			}
		}
	}

	if (Win) {

		Size visibleSize = Director::getInstance()->getVisibleSize();

		Dictionary *strings = Dictionary::createWithContentsOfFile("strings.xml");
		auto gameOver = GameOver::create();
		auto gameOverLabel = LabelTTF::create(((String*)strings->objectForKey("Succeed"))->getCString(), "Arial", 50);
		gameOverLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height - visibleSize.height / 4));
		gameOverLabel->setColor(ccYELLOW);//设置颜色
		gameOver->addChild(gameOverLabel);
		this->getScene()->addChild(gameOver);

		return;
	}

	bool isGameOver = true;

	for (int y = 0; y < levelNum; y++) {
		for (int x = 0; x < levelNum; x++) {
			if (cardArr[x][y]->getNumber() == 0
				|| (x>0 && (cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber()))
				|| (x<levelNum-1 && (cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber()))
				|| (y<0 && (cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber()))
				|| (y<levelNum-1 && (cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))) {
				isGameOver = false;
			}
		}
	}

	if (isGameOver) {
		// 结束游戏
		Size visibleSize = Director::getInstance()->getVisibleSize();

		Dictionary *strings = Dictionary::createWithContentsOfFile("strings.xml");
		auto gameOver = GameOver::create();
		auto gameOverLabel = LabelTTF::create(((String*)strings->objectForKey("Failed"))->getCString(), "Arial", 50);
		gameOverLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height - visibleSize.height / 4));
		gameOverLabel->setColor(ccYELLOW);
		gameOver->addChild(gameOverLabel);
		this->getScene()->addChild(gameOver);
		return;
	}
}

// 自动生成卡片  生成2或4的卡片
void GameMain::autoCreateCardNumber() {

	int i = CCRANDOM_0_1() * levelNum;
	int j = CCRANDOM_0_1() * levelNum;

	// 判断是否已经存在的位置
	if (cardArr[i][j]->getNumber() > 0) {
		// 已存在，递归创建
		autoCreateCardNumber();
	}
	else {
		// 生成2和4的比例是1:9的概率
		cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
	}
}

// 创建卡片，size为屏幕大小
void GameMain::createCardSprite(cocos2d::Size size) {

	//边缘长度
	int border = size.width / 16;

	//偏移量
	int offset = (int)((size.width*1.0 - 2*border) / (levelNum) + 0.5);
	
	//空隙长度
	int cardEmpty = offset / (levelNum*2);

	//方格的长度
	int cardLength = offset-cardEmpty;

	cardEmpty += border;

	// levelNum * levelNum的单元格
	for (int i = 0; i < levelNum; i++) {
		for (int j = 0; j < levelNum; j++) {
			CardSprite *card = CardSprite::createCardSprite(0, cardLength, cardLength, cardEmpty + offset * i, cardEmpty + offset * j + 80);
			addChild(card);
			// 添加卡片到二维数组中
			cardArr[i][j] = card;
		}
	}
}

// 加入手势识别的事件
bool GameMain::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	// 触摸点
	Point touchP0 = touch->getLocation();

	firstX = touchP0.x;
	firstY = touchP0.y;


	return true;
}

// 触摸结束触发
void GameMain::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event){
	// 获取触摸点位置
	Point touchP0 = touch->getLocation();
	// 获取X轴和Y轴的移动距离
	endX = firstX - touchP0.x;
	endY = firstY - touchP0.y;
	// 特判没有移动的情况
	if (endX == 0 && endY == 0) {
		bool can = false;
		for (int i = 0; i < levelNum; i++) {
			for (int j = 0; j < levelNum; j++) {
				if (cardArr[i][j]->getNumber() == 0) {
					can = true;
					break;
				}
			}
		}
		if (can) {
			autoCreateCardNumber();
		}
		doCheckGameOver();
		return;
	}

	// 判断X轴和Y轴的移动距离，如果X轴的绝对值大于Y轴的绝对值就是左右否则是上下
	if (abs(endX) > abs(endY)){
		// 左右
		if (endX + 5 > 0) {
			// 左边
			if (doLeft()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}

		}
		else {
			// 右边
			if (doRight()){
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}

	}
	else {
		// 上下
		if (endY + 5 > 0) {
			// 下边
			if (doDown()) {
				autoCreateCardNumber();
				doCheckGameOver();
			}
		}
		else {
			// 上边
			if (doUp()) {
				autoCreateCardNumber();
				doCheckGameOver();
			};
		}

	}
}

// 向左
bool GameMain::doLeft(){
	log("doLeft");

	bool isdo = false;
	// 最外层循环为遍历所有的位置
	for (int y = 0; y < levelNum; y++) {
		for (int x = 0; x < levelNum; x++) {

			// 这一层循环为判断卡片是合并还是清空
			for (int x1 = x + 1; x1 < levelNum; x1++) {
				if (cardArr[x1][y]->getNumber() > 0) {// 有数字
					if (cardArr[x][y]->getNumber() <= 0) { // 为空
						// 设置为右边卡片的数值
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);

						x--;
						isdo = true;

					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
						// 当前卡片的值与其比较卡片的值相等，设置为其的2倍
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);


						// 设置分数
						score += cardArr[x][y]->getNumber();
						labelTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());
						isdo = true;
					}
					break;// 跳出
				}
			}
		}
	}

	return isdo;
}

// 向右
bool GameMain::doRight(){
	log("doRight");

	bool isdo = false;
	// 
	for (int y = 0; y < levelNum; ++y) {
		for (int x = levelNum-1; x >= 0; --x) {

			// 循环判断左边卡片往右是合并还是清空
			for (int x1 = x - 1; x1 >= 0; --x1) {
				if (cardArr[x1][y]->getNumber() > 0) {
					if (cardArr[x][y]->getNumber() <= 0) {//右边为空
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						isdo = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()) {
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						// 设置分数
						score += cardArr[x][y]->getNumber();
						labelTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;
				}

			}
		}

	}

	return isdo;

}

// 向上
bool GameMain::doUp(){
	log("doUp");
	bool isdo = false;
	for (int x = 0; x < levelNum; x++) {
		for (int y = levelNum-1; y >= 0; y--) {

			// 这一层循环为判断卡片是合并还是清空
			for (int y1 = y - 1; y1 >= 0; y1--) {
				if (cardArr[x][y1]->getNumber() > 0) {// 有数字
					if (cardArr[x][y]->getNumber() <= 0) { // 为空
						// 设置为右边卡片的数值
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);

						y++;
						isdo = true;

					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						// 当前卡片的值与其比较卡片的值相等，设置为其的2倍
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						// 设置分数
						score += cardArr[x][y]->getNumber();
						labelTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;// 跳出
				}
			}
		}
	}
	return isdo;
}

// 向下
bool GameMain::doDown(){
	log("doDown");
	bool isdo = false;
	
	for (int x = 0; x < levelNum; x++) {
		for (int y = 0; y < levelNum; y++) {

			// 这一层循环为判断卡片是合并还是清空
			for (int y1 = y + 1; y1 < levelNum; y1++) {
				if (cardArr[x][y1]->getNumber() > 0) {// 有数字
					if (cardArr[x][y]->getNumber() <= 0) { // 为空
						// 设置为右边卡片的数值
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						isdo = true;

					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()) {
						// 当前卡片的值与其比较卡片的值相等，设置为其的2倍
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);


						// 设置分数
						score += cardArr[x][y]->getNumber();
						labelTTFCardNumber->setString(__String::createWithFormat("%i", score)->getCString());

						isdo = true;
					}
					break;// 跳出
				}
			}
		}
	}
	return isdo;
}