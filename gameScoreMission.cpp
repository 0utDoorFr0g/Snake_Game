#include "gameScoreMission.h"

mission::mission() : growItemMission(false), poisionItemMission(false), gateUseMission(false), snakeLengthMission(false) {;}

bool mission::isGrowItemMissionClear() { return growItemMission;}

bool mission::isPoisionItemMissionClear() {return poisionItemMission;}

bool mission::isGateUseMissionClear() {return gateUseMission;}

bool mission::isSnakeLengthMissionClear() {return snakeLengthMission;}

bool mission::setGrowItemMissionClear(int n)
{
  growItemMission = (n >= GROW_ITEM_MISSION);
  return growItemMission;
}

bool mission::setPoisionItemMissionClear(int n)
{
  poisionItemMission = (n >= POISION_ITEM_MISSON);
  return poisionItemMission;
}

bool mission::setGateUseMissionClear(int n)
{
  gateUseMission = (n >= GATE_USE_MISSION);
  return gateUseMission;
}

bool mission::setSnakeLengthMissionClear(int n)
{
  snakeLengthMission = (n >= SNAKE_LENGTH_MISSION);
  return snakeLengthMission;
}

bool mission::isGameClear()
{
  return (growItemMission && poisionItemMission && gateUseMission && snakeLengthMission);
}

score::score() : gottenGrowItem(0), gottenPoisionItem(0), useGate(0), lengthScore(0) {;}

int score::getGottenGrowItem()
{
  return gottenGrowItem;
}

void score::setGottenGrowItem(int n)
{
  gottenGrowItem = n;
}

int score::getGottenPoisionItem()
{
  return gottenPoisionItem;
}

void score::setGottenPoisionItem(int n)
{
  gottenPoisionItem = n;
}

int score::getUseGate()
{
  return useGate;
}
void score::setUseGate(int n)
{
  useGate = n;
}

int score::getLengthScore()
{
  return lengthScore;
}

void score::setLengthScore(int length)
{
  lengthScore = length;
}
