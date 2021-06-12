
#include "CarDealershipManager.h"

#include <stdlib.h>
#define MAXSIZE 10

CarDealershipManager::CarDealershipManager() :
	max_size(MAXSIZE),
	current_size(0)
{
	agency = (Union**)malloc(sizeof(Union*) * MAXSIZE);

}

CarDealershipManager::~CarDealershipManager()
	
{
	free(agency);
}

StatusType CarDealershipManager::AddAgency() {
	if (current_size == max_size) {
		max_size = max_size * 2;
		agency = (Union**)realloc(agency, sizeof(Union*) * max_size);
		if (!agency)
			return ALLOCATION_ERROR;

	}
	Union* new_agency = new Union();
	agency[current_size] = new_agency;
	current_size++;
	return SUCCESS;
}

