#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;
//int main()
//{
//	char ccString1[] = "Is Page Fault? ?";
//	char ccString2[] = "No Page Fault?? ";
//	strcpy(ccString1, "No");
//	if (strcmp(ccString1, ccString2) == 0)
//		cout << ccString2;
//	else
//		cout << ccString1;
//
//	return 0;
//}
//int Function(unsigned int n) {
//	n = (n & 0x55555555) + ((n >> 1) & 0x55555555); 
//	n - (n & 0x33333333) + ((n >> 2) & 0x33333333); 
//	n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
//	n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff00ff);
//	n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
//	return n;
//}
//
//int main()
//{
//	const char a[] = "111\0ww11";
//	cout << Function(197) << endl;
//	cout << strlen(a) << endl;
//
//}
//class A {
//public:
//	void f() {
//		printf("A\n");
//	}
//};
//class B : public A {
//public:
//	virtual void f() {
//		printf("B\n");
//	}
//};
//int main() {
//	A *a = new B; 
//	a->f();
//	delete a; 
//	return 0;
//}

class Base
{
public:
	virtual int foo(int x)
	{
		cout << 1 << endl;
		return x * 10;
	}
	int foo(char x[14])
	{
		cout << 2 << endl;
		return sizeof(x) + 10;
	}
};
class Derived : public Base
{
	int foo(int x)
	{
		cout << 3 << endl;
		return x * 20;
	}
	virtual int foo(char x[10]) 
	{
		cout << 4 << endl;
		return sizeof(x)+ 20;
	}
};
class A
{
public:
	void print()
	{
		cout << "A: print()";
	}
};
class B : private A {
public:
	void print() {
		cout << "B: print( )";
	}
};
int f(int n) {
	static int i = 1; if (n >= 5)
		return n; n = n + i;
	i++;
	return f(n);
}
void increment_ints(int p[], int n)
{
	assert(p != NULL);/*确保p不为空指针*/
	assert(n >= 0);/*确保n不为负数*/
	while (n)/*循环n次.*/
	{
		*p++;
		/*增大p*/
		p++, n--;
		/*p指向下一位，n减1*/
	}
}

int main()
{
	int a[] = { 1,1,1,1,1,1,1,1 };
	int* p = a;
	int n = 5;
	for(auto e:p)
}

