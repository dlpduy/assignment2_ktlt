#include "knight2.h"
/* * * BEGIN implementaion of class Events * * */
Events :: Events (const string &file_events) {
    ifstream ifs;
    ifs.open(file_events);
    ifs >> countevent;
    ifs.ignore();
    numberevent= new int [countevent];
    for(int i=0; i<countevent; i++) {
        ifs >> numberevent[i];
    }
    ifs.close();
}
int Events::count() const {return countevent;}
int Events::get(int i) const {return numberevent[i];}

Events :: ~Events() {delete[] numberevent;} 
/* * * END implementation of class Events * * */


/* * * BEGIN implementation of class BaseOpponent * * */
OpponentType MadBearOpp::Opp(){return MadBear;}
OpponentType BanditOpp::Opp() {return Bandit;}
OpponentType LordLupinOpp::Opp() {return LordLupin;}
OpponentType ElfOpp::Opp() {return Elf;}
OpponentType TrollOpp::Opp(){return Troll;}
OpponentType TornberyOpp::Opp() {return Tornbery;}
OpponentType QueenOfCardsOpp::Opp() {return QueenOfCards;}
OpponentType NinaDeRingsOpp::Opp() {return NinaDeRings;}
OpponentType DurianGardenOpp::Opp() {return DurianGarden;}
OpponentType OmegaWeaponOpp::Opp() {return OmegaWeapon;}
OpponentType HadesOpp::Opp() {return Hades;}


/* * * END implementation of class BaseOpponent * * */


/* * * BEGIN implementation of class BaseKnight * * */
//khoi tao cau truc class
BaseKnight::BaseKnight(int id, int maxhp, int level, int gil,int antidote,int phoenixdownI, KnightType type){
    this->id=id;
    this->maxhp=maxhp;
    this->level=level;
    this->gil=gil;
    this->antidote=antidote;
    this->hp=maxhp;
    this->knightType=type; 
    switch (type)
    {
        case PALADIN: this->bag=new BagofPaladin(this,antidote,phoenixdownI); break;
        case LANCELOT: this->bag=new BagofLancelot(this,antidote,phoenixdownI); break;
        case DRAGON: this->bag=new BagofDragon(this,antidote,phoenixdownI); break;
        default: this->bag=new BagofNormal(this,antidote,phoenixdownI);
    }
    //khoi tao tui do cho cac hiep si
}

//Tao hiep si chien dau knightfight
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    BaseKnight*knightfight;
    bool checkprime=1; //dung de check hiep si co phai la Paladin khong
    if(maxhp>=2) {
        for(int i=2; i*i<=maxhp; i++) {
            if(maxhp%i==0) {
                checkprime=0;
            }
        }
    }
    else checkprime=0;
    //Tao hiep si Rong
    if(maxhp==345||maxhp==354||maxhp==435||maxhp==453||maxhp==534||maxhp==543) knightfight = new DragonKnight(id,maxhp,level,gil,antidote,phoenixdownI);
    //Tao hiep si Lancelot
    else if (maxhp==888) knightfight = new LancelotKnight(id,maxhp,level,gil,antidote,phoenixdownI);
    //Tao hiep si Paladin 
    else{
     if(checkprime) knightfight = new PaladinKnight(id,maxhp,level,gil,antidote,phoenixdownI);
    //Tao hiep si thuong
    else knightfight = new NormalKnight(id,maxhp,level,gil,antidote,phoenixdownI);
    }
    return knightfight;
};

bool BaseKnight::knightevent(BaseOpponent* opponent, int i) {
    int numevent=opponent->Opp();
        int levelO = (i + numevent)%10 + 1;
        if(numevent >=1 && numevent<=5) {
            if(knightType==PALADIN||knightType==LANCELOT||levelO<=level) {
                for(int m=1; m<=5; m++) {
                    if(numevent==m) {
                        gil+=gilopp[m-1];
                        break; 
                    }
                }
            }
            else {
                for(int m=1; m<=5; m++) {
                    if(numevent==m) {

                        hp-=damgeopp[m-1]*(levelO - level);
                        break;
                    }
                }
            }
        }
        else if(numevent==6) {
            if(level>=levelO) {
                level++;
                if(level>10) level = 10;
            }
            else if (knightType != DRAGON){ 
                this->checkpoison = 1;
                if(this->checkpoison==1) { 
                    if(this->bag->useItemforKnight(Antidote)) return hp>0;
                    this->checkpoison = 0;
                    this->bag->removeitem();
                    this->bag->removeitem();
                    this->bag->removeitem();
                     //roi 3 vat pham gan duoc gan nhat
                    hp=hp-10;
                }
            }
        }
        
        else if (numevent==7) {
            if(level >= levelO) gil*=2;
            else if (knightType != PALADIN) gil/=2;
        }
        else if (numevent==8) {
            if (hp<maxhp/3) {
                if(knightType==PALADIN) hp=hp+maxhp/5;
                else if(gil>=50) {
                    hp=hp+maxhp/5;
                    gil-=50;
                }
            } 
        }
        else if(numevent==9) {
            hp=maxhp;
        }
        else if(numevent==10) {
            if(ArmyKnights::checkmeetOmegaWeapon==0) {
                if(hp==maxhp&&level==10||knightType==DRAGON) {
                    level=10;
                    gil=999;
                    ArmyKnights::checkmeetOmegaWeapon=1;
                }
                else {
                    hp=0;
                }
            }
        }
        else if(numevent==11) {
            if(ArmyKnights::checkmeetHades==0) {
                if (level==10 || level>=8 && knightType == PALADIN) {
                    ArmyKnights::Shield=1;
                    ArmyKnights::checkmeetHades=1;
                }
                else {
                    hp=0;

                }

            }

        }
        if(hp<=maxhp/2) this->bag->useItemforKnight(PhoenixDownI);
        if(this->hp<=0 && this->gil >=100) {
            this->hp= this->maxhp/2;
            this->gil = gil - 100;
        }
    return hp>0;
}

//check va set nhiem doc cho hiep si
bool BaseKnight::checkpoisonknight(){return checkpoison;}
void BaseKnight::setPoisonKnight(bool checkpoison) {this->checkpoison=checkpoison;}
// lay va set hp cho hiep si
int BaseKnight::getHpKnight() {return hp;}
void BaseKnight::setHPforknight(int hp) {
    if(this->hp>hp) {
        this->hp=hp;
        this->bag->useItemforKnight(PhoenixDownI);//dung phoenixdwonI neu co the
        if(this->hp<=0&&this->gil>=100) {
            this->gil=this->gil-100;
            this->hp=maxhp/2;
        }
    }
    else {
        if(hp>maxhp) hp=maxhp;
        this->hp=hp;
        
    }
}
//lay maxhp cua hiep si
int BaseKnight::getMaxHPKnight() {return maxhp;}
//lay va set level cho hiep si
int BaseKnight::getLevelKnight() {return level;}
void BaseKnight::setLevelKnight(int level) {
    if (level>10) this->level=10;
    else this->level;
}
//lay va set gil cho hiep si
int BaseKnight::getGilKnight() {return gil;}
void BaseKnight::setGilKnight(int gil) {this->gil=gil;}
//set tui do cho hiep si
bool BaseKnight::setBagKnight(BaseItem*item) {return bag->insertFirst(item);}

BaseKnight::~BaseKnight() {
    //xoa tui do
    delete bag;
};

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    string s("");
    s += "[Knight:id:" + to_string(id) +','
        + "hp:" + to_string(hp) +','
        + "maxhp:" + to_string(maxhp) +','
        + "level:" + to_string(level) +','
        + "gil:" + to_string(gil) +','
        + bag->toString() +','
        + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

//Set damge danh Ultimecia
int PaladinKnight::DamageForUltimecia() {return hp*level*0.06;}
int LancelotKnight::DamageForUltimecia() {return hp*level*0.05;}
int DragonKnight::DamageForUltimecia() {return hp*level*0.075;}
int NormalKnight::DamageForUltimecia() {return hp*level*0;}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class BaseBag * * */
//construct tui do basebag
BaseBag::BaseBag(BaseKnight* knight, int antidote, int phoenixdownI) {
    this->knight = knight;
    this->Capofbag = 0;
    this->head = nullptr;
    this->sizeofbag = 0;
}
//tao danh sach lien ket tui do
BaseBag::Node::Node(BaseItem* data, Node* next){
    this->data=data;
    this->next=next;
}
//xoa danh sach lien ket tui do
BaseBag::Node::~Node() {delete data;}
//them vat pham vao tui do
bool BaseBag::insertFirst(BaseItem * item) {
    if(sizeofbag==Capofbag) return false;
    else {
        head=new Node(item,head);
        sizeofbag=sizeofbag+1;
        return true;
    }
}
// xoa vat pham dau tien cua tui
void BaseBag::removeitem() {
    if(sizeofbag==0) return;
        else{
            sizeofbag--;
            Node*temp=head;
            head=head->next;
            delete temp;
        } 
}
//kiem tra xem co du dieu kien dung vat pham khong
BaseItem* BaseBag::swapitemtouse() {
     if(sizeofbag==0) return nullptr;
     Node* temp=head;
     while((temp!=nullptr) && !temp->data->canUse(knight)) temp=temp->next;
     if(temp!=nullptr) {
        std::swap(head->data, temp->data);
        return head->data;
     } 
     return nullptr;
}
//lay vat pham tu tui 
BaseItem * BaseBag::get(ItemType item) {
    if(sizeofbag==0) return nullptr;
    else {
        Node* temp = head;
        while(temp&& temp->data->itemforknight() != item) temp=temp->next;
        if(temp!=nullptr) {
            std::swap(head->data,temp->data); //hoan doi vi tri vat pham
            return head->data;
        }
        else return nullptr;
    }
}

//dung vat pham cho hiep si
bool BaseBag::useItemforKnight(ItemType item) {
    BaseItem* temp = nullptr;
    if (item==Antidote) temp=BaseBag::get(item);
    else temp = swapitemtouse();
    if(temp==nullptr) return false;
    this->head->data->use(knight);
    removeitem();
    return true;
}

string BaseBag::toString() const {
    if(sizeofbag == 0) return "Bag[count=0;]";
    string printbasebag = "Bag[count=" + to_string(sizeofbag) + ";";
    string stringitem[] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    Node* temp = head;
    while(temp!=nullptr){ // trong btl cho nao co NULL thi nen thay bang nullptr !!!
        printbasebag += stringitem[temp->data->itemforknight()-1] + ",";
        temp = temp->next;
    }
    printbasebag[printbasebag.length() - 1] = ']';
    return printbasebag;    
}

BagofPaladin::BagofPaladin(BaseKnight* knight, int antidote, int phoenixdownI):BaseBag(knight, antidote, phoenixdownI) {
    this->Capofbag=-2303; // khong gioi han nen de mot so am nao do
    while(this->Capofbag != this->sizeofbag&& antidote--) {
        this->insertFirst(new ItemforAntidote);
    }
    while(this->Capofbag != this->sizeofbag && phoenixdownI--) {
        this->insertFirst(new ItemforPhoenixdownI);
    }
}

BagofDragon::BagofDragon(BaseKnight* knight, int antidote, int phoenixdownI):BaseBag(knight,antidote,phoenixdownI) {
    this->Capofbag=14; //tui do chua toi da 14 vat pham
    while(this->Capofbag!=this->sizeofbag&&phoenixdownI--) {
        this->insertFirst(new ItemforPhoenixdownI);
    } 
}

BagofLancelot::BagofLancelot(BaseKnight* knight, int antidote, int phoenixdownI):BaseBag(knight, antidote, phoenixdownI) {
    this->Capofbag=16; // tui do chua toi da 16 vat pham
    while(this->Capofbag!=this->sizeofbag&&phoenixdownI--) {
        this->insertFirst(new ItemforPhoenixdownI);
    }
    while(this->Capofbag!=this->sizeofbag&&antidote--) {
        this->insertFirst(new ItemforAntidote);
    }
}

BagofNormal::BagofNormal(BaseKnight* knight, int antidote, int phoenixdownI): BaseBag(knight, antidote, phoenixdownI) {
    this->Capofbag=19; // tui do chua toi da 19 vat pham
    while(this->Capofbag!=this->sizeofbag&&phoenixdownI--) {
        insertFirst(new ItemforPhoenixdownI);
    }
    while(this->Capofbag!=this->sizeofbag&&antidote--) {
        insertFirst(new ItemforAntidote);
    }
}

BaseBag::~BaseBag() {
    while(sizeofbag!=0) removeitem();
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string &file_armyknights) {
       ifstream ifs;
       ifs.open(file_armyknights);
       ifs >> numberknight;
       arrKnight = new BaseKnight *[numberknight];
       for(int i=0; i<numberknight; i++) {
          int maxhp, level, phoenixdownI, gil,antidote;
          ifs >> maxhp>>level>>phoenixdownI>>gil>>antidote;
          arrKnight[i]=BaseKnight::create(1+i,maxhp,level,gil,antidote,phoenixdownI);//tao hiep si
       }
       ifs.close();

}
int ArmyKnights:: count() const {return this->numberknight;} // dem so hiep si
BaseKnight* ArmyKnights::lastKnight() const {return this->arrKnight[numberknight-1];} // hiep si cuoi cung

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
bool ArmyKnights::checkmeetOmegaWeapon =0; // dung de check da gap OmegaWeapon chua
bool ArmyKnights::checkmeetHades =0; // dung de check da gap Hades chua
bool ArmyKnights::Shield=0; // dung de check co khien chua
bool ArmyKnights::Spear=0; // dung de check co giao chua
bool ArmyKnights::Hair=0;  // dung de check co toc chua
bool ArmyKnights::Sword=0; // dung de check co guom chua

bool ArmyKnights::hasPaladinShield() const {return Shield!=0;}
bool ArmyKnights::hasLancelotSpear() const {return Spear!=0;}
bool ArmyKnights::hasGuinevereHair() const {return Hair!=0;}
bool ArmyKnights::hasExcaliburSword() const {return Sword!=0;}

void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // hiep si cuoi cung
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        <<string(50,'-')<<endl;
}

bool ArmyKnights::fight(BaseOpponent* opponent) {
    if (numberknight!=0) {
        BaseKnight * lastknight = lastKnight();
        if(lastknight->knightevent(opponent,countnumevent)) {
            if(ArmyKnights::checkmeetHades!=0) this->Shield = 1;
            dividegilforarmy();
        }
       else {
        numberknight--;
        delete lastknight;
       }
    }

    delete opponent;
    return numberknight;
}

void ArmyKnights::dividegilforarmy() {
    if(numberknight==1&&arrKnight[0]->getGilKnight()>999) arrKnight[0]->setGilKnight(999);

     for(int i=numberknight-1; i>=1; i--) {
        if(arrKnight[i]->getGilKnight()>999) {
            arrKnight[i-1]->setGilKnight(arrKnight[i-1]->getGilKnight()+arrKnight[i]->getGilKnight()-999);
            arrKnight[i]->setGilKnight(999);
        }
     }
     if(arrKnight[0]->getGilKnight()>999) arrKnight[0]->setGilKnight(999);
}

bool ArmyKnights::adventure (Events * events) {
    this->countnumevent = 0;
    for(;countnumevent<events->count() ; countnumevent++) {
        int eventopp = events->get(countnumevent);
        BaseItem* item = nullptr;
        if(eventopp==1) this->fight(new MadBearOpp());
        else if (eventopp==2) this->fight(new BanditOpp());
        else if (eventopp==3) this->fight(new LordLupinOpp());
        else if (eventopp==4) this->fight(new ElfOpp());
        else if (eventopp==5) this->fight(new TrollOpp());
        else if (eventopp==6) this->fight(new TornberyOpp());
        else if (eventopp==7) this->fight(new QueenOfCardsOpp());
        else if (eventopp==8) this->fight(new NinaDeRingsOpp());
        else if (eventopp==9) this->fight(new DurianGardenOpp());
        else if (eventopp==10) this->fight (new OmegaWeaponOpp());
        else if (eventopp==11) this->fight (new HadesOpp());
        else if (eventopp==95) this->Shield=1;
        else if (eventopp==96) this->Spear=1;
        else if (eventopp==97) this->Hair=1;
        else if (eventopp==98&&Shield&&Spear&&Hair) this->Sword=1;
        else if (eventopp==99) {
            if(Sword) {
                this->printInfo();
                return true;
            }
            else if(Shield&&Spear&&Hair){
                BaseKnight * lKnight = nullptr;
                int countNormalKnight=0;
                int HpofUltimecia=5000;
                while (numberknight!=0) {

                    BaseKnight* knight = lastKnight();
                    HpofUltimecia=HpofUltimecia-knight->DamageForUltimecia();
                    //check xem co phai la NormalKight khong, neu co thi bo qua
                    if(knight->DamageForUltimecia()==0) {
                        countNormalKnight++;
                        if(lKnight==nullptr) lKnight=knight;
                        else delete knight;
                    }
                    else {
                        if(HpofUltimecia<=0) {
                            numberknight+=countNormalKnight;
                            if(lKnight!=nullptr) arrKnight[numberknight-1] = lKnight;
                            this->printInfo();
                            if(lKnight!=nullptr) delete lKnight;
                            numberknight-=countNormalKnight;
                            return true;
                        }
                        delete knight;
        
                    } 
                    numberknight--;
                    if(!numberknight) {
                        if(lKnight!=nullptr) delete lKnight;
                        this->printInfo();
                        return false; 
                    } 
                }
            }
            else {
                for(int i=0; i<numberknight; i++) {
                    delete arrKnight[i];
                }
                numberknight=0;
                this->printInfo();
                return false;
            }

        }
        else if(eventopp==112||eventopp==113||eventopp==114) {
         if (eventopp==112) item = new ItemforPhoenixdownII();
        else if (eventopp==113) item = new ItemforPhoenixdownIII();
        else if (eventopp==114) item = new ItemforPhoenixdownIV();
        
        bool insert = false; //cam co check
            for(int i = numberknight - 1 ; i >= 0; i--){
                if(arrKnight[i]->setBagKnight(item)) {
                    insert = true;
                    break; 
                }
            }
            if(insert==false) delete item;
        }
    this->printInfo();
        if(numberknight==0) return false;
    }
    return true;
}





ArmyKnights::~ArmyKnights() {
    for(int i=0; i<numberknight; i++) {
        delete arrKnight[i]; // xoa danh sach hiep si
    }
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class BaseItem * * */
ItemType BaseItem::itemforknight() {return item;}

ItemforAntidote::ItemforAntidote(){item=Antidote;}
void ItemforAntidote::use(BaseKnight*knight) {knight->setPoisonKnight(0);}
bool ItemforAntidote::canUse(BaseKnight*knight) {return knight->checkpoisonknight();} 

ItemforPhoenixdownI::ItemforPhoenixdownI(){item=PhoenixDownI;}
void ItemforPhoenixdownI::use(BaseKnight* knight) {knight->setHPforknight(knight->getMaxHPKnight());}
bool ItemforPhoenixdownI::canUse(BaseKnight* knight) {return knight->getHpKnight()<=0;}//neu HP cua hiep si <=0 thi co the dung, nguoc la thi khong

ItemforPhoenixdownII::ItemforPhoenixdownII(){item=PhoenixDownII;}
void ItemforPhoenixdownII::use(BaseKnight* knight) {knight->setHPforknight(knight->getMaxHPKnight());}\
bool ItemforPhoenixdownII::canUse(BaseKnight* knight) {return (knight->getMaxHPKnight()/4)>(knight->getHpKnight());}

ItemforPhoenixdownIII::ItemforPhoenixdownIII(){item=PhoenixDownIII;}
void ItemforPhoenixdownIII::use(BaseKnight* knight) {
    if(knight->getHpKnight()<=0) knight->setHPforknight(knight->getMaxHPKnight()/3);
    else knight->setHPforknight(knight->getHpKnight()+knight->getMaxHPKnight()/4);
}
bool ItemforPhoenixdownIII::canUse(BaseKnight* knight) {return knight->getMaxHPKnight()/3 > knight->getHpKnight();}

ItemforPhoenixdownIV::ItemforPhoenixdownIV(){item=PhoenixDownIV;}
void ItemforPhoenixdownIV::use(BaseKnight* knight) {
    if(knight->getHpKnight()<=0) knight->setHPforknight(knight->getMaxHPKnight()/2);
    else knight->setHPforknight(knight->getMaxHPKnight()/5+knight->getHpKnight());
}
bool ItemforPhoenixdownIV::canUse(BaseKnight* knight) {return knight->getMaxHPKnight()/2 > knight->getHpKnight();}

/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

void KnightAdventure::loadArmyKnights(const string & file_armyknights) { 
    
    this->armyKnights = new ArmyKnights(file_armyknights); 
}
void KnightAdventure::loadEvents(const string& file_events) {
    this->events=new Events(file_events);
}
void KnightAdventure::run() {
    this->armyKnights->printResult(this->armyKnights->adventure(this->events));
}
KnightAdventure::~KnightAdventure (){
    delete this->events;
    delete this->armyKnights;
}

/* * * END implementation of class KnightAdventure * * */