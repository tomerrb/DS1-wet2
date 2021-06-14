#include <stdexcept>
#include"library2.h"
#include"CarDealershipManager.h"

#define CHECK_NULL(DS)                    \
    if (!DS)                              \
    {                                     \
        return StatusType::INVALID_INPUT; \
    }
#define CHECK_POSITIVE(number)            \
    if (number <= 0)                      \
    {                                     \
        return StatusType::INVALID_INPUT; \
    }
#define CHECK_NON_NEGATIVE(number)        \
    if (number < 0)                       \
    {                                     \
        return StatusType::INVALID_INPUT; \
    }


void* Init() {
	CarDealershipManager* DS;
	try
	{
		DS = new CarDealershipManager();
	}
	catch (const std::bad_alloc&)
	{
		DS = nullptr;
	}

	return (void*)DS;
}
StatusType AddAgency(void* DS) {
	CHECK_NULL(DS);
	return ((CarDealershipManager*)DS)->AddAgency();
}
StatusType SellCar(void* DS, int agencyID, int typeID, int k) {
	CHECK_NULL(DS);
	CHECK_NON_NEGATIVE(agencyID);
	CHECK_POSITIVE(k);

	return ((CarDealershipManager*)DS)->SellCar(agencyID, typeID, k);
}
StatusType UniteAgencies(void* DS, int agencyID1, int agencyID2) {
	CHECK_NULL(DS);
	CHECK_NON_NEGATIVE(agencyID1);
	CHECK_NON_NEGATIVE(agencyID2);
	return ((CarDealershipManager*)DS)->UniteAgencies(agencyID1, agencyID2);
}
StatusType GetIthSoldType(void* DS, int agencyID, int i, int* res) {
	CHECK_NON_NEGATIVE(agencyID);
	CHECK_NON_NEGATIVE(i);
	CHECK_NULL(DS);
	CHECK_NULL(res);

	return ((CarDealershipManager*)DS)->GetIthSoldType(agencyID, i, res);
}
void Quit(void** DS) {
	delete (CarDealershipManager*)(*DS);
	*DS = nullptr;
}

