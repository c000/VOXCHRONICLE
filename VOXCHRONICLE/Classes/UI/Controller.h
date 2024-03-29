//
//  Controller.h
//  VOXCHRONICLE
//
//  Created by giginet on 2012/9/8.
//
//

#ifndef __VOXCHRONICLE__Controller__
#define __VOXCHRONICLE__Controller__

#include <iostream>
#include "cocos2d.h"
#include "Skill.h"
#include "CharacterManager.h"

using namespace cocos2d;

class Controller : public CCLayer {
 private:
  CCArray* _triggers;
  virtual bool ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent);
  virtual void registerWithTouchDispatcher();
  bool _enable;

public:
  virtual bool init();
  ~Controller();
  Controller();
  void resetAllTriggers();
  int currentTriggerIndex();
  Skill* currentTriggerSkill();
  void updateSkills(CharacterManager* manager);
  void setEnable(bool enable);
  CREATE_FUNC(Controller);
};

#endif /* defined(__VOXCHRONICLE__Controller__) */
