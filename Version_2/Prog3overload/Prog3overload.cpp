// Prog3overload.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Prog3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Prog3overloadh.h"
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

	Terminal* inpterm(int n) {
		Terminal *term = new Terminal[n];
		Logical_Element lell;
		for (int i = 0; i < n; i++) {
			std::cout << "input type of " << i + 1 << " terminal(0-Input,1-Output)-> " << std::endl;
			while (getNum(term[i].type) < 0 || term[i].type != 0 && term[i].type != 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			int t = 0;
			do {
				t = 0;
				std::cout << "input index number of " << i + 1 << " terminal(from 0 to " << lell.getMaxSize() - 1 << ")-> " << std::endl;
				while (getNum(term[i].number) < 0 || term[i].number < 0 || term[i].number > lell.getMaxSize() - 1 )// || term[term[i].number].value == 0 || term[term[i].number].value == 1 || term[term[i].number].value == 2)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
				for (int j = 0; j < n; j++) {
					if (i != j && term[j].number == term[i].number && term[j].type == term[i].type)
						t++;
				}
				if (t)
					std::cout << "You're wrong. Repeat please" << std::endl;
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
		return term;
	}

	int select_constructor(Logical_Element*& mas, int &num) {
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
	}

	Logical_Element::Logical_Element() {
		int j = 0;
		outp[j].number = j;
		outp[j].type = 1;
		outp[j].value = 2;
		outp[j].count = 0;
		inp_n = 1;
		outp_n = 1;
		inp[j].number = j;
		inp[j].type = 0;
		inp[j].value = 2;
		inp[j].count = 0;
	}

	Logical_Element::Logical_Element(int i, int out) {
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
		try {
			for (int i = 0; i < length; i++) {
				if (t_ar[i].type == 0) {
					inp[t_ar[i].number] = t_ar[i];
					inp_n++;
				}
				else {
					outp[t_ar[i].number] = t_ar[i];
					outp_n++;
				}
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
	}

	Logical_Element::Logical_Element(const Logical_Element &lel) {
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
		*this << lel;
		return *this;
	}


	Logical_Element Logical_Element::operator << (Logical_Element &lel) {
		try {
			for (int i = 0; i < lel.inp_n; i++) {
				inp[i] = lel.inp[i];
			}
			for (int i = 0; i < lel.outp_n; i++) {
				outp[i] = lel.outp[i];
			}
			for (int i = lel.inp_n; i < inp_n; i++) {
				inp[i].type = 2;
			}
			for (int i = lel.outp_n; i < outp_n; i++) {
				outp[i].type = 2;
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
		inp_n = lel.inp_n;
		outp_n = lel.outp_n;
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
						inp[n].type = 2;//УДАЛЕННЫЙ
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
						outp[n].type = 2;//УДАЛЕННЫЙ
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
		std::cout << "Input index number of terminal(from 0 to " << SZ << ")-> " << std::endl;
		int i;
		while (getNum(i) < 0 || i < 0 || i > SZ)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
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
		std::cout << "Input index number of terminal(from 0 to " << SZ << ")-> " << std::endl;
		int i;
		while (getNum(i) < 0 || i < 0 || i > SZ)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
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
		std::cout << "Input index number of terminal(from 0 to " << SZ << ")-> " << std::endl;
		int i;
		while (getNum(i) < 0 || i < 0 || i > SZ)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Input type of terminal(0-Input,1-Output)-> " << std::endl;
		int T;
		while (getNum(T) < 0 || T != 0 && T != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
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
			term = inpterm(1);
			*this += *term;
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

	Logical_Element Logical_Element:: operator += (Terminal term) {
		int T = term.type;
		int i = term.number;
		if (!T) {
			if (inp[i].type == 0) {
				std::cout << "There is terminal already!" << std::endl;
			}
			else {
				inp[i].number = i;
				inp[i].type = T; 
				inp[i].value = term.value;
				inp[i].count = term.count;
				inp_n++;
			}
		}
		else {
			if (outp[i].type == 1) {
				std::cout << "There is terminal already!" << std::endl;
			}
			else {
				outp[i].number = i;
				outp[i].type = T;
				outp[i].value = term.value;
				outp[i].count = term.count;
				outp_n++;

			}
		}
		return *this;
	}

	std::ostream & Logical_Element::print(std::ostream &s) const
	{
		std::cout << "Input Terminals: " << inp_n << std::endl;
		for (int i = 0; i < SZ; i++) {
			if (inp[i].type == 0) {
				std::cout << i + 1 << ") ";
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
		}
		std::cout << "Output Terminals: " << outp_n << std::endl;
		for (int i = 0; i < SZ; i++) {
			if (outp[i].type == 1) {
				std::cout << i + 1 << ") ";
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
		}
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
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
