#include "pch.h"
#include "Prog33h.h"
using namespace Prog3;
int main()
{
	Logical_Element lel;
	int rc;
	std::cout << "First select the constructor" << std::endl;
	rc = dialog(cmsgs, NcMsgs);
	switch (rc) {
	case 0:
		return 0;
	case 1:
		lel = Logical_Element();
		std::cout << "max size = " << lel.getMaxSize() << std::endl;
		std::cout << "1. Empty constructor : done" << std::endl;
		lel.print(std::cout);
		break;
	case 2:
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
		lel = Logical_Element(inp, outp);
		lel.print(std::cout);
		break;
	case 3:
		std::cout << "input number of terminals (0-10)-> " << std::endl;
		int n;
		while (getNum(n) < 0 || n < 0 || n > 10)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		Terminal *term = new Terminal[n];
		term = inpterm(n);
		lel = Logical_Element(term, n);
		lel.print(std::cout);
		break;
	}
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](lel))
			break;
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