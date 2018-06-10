#ifndef SynthesisEquipment_H_
#define SynthesisEquipment_H_

#include "AttackEquipment.h"
#include "DefenceEquipment.h"

class SynthesisEquipment : public AttackEquipment, public DefenceEquipment
{
public:
	SynthesisEquipment();
	virtual ~SynthesisEquipment();

	void SetCounter(int);
	int GetCounter();

	void PrintInfo();
private:
	int Counter;
};

#endif