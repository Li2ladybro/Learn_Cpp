//struct Data
//{
//	void add()
//	{
//
//	}
//};
#include"Data.h"

int main()
{

	Data a1(2026, 1, 12);
	Data a2 = a1;
	cout << (a2 > a1) << endl;
	//	(a1 += 1100).Print();//

	(a1 += 110000).Print();
	a1.Print();

	Data a3(2026, 1, 13);
	(a3 +-11456).Print();


	cout << (a3 + -11456) - a1<<endl;
	cout << a1-(a3 + -11456) <<endl;

	cout << &a1<<endl;


	static int a;

	return 0;
}