#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s1 = "Hello Word";
	cout << s1 << endl;
		auto s2 = s1.c_str();
		cout << s2 << endl;

		//for (unsigned char i = 0; i < 255; i++)
		//{
		//	cout << i << ' ';
		//}

		char str2[] = "丽康华";
		cout << str2 << endl;
		str2[5] = -45;
		cout << str2 << endl; str2[5] = -46;
		cout << str2 << endl; str2[5] = -47;
		cout << str2 << endl; str2[5] = -48;
		cout << str2 << endl; str2[5] = -49;
		cout << str2 << endl; str2[5] = -50;
		cout << str2 << endl; str2[5] = -51;
		cout << str2 << endl;



		str2[5] = -52;
		cout << str2 << endl;
		str2[5] = -53;
		cout << str2 << endl;
		str2[5] = -54;
		cout << str2 << endl;
		str2[5] = -55;
		cout << str2 << endl;
		str2[5] = -56;
		cout << str2 << endl;
		str2[5] = -57;
		cout << str2 << endl;
		str2[5] = -58;
		cout << str2 << endl;

		str2[5] = -59;
		cout << str2 << endl;

		str2[5] = -60;
		cout << str2 << endl;

		

	return 0;
}
