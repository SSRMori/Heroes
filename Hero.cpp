#include "Hero.h"
#include <typeinfo>
#include <string>
using namespace std;

static const HANDLE HANDLE_OUT = GetStdHandle(STD_OUTPUT_HANDLE);

// Heros and enemies information frames' position
static const COORD HERO_0 = { 0, 0 };
static const COORD HERO_1 = { 0, 7 };
static const COORD HERO_2 = { 0, 14 };
static const COORD ENEMY_0 = { 60, 0 };
static const COORD ENEMY_1 = { 60, 7 };
static const COORD ENEMY_2 = { 60, 14 };

// The division's position and the start menu's position
static const COORD DIVISION_POSITION = { 0, 21 };
static const COORD INSTRUCTION_POSITION = { 0, 22 };
static const COORD MENU_POSITION = { 0, 23 };
static const COORD INFO_POSITION = { 0, 24 };

// The difference values of start of frames and the labels 
static const COORD D_NAME_LABEL = { 3, 1 };
static const COORD D_HP_LABEL = { 3, 2 };
static const COORD D_MP_LABEL = { 29, 2 };
static const COORD D_PATK_LABEL = { 3, 3 };
static const COORD D_MATK_LABEL = { 29, 3 };
static const COORD D_PDEF_LABEL = { 3, 4 };
static const COORD D_MDEF_LABEL = { 29, 4 };
static const COORD D_EQ_LABEL = { 3, 5 };

// The difference values of start of frames and the informations
static const COORD D_NAME_INFO_HERO = { 9, 1 };
static const COORD D_NAME_INFO_ENEMY = { 10, 1 };
static const COORD D_HP_INFO = { 7, 2 };
static const COORD D_MP_INFO = { 33, 2 };
static const COORD D_PATK_INFO = { 17, 3 };
static const COORD D_MATK_INFO = { 42, 3 };
static const COORD D_PDEF_INFO = { 17, 4 };
static const COORD D_MDEF_INFO = { 42, 4 };
static const COORD D_EQ_INFO = { 14, 5 };

// The start position of menu options
// Use COORD array to present
static const COORD OPTION[] = { { 0, 23 }, { 20, 23 }, { 40, 23 }, { 60, 23 }, { 80, 23 }, { 100, 23 } };

// Total 15 types of enemies
static const string EnemyName[] = {
	"Divine Arm of Dawn",
	"Roman Soldier",
	"Yaga",
	"Werejaguar",
	"Werewolf",
	"Skeleton",
	"Dragon Tooth Warrior",
	"Fafnir",
	"Primeval Dragon",
	"Stone Golem",
	"Giant Snowman",
	"Chimera",
	"Greater Demon",
	"Solomon",
	"Megalos"
};


// Assistant function
//**************************************************************************************
COORD plusCoord(COORD coord1, COORD coord2) {
	COORD temp = { coord1.X + coord2.X, coord1.Y + coord2.Y };
	return temp;
}


// FUNCTIONS IN HERO
//**************************************************************************************

// A += operator to add an equipment to the hero
// If the equipment is added successfully, it will return true
// Else if there has already been 5 equipment, the addition will fail and false will be returned
bool operator+=(Hero & hero, Equipment * equipment)
{
	if (hero.EquipmentNum == 5) {
		return false;
	}

	hero.Equipments[hero.EquipmentNum] = equipment;
	hero.EquipmentNum++;

	if (typeid(*equipment) == typeid(AttackEquipment)
		|| typeid(*equipment) == typeid(SynthesisEquipment)) {
		hero.SetPATK(hero.GetPATK() + equipment->GetATK());
		hero.SetMATK(hero.GetMATK() + equipment->GetATK());
	}
	if (typeid(*equipment) == typeid(DefenceEquipment)
		|| typeid(*equipment) == typeid(SynthesisEquipment)) {
		hero.SetPDEF(hero.GetPDEF() + equipment->GetDEF());
		hero.SetMDEF(hero.GetMDEF() + equipment->GetDEF());
	}
	return true;
}

// A -= operator to delete an equipment from the hero
// It will delete the equipment by name 
// And only one equipment will be deleted among the equipment of the same name
bool operator-=(Hero & hero, string & name)
{
	if (hero.EquipmentNum == 0) {
		return false;
	}
	for (int i = 0; i < hero.EquipmentNum; i++) {
		// If find the equipment by name
		if (hero.Equipments[i]->GetName() == name) {
			// Delete the equipment and set the pointer to NULL
			Equipment* temp = hero.Equipments[i];
			hero.Equipments[i] = NULL;
			delete temp;

			// Equipment number minus 1
			hero.EquipmentNum--;

			// Move the Equipments' position in pointers
			for (int j = i; j < 4; j++) {
				hero.Equipments[j] = hero.Equipments[j + 1];
			}
			// Set the final pointer to NULL
			hero.Equipments[5] = NULL;
			return true;
		}
		
	}
	return false;
}

// A -= operator to delete an equipment from the hero
// It will delete the equipment by index
// An invalid index will lead to an error
bool operator-=(Hero & hero, short index)
{
	if (hero.EquipmentNum <= index) {
		return false;
	}

	hero.PATK -= hero.Equipments[index]->GetATK();
	hero.MATK -= hero.Equipments[index]->GetATK();

	hero.PDEF -= hero.Equipments[index]->GetDEF();
	hero.MDEF -= hero.Equipments[index]->GetDEF();

	delete hero.Equipments[index];

	hero.Equipments[index] = NULL;


	for (int i = index; i < 4; i++) {
		hero.Equipments[i] = hero.Equipments[i + 1];
	}
	hero.Equipments[4] = NULL;

	hero.EquipmentNum--;

	

	return true;

}

// A -= operator to delete and equipment from the hero
// It will delete the equipment by its type
// A typeid function will be used there
// And only one equipment will be deleted among the equipment of the same name
bool operator-=(Hero & hero, Equipment * equipment)
{
	if (equipment == NULL) {
		return false;
	}
	for (int i = 0; i < hero.EquipmentNum; i++) {
		if (typeid(*hero.Equipments[i]) == typeid(*equipment)) {
			Equipment* temp = hero.Equipments[i];
			hero.Equipments[i] = NULL;
			delete temp;
			for (int j = i; j < 4; j++) {
				hero.Equipments[j] = hero.Equipments[j + 1];
			}
			hero.Equipments[4] = NULL;
			return true;
		}
	}
	return false;
}


// Use += to add a Hero to the Heros
// It will only be used at the beginning of this game
// the Added Heros will be added in order 
bool operator+=(HeroManage & heroManage, Hero & hero)
{
	if (heroManage.HeroNum == 3) {
		return false;
	}
	heroManage.Heros[heroManage.HeroNum] = &hero;
	heroManage.HeroNum++;
	return true;
}

// Use += to add an Enemy to the Enemies
// It will be used whennever there is no enemy left
// the Added Enemies will be added in order
bool operator+=(HeroManage & heroManage, Enemy & enemy)
{
	if (heroManage.HeroNum == 3) {
		return false;
	}
	heroManage.Enemies[heroManage.EnemyNum] = &enemy;
	heroManage.EnemyNum++;
	return true;
}

// Use -= to delete a Hero in the Heros
// It will use typeid to judge which hero should be deleted
bool operator-=(HeroManage & heroManage, Hero & hero)
{
	if (heroManage.HeroNum == 0) {
		return false;
	}
	for (int i = 0; i < 3; i++) {
		if (typeid(*(heroManage.Heros[i])) == typeid(hero)) {
			Hero* temp = heroManage.Heros[i];
			heroManage.Heros[i] = NULL;
			delete temp;
			return true;
		}
	}
	return false;
}

// Use -= to delete an Enemy in the Enemies
// It will be used when the enemies are all dead
// For the enemies will not be specified
// So this should use name to judge which enemy should be deleted
bool operator-=(HeroManage & heroManage, Enemy & enemy)
{
	if (heroManage.HeroNum == 0) {
		return false;
	}
	for (int i = 0; i < 3; i++) {
		if (enemy.GetName() == heroManage.Enemies[i]->GetName()) {
			Enemy* temp = heroManage.Enemies[i];
			heroManage.Enemies[i] = NULL;
			delete temp;
			return true;
		}
	}
	return false;
}

// Default Constructor for Hero that can only called explicitly 
Hero::Hero(string name, string skill1, string skill2)
{
	this->Name = name;
	this->HP = 100;
	this->MP = 100;
	this->PATK = 100;
	this->MATK = 100;
	this->PDEF = 100;
	this->MDEF = 100;
	this->IsDie = false;
	this->SpecialAllowance = false;
	this->Equipments = new Equipment*[5];
	for (int i = 0; i < 5; i++) {
		this->Equipments[i] = NULL;
	}
	this->EquipmentNum = 0;
	this->Skills.push_back(skill1);
	this->Skills.push_back(skill2);
}

// Copy constructor and is a shallow copy
Hero::Hero(Hero & hero)
{
	this->Name = hero.Name;
	this->HP = hero.HP;
	this->MP = hero.MP;
	this->PATK = hero.PATK;
	this->MATK = hero.MATK;
	this->PDEF = hero.PDEF;
	this->MDEF = hero.MDEF;
	this->IsDie = hero.IsDie;
	this->SpecialAllowance = hero.SpecialAllowance;
	this->Equipments = new Equipment*[5];
	// It is a shallow copy
	// For the type of equipment was not clear
	// So this may be dangerous
	// But in this case, we can only decleared as this
	// And should try to avoid this function
	for (int i = 0; i < 5; i++) {
		this->Equipments[i] = hero.Equipments[i];
	}
	this->EquipmentNum = hero.EquipmentNum;
	this->Skills.clear();
	for (unsigned int i = 0; i < hero.Skills.size(); i++) {
		this->Skills.push_back(hero.Skills[i]);
	}
}

// Destruction
Hero::~Hero()
{
	
	while (EquipmentNum > 0) {

		*this -= (short)0;
	}
	if (Equipments != NULL) {
		delete[] Equipments;
	}

	Skills.clear();
}

void Hero::SetName(string Name)
{
	this->Name = Name;
}

void Hero::SetHP(int HP)
{
	this->HP = HP;
}

void Hero::SetMP(int MP)
{
	this->MP = MP;
}

void Hero::SetPATK(int PATK)
{
	this->PATK = PATK;
}

void Hero::SetMATK(int MATK)
{
	this->MATK = MATK;
}

void Hero::SetPDEF(int PDEF)
{
	this->PDEF = PDEF;
}

void Hero::SetMDEF(int MDEF)
{
	this->MDEF = MDEF;
}

void Hero::SetIsDie(bool IsDie)
{
	this->IsDie = IsDie;
}

void Hero::SetSpecialAllowance(bool SpecialAllowance)
{
	this->SpecialAllowance = SpecialAllowance;
}

void Hero::SetEquipments(Equipment ** Equipments)
{
	if (this->Equipments != NULL) {
		delete[] this->Equipments;
	}
	for (int i = 0; i < 6; i++) {
		this->Equipments[i] = Equipments[i];
	}
}

void Hero::SetEquipmentNum(int EquipmentNum)
{
	this->EquipmentNum = EquipmentNum;
}

void Hero::SetSkills(vector<string> Skills)
{
	if (!this->Skills.empty()) {
		this->Skills.clear();
	}
	for (unsigned int i = 0; i < Skills.size(); i++) {
		this->Skills.push_back(Skills[i]);
	}
}

string Hero::GetName()
{
	return Name;
}

int Hero::GetHP()
{
	return HP;
}

int Hero::GetMP()
{
	return MP;
}

int Hero::GetPATK()
{
	return PATK;
}

int Hero::GetMATK()
{
	return MATK;
}

int Hero::GetPDEF()
{
	return PDEF;
}

int Hero::GetMDEF()
{
	return MDEF;
}

bool Hero::GetIsDie()
{
	return IsDie;
}

bool Hero::GetSpecialAllowance()
{
	return SpecialAllowance;
}

Equipment ** Hero::GetEquipments()
{
	return Equipments;
}

int& Hero::GetEquipmentNum()
{
	return EquipmentNum;
}

vector<string> Hero::GetSkills()
{
	return Skills;
}

void Hero::PrintEquipmentInfo(short num) const
{
	if (num < 0 || num >= EquipmentNum) {
		cerr << "Error[In PrintEquipmentInfo(short)] - Invalid Input of num." << endl;
		system("pause");
	}
	(Equipments[num])->PrintInfo();
}

// Synthesis all the equipment to a synthesis equipment
// If the number of Equipment is less than 5, there will be an error
// It will clear the Equipments pointer and add a new Synthesis
// It will set the SpecialAllowance to true
void Hero::Synthesis()
{
	if (SpecialAllowance) {
		for (int i = 0; i < 4; i++) {
			if (Equipments[1] == NULL) {
				break;
			}
			else {
				*this -= (short)1;
			}
		}
		if (dynamic_cast<SynthesisEquipment*>(Equipments[0]) == NULL) {
			cerr << "Error[In Synthesis()] - Invalid type of equipment.";
			system("pause");
		}
		dynamic_cast<SynthesisEquipment*>(Equipments[0])->SetCounter(dynamic_cast<SynthesisEquipment*>(Equipments[0])->GetCounter() + 1);
		dynamic_cast<SynthesisEquipment*>(Equipments[0])->SetATK(200 * (dynamic_cast<SynthesisEquipment*>(Equipments[0])->GetCounter()));
		dynamic_cast<SynthesisEquipment*>(Equipments[0])->SetDEF(200 * (dynamic_cast<SynthesisEquipment*>(Equipments[0])->GetCounter()));

	}
	else {
		for (int i = 0; i < 5; i++) {
			if (Equipments[0] == NULL) {
				break;
			}
			else {
				*this -= (short)0;
			}
		}
		*this += new SynthesisEquipment;
		SpecialAllowance = true;
	}
}


// FUNCTUIONS IN ENEMY
//**************************************************************************************
Enemy::Enemy(string name, int passNum): Hero(name, "", "")
{
	SetHP(GetHP() + passNum * 20);
	SetPATK(GetPATK() + passNum * 50);
	SetMATK(GetMATK() + passNum * 50);
}

Enemy::~Enemy()
{
}

void Enemy::PrintAttackInfo() const
{
	cerr << "Error[In PrintAttackInfo()] - Invalid Called." << endl;
}

void Enemy::PrintSkill1Info() const
{
	cerr << "Error[In PrintSkill1Info()] - Invalid Called." << endl;
}

void Enemy::PrintSkill2Info() const
{
	cerr << "Error[In PrintSkill2Info()] - Invalid Called." << endl;
}

void Enemy::PrintSpecialSkillInfo() const
{
	cerr << "Error[In PrintSpecialSkillInfo()] - Invalid Call." << endl;
}

void Enemy::PrintAttackWord() const
{
	cerr << "Error[In PrintAttackWord()] - Invalid Called." << endl;
}

void Enemy::PrintDefenceWord() const
{
	cerr << "Error[In PrintDefenceWord()] - Invalid Called." << endl;
}

void Enemy::Die()
{
	SetIsDie(true);
}

void Enemy::Skill1()
{
	cerr << "Error[In Skill1()] - Invalid Called." << endl;
}

void Enemy::Skill2()
{
	cerr << "Error[In Skill2()] - Invalid Called." << endl;
}

int Enemy::SpecialSkill()
{
	cerr << "Error[In SpecialSkill()] - Invalid Called." << endl;
	return 0;
}



// FUNCTIONS IN HEROMANAGE
//**************************************************************************************
// Constructor and Destructor
HeroManage::HeroManage(int code)
{
	int hero[3] = { 0 };
	hero[1] = Welcome();
	system("cls");

	srand(static_cast<unsigned int>(time(0)));
	Enemies = new Enemy*[3];
	Heros = new Hero*[3];
	HeroNum = 3;
	EnemyNum = 3;
	PassCounter = 0;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < 3; i++) {
		Enemies[i] = new Enemy(EnemyName[rand() % 15], PassCounter);
		if (rand() % 2 == 1) {
			*Enemies[i] += new AttackEquipment(rand());
		}
		else {
			*Enemies[i] += new DefenceEquipment(rand());
		}

	}
	
	while (hero[0] == hero[2]
		|| hero[2] == hero[1]
		|| hero[1] == hero[0]) {
		hero[0] = rand() % 5;
		hero[2] = rand() % 5;
	}

	for (int i = 0; i < 3; i++) {
		switch (hero[i]) {
		case 0:
			Heros[i] = new ArtoriaPendragon;
			break;
		case 1:
			Heros[i] = new TamamoNoMae;
			break;
		case 2:
			Heros[i] = new Gilgamesh;
			break;
		case 3:
			Heros[i] = new JeannedArc;
			break;
		case 4:
			Heros[i] = new ZhugeLiang;
			break;
		default:
			cerr << "Error[In HeroManage()] - Invalid of hero select." << endl;
			system("pause");
		}
	}

	for (int i = 0; i < 3; i++) {
		Heros[i]->SetHP(120);
		Heros[i]->SetPATK(120);
		Heros[i]->SetMATK(120);
		Heros[i]->SetPDEF(120);
		Heros[i]->SetMDEF(120);
	}

	if (code) {
		for (int i = 0; i < 3; i++) {
			Heros[i]->SetHP(1000);
			Heros[i]->SetPATK(1000);
		}
	}
	
}

HeroManage::HeroManage(HeroManage &)
{
}

HeroManage::~HeroManage()
{
	for (int i = 0; i < 3; i++) {
		if (Heros[i] != NULL) {
			delete Heros[i];
		}
		if (Enemies[i] != NULL) {
			delete Enemies[i];
		}
	}
	if (Heros != NULL) {
		delete Heros;
	}
	if (Enemies != NULL) {
		delete Enemies;
	}
}

void HeroManage::PLAY()
{
	PrintField();
	while (!GameOver) {
		int temp = PassCounter;
		//system("cls");
		ClearSpace();
		PrintInstruction("Please select your next move:");
		PrintBaseMenu();
		
		SelectBaseMenu();

		if (!GameOver) {
			_getch();
			for (int i = 0; i < 3; i++) {
				if (PassCounter != temp || GameOver == true) {
					break;
				}
				if (!Heros[i]->GetIsDie() && i != 1) {
					HeroAutoAttack(i);
					if (GameOver != true) {
						_getch();
					}
				}
			}
			if (PassCounter == temp ) {
				for (int i = 0; i < 3; i++) {
					if (EnemyNum == 0 || GameOver == true) {
						break;
					}
					else if (!Enemies[i]->GetIsDie()) {
						EnemyAutoAttack(i);
						_getch();
					}
				}
			}
		}
	}
	MessageBox(NULL, TEXT("Thinks for playing!"), TEXT("Tip"), MB_OK);
}

void HeroManage::SetPassCounter(int PassCounter)
{
	this->PassCounter = PassCounter;
}

void HeroManage::SetHeros(Hero ** Heros)
{
	for (int i = 0; i < 3; i++) {
		this->Heros[i] = Heros[i];
	}
}

void HeroManage::SetEnemies(Enemy ** Enemies)
{
	for (int i = 0; i < 3; i++) {
		this->Enemies[i] = Enemies[i];
	}
}

void HeroManage::SetHeroNum(short HeroNum)
{
	this->HeroNum = HeroNum;
}

void HeroManage::SetEnemyNum(short EnemyNum)
{
	this->EnemyNum = EnemyNum;
}

void HeroManage::SetSelectNum(short SelectNum)
{
	this->SelectNum = SelectNum;
}

void HeroManage::SetOptionName(vector<string> OptionName)
{
	if (!this->OptionName.empty()) {
		this->OptionName.clear();
	}
	if (OptionName.size() > 6) {
		cerr << "Error[In SetOptionName(vector<string>)] - The Input Vector Exceeds The Max Length.";
		system("pause");
	}
	for (unsigned int i = 0; i < OptionName.size(); i++) {
		this->OptionName.push_back(OptionName[i]);
	}
}

void HeroManage::SetCursor(COORD Cursor)
{
	this->Cursor = Cursor;
}

void HeroManage::SetGameOver(bool GameOver)
{
	this->GameOver = GameOver;
}

int HeroManage::GetPassCounter() const
{
	return PassCounter;
}

Hero ** HeroManage::GetHeros() const
{
	return Heros;
}

Enemy ** HeroManage::GetEnemies() const
{
	return Enemies;
}

short HeroManage::GetHeroNum() const
{
	return HeroNum;
}

short HeroManage::GetEnemyNum() const
{
	return EnemyNum;
}

short HeroManage::GetSelectNum() const
{
	return SelectNum;
}

vector<string> HeroManage::GetOptionName() const
{
	return OptionName;
}

COORD HeroManage::GetCursor() const
{
	return Cursor;
}

bool HeroManage::GetGameOver() const
{
	return GameOver;
}

// Base function to fight
// The privious is the executor and the last is the sufferer
void HeroManage::HeroAttack(int hero, int enemy)
{
	if (Enemies[enemy]->GetIsDie()) {
		cerr << "Error[In HeroAttack(int hero, int enemy)] - Invalid value of enemy.";
		system("pause");
	}

	// Calculate the damage
	int temp = CalculateDamage(Heros[hero]->GetPATK() + Heros[hero]->GetMATK(), Enemies[enemy]->GetPDEF() + Enemies[enemy]->GetMDEF());
	// Give damage
	Enemies[enemy]->SetHP(Enemies[enemy]->GetHP() - temp);

	// Print hero's attack word
	ClearSpace();
	SetCursorPosition(INSTRUCTION_POSITION);
	Heros[hero]->PrintAttackWord();

	// Print the damage
	SetCursorPosition(OPTION[0]);
	cout << Heros[hero]->GetName() << " cause " << temp << " damage to the " << Enemies[enemy]->GetName() << ".";
	// Refresh the enemy's information
	PrintEnemyInfo(enemy);

	// If enemy is dead
	if (Enemies[enemy]->GetHP() <= 0) {
		EnemyDie(enemy);

		if (dynamic_cast<AttackEquipment*>(Enemies[enemy]->GetEquipments()[0]) != NULL) {
			*Heros[hero] += new AttackEquipment(*dynamic_cast<AttackEquipment*>(Enemies[enemy]->GetEquipments()[0]));
		}
		else
		{
			*Heros[hero] += new DefenceEquipment(*dynamic_cast<DefenceEquipment*>(Enemies[enemy]->GetEquipments()[0]));
		}


		Enemies[enemy] -= (short)0;

		PrintHeroInfo(hero);

	}
}

// Base function to fight
// The privious is the executor and the last is the sufferer
void HeroManage::EnemyAttack(int enemy, int hero)
{
	// Calculate the damage
	int temp = CalculateDamage(Enemies[enemy]->GetPATK() + Enemies[enemy]->GetMATK(), Heros[hero]->GetPDEF() + Heros[hero]->GetMDEF());
	Heros[hero]->SetHP(Heros[hero]->GetHP() - temp);

	// Print hero's defence word
	ClearSpace();
	SetCursorPosition(INSTRUCTION_POSITION);
	Heros[hero]->PrintDefenceWord();
	cout << endl;
	cout << Enemies[enemy]->GetName() << " cause " << temp << " damage to " << Heros[hero]->GetName() << ".";
	// Refresh the hero's information
	PrintHeroInfo(hero);

	// If the hero is dead
	if (Heros[hero]->GetHP() <= 0) {
		HeroDie(hero);
		PrintFrame(HERO, hero);
		PrintInfoLabel(HERO, hero);
		PrintHeroInfo(hero);
	}
}

// Function to handling death
// HeroDie may change the gamestatus
void HeroManage::HeroDie(int hero)
{
	ClearSpace();
	SetCursorPosition(INSTRUCTION_POSITION);
	Heros[hero]->Die();
	_getch();
	PrintFrame(HERO, hero);
	PrintInfoLabel(HERO, hero);
	PrintHeroInfo(hero);
	if (hero == 1) {
		Gameover();
	}
}

// Function to handling death
// EnemyDie may call the next pass
void HeroManage::EnemyDie(int enemy)
{
	EnemyNum--;
	Enemies[enemy]->SetIsDie(true);
	PrintFrame(ENEMY, enemy);
	PrintInfoLabel(ENEMY, enemy);

	PrintEnemyInfo(enemy);
	if (EnemyNum == 0) {
		NextPass();
	}
}

// Auto Attack function
// Call the attack function to attack
void HeroManage::HeroAutoAttack(int hero)
{
	bool moved = false;
	// First check can there be a synthesis equipment
	if (Heros[hero]->GetEquipmentNum() == 5) {
		Heros[hero]->Synthesis();
		PrintHeroInfo(hero);
		moved = true;
	}
	else {
		if (Heros[hero]->GetSpecialAllowance()) {
			srand(static_cast<unsigned int>(time(0)));
			if (rand() % 4 == 1) {
				ClearSpace();
				SetCursorPosition(INSTRUCTION_POSITION);
				int temp = Heros[hero]->SpecialSkill();
				cout << endl;
				for (int i = 0; i < 3; i++) {
					if (!Enemies[i]->GetIsDie()) {
						Enemies[i]->SetHP(Enemies[i]->GetHP() - CalculateDamage(temp, Enemies[i]->GetPDEF() + Enemies[i]->GetMATK()));
						if (Enemies[i]->GetHP() <= 0) {
							Enemies[i]->Die();
							EnemyNum--;
						}

						cout << Heros[hero]->GetName() << " cause "
							<< CalculateDamage(temp, Enemies[i]->GetPDEF() + Enemies[i]->GetMDEF())
							<< " damage to " << Enemies[i]->GetName() << "." << endl;
					}
				}

				for (int i = 0; i < 3; i++) {
					PrintEnemyInfo(i);
					PrintFrame(ENEMY, i);
					PrintInfoLabel(ENEMY, i);
				}
				if (EnemyNum == 0) {
					NextPass();
				}
				moved = true;
			}
		}
		if (moved != true) {
			// Check to attack
			for (int i = 0; i < 3; i++) {
				if (!Enemies[i]->GetIsDie()) {
					int temp = CalculateDamage(Heros[hero]->GetPATK() + Heros[hero]->GetMATK(), Enemies[i]->GetPDEF() + Enemies[i]->GetMDEF());
					// If can kill any enemy
					if (temp >= Enemies[i]->GetHP() && !moved) {
						HeroAttack(hero, i);
						moved = true;
					}
					// If will be killed by other enemy
					else {
						int temp1 = CalculateDamage(Enemies[i]->GetPATK() + Enemies[i]->GetMATK(), Heros[hero]->GetPDEF() + Heros[hero]->GetMDEF());
						if (temp1 >= Heros[hero]->GetHP() && Heros[hero]->GetMP() >= 20) {
							ClearSpace();
							SetCursorPosition(INSTRUCTION_POSITION);
							Heros[hero]->Skill1();
							PrintHeroInfo(hero);
							moved = true;
						}
					}
				}
			}
		}
	}
	if (!moved) {
		// If there is enough HP and MP
		//there is half of the posibility to use skill-2 to get buff
		srand(static_cast<unsigned int>(time(0)));
		if (Heros[hero]->GetMP() >= 20 
			&& Heros[hero]->GetHP() >= static_cast<int>(100 + PassCounter * 50 * 0.4)
			&& rand() % 2 == 1)	{
			ClearSpace();
			SetCursorPosition(INSTRUCTION_POSITION);
			Heros[hero]->Skill2();
			PrintHeroInfo(hero);
			moved = true;
		}
		// If not moved until there
		// Attack the enemy with the least HP
		else {
			int Select = 0;
			while (Enemies[Select]->GetIsDie()) {
				Select++;
			}
			int minHP = 100 * PassCounter;
			for (int i = 0; i < 3; i++) {
				if (Enemies[i]->GetHP() < minHP && !Enemies[i]->GetIsDie()) {
					Select = i;
					minHP = Enemies[i]->GetHP();
				}
			}
			HeroAttack(hero, Select);
			moved = true;
		}
	}
}

// Auto Attack function
// Call the attack function to attack
void HeroManage::EnemyAutoAttack(int enemy)
{
	bool moved = false;
	srand(static_cast<unsigned int>(time(0)));
	int Select = rand() % 3;
	for (int i = 0; i < 3; i++) {
		if (!Heros[i]->GetIsDie()) {
			// If can kill one hero
			int temp = CalculateDamage(Enemies[enemy]->GetPATK() + Enemies[enemy]->GetMATK(), Heros[i]->GetPDEF() + Heros[i]->GetMDEF());
			if (temp >= Heros[i]->GetHP()) {
				EnemyAttack(enemy, i);
				moved = true;
			}
		}
	}
	// If NOT, attack the hero randomly
	if (!moved) {
		while (Heros[Select]->GetIsDie()) {
			Select = rand() % 3;
		}
		EnemyAttack(enemy, Select);
		moved = true;
	}
}

// Print the welcome page
// Return the heros that player select
// Use integer to present hero
int HeroManage::Welcome()
{
	const string TITLE = "THE HERO";
	const string INSTRUCTION[18] = { 
		"Welcome to the world of hero!",
		"Our world is under the rule of darkness. Monsters hanging around to get humans' life.",
		"Anyone can not let this happen, but no one have the power to defeat all the monsters.",
		"Even the most brave soldier of this country will be afraid of the endless monsters.",
		"But you, young man! You are the chosen one with endless power.",
		"You are so brave, so undefeatable. No one can stop you to save the world from monsters",
		"You are so eager to get this wonderful chance to prove youself.",
		"But you need to know how dangerous they are and how terrified the way you chosen.",
		"There are endless monsters waiting for you and they will be stronger and stronger.",
		"You can only get your equipments from your enemy and you only have one life.",
		"But don't worry. You have your special ability when facing multiple enemies.",
		"However, you need first find the powerful equipment that you have lost in your heart.",
		"Then you can have the power to defeat anyone.",
		"There will be two other persons who will help you during your journey.",
		"Remember, they are the same as you. You should keep yourself alive while protecting others.",
		"Now, Let's start!",
		"[Use WASD or Up-Down-Left-Right and Enter to operate]",
		"Please select your hero:"
	};

	const string HERONAME[5] = {
		"Altria Pendragon",
		"Tamamo no Mae",
		"Gilgamesh",
		"Jeanne d'Arc",
		"Zhuge Liang (Lord El-Melloi II)"
	};

	SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	SetCursorPosition({ 51, 2 });
	cout << TITLE;
	SetDefaultTextAttribute();

	for (int i = 0; i < 18; i++) {
		Sleep(1000);
		COORD temp = { 0, 0 };
		temp.X = (SHORT)floor(55 - (INSTRUCTION[i].length() / 2));
		temp.Y = 4 + i;
		SetCursorPosition(temp);
		if (i == 16) {
			SetTextAttribute(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		}
		cout << INSTRUCTION[i];
		if (i == 16) {
			SetDefaultTextAttribute();
		}
	}

	vector<COORD> HeroNamePosition;
	int Select = 0;

	SetChosenTextAttribute();
	for (int i = 0; i < 5; i++) {
		COORD temp = { 0, 0 };
		temp.X = (SHORT)floor(55 - (HERONAME[i].length() / 2));
		temp.Y = 23 + i;
		HeroNamePosition.push_back(temp);
		SetCursorPosition(temp);
		cout << HERONAME[i];
		if (i == 0) {
			SetDefaultTextAttribute();
		}
	}

	enum Key input;

	while ((input = GetInput()) != ENTER) {
		if (input == UP) {
			if (Select != 0) {
				SetDefaultTextAttribute();
				SetCursorPosition(HeroNamePosition[Select]);
				cout << HERONAME[Select];

				Select--;
				SetChosenTextAttribute();
				SetCursorPosition(HeroNamePosition[Select]);
				cout << HERONAME[Select];
			}
		}
		else if (input == DOWN) {
			if (Select != 4) {
				SetDefaultTextAttribute();
				SetCursorPosition(HeroNamePosition[Select]);
				cout << HERONAME[Select];

				Select++;
				SetChosenTextAttribute();
				SetCursorPosition(HeroNamePosition[Select]);
				cout << HERONAME[Select];
			}
		}
	}
	SetDefaultTextAttribute();
	return Select;
}

// The main function in this part
// Have many assist functions that are as follows 
void HeroManage::PrintField()
{
	for (int i = 0; i < 3; i++) {
		PrintFrame(HERO, i);
		PrintInfoLabel(HERO, i);
		PrintHeroInfo(i);
		PrintFrame(ENEMY, i);
		PrintInfoLabel(ENEMY, i);
		PrintEnemyInfo(i);
	}
	PrintDivision();
	PrintInstruction("Please choose your next move:");
	PrintBaseMenu();
}

// Set text attribute to default
// Foreground: White
// Background: Black
// Intensity: None
void HeroManage::SetDefaultTextAttribute()
{
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

// Set text attribute to chosen mood
// Foreground: Black
// Background: White
// Intensity: None
void HeroManage::SetChosenTextAttribute()
{
	SetConsoleTextAttribute(HANDLE_OUT, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}

// Set text attribute to certain mood
// Any macro is accepted
void HeroManage::SetTextAttribute(WORD attribute)
{
	SetConsoleTextAttribute(HANDLE_OUT, attribute);
}

// Set text attribute by hero's or enemy's status
// The input enum and short variables will refer to a hero or a enemy
// And it will set the attribute automatically
void HeroManage::SetTextAttributeByStatus(enum ObjectType OT, short num)
{
	if (OT == MENU) {
		cerr << "Error[In SetTextAttributeByStatus(enum ObjectType, short)] - Invalid Input of OT." << endl;
		system("pause");
	}

	bool temp;
	if (OT == HERO) {
		temp = Heros[num]->GetIsDie();
	}
	else if (OT == ENEMY) {
		temp = Enemies[num]->GetIsDie();
	}
	if (temp) {
		SetTextAttribute(NULL);
	 }
}

// Set cursor's position
// A COORD to present the position you want to set
COORD HeroManage::SetCursorPosition(COORD CursorPosition)
{
	SetConsoleCursorPosition(HANDLE_OUT, CursorPosition);
	Cursor = CursorPosition;
	return CursorPosition;
}

// Overload the above function
// An enum type is refered whether the object need to be printed is enemy or hero
// An short function judge which one should be printed
COORD HeroManage::SetCursorPosition(enum ObjectType OT, short num)
{
	if (num < 0 || num > 2) {
		cerr << "Error[In SetCursorPosition(enum ObjectType, short)] - Invalid Input of num." << endl;
		system("pause");
		return { 0, 0 };
	}
	
	if (OT == HERO) {
		if (num == 0) { 
			return SetCursorPosition(HERO_0); 
		}
		else if (num == 1) { 
			return SetCursorPosition(HERO_1); 
		}
		else if (num == 2) { 
			return SetCursorPosition(HERO_2); 
		}
	}
	else if (OT == ENEMY) {
		if (num == 0) { 
			return SetCursorPosition(ENEMY_0); 
		}
		else if (num == 1) { 
			return SetCursorPosition(ENEMY_1);
		}
		else if (num == 2) { 
			return SetCursorPosition(ENEMY_2); 
		}
	}
	else {
		cerr << "Error[In SetCursorPosition(enum ObjectType, short)] - Invalid Input of OT." << endl;
		system("pause");
		return { 0, 0 };
	}
	return { 0, 0 };
}

// Print Frame for the exact member
// An Enum parameter to decide the reference of the short
// It only for Hero and Enemy, NOT Menu, which will lead to an error
void HeroManage::PrintFrame(enum ObjectType OT, short num)
{
	SetTextAttributeByStatus(OT, num);

	COORD temp = SetCursorPosition(OT, num);
	for (int i = 0; i < 58; i++) { cout << "*"; }

	for (int i = 0; i < 5; i++) {
		temp.Y++;		
		SetCursorPosition(temp);
		cout << "*";
		temp.X += 57;
		SetCursorPosition(temp);
		cout << "*";
		temp.X -= 57;
	}

	temp.Y++;
	SetCursorPosition(temp);
	for (int i = 0; i < 58; i++) { cout << "*"; }

	SetDefaultTextAttribute();
}

// Print an Info Label
// Need constant D-value for some Label
// Enum for the reference of the short
// A menu enum is invalid
void HeroManage::PrintInfoLabel(enum ObjectType OT, short num)
{
	SetTextAttributeByStatus(OT, num);

	if (OT == MENU) {
		cerr << "Error[In PrintInfoLabel(enum ObjectType, short)] - Invalid Input of OT." << endl;
		system("pause");
	}

	// Print Name Label 
	// Hero or Enemy
	COORD temp = SetCursorPosition(OT, num);
	SetCursorPosition(plusCoord(temp, D_NAME_LABEL));
	if (OT == HERO) {
		cout << "Hero:";
	}
	else if (OT == ENEMY) {
		cout << "Enemy:";
	}

	// Print HP Label
	SetCursorPosition(plusCoord(temp, D_HP_LABEL));
	cout << "HP:";

	// Print MP Label
	SetCursorPosition(plusCoord(temp, D_MP_LABEL));
	cout << "MP:";

	// Print Physical ATK Label
	SetCursorPosition(plusCoord(temp, D_PATK_LABEL));
	cout << "Physical ATK:";

	// Print Magic ATK Label
	SetCursorPosition(plusCoord(temp, D_MATK_LABEL));
	cout << "Magical ATK:";

	// Print Physical DEF Label
	SetCursorPosition(plusCoord(temp, D_PDEF_LABEL));
	cout << "Physical DEF:";

	// Print Magical DEF Label
	SetCursorPosition(plusCoord(temp, D_MDEF_LABEL));
	cout << "Magical DEF:";

	// Print Equipment Label
	SetCursorPosition(plusCoord(temp, D_EQ_LABEL));
	cout << "Equipment:";

	SetDefaultTextAttribute();
}

// Print hero's information
// A short to decide which hero to print
void HeroManage::PrintHeroInfo(short num)
{
	COORD temp = SetCursorPosition(HERO, num);
	SetDefaultTextAttribute();
	// If the hero is not dead, print its name in light blue
	if (!Heros[num]->GetIsDie()) {
		SetTextAttribute(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		if (num == 1) {
			// If the hero is player, print its name in yellow
			SetTextAttribute(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		}
	}
	else {
		SetTextAttributeByStatus(HERO, num);
	}

	// Print Name Information
	SetCursorPosition(plusCoord(temp, D_NAME_INFO_HERO));
	// Clear the previous data
	ClearGird(1);
	SetCursorPosition(plusCoord(temp, D_NAME_INFO_HERO));
	cout << Heros[num]->GetName();

	// Set text attribute by hero's status
	SetDefaultTextAttribute();
	SetTextAttributeByStatus(HERO, num);
	// Print HP Information
	SetCursorPosition(plusCoord(temp, D_HP_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_HP_INFO));
	cout << Heros[num]->GetHP();

	// Print MP Information
	SetCursorPosition(plusCoord(temp, D_MP_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MP_INFO));
	cout << Heros[num]->GetMP();

	// Print PATK Information
	SetCursorPosition(plusCoord(temp, D_PATK_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_PATK_INFO));
	cout << Heros[num]->GetPATK();

	// Print MATK Information
	SetCursorPosition(plusCoord(temp, D_MATK_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MATK_INFO));
	cout << Heros[num]->GetMATK();

	// Print PDEF Information
	SetCursorPosition(plusCoord(temp, D_PDEF_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_PDEF_INFO));
	cout << Heros[num]->GetPDEF();

	// Print MDEF Information
	SetCursorPosition(plusCoord(temp, D_MDEF_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MDEF_INFO));
	cout << Heros[num]->GetMDEF();

	// Print Equipments' Name
	SetCursorPosition(plusCoord(temp, D_EQ_INFO));
	// Clear the previous data
	ClearGird(1);
	// Print the three top Equipments
	// To avoid exceeds the frame
	SetCursorPosition(plusCoord(temp, D_EQ_INFO));
	
	// Output at most 3 equipments
	if (Heros[num]->GetEquipments()[0] != NULL) {
		cout << Heros[num]->GetEquipments()[0]->GetName();
	}
	if (Heros[num]->GetSpecialAllowance()) {
		if (Heros[num]->GetEquipmentNum() > 1) {
			cout << "...";
		}
	}
	else {
		for (int i = 1; (i < Heros[num]->GetEquipmentNum()) && (i < 3); i++) {
			cout << ", " << Heros[num]->GetEquipments()[i]->GetName();
		}
		// If the equipments is more than three, output a ellipsis
		if (Heros[num]->GetEquipmentNum() > 3) {
			cout << "...";
		}
	}
	// If there is no equipments, output "None"
	if (Heros[num]->GetEquipmentNum() == 0) {
		cout << "None";
	}
	SetDefaultTextAttribute();
}

// Print enemy's information
// A short to decide which enemy to print
void HeroManage::PrintEnemyInfo(short num)
{
	COORD temp = SetCursorPosition(ENEMY, num);
	SetDefaultTextAttribute();
	// If the enemy is not dead, print its name in purple
	if (!Enemies[num]->GetIsDie()) {
		SetTextAttribute(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
	else {
		SetTextAttributeByStatus(ENEMY, num);
	}

	// Print Enemy's Name
	SetCursorPosition(plusCoord(temp, D_NAME_INFO_ENEMY));
	cout << Enemies[num]->GetName();

	// Set text attribute by enemy's status
	SetDefaultTextAttribute();
	SetTextAttributeByStatus(ENEMY, num);

	// Print Enemy's HP
	SetCursorPosition(plusCoord(temp, D_HP_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_HP_INFO));
	cout << Enemies[num]->GetHP();

	// Print Enemy's MP
	SetCursorPosition(plusCoord(temp, D_MP_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MP_INFO));
	cout << Enemies[num]->GetMP();

	// Print Enemy's Physical ATK
	SetCursorPosition(plusCoord(temp, D_PATK_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_PATK_INFO));
	cout << Enemies[num]->GetPATK();

	// Print Enemy's Magical ATK
	SetCursorPosition(plusCoord(temp, D_MATK_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MATK_INFO));
	cout << Enemies[num]->GetMATK();

	// Print Enemy's Physical DEF
	SetCursorPosition(plusCoord(temp, D_PDEF_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_PDEF_INFO));
	cout << Enemies[num]->GetPDEF();

	// Print Enemy's Magical DEF
	SetCursorPosition(plusCoord(temp, D_MDEF_INFO));
	// Clear the previous data
	ClearGird();
	SetCursorPosition(plusCoord(temp, D_MDEF_INFO));
	cout << Enemies[num]->GetMDEF();

	SetCursorPosition(plusCoord(temp, D_EQ_INFO));
	// Print the three top Equipments
	// To avoid exceeds the frame
	SetCursorPosition(plusCoord(temp, D_EQ_INFO));
	// Output at most 3 equipments
	if (Enemies[num]->GetEquipments()[0] != NULL) {
		cout << Enemies[num]->GetEquipments()[0]->GetName();
	}
	for (int i = 1; (i < Enemies[num]->GetEquipmentNum() - 1) && (i < 3); i++) {
		cout << ", " << Enemies[num]->GetEquipments()[i]->GetName();
	}
	// If the equipments is more than three, output a ellipsis
	if (Enemies[num]->GetEquipmentNum() > 3) {
		cout << "...";
	}
	// If there is no equipments, output "None"
	else if (Enemies[num]->GetEquipmentNum() == 0) {
		cout << "None";
	}
	SetDefaultTextAttribute();

}

// Print a line of =
// To divide the Battlefield and Menu
void HeroManage::PrintDivision()
{
	SetCursorPosition(DIVISION_POSITION);
	SetDefaultTextAttribute();
	for (int i = 0; i < 120; i++) {
		cout << "=";
	}
}

// Print a line of " "
// A short parameter to suggest the line to clear
void HeroManage::ClearLine(short line)
{
	COORD temp = { 0, line };
	SetCursorPosition(temp);
	for (int i = 0; i < 120; i++) {
		cout << " ";
	}
}

inline void HeroManage::ClearGird(int num)
{
	int temp = 5;
	if (num != 0) {
		temp = 43;
	}
	for (int i = 0; i < temp; i++) {
		cout << " ";
	}
}

// Clear the space of instruction, options and informations
// Call the Clear Line function for 7 times
void HeroManage::ClearSpace()
{
	SetCursorPosition(INSTRUCTION_POSITION);
	for (int i = 0; i < 7; i++) {
		ClearLine(INSTRUCTION_POSITION.Y + i);
	}
}

// Print the basic menu
// Call different function according to the selected option
// Have options: Attack Skill Equipment Information Quit
void HeroManage::PrintBaseMenu()
{
	OptionName.clear();
	SelectNum = 0;
	ClearLine(OPTION[0].Y);

	// Print the Attack option
	// Set it to the chosen option
	SetChosenTextAttribute();
	SetCursorPosition(OPTION[0]);
	cout << "Attack";
	OptionName.push_back("Attack");
	// Set back the text attribute
	SetDefaultTextAttribute();

	// Print the Skill option
	SetCursorPosition(OPTION[1]);
	cout << "Skill";
	OptionName.push_back("Skill");

	// Print the Equipment option
	SetCursorPosition(OPTION[2]);
	cout << "Equipment";
	OptionName.push_back("Equipment");

	// Print the Information option
	SetCursorPosition(OPTION[3]);
	cout << "Information";
	OptionName.push_back("Information");

	// Print the Quit option
	SetCursorPosition(OPTION[4]);
	cout << "Quit";
	OptionName.push_back("Quit");
}

// Print attack menu of Heros
// Have two options: Normal, Special
void HeroManage::PrintAttackMenu()
{
	OptionName.clear();
	SelectNum = 0;
	ClearLine(OPTION[0].Y);

	// Print the Attack option 
	// Set it to the chosen option
	SetChosenTextAttribute();
	SetCursorPosition(OPTION[0]);
	cout << "Normal";
	OptionName.push_back("Normal");
	SetDefaultTextAttribute();

	// Print the Special option
	if (Heros[1]->GetSpecialAllowance()) {
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else {
		SetTextAttribute(FOREGROUND_BLUE);
	}
	SetCursorPosition(OPTION[1]);
	cout << "Special";
	OptionName.push_back("Special");
	SetDefaultTextAttribute();

	// Print the Back option to back to the base menu
	SetCursorPosition(OPTION[2]);
	cout << "Back";
	OptionName.push_back("Back");

	SetCursorPosition(INFO_POSITION);
	Heros[1]->PrintAttackInfo();
}

// Print skill menu of Heros
// Have differentoptions according to heros
// If the skill can be used, print it in white
// If not, print it in gray
void HeroManage::PrintSkillMenu()
{
	OptionName.clear();
	SelectNum = 0;
	ClearLine(OPTION[0].Y);

	vector<string> temp = Heros[1]->GetSkills();
	
	// Print Skill-1's name and Set it to the chosen option
	SetChosenTextAttribute();
	SetCursorPosition(OPTION[0]);
	cout << temp[0];
	OptionName.push_back(temp[0]);

	// Set the text attribute back to the default
	SetDefaultTextAttribute();

	// Print Skill-2's name
	SetCursorPosition(OPTION[1]);
	cout << temp[1];
	OptionName.push_back(temp[1]);

	// Print Back option
	SetCursorPosition(OPTION[2]);
	cout << "Back";
	OptionName.push_back("Back");

	SetCursorPosition(INFO_POSITION);
	if (Heros[1]->GetMP() >= 20) {
		Heros[1]->PrintSkill1Info();
	}
	else {
		cout << "You do not have enough MP.";
	}
}

// Print equipment menu
// Including Information and Synthesis
void HeroManage::PrintEquipmentMenu()
{
	OptionName.clear();
	SelectNum = 0;
	ClearLine(OPTION[0].Y);

	// Print Information option and set it to the chosen option
	SetChosenTextAttribute();
	SetCursorPosition(OPTION[0]);
	cout << "Information";
	OptionName.push_back("Information");
	// Set back the text attribute
	SetDefaultTextAttribute();

	// Print the Synthesis option
	if (Heros[1]->GetEquipmentNum() != 5) {
		SetTextAttribute(FOREGROUND_BLUE);
	}
	else {
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	SetCursorPosition(OPTION[1]);
	cout << "Synthesis";
	OptionName.push_back("Synthesis");
	SetDefaultTextAttribute();

	// Print the Back Option
	SetCursorPosition(OPTION[2]);
	cout << "Back";
	OptionName.push_back("Back");
	
	SetCursorPosition(INFO_POSITION);
	cout << "Look for hero's equipments' information in detail.";
}

// Print equipments of heros
// The systhesis equipment should be at the top
// There should at most 5 equipment
// if there is none, print None message(a sentence)
void HeroManage::PrintEquipmentInfoMenu()
{
	OptionName.clear();
	SelectNum = 0;
	ClearLine(OPTION[0].Y);
	ClearLine(OPTION[0].Y + 1);

	Equipment** temp = Heros[1]->GetEquipments();
	int counter = 0;
	// While there is still equipment left
	// Print its name
	for (int i = 0; i < 5; i++) {
		counter = i;
		if (temp[i] == NULL) {			
			break;
		}
		// If it is the first equipment
		// Set it to the chosen text attribute
		if (i == 0) {
			SetChosenTextAttribute();
		}
		SetCursorPosition(OPTION[i]);
		OptionName.push_back(temp[i]->GetName());
		cout << temp[i]->GetName();
		if (i == 0) {
			SetDefaultTextAttribute();
		}
	}
	// If there is no equipment
	// Set the Back option to the chosen text attribute
	if (counter == 0) {
		SetChosenTextAttribute();
	}

	SetCursorPosition(OPTION[Heros[1]->GetEquipmentNum()]);
	cout << "Back";
	OptionName.push_back("Back");

	if (counter == 0) {
		SetDefaultTextAttribute();
	}

	SetCursorPosition(INFO_POSITION);
	if (counter == 0) {
		if (Heros[1]->GetEquipmentNum() == 0) {
			cout << "Back to the equipment menu.";
		}
		else {
			Heros[1]->GetEquipments()[0]->PrintInfo();
		}
	}
	else if (counter > 0) {
		Heros[1]->GetEquipments()[0]->PrintInfo();
	}
}

// Print information of heros
// HP and MP should be present by graph
// Equipment should be printed in one line
void HeroManage::PrintHeroInfoMenu()
{
	for (int i = 0; i < 4; i++) {
		ClearLine(INSTRUCTION_POSITION.Y + i);
	}
	// Print Hero's Name in yellow
	SetCursorPosition(INSTRUCTION_POSITION);
	SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << Heros[1]->GetName() << endl;

	// Print Hero's HP
	// According Hero's HP value, print in different color
	SetDefaultTextAttribute();
	cout << "HP: ";
	if (Heros[1]->GetHP() >= 50) {
		SetTextAttribute(BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	}
	else if (Heros[1]->GetHP() >= 30) {
		SetTextAttribute(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	}
	else if (Heros[1]->GetHP() >= 0) {
		SetTextAttribute(BACKGROUND_RED | BACKGROUND_INTENSITY);
	}
	for (int i = 0; i * 5 < Heros[1]->GetHP() && i < 20; i++) {
		cout << " ";
	}

	// Print Hero's MP
	// Print it all in purple
	SetCursorPosition(OPTION[3]);
	SetDefaultTextAttribute();
	cout << "MP: ";
	SetTextAttribute(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
	for (int i = 0; i * 5 < Heros[1]->GetMP() && i < 20; i++) {
		cout << " ";
	}
	cout << endl;
	SetDefaultTextAttribute();

	// Print Hero's Physical Attack
	// The part that over 100 should be print in yellow
	// If it is no more than 100, print in white
	cout << "Physical Attack: ";
	if (Heros[1]->GetPATK() > 100) {
		cout << "100 + ";
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << Heros[1]->GetPATK() - 100;
		SetDefaultTextAttribute();
	}
	else if (Heros[1]->GetPATK() <= 100) {
		cout << Heros[1]->GetPATK();
	}

	// Print Hero's Magical Attack
	// The part that over 100 should be print in yellow
	// If it is no more than 100, print in white
	COORD temp = { 0, 1 };
	SetCursorPosition(plusCoord(OPTION[3], temp));
	cout << "Magical Attack: ";
	if (Heros[1]->GetMATK() > 100) {
		cout << "100 + ";
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << Heros[1]->GetMATK() - 100;
		SetDefaultTextAttribute();
	}
	else if (Heros[1]->GetMATK() <= 100) {
		cout << Heros[1]->GetMATK();
	}
	cout << endl;

	// Print Hero's Physical Defence
	// The part that over 100 should be print in yellow
	// If it is no more than 100, print in white
	temp.Y++;
	cout << "Physical Defence: ";
	if (Heros[1]->GetPDEF() > 100) {
		cout << "100 + ";
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << Heros[1]->GetPDEF() - 100;
		SetDefaultTextAttribute();
	}
	else if (Heros[1]->GetPDEF() <= 100) {
		cout << Heros[1]->GetPDEF();
	}
	
	// Print Hero's Magical Defence
	// The part that over 100 should be print in yellow
	// If it is no more than 100, print in white
	SetCursorPosition(plusCoord(OPTION[3], temp));
	cout << "Magical Defence: ";
	if (Heros[1]->GetMDEF() > 100) {
		cout << "100 + ";
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << Heros[1]->GetMDEF() - 100;
		SetDefaultTextAttribute();
	}
	else if (Heros[1]->GetMDEF() <= 100) {
		cout << Heros[1]->GetMDEF();
	}
	cout << endl;

	// Print Hero's equipments
	// Print in two lines
	// If there is no equipment, print "None"
	temp.Y++;
	cout << "Equipment:" << endl;
	temp.Y++;
	if (Heros[1]->GetEquipments()[0] == NULL) {
		cout << "None";
	}
	else {
		for (int i = 0; i < 5 && Heros[1]->GetEquipments()[i] != NULL; i++) {
			SetCursorPosition(plusCoord(OPTION[i], temp));
			cout << Heros[1]->GetEquipments()[i]->GetName();
		}
	}

	// Print the "Back" option
	// Can not nove the cursor from it
	// Will jump to the Base Menu until the enter key is pressed
	cout << endl;
	SetChosenTextAttribute();
	cout << "Back";
	SetDefaultTextAttribute();

	while (GetInput() != ENTER) {

	}

	// Clear the informations
	for (int i = 0; i < 7; i++) {
		ClearLine(INSTRUCTION_POSITION.Y + i);
	}

	// Print the Base Menu
	PrintInstruction("Please choose your next move:");
	PrintBaseMenu();
	SelectBaseMenu();
}

// An string variable is what it need to print
// The function will set the cursor's position and change the text attribute
void HeroManage::PrintInstruction(string words)
{
	SetCursorPosition(INSTRUCTION_POSITION);
	SetDefaultTextAttribute();
	cout << words;
}

// Print an option that is saved in OptionName
// Will not set text's attribute
void HeroManage::PrintOption(short num)
{
	if ((unsigned)num >= OptionName.size() || num < 0) {
		cerr << "Error[In PrintOption(short)] - Invalid Input of num." << endl;
		system("pause");
	}
	SetCursorPosition(OPTION[num]);
	cout << OptionName[num];
}

// Return an enum yupe to decide the input key
// WASD and Dir is allowed
// Can return the Enter
Key HeroManage::GetInput() const
{
	int ch = 0;
	
	while (1) {
		ch = _getch();

		if (ch == 97) return LEFT;
		if (ch == 100) return RIGHT;
		if (ch == 119)	return UP;
		if (ch == 115) return DOWN;
		if (ch == 13) return ENTER;
		if (ch == 224) {
			ch = _getch();
			if (ch == 75) return LEFT;
			if (ch == 77) return RIGHT;
			if (ch == 72) return UP;
			if (ch == 80) return DOWN;
		}
	}
}

// To select menu option
// Print the previous option to default text attribute
// Print the next option to chosen text attribute
// If the input is enter, call the functions
void HeroManage::SelectBaseMenu()
{
	enum Key temp;
	while ((temp = GetInput()) != ENTER) {
		if (temp == UP || temp == DOWN) {
			continue;
		}
		if (temp == LEFT) {
			if (SelectNum != 0) {
				SetDefaultTextAttribute();
				PrintOption(SelectNum);

				SelectNum--;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
		else if (temp == RIGHT) {
			if (SelectNum != OptionName.size() - 1) {
				SetDefaultTextAttribute();
				PrintOption(SelectNum);

				SelectNum++;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
	}
	if (SelectNum == 0) {
		PrintAttackMenu();
		SelectAttackMenu();
	}
	else if (SelectNum == 1) {
		PrintSkillMenu();
		SelectSkillMenu();
	}
	else if (SelectNum == 2) {
		PrintEquipmentMenu();
		SelectEquipmentMenu();
	}
	else if (SelectNum == 3) {
		PrintHeroInfoMenu();
	}
	else if (SelectNum == 4) {
		Quit();
	}

}

// To select option in Attack menu
// Output the exlanation of the nomal
// If the special is NOT available
// Print it in dark blue and the cursor should not be on it, which will lead to an instruction
// If the special is available
// Print it in yellow and print the explanation
void HeroManage::SelectAttackMenu()
{
	enum Key temp;
	while ((temp = GetInput()) != ENTER
		|| (SelectNum == 1 && !Heros[1]->GetSpecialAllowance())) {
		if (temp == UP || temp == DOWN) {
			continue;
		}
		if (temp == LEFT) {
			if (SelectNum != 0) {

				// Treat differently with the sepcial attack option
				if (SelectNum == 1 && !Heros[1]->GetSpecialAllowance()) {
					SetTextAttribute(FOREGROUND_BLUE);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else if (SelectNum == 1 && Heros[1]->GetSpecialAllowance()){
					SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					PrintOption(1);
					SetDefaultTextAttribute();
				}

				else {
					SetDefaultTextAttribute();
					PrintOption(SelectNum);
				}

				SelectNum--;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
		else if (temp == RIGHT) {
			if ((unsigned)SelectNum < OptionName.size() - 1) {

				// Treat differently with the sepcial attack option
				if (SelectNum == 1 && !Heros[1]->GetSpecialAllowance()) {
					SetTextAttribute(FOREGROUND_BLUE);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else if (SelectNum == 1 && Heros[1]->GetSpecialAllowance()) {
					SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				
				else {
					SetDefaultTextAttribute();
					PrintOption(SelectNum);
				}

				SelectNum++;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}

		// Print the explanation
		if (SelectNum == 0) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);			
			Heros[1]->PrintAttackInfo();
		}
		else if (SelectNum == 1) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			if (Heros[1]->GetSpecialAllowance()) {
				Heros[1]->PrintSpecialSkillInfo();
			}
			else {
				cout << "You need to get special equipment to use special attack.";
			}
		}
		else if (SelectNum == 2) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			cout << "Back to the base menu.";
		}
	}

	if (SelectNum == 2) {
		ClearLine(OPTION[0].Y);
		ClearLine(INFO_POSITION.Y);
		PrintBaseMenu();
		SelectBaseMenu();
	}
	else if (SelectNum == 0) {
		HeroAttack(1, SelectEnemy());
	}
	else if (SelectNum == 1) {
		ClearSpace();
		SetCursorPosition(INSTRUCTION_POSITION);
		int temp = Heros[1]->SpecialSkill();
		cout << endl;

		for (int i = 0; i < 3; i++) {
			if (!Enemies[i]->GetIsDie()) {
				Enemies[i]->SetHP(Enemies[i]->GetHP() - CalculateDamage(temp, Enemies[i]->GetPDEF() + Enemies[i]->GetMDEF()));
				if (Enemies[i]->GetHP() <= 0) {
					Enemies[i]->Die();
					EnemyNum--;
				}
				
				cout << Heros[1]->GetName() << " cause " 
					<< CalculateDamage(temp, Enemies[i]->GetPDEF() + Enemies[i]->GetMDEF())
					<< " damage to " << Enemies[i]->GetName() << "." << endl;
			}
		}
		for (int i = 0; i < 3; i++) {
			PrintEnemyInfo(i);
			PrintFrame(ENEMY, i);
			PrintInfoLabel(ENEMY, i);
		}
		if (EnemyNum <= 0) {
			NextPass();
		}
	}

}


void HeroManage::SelectSkillMenu() {
	enum Key temp;
	while ((temp = GetInput()) != ENTER
		|| (SelectNum != 2 && Heros[1]->GetMP() < 20)) {
		if (temp == UP || temp == DOWN) {
			continue;
		}
		if (temp == LEFT) {
			if (SelectNum != 0) {
				SetDefaultTextAttribute();
				PrintOption(SelectNum);


				SelectNum--;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
		else if (temp == RIGHT && SelectNum != 2) {
			SetDefaultTextAttribute();
			PrintOption(SelectNum);

			SelectNum++;
			SetChosenTextAttribute();
			PrintOption(SelectNum);
			SetDefaultTextAttribute();
		}
		// Print the explanation
		if (SelectNum == 0) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			if (Heros[1]->GetMP() >= 20) {
				Heros[1]->PrintSkill1Info();
			}
			else {
				cout << "You do not have enough MP.";
			}
		}
		else if (SelectNum == 1) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			if (Heros[1]->GetMP() >= 20) {
				Heros[1]->PrintSkill2Info();
			}
			else {
				cout << "You do not have enough MP.";
			}
		}
		else if (SelectNum == 2) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			cout << "Back to the base menu.";
		}
	}

	if (SelectNum == 2) {
		ClearLine(OPTION[0].Y);
		ClearLine(INFO_POSITION.Y);
		ClearLine(INFO_POSITION.Y + 1);
		PrintBaseMenu();
		SelectBaseMenu();
	}
	else if (SelectNum == 0) {
		ClearSpace();
		SetCursorPosition(INSTRUCTION_POSITION);
		Heros[1]->Skill1();
		PrintHeroInfo(1);
	}
	else if (SelectNum == 1) {
		ClearSpace();
		SetCursorPosition(INSTRUCTION_POSITION);
		Heros[1]->Skill2();
		PrintHeroInfo(1);
	}
}

// To select equipment menu
// Will print information while moving the cursor
// Do not need to call functions
void HeroManage::SelectEquipmentMenu()
{
	enum Key temp;
	while ((temp = GetInput()) != ENTER
		|| (SelectNum == 1 && Heros[1]->GetEquipmentNum() != 5)) {
		if (temp == UP || temp == DOWN) {
			continue;
		}
		if (temp == LEFT) {
			if (SelectNum != 0) {

				// Treat differently with the Synthesis option
				if (SelectNum == 1 && Heros[1]->GetEquipmentNum() != 5) {
					SetTextAttribute(FOREGROUND_BLUE);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else if (SelectNum == 1 && Heros[1]->GetEquipmentNum() ==  5){
					SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else {
					SetDefaultTextAttribute();
					PrintOption(SelectNum);
				}

				SelectNum--;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
		else if (temp == RIGHT) {
			if ((unsigned)SelectNum < OptionName.size() - 1) {

				// Treat differently with the Synthesis option
				if (SelectNum == 1 && Heros[1]->GetEquipmentNum() != 5) {
					SetTextAttribute(FOREGROUND_BLUE);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else if (SelectNum == 1 && Heros[1]->GetEquipmentNum() == 5) {
					SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN |FOREGROUND_INTENSITY);
					PrintOption(1);
					SetDefaultTextAttribute();
				}
				else {
					SetDefaultTextAttribute();
					PrintOption(SelectNum);
				}

				SelectNum++;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}

		// Print the explanation
		if (SelectNum == 0) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			cout << "Look for hero's equipments' information in detail.";
		}
		else if (SelectNum == 1) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			if (Heros[1]->GetEquipmentNum() == 5) {
				cout << "Use all your equipments to synthesis the special equipment.";
			}
			else {
				cout << "You need to get 5 equipments to synthesis.";
			}
		}
		else if (SelectNum == 2) {
			ClearLine(INFO_POSITION.Y);
			ClearLine(INFO_POSITION.Y + 1);

			SetCursorPosition(INFO_POSITION);
			cout << "Back to the base menu.";
		}
	}

	if (SelectNum == 2) {
		ClearLine(OPTION[0].Y);
		ClearLine(INFO_POSITION.Y);
		PrintBaseMenu();
		SelectBaseMenu();
	}
	else if (SelectNum == 0) {
		PrintEquipmentInfoMenu();
		SelectEquipmentInfo();
	}
	else if (SelectNum == 1) {
		Heros[1]->Synthesis();
		ClearSpace();
		SetCursorPosition(INSTRUCTION_POSITION);
		SetTextAttribute(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << "Synthesis Succeed!";
		SetDefaultTextAttribute();
		PrintHeroInfo(1);
	}
}

// To select equipment to print its info while moving cursor
// Only back can be select as an option
void HeroManage::SelectEquipmentInfo() {
	enum Key temp;
	while ((temp = GetInput()) != ENTER
		|| (SelectNum != Heros[1]->GetEquipmentNum())) {
		if (temp == UP || temp == DOWN) {
			continue;
		}
		if (temp == LEFT) {
			if (SelectNum != 0) {
				SetDefaultTextAttribute();
				PrintOption(SelectNum);

				SelectNum--;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}
		else if (temp == RIGHT) {
			if (SelectNum != OptionName.size() - 1) {
				SetDefaultTextAttribute();
				PrintOption(SelectNum);

				SelectNum++;
				SetChosenTextAttribute();
				PrintOption(SelectNum);
				SetDefaultTextAttribute();
			}
		}

		for (int i = 0; i < 3; i++) {
			ClearLine(INFO_POSITION.Y + i);
		}
		SetCursorPosition(INFO_POSITION);
		if (SelectNum == Heros[1]->GetEquipmentNum()) {
			
			cout << "Back to the equipment menu.";
		}
		else {
			Heros[1]->GetEquipments()[SelectNum]->PrintInfo();
		}
	}

	PrintEquipmentMenu();
	SelectEquipmentMenu();
}

// To select an enemy to attack
// Will Clear the space of instruction, options and information
// Print the instruction to select enemy
// And the cursor will on the alive enemies
// Return the enemy's num to attack
int HeroManage::SelectEnemy()
{
	ClearSpace();
	PrintInstruction("Please select the enemy you want to attack.");
	SelectNum = 0;
	while (Enemies[SelectNum]->GetIsDie()) {
		SelectNum++;
	}

	SetChosenTextAttribute();
	PrintFrame(ENEMY, SelectNum);
	SetDefaultTextAttribute();

	enum Key temp;
	while ((temp = GetInput()) != ENTER
		|| (Enemies[SelectNum]->GetIsDie())) {
		if (temp == UP) {
			if (SelectNum != 0) {
				int previous = SelectNum;
				SelectNum = SelectNum - 1;
				while (SelectNum >= 0 && Enemies[SelectNum]->GetIsDie()) {
					SelectNum--;
				}
				if (previous != SelectNum && !Enemies[SelectNum]->GetIsDie()) {
					SetDefaultTextAttribute();
					PrintFrame(ENEMY, previous);

					SetChosenTextAttribute();
					PrintFrame(ENEMY, SelectNum);

					SetDefaultTextAttribute();
				}
				else {
					SelectNum = previous;
				}
			}
		}
		else if (temp == DOWN) {
			if (SelectNum != 2) {
				int previous = SelectNum;
				SelectNum = SelectNum + 1;
				while (SelectNum <= 2 && Enemies[SelectNum]->GetIsDie()) {
					SelectNum++;
				}
				if (previous != SelectNum) {
					SetDefaultTextAttribute();
					PrintFrame(ENEMY, previous);

					SetChosenTextAttribute();
					PrintFrame(ENEMY, SelectNum);

					SetDefaultTextAttribute();
				}
				else
				{
					SelectNum = previous;
				}
			}
		}
	}

	SetDefaultTextAttribute();
	PrintFrame(ENEMY, SelectNum);
	return SelectNum;
}


//**********************************************************************************


// Gaming Functions:
//**********************************************************************************

// Calculate the damage
// Inline function
// Accept two int represent the attacker's total attack and the suffer's total defenct
// Return the damage the suffer's should suffer
int HeroManage::CalculateDamage(int ATK, int DEF)
{
	return static_cast<int>((ATK - DEF * 0.8) / 2);
}

// Move to next pass
// Clear screen and pop the congratulations using message box
// reset three enemies
// PassCounter plus 1
void HeroManage::NextPass()
{
	PassCounter++;
	srand(static_cast<unsigned int>(time(0)));
	if (MessageBox(NULL, TEXT("You have clear the stage!\nAre you want to go to next stage?"), TEXT("Tip"), MB_OKCANCEL) == IDOK
		|| MessageBox(NULL, TEXT("Are you shure you want to quit this game?"), TEXT("Tip"), MB_OKCANCEL) == IDCANCEL) {
		for (int i = 0; i < 3; i++) {
			
			delete Enemies[i];
			Enemies[i] = NULL;

			Enemies[i] = new Enemy(EnemyName[rand() % 15], PassCounter);

			if (rand() % 2 == 1) {
				*Enemies[i] += new AttackEquipment(rand());
			}
			else {
				*Enemies[i] += new DefenceEquipment(rand());
			}

			if (!Heros[i]->GetIsDie()) {
				Heros[i]->SetMP(Heros[i]->GetMP() + 50);
				Heros[i]->SetHP(Heros[i]->GetHP() + 50);
			}
			
		}

		EnemyNum = 3;
		system("cls");
		PrintField();
	}
	else {
		GameOver = true;
	}
}

// If the player is dead, than call this function
void HeroManage::Gameover()
{
	MessageBox(NULL, TEXT("You are dead!"), TEXT("Tip"), MB_OK);
	GameOver = true;
}

// Set GameOver to True
void HeroManage::Quit()
{
	if (MessageBox(NULL, TEXT("Are you sure you want to quit this game?"), TEXT("Tip"), MB_OKCANCEL) == IDOK) {
		GameOver = true;
	}
	else {
		PrintBaseMenu();
		SelectBaseMenu();
	}
}



ArtoriaPendragon::ArtoriaPendragon(): Hero("Altoria Pendragon", "Charisma", "Instinct")
{
}

ArtoriaPendragon::~ArtoriaPendragon()
{
}

void ArtoriaPendragon::PrintAttackInfo() const
{
	cout << "Using the sword to attack with honor of Great Britain." << endl;
	cout << "Causing great damage to it.";
}

void ArtoriaPendragon::PrintSkill1Info() const
{
	cout << "Ues the power of Avallon." << endl;
	cout << "Get 50 of HP.";
}

void ArtoriaPendragon::PrintSkill2Info() const
{
	cout << "Gain the power from Great Britain." << endl;
	cout << "Get 20 Pysical ATK and 20 Magical ATK.";
}

void ArtoriaPendragon::PrintSpecialSkillInfo() const
{
	cout << "Not a man-made weapon, but a Divine Construct forged by the planet." << endl;
	cout << "A Noble Phantasm that stands at the top of all holy swords.";
}

void ArtoriaPendragon::PrintEquipmentInfo(short num)
{
	cout << GetEquipments()[num]->GetInfo();
}

void ArtoriaPendragon::PrintAttackWord() const
{
	cout << "My sword will follow your guidance. My fate will go where you lead.";
}

void ArtoriaPendragon::PrintDefenceWord() const
{
	cout << "No big problem, Master.";
}

void ArtoriaPendragon::Die()
{
	SetIsDie(true);
	cout << "I...I still have people to save...";
}

void ArtoriaPendragon::Skill1()
{
	SetMP(GetMP() - 20);
	SetHP(GetHP() + 50);
	cout << "As the wish of Avallon...I pray for a guidance to success...";
}

void ArtoriaPendragon::Skill2()
{
	SetMP(GetMP() - 20);
	SetPATK(GetPATK() + 20);
	SetMATK(GetMATK() + 20);
	cout << "To defeat the enemies, please give me your power, Master!";
}

int ArtoriaPendragon::SpecialSkill()
{
	cout << "束ねるは星の息吹。";
	Sleep(1000);
	cout << "輝ける命の奔流。";
	Sleep(1000);
	cout << "受けるが良い！";
	Sleep(1000);
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "『約束された勝利の剣』！！";
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	return static_cast<int>(floor(0.7 * (GetPATK() + GetMATK())));
}

void ArtoriaPendragon::Synthesis()
{
	Hero::Synthesis();
	if (dynamic_cast<SynthesisEquipment*>(GetEquipments()[0]) == NULL) {
		cerr << "Error[In Synthesis()] - Invalid type of equipment.";
	}
	GetEquipments()[0]->SetName("Excaliburn" + (string)" Lv." + to_string(dynamic_cast<SynthesisEquipment*>(GetEquipments()[0])->GetCounter()));
	GetEquipments()[0]->SetInfo("It is not the sword, but its scabbard that truly possesses an outstanding ability.\nHowever, that scabbard has been forever lost.");
}

TamamoNoMae::TamamoNoMae():
	Hero("Tamamo no Mae", "Shapeshift", "Witchcraft")
{}

TamamoNoMae::~TamamoNoMae()
{
}

// Print attack explanation words when the cursor is on the Attack option
// It will be different for different heros so it is virtual
// Do not need to set cursor's position
void TamamoNoMae::PrintAttackInfo() const
{
	cout << "Use her witch mirro to reflect the light of sun." << endl;
	cout << "Cause sacred damage.";
}

void TamamoNoMae::PrintSkill1Info() const
{
	cout << "Change the posture of herself to defend." << endl;
	cout << "Get extra 20 points of physical defence and magical defence.";
}

void TamamoNoMae::PrintSkill2Info() const
{
	cout << "Get the mysterious power from the mirro." << endl;
	cout << "Get extra 20 points of magical attack and MP.";
}

void TamamoNoMae::PrintSpecialSkillInfo() const
{
	cout << "A Noble Phantasm in the shape of a mirror" << endl;
	cout << "The temporarily released form of the sacred treasure Tamamo Shizuishi.";
}

void TamamoNoMae::PrintEquipmentInfo(short num)
{
	cout << GetEquipments()[num]->GetInfo();
}

void TamamoNoMae::PrintAttackWord() const
{
	cout << "Yes, my darling! I will defeat anyone who want to hurt you.";
}

void TamamoNoMae::PrintDefenceWord() const
{
	cout << "@_@ I shall became angry now...";
}

void TamamoNoMae::Die()
{
	SetIsDie(true);
	cout << "My darling...I can't be without you...please...";
}

void TamamoNoMae::Skill1()
{
	SetMP(GetMP() - 20);
	SetPDEF(GetPDEF() + 20);
	SetMDEF(GetMDEF() + 20);
	cout << "(*v*)~The power of love, Get!";
}

void TamamoNoMae::Skill2()
{
	SetMP(GetMP() - 20);
	SetMATK(GetMATK() + 20);
	SetMP(GetMP() + 40);
	cout << "Kilikili~ Kilikili~";
}

int TamamoNoMae::SpecialSkill()
{
	cout << "出云に神在り。";
	Sleep(1000);
	cout << "是自在にして禊ぎの证、";
	Sleep(1000);
	cout << "神宝宇迦之镜也。";
	Sleep(1000);
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "『水天日光天照八野镇石すいてんにっこうあまてらすやのしずいし』" << endl;
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	Sleep(1000);
	cout << "……なんちゃって~";
	return static_cast<int>(floor(0.7 * (GetPATK() + GetMATK())));
}

void TamamoNoMae::Synthesis()
{
	Hero::Synthesis();
	if (dynamic_cast<SynthesisEquipment*>(GetEquipments()[0]) == NULL) {
		cerr << "Error[In Synthesis()] - Invalid type of equipment.";
	}
	GetEquipments()[0]->SetName("Shizuishi" + (string)" Lv." + to_string(dynamic_cast<SynthesisEquipment*>(GetEquipments()[0])->GetCounter()));
	GetEquipments()[0]->SetInfo("Originally a sacred treasure of the netherword that could even ressurect the dead\nBut her current self cannot draw out that much power.");
}

Gilgamesh::Gilgamesh():
	Hero("Gilgamesh", "Golden Rule", "Collector")
{}

Gilgamesh::~Gilgamesh()
{}

void Gilgamesh::PrintAttackInfo() const
{
	cout << "Release the strong power of Enuma Elish." << endl;
	cout << "Cause multiple damage to the enemies";
}

void Gilgamesh::PrintSkill1Info() const
{
	cout << "The Rule of the Great Story, The Epic of Gilgamesh" << endl;
	cout << "Get extra 20 HP and 10 points of physical defence and 10 points of magical defence.";
}

void Gilgamesh::PrintSkill2Info() const
{
	cout << "The Great treasure of the acient king." << endl;
	cout << "Get extra 10 points of physical attack and magical attack, and 10 MP.";
}

void Gilgamesh::PrintSpecialSkillInfo() const
{
	cout << "The Sword of Rupture – Ea that distorts space." << endl;
	cout << "It is the top ranked Noble Phantasm, a sword that \"cuts the world.\"";
}

void Gilgamesh::PrintEquipmentInfo(short num)
{
	cout << GetEquipments()[num]->GetInfo();
}

void Gilgamesh::PrintAttackWord() const
{
	cout << "Disgusting! Why I, the Great King, need to do this.";
}

void Gilgamesh::PrintDefenceWord() const
{
	cout << "You dare to challenge me! You will pay for your stupid behaviour!";
}

void Gilgamesh::Die()
{
	SetIsDie(true);
	cout << "Impossible...It can't happen...I don't believe it...";
}

void Gilgamesh::Skill1()
{
	SetMP(GetMP() - 20);
	SetHP(GetHP() + 20);
	SetPDEF(GetPDEF() + 10);
	SetMDEF(GetMDEF() + 10);
	cout << "Fine, then I will play with you a little.";
}

void Gilgamesh::Skill2()
{
	SetMP(GetMP() - 20);
	SetPATK(GetPATK() + 10);
	SetMATK(GetMATK() + 10);
	SetMP(GetMP() + 30);
	cout << "Your soul will be suffered!";
}

int Gilgamesh::SpecialSkill()
{
	cout << "裁きの時だ。";
	Sleep(1000);
	cout << "世界を裂くは我が乖離剣！";
	Sleep(1000);
	cout << "受けよ！";
	Sleep(1000);
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "『天地乖離す開闢の星 』！！";
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	return static_cast<int>(floor(0.7 * (GetPATK() + GetMATK())));
}

void Gilgamesh::Synthesis()
{
	Hero::Synthesis();
	if (dynamic_cast<SynthesisEquipment*>(GetEquipments()[0]) == NULL) {
		cerr << "Error[In Synthesis()] - Invalid type of equipment.";
	}
	GetEquipments()[0]->SetName("Enuma" + (string)" Lv." + to_string(dynamic_cast<SynthesisEquipment*>(GetEquipments()[0])->GetCounter()));
	GetEquipments()[0]->SetInfo("A sword which name was given after the god of Mesopotamian myth.");
}

JeannedArc::JeannedArc() :
	Hero("Jeanne d'Arc", "God's Resolution", "Revelation")
{}

JeannedArc::~JeannedArc()
{}

void JeannedArc::PrintAttackInfo() const
{
	cout << "Use her great soul as the source of power" << endl;
	cout << "Cause sacred damage to the enemies";
}

void JeannedArc::PrintSkill1Info() const
{
	cout << "The resolution from the God" << endl;
	cout << "Get extra 10 points of physical defence, magical defence, physical attack and magical attack.";
}

void JeannedArc::PrintSkill2Info() const
{
	cout << "Revelation of the future, get the ability to predict." << endl;
	cout << "Get extra 40 points of physical attack or physical defence.";
}

void JeannedArc::PrintSpecialSkillInfo() const
{
	cout << "\"O Lord, I entrust this body to you--\"" << endl;
	cout << "These are the words to activate this Concept Crystallization Weapon.";
}

void JeannedArc::PrintEquipmentInfo(short num)
{
	cout << GetEquipments()[num]->GetInfo();
}

void JeannedArc::PrintAttackWord() const
{
	cout << "Lord, please save the pity soul.";
}

void JeannedArc::PrintDefenceWord() const
{
	cout << "May god forgive your rudeness";
}

void JeannedArc::Die()
{
	SetIsDie(true);
	cout << "Lord, why the ending should be like that...";
}

void JeannedArc::Skill1()
{
	SetMP(GetMP() - 20);
	SetPATK(GetPATK() + 10);
	SetMATK(GetMATK() + 10);
	SetPDEF(GetPDEF() + 10);
	SetMDEF(GetMDEF() + 10);
	cout << "Let us pary for the redemption...";
}

void JeannedArc::Skill2()
{
	SetMP(GetMP() - 20);
	srand(static_cast<unsigned int>(time(0)));
	if (rand() % 2) {
		SetPATK(GetPATK() + 40);
	}
	else {
		SetPDEF(GetPDEF() + 40);
	}
	cout << "Finally, We can see what this cruel world is going to be...";
}

int JeannedArc::SpecialSkill()
{
	cout << "我が旗よ、";
	Sleep(1000);
	cout << "我が同胞を守りたまえ！";
	Sleep(1000);
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "『我が神はここにありて』！";
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	return static_cast<int>(floor(0.7 * (GetPATK() + GetMATK())));
}

void JeannedArc::Synthesis()
{
	Hero::Synthesis();
	if (dynamic_cast<SynthesisEquipment*>(GetEquipments()[0]) == NULL) {
		cerr << "Error[In Synthesis()] - Invalid type of equipment.";
	}
	GetEquipments()[0]->SetName("Luminosite" + (string)" Lv." + to_string(dynamic_cast<SynthesisEquipment*>(GetEquipments()[0])->GetCounter()));
	GetEquipments()[0]->SetInfo("It is a variant of Reality Marble that crystallizes the mental landscape of the user into a sword.");
}


ZhugeLiang::ZhugeLiang() :
	Hero("Zhuge Liang (Lord El-Melloi II)", "Discerning Eye", "Strategist's Advice")
{}

ZhugeLiang::~ZhugeLiang()
{}

void ZhugeLiang::PrintAttackInfo() const
{
	cout << "Learn from the ancient Chinese, use wisdom to attack." << endl;
	cout << "Cause small damage to the enemies";
}

void ZhugeLiang::PrintSkill1Info() const
{
	cout << "The great ability to appreciate, give himself inspirations" << endl;
	cout << "Get extra 40 HP and 10 points of physical attack and magical attack.";
}

void ZhugeLiang::PrintSkill2Info() const
{
	cout << "Think objectivly with the great mind. Learned more clearly with the situation." << endl;
	cout << "Get extra 20 points of physical and magical attack or 20 points of physical and magical defence.";
}

void ZhugeLiang::PrintSpecialSkillInfo() const
{
	cout << "Composed by huge rocks." << endl;
	cout << "Said formation bewildered invaders and drove them to death.";
}

void ZhugeLiang::PrintEquipmentInfo(short num)
{
	cout << GetEquipments()[num]->GetInfo();
}

void ZhugeLiang::PrintAttackWord() const
{
	cout << "It's a trap! I know from the very beginning!";
}

void ZhugeLiang::PrintDefenceWord() const
{
	cout << "Don't worry, it's in my plan.";
}

void ZhugeLiang::Die()
{
	SetIsDie(true);
	cout << "I can't calculate this...It's too difficult with so many posibilities...";
}

void ZhugeLiang::Skill1()
{
	SetMP(GetMP() - 20);
	SetHP(GetHP() + 40);
	SetPATK(GetPATK() + 10);
	SetMATK(GetMATK() + 10);
	cout << "I admire you a lot, my Master.";
}

void ZhugeLiang::Skill2()
{
	SetMP(GetMP() - 20);
	if (GetPATK() + GetMATK() > GetPDEF() + GetMDEF()) {
		
		SetPDEF(GetPDEF() + 20);
		SetMDEF(GetMDEF() + 20);
	}
	else {
		SetPATK(GetPATK() + 20);
		SetMATK(GetMATK() + 20);
	}
	cout << "It's a nice step, Master. I can't wait to see the result.";
}

int ZhugeLiang::SpecialSkill()
{
	cout << "これぞ大軍師の究極陣地、";
	
	Sleep(1000);
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "『石兵八陣 』！";
	SetConsoleTextAttribute(HANDLE_OUT, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	Sleep(1000);
	cout << "　……破ってみせるがいい";
	return static_cast<int>(floor(0.7 * (GetPATK() + GetMATK())));
}

void ZhugeLiang::Synthesis()
{
	Hero::Synthesis();
	if (dynamic_cast<SynthesisEquipment*>(GetEquipments()[0]) == NULL) {
		cerr << "Error[In Synthesis()] - Invalid type of equipment.";
	}
	GetEquipments()[0]->SetName("Sentinel Maze" + (string)" Lv." + to_string(dynamic_cast<SynthesisEquipment*>(GetEquipments()[0])->GetCounter()));
	GetEquipments()[0]->SetInfo("A legendary military formation set by Zhuge Liang\nAt the occasion when he decided for his army to take flight.");
}