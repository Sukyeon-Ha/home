#include <fstream>
#include <iostream>

using namespace std;

void compare(string str1, string str2)
{
	if(str1.length() != str2.length()) cout << "length is different!" << endl << str1.length() << " and " << str2.length() << endl;
	int len = 0;
	if (str1.length() < str2.length()) len = int(str1.length());
	else len = str2.length();
	for (int i = 0; i < len; i++)
	{
	if ((str1[i] != str2[i])) cout << "at location " << i << ", " << (int)str1[i] << " and " << (int)str2[i] << " are different" << endl;
	}
	//int x = 1;
	//int y = 0;
	//for(int i = 0; i < str1.length(); i++)
	//{
	//	y++;
	//	if (str1[i] != str2[i]) cout << "mistmatch at " << x << ", " << y << ": " << str1[i] << " and " << str2[i] << endl;
	//	if (str1[i] == '\n')
	//	{
	//	x += 1;
	//	y = 0;
	//	}
	//}
}

int main()
{
	string path1 = "out-p1e1.txt";
	string path2 = "p1e1-output.txt";
	string data1 = "";
	string data2 = "";

	ifstream file1(path1.data());
	string line = "";
	while(getline(file1,line)) data1.append(line + "\n");
	file1.close();

	ifstream file2(path2.data());
	while(getline(file2,line)) data2.append(line + "\n");
	file2.close();

	compare(data1,data2);
	//cout << data1 << endl << endl;
	//cout << data2 << endl << endl;
	return 0;
}
