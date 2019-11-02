#ifndef _PROG3H_
#define _PROG3H_
#include <iostream>
namespace Prog3 {
	int getNum(int &a);
	struct Terminal {
		int number; //ÏÎĞßÄÊÎÂÛÉ ÍÎÌÅĞ ÊËÅÌÛ
		int type; //0 ÂÕÎÄÍÎÉ ; 1 ÂÛÕÎÍÎÉ
		int count; //ÊÎËÈ×ÅÑÒÂÎ ÑÂßÇÅÉ
		int value; //ÇÍÀ×ÅÍÈÅ ÍÀ ÊËÅÌÅ
	};
	/*struct TerminalC {
		Terminal* p;
		Terminal operator [](int);
	};*/
	class Logical_Element {
	private:
		static const int SZ = 10;
		int inp_n;
		int outp_n;
		Terminal inp[SZ];
		Terminal outp[SZ];
	public:
		Logical_Element();
		Logical_Element(int i, int out);
		Logical_Element(Terminal* t_ar, int length);
		Logical_Element(const Logical_Element &lel);
		Logical_Element operator += (Terminal);
		Logical_Element operator << (Logical_Element &lel);
		Terminal* operator [](int);
		void reorg();
		void add_connection();
		void delete_connection();
		void add_terminal();        // +=
		std::ostream & get_Terminal_info(std::ostream&) const;
		std::ostream & print(std::ostream&) const;
		int getMaxSize() const { return SZ; }
		Logical_Element copy(Logical_Element &lel);
		// äîñòóï ê ıëåìåíòó ÷åğåç     Logical_Element[ type ][ index ]
		// Logical_Element << Logical_Element_2        =

		//++++++++++++++++++++++++ ïåğåãğóçèòü ââîä è âûâîä ÷åğåç << >>

		/*int push(int);
		int pop(int&);
		Stack & copy(const Stack &);
		Stack & move(Stack &); */
	};
	extern const char *msgs[];
	extern const char *cmsgs[];
	extern const char *msgsM[];
	extern const int NMsgs;
	extern const int NcMsgs;
	extern const int NMsgsM;
	int D_Reorg(Logical_Element &),
		D_Print_one(Logical_Element &),
		D_Add_link(Logical_Element &),
		D_Delete_link(Logical_Element &),
		D_Print_all(Logical_Element &),
		D_Add_terminal(Logical_Element &);
	/*Logical_Element* D_Empty_constructor();
	Logical_Element* D_Constructor_2();
	Logical_Element* D_Constructor_3();*/
	extern int(*fptr[])(Logical_Element &);
	/*Logical_Element* (*cptr[])() = { NULL, D_Empty_constructor, D_Constructor_2, D_Constructor_3};*/
	int dialog(const char *msgs[], int);
	Terminal* inpterm(int n);
	int select_constructor(Logical_Element*&, int &num);
}
#endif
#pragma once
