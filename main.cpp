#include <iostream>
#include "Hero.h"
//#include "AttackEquipment.h"
//#include "DefenceEquipment.h"
//#include "SynthesisEquipment.h"
using namespace std;

int main(int argc, char* argv[])
{
	system("cls");
	int temp = 0;
	if (argc == 2) {
		temp = 1;
	}
	HeroManage Player(temp);
	Player.PLAY();
	system("cls");
	return 0;
}