#include "DefenceEquipment.h"

string DEFNames[] = {
	"Shield",
	"Armor",
	"Spirit Eater",
	"Merry Sheep",
	"Fate-EXTRA",
	"Save Wire",
	"Melty Heart",
	"Somber",
	"O.T.M.A.",
	"Conflict"
};

int DEFs[] = {
	10,
	15,
	14,
	20,
	18,
	21,
	15,
	18,
	19,
	23

};

string DEFInfos[] = {
	"A small protable defence equipment.\nEasy to crash.",
	"A suit made by iron.\nProtect the wearer's body.",
	"¡ºOuter-Seal, Blood Temple	Blood Fort Andromeda¡»",
	"By the light of the fireplace.\nShe knits her love on the holy night.",
	"It is the story of the \"human and hero\" in the near future\nThat made the fundamentals different though it is the same premise.",
	"If you ever need a lift, just say the word.\nI'll pull you up without any grumbles or restraint.",
	"A Valentine Chocolate from Meltlilith \nA chocolate that shines like a sparkling crystal.",
	"There is a shadow that will blossom into the dark.\nDo not avert your eyes.",
	"Olga          Tatiana          Maria          Anastasia",
	"Power is to me.\nUntil you grab the victory in that hand."
};

DefenceEquipment::DefenceEquipment()
{
}

DefenceEquipment::DefenceEquipment(int i)
{
	i = i % 10;
	SetName(DEFNames[i]);
	SetATK(0);
	SetDEF(DEFs[i]);
	SetInfo(DEFInfos[i]);
}

DefenceEquipment::DefenceEquipment(string Name, int DEF, string Info)
{
	SetName(Name);
	SetATK(0);
	SetDEF(DEF);
	SetInfo(Info);
}


DefenceEquipment::~DefenceEquipment()
{
}

void DefenceEquipment::PrintInfo()
{
	cout << "DEF: " << GetDEF() << endl;
	cout << GetInfo();
}
