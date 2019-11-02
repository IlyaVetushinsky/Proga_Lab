#ifndef _PROG3H_
#define _PROG3H_
#include <iostream>
namespace Prog3 {
	class Logical_Element;
	struct Terminal {
		int number; //ÏÎÐßÄÊÎÂÛÉ ÍÎÌÅÐ ÊËÅÌÛ
		int type; //0 ÂÕÎÄÍÎÉ ; 1 ÂÛÕÎÍÎÉ
		int count; //ÊÎËÈ×ÅÑÒÂÎ ÑÂßÇÅÉ
		int value; //ÇÍÀ×ÅÍÈÅ ÍÀ ÊËÅÌÅ
		Terminal* next; //âûõîä ê êëåìå ñëåäóþùåãî ýëåìåíòà ñõåìû
		Logical_Element* jump; //óêàçàòåëü íà ñëåäóþùèé ýëåìåíò ñõåìû(äëÿ îáõîäà)
	};
	struct Res {
		int q;
		int n;
	};
	class Logical_Element {
	private:
		int number; //íîìåð ëîãè÷åñêîãî ýëåìåíòà â öåïè
		int type; //òèï ëîãè÷åñêîãî ýëåìåíòà È-0 ÈËÈ-1 ÍÅ-2
		int SZ;
		int inp_n;
		int outp_n;
		Terminal* inp;
		Terminal* outp;
	public:
		Logical_Element();
		Logical_Element(int, int, int);
		Logical_Element(int, int);
		Logical_Element(Terminal*, int);
		//Logical_Element(const Logical_Element &lel);
		Logical_Element operator >> (Terminal);
		Logical_Element operator = (Logical_Element &);
		friend std::ostream & operator <<(std::ostream &, const Logical_Element &);
		Terminal* operator [](int);
		void add_terminal();        // +=
		std::ostream & print(std::ostream&) const;
		int getMaxSize() const { return SZ; }
		int getinpSize() const { return inp_n; }
		int getoutpSize() const { return outp_n; }
		int getType() const { return type; }
		int getNumber() const { return number; }
		Logical_Element copy(Logical_Element &);
		friend int Logical_function(Logical_Element);
		friend void add_conection(Logical_Element*&, int, int&);
		friend Res*& Start(Logical_Element*&, int);
		friend void rec(Logical_Element*&);
		friend void Qrec(Logical_Element*&);
		friend Res* Outrec(Logical_Element*&, Res*, int, int&);
		void Set_value();
	};
	extern const char *msgsM[];
	extern const int NMsgsM;
	extern int(*fptr[])(Logical_Element &);
	int dialog(const char *msgs[], int);
	int getNum(int &a);
	Terminal* inpterm(int n, Logical_Element lell);
}
#endif
#pragma once
