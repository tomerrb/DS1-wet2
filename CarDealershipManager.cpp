#include "CarDealershipManager.h"

//#include <stdlib.h>
#define MAXSIZE 10

CarDealershipManager::CarDealershipManager() :
	max_size(MAXSIZE),
	current_size(0)
{
	agency = (Union::Agency**)malloc(sizeof(Union::Agency*) * MAXSIZE);
}

CarDealershipManager::~CarDealershipManager()
	
{
	free(agency);
}

StatusType CarDealershipManager::AddAgency() {
	if (current_size == max_size) {
		max_size = max_size * 2;
		agency = (Union::Agency**)realloc(agency, sizeof(Union::Agency*) * max_size);
		if (!agency)
			return ALLOCATION_ERROR;
	}
	Union::Agency* new_agency = new Union::Agency();
	agency[current_size] = new_agency;
	current_size++;
	return SUCCESS;
}

StatusType CarDealershipManager::SellCar(int agencyID, int typeID, int k) {
	if (agencyID >= current_size)
		return FAILURE;
	agency[agencyID]->SellCar(typeID, k);
	return SUCCESS;
}

StatusType CarDealershipManager::UniteAgencies(int agencyID1, int agencyID2) {
	if (agencyID1 >= current_size || agencyID2 >= current_size)
		return FAILURE;
	agency[agencyID1]->UniteAgencies(agency[agencyID2]);
	return SUCCESS;
}

StatusType CarDealershipManager::GetIthSoldType(int agencyID, int i, int* res) {
	if (agencyID >= current_size)
		return FAILURE;
	if (agency[agencyID]->GetIthSoldType(i, res))
		return SUCCESS;
	return FAILURE;
}


