#include "Map.h"
#include "CarMap.h"
#include <iostream>

using namespace std;

CarMap::CarMap()
{
	Map m_map;
}

int CarMap::fleetSize() const
{
	return m_map.size();
}

bool CarMap::addCar(std::string license)
{	
	return m_map.insert(license, 0);
}

double CarMap::gas(std::string license) const
{
	double gas;

	if (m_map.get(license, gas))
		return gas;
	return -1;
}

bool CarMap::addGas(std::string license, double gallons)
{
	if (gallons < 0)
		return false;
	else
	{
		double gasTank = gas(license);
		return m_map.update(license, gallons + gasTank);
	}
}

bool CarMap::useGas(std::string license, double gallons)
{
	if (m_map.contains(license) == false)
		return false;
	else if (gallons > gas(license))
		return false;
	else if (gallons < 0)
		return false;
	else
	{
		double gasTank = gas(license);
		return m_map.update(license, gallons - gasTank);
	}
}

void CarMap::print() const
{
	std::string license;
	double gas;

	for (int i = 0; i < fleetSize(); i++)
	{
		m_map.get(i, license, gas);
		cout << license << " " << gas << endl;
	}
}