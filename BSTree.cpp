#include "BSTree.h"
#include "BSTreeKV.h"
using namespace std;
void BSTreeTest()
{
	//插入节点
	BSTree<int> i;
	i.Insert(5);
	i.Insert(6);
	i.Insert(7);
	i.Insert(8);
	i.Insert(4);
	i.Insert(3);
	i.Insert(2);
	i.Insert(1);
	i.Insert(9);
	i.InOrder();
	cout << endl;
	//寻找节点
	BSTNode<int>* ret1 = i.Find(6);
	if (ret1)
	{
		cout << "FIND IT!" << endl;
	}
	BSTNode<int>* ret2 = i.Find(0);
	if (ret2)
	{
		cout << "FIND IT!" << endl;
	}
	cout << endl;

	//删除节点
	i.Erase(0);
	i.Erase(5);
	i.Erase(1);
	i.Erase(9);
	i.InOrder();

}
void BSTreeKVTest()
{
	////插入与遍历
	//BSTreeKV<string, string> dict;
	//dict.Insert("banana", "香蕉");
	//dict.Insert("ciname", "电影");
	//dict.Insert("apple", "苹果");
	//dict.Insert("dog", "狗");
	//dict.Insert("string", "字符串");
	//dict.Insert("sort", "排序");
	//dict.InOrder();
	//
	////通过key寻找value
	//cout << dict.FindValue("sort") << endl;
	//cout << dict.FindValue("dog") << endl;
	//cout << dict.FindValue("aaaa") <<endl;
	//
	
	//计数功能
	string strArr[] = { "Aa","Aa" ,"Aa" ,"Bb","Bb" ,"Cc" };
	BSTreeKV<string, int>countTree;
	for (auto& str : strArr)
	{
		auto ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			++ret->_value;
		}
	}
	countTree.InOrder();

}
int main()
{
	/*BSTreeTest();
	cout << endl << endl << endl;*/
	BSTreeKVTest();
	return 0;
}