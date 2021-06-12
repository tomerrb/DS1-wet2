
#include "tree.h"

#include "library2.h"

#include "Union.h"


#ifndef CARDEALERSHIPMANAGER_H
#define CARDEALERSHIPMANAGER_H



class CarDealershipManager
{
	Union** agency;
	int max_size;
	int current_size;
	

public:


	CarDealershipManager();
	~CarDealershipManager();

	StatusType AddAgency();

	StatusType SellCar(int agencyID, int typeID, int k);

	StatusType UniteAgencies(int agencyID1, int agencyID2);

	StatusType GetIthSoldType(int agencyID, int i, int* res);

	void Quit();

};

#endif