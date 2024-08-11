#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
// #define DEBUG
class ArmyKnights;
class Event;
class BaseBag;
class BaseItem;
class BaseKnight;
class KnightAdventure;

class BaseOpponent;
class MadBearOpp;
class BanditOpp;
class LordLupinOpp;
class EllOpp;
class TrollOpp;
class TornberyOpp;
class QueenOfCardsOpp;
class NinaDeRingsOpp;
class DurianGardenOpp;
class OmegaWeaponOpp;
class HadesOpp;

class BagofDragon;
class BagofLancelot;
class BagofNormal;
class BagofPaladin;

class PaladinKnight;
class LancelotKnight;
class DragonKnight;
class NormalKnight;

class ItemforAntidote;
class ItemforPhoenixdownI;
class ItemforPhoenixdownII;
class ItemforPhoenixdownIII;
class ItemforPhoenixdownIV;


enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType {Antidote=1, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV};
enum OpponentType {MadBear=1,Bandit,LordLupin,Elf,Troll,Tornbery,QueenOfCards,NinaDeRings,DurianGarden,OmegaWeapon,Hades};
//
class Events {
private:
    int countevent;
    int *numberevent;
public:
    Events(const string & file_events);
    int count() const ;
    int get(int i) const ;
    ~Events();
};


class BaseOpponent {
public:
    virtual OpponentType Opp()=0;
};
class MadBearOpp : public BaseOpponent {
    public:
    OpponentType Opp();
};
class BanditOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class LordLupinOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class ElfOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class TrollOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class TornberyOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class QueenOfCardsOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class NinaDeRingsOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class DurianGardenOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class OmegaWeaponOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};
class HadesOpp: public BaseOpponent {
    public:
    OpponentType Opp();
};

class BaseBag {
protected:
    int sizeofbag=0;
    int Capofbag=0;
public:
  //Tao danh sach lien ket cho tui
    class Node {
        public:
        BaseItem* data;
        Node* next;

        Node(BaseItem * data, Node* next);
        ~Node();
    };
    BaseKnight* knight;
    Node* head = nullptr;
    BaseBag(BaseKnight* knight, int antidote, int phoenixdownI);
    virtual BaseItem* swapitemtouse();
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    virtual bool useItemforKnight(ItemType itemType);
    virtual void removeitem();
    ~BaseBag();
};

class BagofPaladin: public BaseBag{
public:
    BagofPaladin(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagofLancelot : public BaseBag{
public:
    BagofLancelot(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagofDragon : public BaseBag{
public:
    BagofDragon(BaseKnight* knight, int antidote, int phoenixDownI);
};
class BagofNormal : public BaseBag{
public:
    BagofNormal(BaseKnight* knight, int antidote, int phoenixDownI);
};






class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    bool checkpoison=0;
    bool checkprime=1;
    int gilopp[5]={100,150,450,750,800}; // de mang nhu nay coi chung lon index
    int damgeopp[5]={10,15,45,75,95};
    BaseBag * bag;
    KnightType knightType;
public:
    bool knightevent(BaseOpponent* opponent, int i);
    bool checkpoisonknight();
    void setPoisonKnight(bool checkpoison);
    int getHpKnight();
    int getMaxHPKnight();
    void setHPforknight(int hp);
    int getLevelKnight ();
    void setLevelKnight(int level);
    int getGilKnight();
    void setGilKnight(int gil);
    bool setBagKnight(BaseItem*item);
    

    BaseKnight(int id, int maxhp, int level, int gil, int antidote,int phoenixdownI,KnightType type); // bo sung cai enum nay
    virtual int DamageForUltimecia()=0;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    ~ BaseKnight ();
};
class PaladinKnight : public BaseKnight {
    public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id,maxhp,level,gil,antidote,phoenixdownI,PALADIN) {}
    int DamageForUltimecia();
};
class LancelotKnight : public BaseKnight {
      public:
      LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id,maxhp,level,gil,antidote,phoenixdownI,LANCELOT) {}
      int DamageForUltimecia();
};
class DragonKnight : public BaseKnight {
      public:
      DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id,maxhp,level,gil,antidote,phoenixdownI,DRAGON) {}
      int DamageForUltimecia();
};
class NormalKnight : public BaseKnight {
      public:
      NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI):BaseKnight(id,maxhp,level,gil,antidote,phoenixdownI,NORMAL) {}
      int DamageForUltimecia();
};


class ArmyKnights   {
protected:
    int maxhp;
    int hp;
    int level;
    int phoenixdownI;
    int gil;
    int antidote;
    int countnumevent=0;
public:
    static bool Shield;
    static bool Spear;
    static bool Hair;
    static bool Sword;
    static bool checkmeetOmegaWeapon ;
    static bool checkmeetHades;
    KnightType knightType;
    int numberknight;
    BaseKnight ** arrKnight;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    void dividegilforarmy();
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
protected:
    ItemType item;
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType itemforknight();
};
class ItemforAntidote: public BaseItem {
public:
    ItemforAntidote();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight * knight);
};
class ItemforPhoenixdownI: public BaseItem {
public:
    ItemforPhoenixdownI();
    bool canUse(BaseKnight*knight);
    void use(BaseKnight * knight);
};
class ItemforPhoenixdownII: public BaseItem {
public:
    ItemforPhoenixdownII();
    bool canUse(BaseKnight*knight);
    void use(BaseKnight * knight);
};
class ItemforPhoenixdownIII: public BaseItem {
public:
    ItemforPhoenixdownIII();
    bool canUse(BaseKnight*knight);
    void use(BaseKnight * knight);
};
class ItemforPhoenixdownIV: public BaseItem {
public:
    ItemforPhoenixdownIV();
    bool canUse(BaseKnight*knight);
    void use(BaseKnight * knight);
};

class KnightAdventure;

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure();

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__ 