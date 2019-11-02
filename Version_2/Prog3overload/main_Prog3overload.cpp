#include "pch.h"
#include "Prog3overloadh.h"
#include <stdio.h>
#include <Windows.h>
using namespace Prog3;
int main()
{
	int num = 0;
	Logical_Element* mas = new Logical_Element[1000];
	int rv;
	std::cout << "First select the constructor" << std::endl;
	if (!select_constructor(mas, num)) {
		return 0;
	}
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
			while(ind) {
				std::cout << "Select the constructor" << std::endl;
				if (!select_constructor(mas, num)) {
					return 0;
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
			for (int i = 0; i < num; i++) {
				mas[i].print(std::cout);
			}
			continue;
		}
		if (rc == 3) {
			bool ind = true;
			while (ind) {
				if (num < 2) {
					std::cout << "You have only 1 Logical elem. Repeat please" << std::endl;
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
					mas[j] << mas[i];//
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
				std::cout <<"(" << i << ") ";
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









	/*
	Logical_Element lel;
	std::cout << "max size = " << lel.getMaxSize() << std::endl;
	std::cout << "1. Empty constructor : done" << std::endl;
	lel.print(std::cout);
	std::cout << "2. Input count of input terminals-> " << std::endl;
	int inp;
	while (getNum(inp) < 0 || inp > lel.getMaxSize() || inp < 0)
	{
		std::cout << "You're wrong. Repeat please" << std::endl;
	}
	std::cout << "Input count of output terminals-> " << std::endl;
	int outp;
	while (getNum(outp) < 0 || outp > lel.getMaxSize() - inp || outp < 0)
	{
		std::cout << "You're wrong. Repeat please" << std::endl;
	}
	Logical_Element lel2(inp, outp);
	lel2.print(std::cout);
	std::cout << "3. Array of terminals:" << std::endl;
	std::cout << "input number of terminals (0-10)-> " << std::endl;
	int n;
	while (getNum(n) < 0 || n < 0 || n > 10 )
	{
		std::cout << "You're wrong. Repeat please" << std::endl;
	}
	Terminal *term = new Terminal[n];
	for (int i = 0; i < n; i++) {
		std::cout << "input type of " << i + 1 << " terminal(0-Input,1-Output)-> " << std::endl;
		while (getNum(term[i].type) < 0 || term[i].type != 0 && term[i].type != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		int t = 0;
		do {
			t = 0;
			std::cout << "input index number of " << i + 1 << " terminal(from 0 to " << n - 1 << ")-> " << std::endl;
			while (getNum(term[i].number) < 0 || term[i].number < 0 || term[i].number > n - 1)// || term[term[i].number].value == 0 || term[term[i].number].value == 1 || term[term[i].number].value == 2)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			for (int j = 0; j < n; j++) {
				if (i!=j && term[j].number == term[i].number)
					t++;
			}
		} while (t);
		std::cout << "input value of " << i + 1 << " terminal(0,1,undefined(2))-> " << std::endl;
		while (getNum(term[i].value) < 0 || term[i].value != 0 && term[i].value != 1 && term[i].value != 2)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "input count of links of " << i + 1 << " terminal(for Input Terminal: 0-1, for Output Termainal: 0-3)-> " << std::endl;
		while (getNum(term[i].count) < 0 || term[i].type == 0 && (term[i].count < 0 || term[i].count > 1) || term[i].type == 1 && (term[i].count < 0 || term[i].count > 3))
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
	}
	Logical_Element lel3(term, n);
	lel3.print(std::cout);
	std::cout << "4. Reorg:" << std::endl;
	lel3.reorg();
	lel3.print(std::cout);
	std::cout << "5. Print one:" << std::endl;
	lel3.get_Terminal_info(std::cout);
	std::cout << "6. Add link" << std::endl;
	lel3.add_connection();
	lel3.print(std::cout);
	std::cout << "7. Delete link" << std::endl;
	lel3.delete_connection();
	lel3.print(std::cout);
	std::cout << "8. Add terminal" << std::endl;
	lel3.add_terminal();
	lel3.print(std::cout);
	std::cout << std::endl;
	return 0;
	*/
}