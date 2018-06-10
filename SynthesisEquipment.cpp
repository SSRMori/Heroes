#include "SynthesisEquipment.h"



SynthesisEquipment::SynthesisEquipment()
{
	Counter = 1;
	SetATK(100 * Counter);
	SetDEF(100 * Counter);
}


SynthesisEquipment::~SynthesisEquipment()
{
}

void SynthesisEquipment::SetCounter(int Counter)
{
	this->Counter = Counter;
	SetName(GetName() + " Lv." + to_string(Counter));
}

int SynthesisEquipment::GetCounter()
{
	return Counter;
}

void SynthesisEquipment::PrintInfo()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << "ATK: " << GetATK();
	cout << "                    ";
	cout << "DEF: " << GetDEF();
	cout << endl;
	cout << GetInfo();
}
