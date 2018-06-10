#ifndef DefenceEquipment_H_
#define DefenceEquipment_H_

#include "AttackEquipment.h"

class DefenceEquipment : virtual public Equipment
{
public:
	DefenceEquipment();
	DefenceEquipment(int);
	DefenceEquipment(string, int, string);
	virtual ~DefenceEquipment();

	void PrintInfo();
};

#endif