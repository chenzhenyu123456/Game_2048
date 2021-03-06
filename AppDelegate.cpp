﻿#include "AppDelegate.h"  
#include "ChooseScene.h"  
#include "MainMenu.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director  
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
		//修改屏幕大小
		glview = GLView::create("2048 Game");
		director->setOpenGLView(glview);
	}
	//不显示帧频
	director->setDisplayStats(false);

	// set FPS. the default value is 1.0/60 if you don't call this  
	director->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object  
	auto scene = MainMenu::createScene();

	// run  
	director->runWithScene(scene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too  
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

	// if you use SimpleAudioEngine, it must be pause  
	// SimpleAudioEngine::getInstance()->pauseBackgroundMusic();  
}

// this function will be called when the app is active again  
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

	// if you use SimpleAudioEngine, it must resume here  
	// SimpleAudioEngine::getInstance()->resumeBackgroundMusic();  
}