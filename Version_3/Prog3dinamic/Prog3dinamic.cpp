#include "pch.h"
#include "Prog3dinamich.h"
#include <stdio.h>
#include <Windows.h>
using namespace Prog3;
int main()
{
	int num = 0;
	Logical_Element* mas = new Logical_Element[1];
	int rv;
	Logical_Element llel;
	mas[num] = llel;
	num++;
	std::cout << "Empty constructur done" << std::endl;
	int i;
	int rc;
	Logical_Element* lel = nullptr;

	while (rc = dialog(msgsM, NMsgsM)) {
		if (rc == 1) {
			std::cout << "Input index number of Logical element from 0 to " << num - 1 << std::endl;
			int i;
			while (getNum(i) < 0 || i < 0 || i > num - 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			lel = &mas[i];
		}
		if (rc == 2) {
			if (num == 1000) {
				std::cout << "Overflow" << std::endl;
			}
			bool ind = true;
			while (ind) {
				Logical_Element lell;
				Logical_Element* mas2 = new Logical_Element[num];
				for (int i = 0; i < num; i++) {
					mas2[i] = mas[i];
				}
				delete[] mas;
				mas = new Logical_Element[num + 1];
				for (int i = 0; i < num; i++) {
					mas[i] = mas2[i];
				}
				mas[num] = lell;
				num++;
				std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
				int l;
				while (getNum(l) < 0 || l != 0 && l != 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (!l)
					ind = false;
			}
			continue;
		}
		if (rc == 3) {
			bool ind = true;
			while (ind) {
				if (num < 2) {
					std::cout << "You have not 2 Logical elements. Repeat please" << std::endl;
					ind = false;
					continue;
				}
				else {
					std::cout << "Choose wherefrom to copy :from 0 to " << num - 1 << std::endl;
					int i;
					while (getNum(i) < 0 || i < 0 || i > num)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << "Choose where to copy :from 0 to " << num - 1 << std::endl;
					int j;
					while (getNum(j) < 0 || j < 0 || j > num)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					mas[j] = mas[i];//
				}
				std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
				int l;
				while (getNum(l) < 0 || l != 0 && l != 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (!l)
					ind = false;
			}
			continue;
		}
		if (rc == 4) {
			for (int i = 0; i < num; i++) {
				std::cout << "(" << i << ") ";
				std::cout << std::endl;
				mas[i].print(std::cout);
				std::cout << std::endl;
			}
			continue;
		}
		while (rc = dialog(msgs, NMsgs))
			if (!fptr[rc](*lel))
				break;
	}
	return 0;
}