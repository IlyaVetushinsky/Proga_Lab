// Prog3overload.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

// Prog3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "Prog3applyh.h"
namespace Prog3 {

	void Logical_Element::Set_value() {
		for (int i = 0; i < inp_n; i++) {
			std::cout << "Input value of " << i << " Terminal:" << std::endl;
			int v;
			while (getNum(v) < 0 || v != 0 && v != 1)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
			inp[i].value = v;
		}
	}

	int Logical_function(Logical_Element lel) {
		if (lel.type == 0) {
			if (lel.inp[0].value == 2 || lel.inp[1].value == 2)
				return 2;
			return (lel.inp[0].value && lel.inp[1].value);
		}
		else if (lel.type == 1) {
			if (lel.inp[0].value == 2 || lel.inp[1].value == 2)
				return 2;
			return (lel.inp[0].value || lel.inp[1].value);
		}
		else if (lel.type == 2) {
			if (lel.inp[0].value == 2)
				return 2;
			return (!lel.inp[0].value);
		}
		else 
		return 2;
	}

	void add_conection(Logical_Element*& mas, int num, int& ou) {
		std::cout << "If you want to add result connection put 1, else put 0" << std::endl;
		int R;
		while (getNum(R) < 0 || R != 0 && R != 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		std::cout << "Put the number of the Logical element from which the connection will go" << std::endl;
		int f;
		while (getNum(f) < 0 || f < 0 || f > num - 1)
		{
			std::cout << "You're wrong. Repeat please" << std::endl;
		}
		int t;
		if (!R) {
			std::cout << "Put the number of the Logical element to which the connection will go" << std::endl;
			while (getNum(t) < 0 || t < 0 || t > num - 1 || t == f)
			{
				std::cout << "You're wrong. Repeat please" << std::endl;
			}
		}
		int i = 0;
		for (i = 0; i < mas[f].outp_n; i++) {
			if (mas[f].outp[i].count < 1)
				break;
		}
		int y = i;
		if (i == mas[f].outp_n) {
			Terminal* outp2 = new Terminal[mas[f].outp_n];
			for (int i = 0; i < mas[f].outp_n; i++) {
				outp2[i] = mas[f].outp[i];
			}
			delete[] mas[f].outp;
			mas[f].outp = new Terminal[mas[f].outp_n + 1];
			for (int i = 0; i < mas[f].outp_n; i++) {
				mas[f].outp[i] = outp2[i];
			}
			mas[f].outp_n++;
		}
		int nt = 0;
		if (!R) {
			if (mas[t].inp_n > 1) {
				std::cout << "Put the number of the Terminal to which the connection will go: 0 or 1" << std::endl;
				while (getNum(nt) < 0 || nt < 0 || nt > mas[f].inp_n)
				{
					std::cout << "You're wrong. Repeat please" << std::endl;
				}
			}
		}
		i = y;
		if (mas[f].outp[i].next == nullptr) {
			mas[f].outp[i].count++;
		}
		if (!R && mas[t].inp[nt].count == 0) {
			mas[t].inp[nt].count++;
		}
		if (!R) {
			mas[f].outp[i].next = &mas[t].inp[nt];
			mas[f].outp[i].jump = &mas[t];
		}
		else {
			mas[f].outp[i].next = nullptr;
			mas[f].outp[i].jump = nullptr;
			ou++;
		}
	}

	Res*& Start(Logical_Element*& mas, int num) {
		int r = 2;
		for (int i = 0; i < num; i++) {
			Logical_Element* ptr = &mas[i];
		 	Qrec(ptr);
		}
		for (int i = 0; i < num; i++) {
			Logical_Element* ptr = &mas[i];
			rec(ptr);
		}
		Res *res = new Res[num];
		int k = 0;
		res[0].q = 2;
		res[0].n = -1;
		
			Logical_Element* ptr = &mas[0];
			Outrec(ptr, res, num, k);
		
		return res;
	}

	Res* Outrec(Logical_Element*& ptr, Res* res, int num, int& k) {
		if (ptr != nullptr) {
			for (int y = 0; y < ptr->outp_n; y++) {
				if (ptr->outp[y].next == nullptr) {
					Qrec(ptr);
					int flag = 0;
					for (int j = 0; j < k; j++) {
						if (ptr->outp[y].value == res[j].q && ptr->number == res[j].n) {
							flag++;
						}
					}
					if (!flag) {
						res[k].n = ptr->getNumber();
						res[k].q = ptr->outp[y].value;
						k++;
					}
				}
			}
			for (int y = 0; y < ptr->outp_n; y++) {
				if (ptr->outp[y].next != nullptr) {
					Outrec(ptr->outp[y].jump, res, num, k);
				}
			}
		}
		return res;
	}

	void rec(Logical_Element*& ptr) {
		if (ptr != nullptr) {
			for (int k = 0; k < ptr->outp_n; k++) {
				if (ptr->outp[k].next != nullptr) {
					ptr->outp[k].next->value = ptr->outp[k].value;
					rec(ptr->outp[k].jump);
				}
			}
		}
	}

	void Qrec(Logical_Element*& ptr) {
		if (ptr != nullptr) {
			for (int k = 0; k < ptr->outp_n; k++) {
				ptr->outp[k].value = Logical_function(*ptr);
				if (ptr->outp[k].jump != nullptr) {
					Qrec(ptr->outp[k].jump);
				}
			}
		}
	}

	const char *msgsM[] = { "0. Quit", "1. Select logical element to configure", "2. Add logical element into the circuit", "3. Add conection", "4. Print info", "5. Start"};
	const int NMsgsM = sizeof(msgsM) / sizeof(msgsM[0]);
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
				term[i].number = lell.getinpSize();
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

	Logical_Element::Logical_Element() {
		SZ = 2;
		inp_n = 0;
		outp_n = 0;
	}

	Logical_Element::Logical_Element(int l, int num, int t) {
		if (l == 0 || l == 1) {
			int i = 2;
			int out = 1;
			SZ = i + out;
			outp = new Terminal[i];
			inp = new Terminal[out];
			inp_n = i;
			number = num;
			for (int j = 0; j < inp_n; j++) {
				inp[j].number = j;
				inp[j].type = 0;
				inp[j].value = 2;
				inp[j].count = 0;
				inp[j].jump = nullptr;
				inp[j].next = nullptr;
			}
			outp_n = out;
			for (int j = 0; j < outp_n; j++) {
				outp[j].number = j;
				outp[j].type = 1;
				outp[j].value = 2;
				outp[j].count = 0;
				outp[j].jump = nullptr;
				outp[j].next = nullptr;
			}
		}
		else {
			number = num;
			int i = 1;
			int out = 1;
			SZ = i + out;
			outp = new Terminal[i];
			inp = new Terminal[out];
			inp_n = i;
			for (int j = 0; j < inp_n; j++) {
				inp[j].number = j;
				inp[j].type = 0;
				inp[j].value = 2;
				inp[j].count = 0;
				inp[j].jump = nullptr;
				inp[j].next = nullptr;
			}
			outp_n = out;
			for (int j = 0; j < outp_n; j++) {
				outp[j].number = j;
				outp[j].type = 1;
				outp[j].value = 2;
				outp[j].count = 0;
				outp[j].jump = nullptr;
				outp[j].next = nullptr;
			}
		}
		type = l;
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

	/*Logical_Element::Logical_Element(const Logical_Element &lel) {
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
	}*/

	Logical_Element Logical_Element::copy(Logical_Element &lel) {
		*this = lel;
		return *this;
	}

	Logical_Element Logical_Element::operator = (Logical_Element &lel) {
		number = lel.number;
		type = lel.type;
		SZ = lel.SZ;
		if (lel.inp_n == 0) {
			lel.inp_n = 1;
		}
		if (lel.outp_n == 0) {
			lel.outp_n = 1;
		}		
		inp = new Terminal[sizeof(lel.inp) / lel.inp_n];
		outp = new Terminal[sizeof(lel.outp) / lel.outp_n];
		inp_n = lel.inp_n;
		outp_n = lel.outp_n;
		try {
			for (int i = 0; i < inp_n; i++) {
				inp[i].count = lel.inp[i].count;
				inp[i].jump = lel.inp[i].jump;
				inp[i].next = lel.inp[i].next;
				inp[i].number = lel.inp[i].number;
				inp[i].type = lel.inp[i].type;
				inp[i].value = lel.inp[i].value;
			}
			for (int i = 0; i < outp_n; i++) {
				outp[i].count = lel.outp[i].count;
				outp[i].jump = lel.outp[i].jump;
				outp[i].next = lel.outp[i].next;
				outp[i].number = lel.outp[i].number;
				outp[i].type = lel.outp[i].type;
				outp[i].value = lel.outp[i].value;
			}
		}
		catch (const std::exception &msg)
		{
			std::cout << msg.what() << std::endl;
		}
		return *this;
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
			for (i = 0; i < lel2.inp_n; i++) {
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
