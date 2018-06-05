#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>

/*
12. Inventory Bin Stack
Design an inventory class that stores the following members:
serialNum : An integer that holds a part's serial number.
manufactDate : A member that holds the date the part was manufactured.
lotNum : An integer that holds the part's lot number.

The class should have appropriate member functions for storing data into,
and retrieving data from, these members. Next, design a stack class that can hold
objects of the class described above. If you wish, you may use the template you
designed in Programming Challenge 1 or 2. Last, design a program that uses the stack
class described above. The program should have a loop that asks the user if he or
she wishes to add a part to inventory, or take a part from inventory. The loop
should repeat until the user is finished. If the user wishes to add a part to
inventory, the program should ask for the serial number, date of manufacture,
and lot number. The data should be stored in an inventory object, and pushed
onto the stack. If the user wishes to take a part from inventory, the program
should pop the top-most part from the stack and display the contents of its
member variables. When the user finishes the program, it should display the
contents of the member values of all the objects that remain on the stack.

13. Inventory Bin Queue
Modify the program you wrote for Programming Challenge 12 so it uses a queue instead of
a stack. Compare the order in which the parts are removed from the bin for each program.
*/

class Inventory
{
public:
	Inventory();
	Inventory(int serialNumber, const std::string& manufactureDate, int lotNumber);
	~Inventory();

	void setLotNum(int lotNumber);
	void setSerialNumber(int serialNumber);
	void setManufactureDate(const std::string& manufactureDate);
	
	inline int getLotNum() const {
		return m_lotNumber;
	}

	inline int getSerialNum() const {
		return m_serialNumber;
	}

	inline const std::string& getManufactureDate() const {
		return m_manufactureDate;
	}

private:
	int m_serialNumber;
	std::string m_manufactureDate;
	int m_lotNumber;
};

#endif
