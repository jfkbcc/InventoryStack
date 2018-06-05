#include "Inventory.h"

Inventory::Inventory()
{
	m_serialNumber = 0;
	m_manufactureDate = "";
	m_lotNumber = 0;
}

Inventory::Inventory(int serialNumber, const std::string& manufactureDate, int lotNumber)
{
	m_serialNumber = serialNumber;
	m_manufactureDate = manufactureDate;
	m_lotNumber = lotNumber;
}

Inventory::~Inventory()
{
}

void Inventory::setSerialNumber(int serialNumber)
{
	m_serialNumber = serialNumber;
}

void Inventory::setManufactureDate(const std::string& manufactureDate)
{
	m_manufactureDate = manufactureDate;
}

void Inventory::setLotNum(int lotNumber)
{
	m_lotNumber = lotNumber;
}