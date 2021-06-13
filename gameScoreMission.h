
#define GROW_ITEM_MISSION 4
#define POISION_ITEM_MISSON 2
#define GATE_USE_MISSION 1
#define SNAKE_LENGTH_MISSION 5

class mission
{
private:
  bool growItemMission;
  bool poisionItemMission;
  bool gateUseMission;
  bool snakeLengthMission;
public:
  mission();

  bool isGrowItemMissionClear();
  bool isPoisionItemMissionClear();
  bool isGateUseMissionClear();
  bool isSnakeLengthMissionClear();

  bool setGrowItemMissionClear(int n);
  bool setPoisionItemMissionClear(int n);
  bool setGateUseMissionClear(int n);
  bool setSnakeLengthMissionClear(int n);

  bool isGameClear();
};

class score
{
private:
  int gottenGrowItem;
  int gottenPoisionItem;
  int useGate;
  int lengthScore;
public:
  score();
  int getGottenGrowItem();
  void setGottenGrowItem(int n);
  int getGottenPoisionItem();
  void setGottenPoisionItem(int n);
  int getUseGate();
  void setUseGate(int n);
  int getLengthScore();
  void setLengthScore(int length);
};
