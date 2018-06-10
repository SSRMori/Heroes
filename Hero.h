#ifndef Hero_H_
#define Hero_H_

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <time.h>
#include <cstdlib>
#include "AttackEquipment.h"
#include "DefenceEquipment.h"
#include "SynthesisEquipment.h"
using namespace std;

enum ObjectType { HERO = 0, ENEMY = 1, MENU = 2 };
enum Key { UP, DOWN, LEFT, RIGHT, ENTER };

class Hero
{
	// A += operator to add an equipment to the hero
	// If the equipment is added successfully, it will return true
	// Else if there has already been 5 equipment, the addition will fail and false will be returned
	friend bool operator+=(Hero&, Equipment*);

	// A -= operator to delete an equipment from the hero
	// It will delete the equipment by name 
	// And only one equipment will be deleted among the equipment of the same name
	friend bool operator-=(Hero&, string&);

	// A -= operator to delete an equipment from the hero
	// It will delete the equipment by index
	// An invalid index will lead to an error
	friend bool operator-=(Hero&, short);

	// A -= operator to delete and equipment from the hero
	// It will delete the equipment by its type
	// A typeid function will be used there
	// And only one equipment will be deleted among the equipment of the same name
	friend bool operator-=(Hero&, Equipment*);
public:
	explicit Hero(string, string, string);
	Hero(Hero&);
	virtual ~Hero();

	// Set functions
	void SetName(string);
	void SetHP(int);
	void SetMP(int);
	void SetPATK(int);
	void SetMATK(int);
	void SetPDEF(int);
	void SetMDEF(int);
	void SetIsDie(bool);
	void SetSpecialAllowance(bool);
	void SetEquipments(Equipment**);
	void SetEquipmentNum(int);
	void SetSkills(vector<string>);

	// Get functions
	string GetName();
	int GetHP();
	int GetMP();
	int GetPATK();
	int GetMATK();
	int GetPDEF();
	int GetMDEF();
	bool GetIsDie();
	bool GetSpecialAllowance();
	Equipment** GetEquipments();
	int& GetEquipmentNum();
	vector<string> GetSkills();

// EXPLANATION-PRINT FUNCTIONS:
// *************************************************************************************

	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	virtual void PrintAttackInfo() const = 0;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	virtual void PrintSkill1Info() const = 0;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	virtual void PrintSkill2Info() const = 0;

	virtual void PrintSpecialSkillInfo() const = 0;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short) const;

// MOVE FUNCTIONS:
// ************************************************************************************

	// Print the attack words when attacking
	virtual void PrintAttackWord() const = 0;

	// Print the defenct words when defencing
	virtual void PrintDefenceWord() const = 0;

	// Set the IsDie to True
	// Print Diewords
	virtual void Die() = 0;

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	virtual void Skill1() = 0;
	virtual void Skill2() = 0;

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	virtual int SpecialSkill() = 0;

	// Synthesis all the equipment to a synthesis equipment
	// If the number of Equipment is less than 5, there will be an error
	// It will clear the Equipments pointer and add a new Synthesis
	// It will set the SpecialAllowance to true
	virtual void Synthesis();

private:
	string Name;
	int HP;
	int MP;
	int PATK;
	int MATK;
	int PDEF;
	int MDEF;
	bool IsDie;
	bool SpecialAllowance;
	Equipment** Equipments;
	int EquipmentNum;
	vector<string> Skills;
};

class ArtoriaPendragon : public Hero
{
public:
	ArtoriaPendragon();
	~ArtoriaPendragon();
	// EXPLANATION-PRINT FUNCTIONS:
	// *************************************************************************************
	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintAttackInfo() const;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill1Info() const;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill2Info() const;

	virtual void PrintSpecialSkillInfo() const;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short);

	// MOVE FUNCTIONS:
	// ************************************************************************************
	// Print the attack words when attacking
	void PrintAttackWord() const;

	// Print the defenct words when defencing
	void PrintDefenceWord() const;

	// Set the IsDie to True
	// Print Diewords
	void Die();

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	void Skill1();
	void Skill2();

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	int SpecialSkill();

	// Call the Synthesis in hero 
	// Set the Info and the Name of the Equipment
	void Synthesis();
};

class TamamoNoMae : public Hero
{
public:
	TamamoNoMae();
	~TamamoNoMae();
	// EXPLANATION-PRINT FUNCTIONS:
	// *************************************************************************************
	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintAttackInfo() const;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill1Info() const;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill2Info() const;

	virtual void PrintSpecialSkillInfo() const;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short);

	// MOVE FUNCTIONS:
	// ************************************************************************************
	// Print the attack words when attacking
	void PrintAttackWord() const;

	// Print the defenct words when defencing
	void PrintDefenceWord() const;

	// Set the IsDie to True
	// Print Diewords
	void Die();

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	void Skill1();
	void Skill2();

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	int SpecialSkill();

	// Call the Synthesis in hero 
	// Set the Info and the Name of the Equipment
	void Synthesis();
};

class Gilgamesh : public Hero
{
public:
	Gilgamesh();
	~Gilgamesh();
	// EXPLANATION-PRINT FUNCTIONS:
	// *************************************************************************************
	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintAttackInfo() const;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill1Info() const;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill2Info() const;

	virtual void PrintSpecialSkillInfo() const;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short);

	// MOVE FUNCTIONS:
	// ************************************************************************************
	// Print the attack words when attacking
	void PrintAttackWord() const;

	// Print the defenct words when defencing
	void PrintDefenceWord() const;

	// Set the IsDie to True
	// Print Diewords
	void Die();

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	void Skill1();
	void Skill2();

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	int SpecialSkill();

	// Call the Synthesis in hero 
	// Set the Info and the Name of the Equipment
	void Synthesis();
};

class JeannedArc : public Hero
{
public:
	JeannedArc();
	~JeannedArc();
	// EXPLANATION-PRINT FUNCTIONS:
	// *************************************************************************************
	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintAttackInfo() const;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill1Info() const;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill2Info() const;

	virtual void PrintSpecialSkillInfo() const;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short);

	// MOVE FUNCTIONS:
	// ************************************************************************************
	// Print the attack words when attacking
	void PrintAttackWord() const;

	// Print the defenct words when defencing
	void PrintDefenceWord() const;

	// Set the IsDie to True
	// Print Diewords
	void Die();

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	void Skill1();
	void Skill2();

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	int SpecialSkill();

	// Call the Synthesis in hero 
	// Set the Info and the Name of the Equipment
	void Synthesis();
};

class ZhugeLiang : public Hero
{
public:
	ZhugeLiang();
	~ZhugeLiang();
	// EXPLANATION-PRINT FUNCTIONS:
	// *************************************************************************************
	// Print attack explanation words when the cursor is on the Attack option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintAttackInfo() const;

	// Print the explanation of skill-1 when the cursor is on the skill-1's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill1Info() const;

	// Print the explanation of skill-2 when the cursor is on the skill-2's option
	// It will be different for different heros so it is virtual
	// Do not need to set cursor's position
	void PrintSkill2Info() const;

	virtual void PrintSpecialSkillInfo() const;

	// A short parameter is referring to an equipment in the Equipments ptr
	// Print the information of the referred equipment
	void PrintEquipmentInfo(short);

	// MOVE FUNCTIONS:
	// ************************************************************************************
	// Print the attack words when attacking
	void PrintAttackWord() const;

	// Print the defenct words when defencing
	void PrintDefenceWord() const;

	// Set the IsDie to True
	// Print Diewords
	void Die();

	// Two skills of hero
	// It will be different for different hero
	// So it is pure virtual
	// It should only change the status of the hero himself
	// It will not make any attack or defence
	void Skill1();
	void Skill2();

	// To print Special Skill's word
	// return the damage of this skill to all enemies
	// And can cause changes to self's status
	int SpecialSkill();

	// Call the Synthesis in hero 
	// Set the Info and the Name of the Equipment
	void Synthesis();
};

class Enemy: public Hero
{
public:
	Enemy(string name, int passNum);
	~Enemy();
	
	void PrintAttackInfo() const;
	void PrintSkill1Info() const;
	void PrintSkill2Info() const;
	void PrintSpecialSkillInfo() const;
	void PrintAttackWord() const;
	void PrintDefenceWord() const;
	void Die();
	void Skill1();
	void Skill2();
	int SpecialSkill();
};


class HeroManage
{
	// Use += to add a Hero to the Heros
	// It will only be used at the beginning of this game
	// the Added Heros will be added in order 
	friend bool operator+=(HeroManage&, Hero&);

	// Use += to add an Enemy to the Enemies
	// It will be used whennever there is no enemy left
	// the Added Enemies will be added in order
	friend bool operator+=(HeroManage&, Enemy&);

	// Use -= to delete a Hero in the Heros
	// It will use typeid to judge which hero should be deleted
	friend bool operator-=(HeroManage&, Hero&);

	// Use -= to delete an Enemy in the Enemies
	// It will be used when the enemies are all dead
	// For the enemies will not be specified
	// So this should use name to judge which enemy should be deleted
	friend bool operator-=(HeroManage&, Enemy&);

public:
	// Constructor and Destructor
	HeroManage(int code = 0);
	HeroManage(HeroManage&);
	~HeroManage();

	// Play The Game!
	void PLAY();

	// Set functions
	void SetPassCounter(int);
	void SetHeros(Hero**);
	void SetEnemies(Enemy**);
	void SetHeroNum(short);
	void SetEnemyNum(short);
	void SetSelectNum(short);
	void SetOptionName(vector<string>);
	void SetCursor(COORD);
	void SetGameOver(bool);

	// Get functions
	int GetPassCounter() const;
	Hero** GetHeros() const;
	Enemy** GetEnemies() const;
	short GetHeroNum() const;
	short GetEnemyNum() const;
	short GetSelectNum() const;
	vector<string> GetOptionName() const;
	COORD GetCursor() const;
	bool GetGameOver() const;

	//Functions About Play:
	//**********************************************************************************
	// Two base function to fight
	// The privious is the executor and the last is the sufferer
	void HeroAttack(int hero, int enemy);
	void EnemyAttack(int enemy, int hero);

	// Two function to handling death
	// HeroDie may change the gamestatus
	// EnemyDie may call the next pass
	void HeroDie(int hero);
	void EnemyDie(int enemy);

	// Auto Attack function
	// Call the attack function to attack
	void HeroAutoAttack(int hero);
	void EnemyAutoAttack(int enemy);
	//**********************************************************************************


	//Functions About Print Frame and Info:
	//**********************************************************************************

	// Print the welcome page
	// Return the heros that player select
	// Use integer to present hero
	int Welcome();

	// The main function in this part
	// Have many assist functions that are as follows 
	void PrintField();

	// Set text attribute to default
	// Foreground: White
	// Background: Black
	// Intensity: None
	void SetDefaultTextAttribute();

	// Set text attribute to chosen mood
	// Foreground: Black
	// Background: White
	// Intensity: None
	void SetChosenTextAttribute();

	// Set text attribute to certain mood
	// Any macro is accepted
	void SetTextAttribute(WORD);

	// Set text attribute by hero's or enemy's status
	// The input enum and short variables will refer to a hero or a enemy
	// And it will set the attribute automatically
	void SetTextAttributeByStatus(enum ObjectType, short);

	// Set cursor's position
	// A COORD to present the position you want to set
	COORD SetCursorPosition(COORD);

	// Overload the above function
	// An enum type is refered whether the object need to be printed is enemy or hero
	// An short function judge which one should be printed
	COORD SetCursorPosition(enum ObjectType, short);

	// Print Frame for the exact member
	// An Enum parameter to decide the reference of the short
	// It only for Hero and Enemy, NOT Menu, which will lead to an error
	void PrintFrame(enum ObjectType, short);

	// Print an Info Label
	// Need constant D-value for some Label
	// Enum for the reference of the short
	// A menu enum is invalid
	void PrintInfoLabel(enum ObjectType, short);

	// Print hero's information
	// A short to decide which hero to print
	void PrintHeroInfo(short);

	// Print enemy's information
	// A short to decide which enemy to print
	void PrintEnemyInfo(short);

	// Print a line of =
	// To divide the Battlefield and Menu
	void PrintDivision();

	// Print a line of " "
	// A short parameter to suggest the line to clear
	void ClearLine(short);

	// Print 5 " " to clear a gird
	// Do not set cursor's position and text attribute
	inline void ClearGird(int num = 0);

	// Clear the space of instruction, options and informations
	// Call the Clear Line function for 7 times
	void ClearSpace();

	// Print the basic menu
	// Call different function according to the selected option
	// Have options: Attack Skill Equipment Information Quit
	void PrintBaseMenu();

	// Print attack menu of Heros
	// Have two options: Attack Special
	void PrintAttackMenu();

	// Print skill menu of Heros
	// Have differentoptions according to heros
	// If the skill can be used, print it in white
	// If not, print it in gray
	void PrintSkillMenu();

	// Print equipment menu
	// Including Information and Synthesis
	void PrintEquipmentMenu();

	// Print equipments of heros
	// The systhesis equipment should be at the top
	// There should at most 6 equipment
	// if there is none, print None message(a sentence)
	void PrintEquipmentInfoMenu();

	// Print information of heros
	// HP and MP should be present by graph
	// Equipment should be printed in one line
	void PrintHeroInfoMenu();

	// An string variable is what it need to print
	// The function will set the cursor's position and change the text attribute
	void PrintInstruction(string);

	// Print certain Option
	// Use OptionName and SelectNum to help
	// Easy to use when choosing options
	void PrintOption(short);

	//**********************************************************************************

	// Get Input Functions:
	//**********************************************************************************

	// Return an enum yupe to decide the input key
	// WASD and Dir is allowed
	// Can return the Enter
	enum Key GetInput() const;

	// To select options in base menu
	// Print the previous option to default text attribute
	// Print the next option to chosen text attribute
	// If the input is enter, use the SelectNum to call functions
	void SelectBaseMenu();

	// To select option in Attack menu
	// Output the explanation of the nomal
	// If the special is NOT available
	// Print it in dark blue and the cursor should not be on it, which will lead to an instruction
	// If the special is available
	// Print it in yellow and print the explanation
	void SelectAttackMenu();

	// To select option in Skill Menu
	// Output the explanation while moving cursor
	void SelectSkillMenu();

	// To select equipment menu
	// Will print information while moving the cursor
	// Do not need to call functions
	void SelectEquipmentMenu();

	// To select equipment to print its info while moving cursor
	// Only back can be select as an option
	void SelectEquipmentInfo();

	// To select an enemy to attack
	// Will Clear the space of instruction, options and information
	// Print the instruction to select enemy
	// And the cursor will on the alive enemies
	// Return the enemy's num to attack
	int SelectEnemy();

	//**********************************************************************************
	

	// Gaming Functions:
	//**********************************************************************************

	// Calculate the damage
	// Inline function
	// Accept two int represent the attacker's total attack and the suffer's total defenct
	// Return the damage the suffer's should suffer
	inline int CalculateDamage(int, int);

	// Move to next pass
	// Clear screen and pop the congratulations using message box
	// reset three enemies
	// PassCounter plus 1
	void NextPass();

	// If the player is dead, than call this function
	void Gameover();

	// Set GameOver to True
	void Quit();

//**************************************************************************************
private:
	// Counting the pass number to add difficulty 
	int PassCounter;
	
	// Saving heros and enemies
	// The max numbers of them are all 3
	Hero** Heros;
	Enemy** Enemies;
	
	// Counting the number of existing heros and existing enemies
	// Less than three
	short HeroNum;
	short EnemyNum;

	// Use number to save the menu that select
	// Help  to call the function
	short SelectNum;

	// A vector to storage the menu options name
	// The max length is 6
	vector<string> OptionName;

	// Save the cursor's position
	// For there is only one cursor
	// Any function shoul use this to move cursor to avoid mistake
	COORD Cursor;

	// An enum type
	// To decide the type of the import parameter
	enum ObjectType Object_t;

	// Boolean to decide whether game is over
	bool GameOver;
};

#endif