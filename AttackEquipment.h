#ifndef AttackEquipment_H_
#define AttackEquipment_H_
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

class Equipment
{
public:
	Equipment();
	virtual ~Equipment();

	// Set functions
	void SetName(string);
	void SetATK(int);
	void SetDEF(int);
	void SetInfo(string);

	// Get functions
	string GetName() const;
	int GetATK() const;
	int GetDEF() const;
	string GetInfo() const;

	// Print the information of this equipment
	// Including the buff and introduction
	virtual void PrintInfo() = 0;
private:
	string Name;
	int ATK;
	int DEF;
	string Info;
};

class AttackEquipment : virtual public Equipment
{
public:
	AttackEquipment();
	AttackEquipment(int);
	virtual ~AttackEquipment();
	void PrintInfo();
};

#endif