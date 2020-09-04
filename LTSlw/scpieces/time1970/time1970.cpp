#include <iostream>
#include <ctime>
#include <sys/timeb.h>
using namespace std;

int main()
{
	cout << time(NULL) << endl;//s
	timeb t;
	ftime(&t);
	cout << t.time << endl;
	cout << t.millitm << endl;
	return 0;
}