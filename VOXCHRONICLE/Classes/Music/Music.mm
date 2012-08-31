//
//  Music.cpp
//  VOXCHRONICLE
//
//  Created by giginet on 2012/8/31.
//
//

#include "Music.h"

using namespace VISS;

VISS::Music::Music() {
  Music(0);
}

VISS::Music::Music(int trackCount) {
  _trackCount = trackCount;
  _tracks = std::vector< std::deque<boost::shared_ptr<Track> > >(trackCount);
}

VISS::Music::~Music() {
}

boost::shared_ptr<VISS::Track> VISS::Music::getTrack(int trackNumber) {
  return _tracks.at(trackNumber).front();
}

boost::shared_ptr<VISS::Track> VISS::Music::getNextTrack(int trackNumber) {
  return _tracks.at(trackNumber).at(1);
}
  
bool VISS::Music::setTrack(const std::string* fileName, int trackNumber, int index) {
  Track* next = new Track(fileName);
  return setTrack(next, trackNumber, index);
}

bool VISS::Music::setTrack(Track* track, int trackNumber, int index) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber).at(index) = boost::shared_ptr<Track>(track);
  return true;
}

bool VISS::Music::pushTrack(const std::string* fileName, int trackNumber) {
  Track* next = new Track(fileName);
  return pushTrack(next, trackNumber);
}

bool VISS::Music::pushTrack(Track* track, int trackNumber) {
  if (trackNumber >= _trackCount) {
    return false;
  }
  _tracks.at(trackNumber).push_back(boost::shared_ptr<Track>(track));
  return true;
}
    
bool VISS::Music::play() {
  cocos2d::SEL_SCHEDULE selector = (cocos2d::SEL_SCHEDULE)&Music::update;
  cocos2d::CCDirector::sharedDirector()->getScheduler()->scheduleSelector(selector, this, 0.01, false, -1, 0);
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0 && !it->at(0)->play()) {
      return false;
    }
  }
  return true;
}
    
void VISS::Music::stop() {
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0) {
      it->at(0)->stop();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::pause() {
  for (std::vector< std::deque< boost::shared_ptr<Track> > >::iterator it = _tracks.begin(); it != _tracks.end(); ++it) {
    if (it->size() > 0) {
      it->at(0)->pause();
    }
  }
  cocos2d::CCDirector::sharedDirector()->getScheduler()->unscheduleAllSelectorsForTarget(this);
}

void VISS::Music::update(float dt) {
  for (int i = 0; i < _trackCount; ++i) {
    std::deque< boost::shared_ptr<Track> >* it = &_tracks.at(i);
    if (it->size() > 1 && (!it->front()->isPlaying() || (it->front()->getDuration() - it->front()->getPosition()) <= dt * 2)) {
      it->pop_front();
      it->front()->play();
    }
  }
}