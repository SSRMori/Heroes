#include "AttackEquipment.h"

string ATKNames[] = { 
	"Knife",
	"Azoth Blade",
	"Grimoire",
	"Magic Crystal",
	"Lugh's Halo",
	"Empieta",
	"Elixir",
	"Usumidori",
	"Rome",
	"Bai Long",
	"Ramesseum",
	"Gringolet",
	"King's Horse",
	"First Order",
	"Chrysaor",
	"Urvara Nandi"
};

int ATKs[] = { 
	10,
	15,
	17,
	12,
	10,
	16,
	18,
	14,
	17,
	20,
	10,
	19,
	21,
	25,
	17,
	18
};
string ATKInfos[] = {
	"A small protable attack equipment.\nCan cause little damage to the enemies.",
	"A basic blade carried by all Magic users\nTo be used in rituals.",
	"Both a tome that chronicles the secrets of thaumaturgy.\nAnd a record of the life of the magus who transcribed them.",
	"A jewel used as catalyst by gem mages.",
	"The wheel of sunlight sent by the God of Light, Lugh.",
	"The free love is precious, the devotion from the heart is beautiful.",
	"This elixir is the crystalization.\nIt is a medicine tempered by Elizabeth, which is able to cure countless diseases.",
	"The person cuts down the Earth Spider without a second thought.\nThus exterminating the monster by taking its life away with a sword.",
	"What is this, you asked ?Of course-- \nOnce more, it is none other than something that Rome has shaped.",
	"A beautiful white horse--\nBeen with the Sanzang and finally get lost.",
	"Perhaps he drawing closer the world where the gods deign to the present world.\nPerhaps he had aimed for the unification of this world and the other world.",
	"I am called the fae horse, Gringolet.\nA gorilla rides upon my back.",
	"A mysterious creature that can endure a blow that is delivered, is not it.\mIf so, you ride on the back of the maid Dun Stallion.",
	"The year 2115\nThe last era in which magecraft still existed.",
	"The fearsome Gorgon--- \nRather, the existence that had rampaged as the monster Gorgon had killed many humans, but finally, she has met her end.",
	"This is the personification of a fertile land.\nA guardian of the promised blessing."
};

Equipment::Equipment()
{
	Name = "";
	DEF = 0;
	ATK = 0;
	Info = "";
}

Equipment::~Equipment()
{
}

void Equipment::SetName(string Name)
{
	this->Name = Name;
}

void Equipment::SetATK(int ATK)
{
	this->ATK = ATK;
}

void Equipment::SetDEF(int DEF)
{
	this->DEF = DEF;
}

void Equipment::SetInfo(string Info)
{
	this->Info = Info;
}

int Equipment::GetATK() const
{
	return ATK;
}

int Equipment::GetDEF() const
{
	return DEF;
}

string Equipment::GetInfo() const
{
	return Info;
}

string Equipment::GetName() const
{
	return Name;
}


AttackEquipment::AttackEquipment()
{
	SetName("");
	SetATK(0);
	SetDEF(0);
	SetInfo("");
}

AttackEquipment::AttackEquipment(int i)
{
	i = i % 16;
	SetName(ATKNames[i]);
	SetATK(ATKs[i]);
	SetDEF(0);
	SetInfo(ATKInfos[i]);
}


AttackEquipment::~AttackEquipment()
{
}

void AttackEquipment::PrintInfo()
{
	cout << "ATK: " << GetATK() << endl;
	cout << GetInfo();
}

