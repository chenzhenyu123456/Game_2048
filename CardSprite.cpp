#include "CardSprite.h"  

USING_NS_CC;

// 初始化游戏卡片的方法  
CardSprite* CardSprite::createCardSprite(int numbers, int width, int height, float CardSpriteX, float CardSpriteY) {
	// new一个卡片精灵  
	CardSprite *enemy = new CardSprite();
	if (enemy && enemy->init()) {
		enemy->autorelease();
		enemy->enemyInit(numbers, width, height, CardSpriteX, CardSpriteY);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

// 卡片初始化方法  
bool CardSprite::init() {
	if (!Sprite::init()) {
		return false;
	}
	return true;
}


// 设置数字  
void CardSprite::setNumber(int num) {
	number = num;

	// 判断数字的大小来调整字体的大小  
	if (number >= 0) {
		labTTFCardNumber->setFontSize(50);
	}
	if (number >= 16) {
		labTTFCardNumber->setFontSize(40);
	}
	if (number >= 128) {
		labTTFCardNumber->setFontSize(30);
	}
	if (number >= 1024) {
		labTTFCardNumber->setFontSize(20);
	}

	// 判断数组的大小调整颜色  
	if (number == 0) {
		layerColorBG->setColor(cocos2d::Color3B(200, 190, 180));
	}
	if (number == 2) {
		layerColorBG->setColor(cocos2d::Color3B(240, 230, 180));
	}
	if (number == 4) {
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 150));
	}
	if (number == 8) {
		layerColorBG->setColor(cocos2d::Color3B(240, 180, 120));
	}
	if (number == 16) {
		layerColorBG->setColor(cocos2d::Color3B(240, 140, 90));
	}
	if (number == 32) {
		layerColorBG->setColor(cocos2d::Color3B(240, 120, 90));
	}
	if (number == 64) {
		layerColorBG->setColor(cocos2d::Color3B(240, 100, 80));
	}
	if (number == 128) {
		layerColorBG->setColor(cocos2d::Color3B(240, 100, 80));
	}
	if (number == 256) {
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 512) {
		layerColorBG->setColor(cocos2d::Color3B(240, 200, 70));
	}
	if (number == 1024) {
		layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
	}
	if (number == 2048) {
		layerColorBG->setColor(cocos2d::Color3B(0, 130, 0));
	}


	// 更新显示的数字  
	if (number > 0) {
		labTTFCardNumber->setString(__String::createWithFormat("%i", num)->getCString());
		labTTFCardNumber->setString(__String::createWithFormat("%i", num)->getCString());
	}
	else {
		labTTFCardNumber->setString("");
	}
}

// 获取数字  
int CardSprite::getNumber() {
	return number;
}


//第1个参数为数字，第2、3个参数为卡片的宽高，第4、5个参数为卡片的位置  
void CardSprite::enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY) {
	// 初始化数字  
	number = numbers;

	// 加入游戏卡片的背景颜色  
	layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200, 190, 180, 255), width - 15, height - 15);
	layerColorBG->setPosition(Point(CardSpriteX, CardSpriteY));

	// 判断如果不等于0就显示，否则为空  
	if (number > 0) {
		// 加入中间字体  
		labTTFCardNumber = cocos2d::LabelTTF::create(__String::createWithFormat("%i", number)->getCString(), "HirakakuProN-W6", 100);
		// 显示卡片数字的位置，这里显示在背景的中间  
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		// 添加卡片数字到背景中  
		layerColorBG->addChild(labTTFCardNumber);
	}
	else {
		// 加入中间字体  
		labTTFCardNumber = cocos2d::LabelTTF::create("", "HirakakuProN-w6", 80);
		labTTFCardNumber->setPosition(Point(layerColorBG->getContentSize().width / 2, layerColorBG->getContentSize().height / 2));
		layerColorBG->addChild(labTTFCardNumber);
	}
	// 将卡片添加到层  
	this->addChild(layerColorBG);

}