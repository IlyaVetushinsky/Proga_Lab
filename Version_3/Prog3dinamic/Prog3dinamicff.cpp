// Prog3overload.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

// Prog3.cpp : ���� ���� �������� ������� "main". ����� ���������� � ������������� ���������� ���������.
//

#include "pch.h"
#include "Prog3dinamich.h"
namespace Prog3 {
	const char *msgs[] = { "0. Quit or select other logical element", "1. Reorg", "2. Print one", "3. Add link", "4. Delete link" , "5. Add terminal", "6. Print all" };
	const char *cmsgs[] = { "0. Quit", "1. Empty constructor", "2. Constructor 2", "3. Constructor 3(from array)" };
	const char *msgsM[] = { "0. Quit", "1. Select logical element", "2. Add logical element", "3. Copy logical element", "4. Print all" };
	const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
	const int NMsgsM = sizeof(msgsM) / sizeof(msgsM[0]);
	const int NcMsgs = sizeof(cmsgs) / sizeof(cmsgs[0]);
	int(*fptr[])(Logical_Element &) = { NULL, D_Reorg, D_Print_one, D_Add_link, D_Delete_link, D_Add_terminal, D_Print_all };
	int getNum(int &a)
	{
		std::cin >> a;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
			return -1;
		}
		std::cin.clear();
		std::cin.ignore();
		return 1;
	}

	int dialog(const char *msgs[], int N)
	{
		const char *errmsg = "";
		int i, n = 0;
		do {
			puts(errmsg);
			errmsg = "You're wrong. Repeat, please!";
			for (i = 0; i < N; ++i)
				puts(msgs[i]);
			puts("Make our choice: ");
			getNum(n);
		} while (n < 0 || n >= N);
		return n;
	}

	Terminal* Logical_Element::operator [](int i) {
		if (i == 0) {
			return inp;
		}
		else {
			return outp;
		}
	}

	/*Terminal TerminalC::operator [](int i) {
		return p[i];
	}*/

	Terminal* inpterm(int n, Logical_Element lell) {
		Terminal *term = new Terminal[n];
		for (int i = 0; i < n; i++) {
			std::cout << "input type of " << i + 1 << " terminal(0-Input,1-Output)-> " << std::endl;
			while (getNum(term[i].type) < 0 || term[i].type != 0 && term[i].type != 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			int t = 0;
			t = 0;
			if (term[i].type == 0) {
				term[i].number = lell.getinpSize() ;
			}
			else {
				term[i].number = lell.getoutpSize();
			}
			std::cout << "input index number is " << term[i].number << std::endl;
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
		return term;
	}

	/*int select_constructor(Logical_Element*& mas, int &num) {
		Logical_Element lel;
		int rc;
		rc = dialog(cmsgs, NcMsgs);
		switch (rc) {
		case 0:
			return 0;
		case 1:
			lel = Logical_Element();
			std::cout << "max size = " << lel.getMaxSize() << std::endl;
			std::cout << "Empty constructor : done" << std::endl;
			lel.print(std::cout);
			mas[num] = lel;
			num++;
			break;
		case 2:
			std::cout << "Input count of input terminals-> " << std::endl;
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
			mas[num] = lel;
			num++;
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
			mas[num] = lel;
			num++;
			break;
		}
		std::cout << std::endl;
		return 1;
	}*/

	Logical_Element::Logical_Element() {
		SZ = 2;
		int j = 0;
		outp = new Terminal[1];
		inp = new Terminal[1];
		outp[j].number = 0;
		outp[j].type = 1;
		outp[j].value = 2;
		outp[j].count = 0;
		inp_n = 1;
		outp_n = 1;
		inp[j].number = 0;
		inp[j].type = 0;
		inp[j].value = 2;
		inp[j].count = 0;
	}

	Logical_Element::Logical_Element(int i, int out) {
		SZ = i + out;
		outp = new Terminal[i];
		inp = new Terminal[out];
		inp_n = i;
		for (int j = 0; j < inp_n; j++) {
			inp[j].number = j;
			inp[j].type = 0;
			inp[j].value = 2;
			inp[j].count = 0;
		}
		outp_n = out;
		for (int j = 0; j < outp_n; j++) {
			outp[j].number = j;
			outp[j].type = 1;
			outp[j].value = 2;
			outp[j].count = 0;
		}
	}
	Logical_Element::Logical_Element(Terminal* t_ar, int length) {
		inp_n = 0;
		outp_n = 0;
		outp = new Terminal[sizeof(t_ar) / length];
		inp = new Terminal[sizeof(t_ar) / length];
		try {
			for (int i = 0; i < length; i++) {
				if (t_ar[i].type == 0) {
					inp[t_ar[i].number] = t_ar[i];
					inp_n++;
					SZ++;
				}
				else {
					outp[t_ar[i].number] = t_ar[i];
					outp_n++;
					SZ++;
				}
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
	}

	Logical_Element::Logical_Element(const Logical_Element &lel) {
		SZ = lel.SZ;
		outp = new Terminal[sizeof(lel.inp) / lel.inp_n];
		inp = new Terminal[sizeof(lel.outp) / lel.outp_n];
		inp_n = lel.inp_n;
		outp_n = lel.outp_n;
		try {
			for (int i = 0; i < lel.inp_n; i++) {
				inp[i] = lel.inp[i];
			}
			for (int i = 0; i < lel.outp_n; i++) {
				outp[i] = lel.outp[i];
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
	}

	Logical_Element Logical_Element::copy(Logical_Element &lel) {
		*this = lel;
		return *this;
	}

	Logical_Element Logical_Element::operator = (Logical_Element &lel) {
		delete[] inp;
		delete[] outp;
		inp = new Terminal[sizeof(lel.inp) / lel.inp_n];
		outp = new Terminal[sizeof(lel.outp) / lel.outp_n];
		inp_n = lel.inp_n;
		outp_n = lel.outp_n;
		try {
			for (int i = 0; i < inp_n; i++) {
				inp[i] = lel.inp[i];
			}
			for (int i = 0; i < outp_n; i++) {
				outp[i] = lel.outp[i];
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
		return *this;
	}

	void Logical_Element::reorg() {
		bool ind = true;
		while (ind) {
			std::cout << "Input the terminal number you want to change" << std::endl;
			int n;
			while (getNum(n) < 0 || n < 0)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			std::cout << "Input the terminal type you want to change" << std::endl;
			int t;
			while (getNum(t) < 0 || t != 0 && t != 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			int pf = 0;
			if (!t) {
				for (int j = 0; j < inp_n; j++) {
					if (inp[j].number == n) {
						pf++;
					}
				}
			}
			else {
				for (int j = 0; j < outp_n; j++) {
					if (outp[j].number == n) {
						pf++;
					}
				}
			}
			if (!pf) {
				std::cout << "There is no such terminal" << std::endl;
				break;
			}
			try {
				if (!t) {
					std::cout << "input --NEW-- value of " << n << " terminal(0,1,undefined(2))-> " << std::endl;
					while (getNum(inp[n].value) < 0 || inp[n].value != 0 && inp[n].value != 1 && inp[n].value != 2)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << "input --NEW-- count of links of " << n << " terminal(for Input Terminal: 0-1, for Output Termainal: 0-3)-> " << std::endl;
					while (getNum(inp[n].count) < 0 || inp[n].type == 0 && (inp[n].count < 0 || inp[n].count > 1))
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					/*std::cout << "input --NEW-- index number of " << n << " terminal(from 0 to 9)-> " << std::endl;
					while (getNum(inp[n].number) < 0 || inp[n].number < 0 || inp[n].number > SZ-1)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					if (n != inp[n].number) {
						inp[inp[n].number] = inp[n];
						inp[n].type = 2;//���������
					}*/
				}
				else {
					std::cout << "input --NEW-- value of " << n << " terminal(0,1,undefined(2))-> " << std::endl;
					while (getNum(outp[n].value) < 0 || outp[n].value != 0 && outp[n].value != 1 && outp[n].value != 2)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					std::cout << "input --NEW-- count of links of " << n << " terminal(for Input Terminal: 0-1, for Output Termainal: 0-3)-> " << std::endl;
					while (getNum(outp[n].count) < 0 || outp[n].type == 1 && (outp[n].count < 0 || outp[n].count > 3))
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					/*std::cout << "input --NEW-- index number of " << n << " terminal(from 0 to " << SZ - 1 << ")-> " << std::endl;
					while (getNum(outp[n].number) < 0 || outp[n].number < 0 || outp[n].number > SZ)
					{
						std::cout << "You're wrong. Repeat please" << std::endl;
					}
					if (n != outp[n].number) {
						outp[outp[n].number] = outp[n];
						outp[n].type = 2;//���������
					}*/
				}
			}
			catch (const std::exception &msg)
			{
				std::cout << msg.what() << std::endl;
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
	}

	std::ostream & Logical_Element::get_Terminal_info(std::ostream& s) const {
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		int i;
		if (T) {
			std::cout << "Input index number of terminal(from 0 to " << outp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > outp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		else {
			std::cout << "Input index number of terminal(from 0 to " << inp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > inp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		if (!T) {
			if (inp[i].type == 0) {
				std::cout << "count of connections: ";
				s << inp[i].count << ", ";
				std::cout << "number of terminal: ";
				s << inp[i].number << ", ";
				std::cout << "type of terminal: ";
				if (inp[i].type == 0)
					s << "INPUT" << ", ";
				if (inp[i].type == 1)
					s << "OUTPUT" << ", ";
				std::cout << "value: ";
				s << inp[i].value << '.';
				s << std::endl;
			}
			else {
				std::cout << "There is no such terminal" << std::endl;
			}
		}
		else {
			if (outp[i].type == 1) {
				std::cout << "count of connections: ";
				s << outp[i].count << ", ";
				std::cout << "number of terminal: ";
				s << outp[i].number << ", ";
				std::cout << "type of terminal: ";
				if (outp[i].type == 0)
					s << "INPUT" << ", ";
				if (outp[i].type == 1)
					s << "OUTPUT" << ", ";
				std::cout << "value: ";
				s << outp[i].value << '.';
				s << std::endl;
			}
			else {
				std::cout << "There is no such terminal" << std::endl;
			}
		}
		return s;
	}
	void Logical_Element::add_connection() {
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		int i;
		if (T) {
			std::cout << "Input index number of terminal(from 0 to " << outp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > outp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		else {
			std::cout << "Input index number of terminal(from 0 to " << inp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > inp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		if (!T) {
			if (inp[i].type == 0) {
				if (inp[i].count < 1)
					inp[i].count++;
			}
			else {
				std::cout << "There is no this terminal" << std::endl;
			}
		}
		else {
			if (outp[i].type == 1) {
				if (outp[i].count < 3)
					outp[i].count++;
			}
			else {
				std::cout << "There is no this terminal" << std::endl;
			}
		}
	}
	void Logical_Element::delete_connection() {
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		int i;
		if (T) {
			std::cout << "Input index number of terminal(from 0 to " << outp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > outp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		else {
			std::cout << "Input index number of terminal(from 0 to " << inp_n << ")-> " << std::endl;
			while (getNum(i) < 0 || i < 0 || i > inp_n)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		if (!T) {
			if (inp[i].type == 0) {
				if (inp[i].count > 0)
					inp[i].count--;
			}
			else {
				std::cout << "There is no this terminal" << std::endl;
			}
		}
		else {
			if (outp[i].type == 1) {
				if (outp[i].count > 0)
					outp[i].count--;
			}
			else {
				std::cout << "There is no this terminal" << std::endl;
			}
		}
	}


	void Logical_Element::add_terminal() {
		bool ind = true;
		while (ind) {
			Terminal *term = new Terminal[1];
			term = inpterm(1, *this);
			*this >> *term;
			std::cout << "Do you want to continue? 1-yes, 0-no" << std::endl;
			int l;
			while (getNum(l) < 0 || l != 0 && l != 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			if (!l)
				ind = false;
		}
	}

	Logical_Element Logical_Element:: operator >> (Terminal term) {
		Logical_Element lel2;
		lel2 = *this;
		if (term.type == 0) {
			delete[] inp;
			int i;
			inp = new Terminal[sizeof(lel2.inp) / lel2.inp_n + 1];
			for (i = 0; i < lel2.inp_n ; i++) {
				inp[i].count = lel2.inp[i].count;
				inp[i].number = lel2.inp[i].number;
				inp[i].type = lel2.inp[i].type;
				inp[i].value = lel2.inp[i].value;
			}
			inp[i].count = term.count;
			inp[i].number = term.number;
			inp[i].type = term.type;
			inp[i].value = term.value;
			inp_n++;
		}
		else {
			delete[] outp;
			int i;
			outp = new Terminal[sizeof(lel2.outp) / lel2.outp_n + 1];
			for (i = 0; i < lel2.outp_n; i++) {
				outp[i].count = lel2.outp[i].count;
				outp[i].number = lel2.outp[i].number;
				outp[i].type = lel2.outp[i].type;
				outp[i].value = lel2.outp[i].value;
			}
			outp[i].count = term.count;
			outp[i].number = term.number;
			outp[i].type = term.type;
			outp[i].value = term.value;
			outp_n++;
		}
		return *this;
	}

	std::ostream & operator <<(std::ostream & s, const Logical_Element & lel) {
		std::cout << "Input Terminals: " << lel.inp_n << std::endl;
		for (int i = 0; i < lel.inp_n; i++) {
			if (lel.inp[i].type == 0) {
				std::cout << i + 1 << ") ";
				std::cout << "count of connections: ";
				s << lel.inp[i].count << ", ";
				std::cout << "number of terminal: ";
				s << lel.inp[i].number << ", ";
				std::cout << "type of terminal: ";
				if (lel.inp[i].type == 0)
					s << "INPUT" << ", ";
				if (lel.inp[i].type == 1)
					s << "OUTPUT" << ", ";
				std::cout << "value: ";
				s << lel.inp[i].value << '.';
				s << std::endl;
			}
		}
		std::cout << "Output Terminals: " << lel.outp_n << std::endl;
		for (int i = 0; i < lel.outp_n; i++) {
			if (lel.outp[i].type == 1) {
				std::cout << i + 1 << ") ";
				std::cout << "count of connections: ";
				s << lel.outp[i].count << ", ";
				std::cout << "number of terminal: ";
				s << lel.outp[i].number << ", ";
				std::cout << "type of terminal: ";
				if (lel.outp[i].type == 0)
					s << "INPUT" << ", ";
				if (lel.outp[i].type == 1)
					s << "OUTPUT" << ", ";
				std::cout << "value: ";
				s << lel.outp[i].value << '.';
				s << std::endl;
			}
		}
		return s;
	}


	std::ostream & Logical_Element::print(std::ostream &s) const
	{
		s << *this;
		return s;
	}


	/*
	Logical_Element * D_Empty_constructor() {
		Logical_Element lel;
		std::cout << "max size = " << lel.getMaxSize() << std::endl;
		std::cout << "1. Empty constructor : done" << std::endl;
		lel.print(std::cout);
		Logical_Element* lelll = &lel;
		return lelll;
	}

	Logical_Element* D_Constructor_2() {
		Logical_Element lel;
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
		Logical_Element* lelll = &lel2;
		return lelll;
	}

	Logical_Element* D_Constructor_3() {
		std::cout << "input number of terminals (0-10)-> " << std::endl;
		int n;
		while (getNum(n) < 0 || n < 0 || n > 10)
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
					if (i != j && term[j].number == term[i].number)
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
		Logical_Element* lelll = &lel3;
		return lelll;
	}*/

	int D_Reorg(Logical_Element & lel) {
		lel.reorg();
		lel.print(std::cout);
		return 1;
	}

	int D_Print_one(Logical_Element & lel) {
		lel.get_Terminal_info(std::cout);
		return 1;
	}

	int D_Add_link(Logical_Element & lel) {
		lel.add_connection();
		lel.print(std::cout);
		return 1;
	}

	int D_Delete_link(Logical_Element &lel) {
		lel.delete_connection();
		lel.print(std::cout);
		return 1;
	}

	int D_Print_all(Logical_Element &lel) {
		lel.print(std::cout);
		return 1;
	}

	int D_Add_terminal(Logical_Element &lel) {
		lel.add_terminal();
		lel.print(std::cout);
		return 1;
	}
	/*int Stack::pop(int &el)
	{
		int rc = top - 1;
		if (top > 0)
			el = ar[--top];
		return rc;
	}
	int Stack::push(int el)
	{
		if (top < SZ)
			ar[top++] = el;
		else
			throw std::exception("Stack overflow!");
		return top;
	}
		Stack & Stack::copy(const Stack &st)
	{
		Stack tmp(st);
		int el;
		while (tmp.pop(el) >= 0)
			push(el);
		return *this;
	}
	Stack & Stack::move(Stack &st)
	{
		int el;
		while (st.pop(el) >= 0)
			push(el);
		return *this;
	}*/
}
// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.


// ������ ���������: CTRL+F5 ��� ���� "�������" > "������ ��� �������"
// ������� ���������: F5 ��� ���� "�������" > "��������� �������"

// ������ �� ������ ������ 
//   1. � ���� ������������ ������� ����� ��������� ����� � ��������� ���.
//   2. � ���� Team Explorer ����� ������������ � ������� ���������� ��������.
//   3. � ���� "�������� ������" ����� ������������� �������� ������ ������ � ������ ���������.
//   4. � ���� "������ ������" ����� ������������� ������.
//   5. ��������������� �������� ������ ���� "������" > "�������� ����� �������", ����� ������� ����� ����, ��� "������" > "�������� ������������ �������", ����� �������� � ������ ������������ ����� ����.
//   6. ����� ����� ������� ���� ������ �����, �������� ������ ���� "����" > "�������" > "������" � �������� SLN-����.
