//
//  DetailBase.cpp
//  diablo
//
//  Created by Kosuke Takami on 2013/11/17.
//
//

#include "DetailBase.h"

DetailBase *DetailBase::create(){
	DetailBase * pRet = new DetailBase();
	pRet->autorelease();
	return pRet;
}

DetailBase::DetailBase(){
}

DetailBase::~DetailBase(){
}

void DetailBase::addWindowObjects(){
}

void DetailBase::update(){
}

void DetailBase::setParentLayer(DialogLayerInterface* layer){
}