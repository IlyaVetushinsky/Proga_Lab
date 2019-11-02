#include "pch.h"
#include "Prog3applyh.h"
#include <stdio.h>
using namespace Prog3;
int main()
{
	int num = 0;
	Logical_Element* mas = new Logical_Element[1];
	int rc;
	Logical_Element* lel = nullptr;
	int ou = 0;
	while (rc = dialog(msgsM, NMsgsM)) {
		if (rc == 1) {
			if (num > 0) {
				std::cout << "Input index number of Logical element from 0 to " << num - 1 << std::endl;
				int i;
				while (getNum(i) < 0 || i < 0 || i > num - 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				lel = &mas[i];
			}
			else {
				std::cout << "There is 0 Logical elements. Please, first add Logical element" << std::endl;
				continue;
			}
		}
		if (rc == 2) {
			bool ind = true;
			while (ind) {
				std::cout << "Put 0 for \"AND\", 1 for \"OR\", 2 for \"NOT\"" << std::endl;
				int l;
				while (getNum(l) < 0 || l < 0 && l > 2)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				int t = 0;
				Logical_Element lell(l, num, t);
				Logical_Element* mas2 = new Logical_Element[num];
				for (int i = 0; i < num; i++) {
					mas2[i] = mas[i];
				}
				mas = new Logical_Element[num + 1];
				for (int i = 0; i < num; i++) {
					mas[i] = mas2[i];
				}
				mas[num] = lell;
				num++;
				std::cout << std::endl;
				std::cout << "This Logical element will be numbered as "<< num - 1 << std::endl;
				std::cout << std::endl;
				std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
				int lr;
				while (getNum(lr) < 0 || lr != 0 && lr != 1)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				if (!lr)
					ind = false;
			}
			continue;
		}
		if (rc == 3) {
			if (num > 1) {
				add_conection(mas, num, ou);
			}
			else {
				std::cout << "There is 0 Logical elements. Please, first add Logical element" << std::endl;
			}
			continue;
		}
		if (rc == 4) {
			for (int i = 0; i < num; i++) {
				std::cout << "(" << i << " , type: " << mas[i].getType() << ") ";
				std::cout << std::endl;
				std::cout << mas[i];
				std::cout << std::endl;
			}
			continue;
		}
		if (rc == 5) {
			if (num > 0) {
				std::cout << std::endl;
				std::cout << "RESULT" << std::endl;
				for (int i = 0; i < ou+1; i++) {
					std::cout << "Number of element is ";
					std::cout << Start(mas, num)[i].n;
					std::cout << ", Value is ";
					std::cout << Start(mas, num)[i].q;
					std::cout << std::endl;
				}
				std::cout << std::endl;
			}
			else {
				std::cout << "There is 0 Logical elements. Please, first add Logical element" << std::endl;
			}
			continue;
		}
		std::cout << "Init input Terminals of selected Logical element" << std::endl;
		lel->Set_value();
	}
	return 0;
}





/*for (int i = 0; i < num; i++) {
						Logical_Element* ptr = &mas[i];
						while (ptr != nullptr && ptr->outp[0].jump != nullptr) {
							ptr = ptr->outp[0].jump;
						}
						Qrec(ptr);
						r = ptr->outp[0].value;*/