#include "stlList.h"
namespace test
{
    void Test1()
    {
        list<int> lt;
        lt.push_back(0);
        lt.push_back(1);
        lt.push_back(2);
        lt.push_back(3);
        lt.push_back(4);
        lt.push_front(-1);
        lt.push_front(-2);

        //遍历1：迭代器
        list<int>::iterator it = lt.begin();
        while (it != lt.end())
        {
            cout << *it++ << " ";
        }
        cout << endl;
        //遍历2：范围for
        for (auto e : lt)
        {
            cout << e << " ";
        }
        cout << endl;
        //遍历3：反向遍历：迭代器
        list<int>::reverse_iterator rit = lt.rbegin();
        while (rit != lt.rend())
        {
            cout << *rit++ << " ";
        }
        cout << endl;
    }
    void Test2()
    {
        list<int> lt;
        lt.push_back(0);
        lt.push_back(1);
        lt.push_back(2);
        lt.push_back(3);
        lt.push_back(4);
        lt.push_front(-1);
        lt.push_front(-2);
        list<int>::iterator pos = find(lt.begin(), lt.end(), 3);
        lt.insert(pos, 99);
        //遍历2：范围for 
        for (auto e : lt)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}
namespace L
{
    struct point
    {
        int x;
        int y;
    }; 
    void Test1()
    {
        cout << "Test1" << endl;
        list<int> lt;
        lt.push_back(0);
        lt.push_back(1);
        lt.push_back(2);
        lt.push_back(3);
        lt.push_back(4);
        lt.push_back(5);
        list<int>::iterator it = lt.begin();
        while (it != lt.end())
        {
            cout << *it << " ";
            it ++;
        }
        cout << endl;
    }
    void Test2()
    {
        cout << "Test2" << endl;
        
        list<point> lt;
        lt.push_back({ 1,1 });
        lt.push_back({ 2,2 });
        lt.push_back({ 3,3 });
        list<point>::iterator it = lt.begin();
        while (it != lt.end())
        {
            //it->operator()->x;it->operator()->y;
            cout << "(" << it->x << "," << it->y << ")" << " ";
            it++;
        }
        cout << endl;
    }
    void Test3()
    {
        cout << "Test3" << endl;

        list<int> lt;
        lt.push_back(0);
        lt.push_back(1);
        lt.push_back(2);
        lt.push_back(3);
        lt.push_back(4);
        lt.push_back(5);
        list<int> copy = lt;
        for (auto e : lt)
        {
            cout << e << " ";
        }
        cout << endl;
    }
}
int main()
{
    L::Test1();
    L::Test2();
    L::Test3();

    return 0;
}
