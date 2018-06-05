#include <iostream>
#include <string>
#include "Inventory.h"
#include "Queue.h"
#include "Stack.h"

int main(int argc, char *argv[])
{
	bool isRunning = true;
	int choice;
	Queue<Inventory> inventoryQueue;
	Stack<Inventory> inventoryStack;

	while (isRunning)
	{
		// display menu
		std::cout << "Menu" << std::endl
			<< "1. Pop Item" << std::endl
			<< "2. Push Item" << std::endl
			<< "3. Load Default Items" << std::endl
			<< "4. Quit" << std::endl;

		// input
		std::cout << "Enter a number (1-4): ";
		std::cin >> choice;
		std::cin.clear();
		std::cin.ignore();

		// switch choice
		switch (choice)
		{
			case 1: // pop item
			{
				if (!inventoryQueue.empty())
				{
					Inventory item = inventoryQueue.front();
					std::cout << "Inventory Queue: " << std::endl;
					std::cout << "\tSerial Number: " << item.getSerialNum() << std::endl
						<< "\tLot Number: " << item.getLotNum() << std::endl
						<< "\tManufacture Date: " << item.getManufactureDate() << std::endl << std::endl;
					inventoryQueue.pop();
				}

				if (!inventoryStack.empty())
				{
					Inventory item = inventoryStack.top();
					std::cout << "Inventory Stack: " << std::endl;
					std::cout << "\tSerial Number: " << item.getSerialNum() << std::endl
						<< "\tLot Number: " << item.getLotNum() << std::endl
						<< "\tManufacture Date: " << item.getManufactureDate() << std::endl;
					inventoryStack.pop();
				}

				break;
			}

			case 2: // push item
			{
				std::string manufactureDate;
				int lotNumber;
				int serialNumber;

				std::cout << "Serial Number: ";
				std::cin >> serialNumber;
				std::cout << "Lot Number: ";
				std::cin >> lotNumber;
				std::cout << "Manufacture Date: ";
				std::cin >> manufactureDate;
				std::cout << std::endl;

				Inventory item;
				item.setLotNum(lotNumber);
				item.setManufactureDate(manufactureDate);
				item.setSerialNumber(serialNumber);
				inventoryQueue.push(item);
				inventoryStack.push(item);
				break;
			}

			case 3: // load default items
			{
				Inventory items[] = {
					{ 1, "2018-01-01", 10 },
					{ 2, "2018-02-01", 20 },
					{ 3, "2018-03-01", 30 },
					{ 4, "2018-04-01", 40 },
					{ 5, "2018-05-01", 50 },
					{ 6, "2018-06-01", 60 }
				};

				inventoryQueue.clear();
				inventoryStack.clear();
				for (int i = 0; i < sizeof(items) / sizeof(Inventory); i++)
				{
					inventoryQueue.push(items[i]);
					inventoryStack.push(items[i]);
				}

				break;
			}

			case 4: // quit
				isRunning = false;
				break;

			default: // invalid choice
				std::cout << "Invalid choice, try again." << std::endl;
				continue;
		}
	}
	
	system("pause");
	return 0;
}