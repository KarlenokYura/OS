// SoProc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
int main()
{
	float a, b, c;
	float y = 0;
	std::cout << " Vvedite chislo a: ";
	std::cin >> a;
	std::cout << " Vvedite chislo b: ";
	std::cin >> b;
	std::cout << " Vvedite chislo c: ";
	std::cin >> c;
	__asm {
	START:
		FINIT
		FLD a
		FLD b
		FCOMI st(0), st(1)
		jbe AleB
		ja AgtB

		AleB :
		FSTP st(1)
		FLD c
		FCOMI st(0), st(1)
		jbe AleC
		ja AgtC

		AleC :
		FST y
		JNE END

		AgtC :
		FSTP st(0)
		FST y
		JNE END

		AgtB :
		FSTP st(0)
		FLD c
		FCOMI st(0), st(1)
		jbe BleC
		ja BgtC

		BleC :
		FST y
		JNE END

		BgtC :
		FSTP st(0)
		FST y
		JNE END

		END:
		FWAIT // Синхронизация работы с центральным процессором
	}
	std::cout << "\n Minimalnoe chislo y=min(a, b, c) = " << y;
	std::cout << "\n By Borodina Elizaveta. FIT 3 course, 4 group \n";
}
