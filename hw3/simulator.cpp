//pass
#include <iostream>
#include <fstream>

using namespace std;
int power(int a, int n)
{
	int value = 1;
	for(int i=0;i<n;i++) value *= a;
	return value;
}

int string_to_int(string str)
{
	int value = 0;
	int len = str.length();
	for(int i=0;i<(int)str.length();i++) 
	{
		int adder = ( (int)str[len-1-i] - 48 ) * power(10,i);
		value += adder;
	}
	return value;
}

string ohd(int num)
{
	if(num == 0)return "0";
	if(num == 1)return "1";
	if(num == 2)return "2";
	if(num == 3)return "3";
	if(num == 4)return "4";
	if(num == 5)return "5";
	if(num == 6)return "6";
	if(num == 7)return "7";
	if(num == 8)return "8";
	if(num == 9)return "9";
	if(num == 10)return "A";
	if(num == 11)return "B";
	if(num == 12)return "C";
	if(num == 13)return "D";
	if(num == 14)return "E";
	if(num == 15)return "F";

	return "Invalid PC";
}

string fhd(int counter)
{
	string value = "";
	for(int i = 0; i < 10; i++)
	{
		if (counter < 16)
		{
		value = ohd(counter) + value;
		break;
		}
		value = ohd(counter % 16) + value;
		counter = counter / 16;
	}
	while (value.length() < 4) value = '0' + value;
	if (value.length() > 4) return "invalid PC!!!!!!!!";
	return value;
}

string ch2bin(char c)
{
	if(c == '0') return "0000";
	if(c == '1') return "0001";
	if(c == '2') return "0010";
	if(c == '3') return "0011";
	if(c == '4') return "0100";
	if(c == '5') return "0101";
	if(c == '6') return "0110";
	if(c == '7') return "0111";
	if(c == '8') return "1000";
	if(c == '9') return "1001";
	if(c == 'a') return "1010";
	if(c == 'b') return "1011";
	if(c == 'c') return "1100";
	if(c == 'd') return "1101";
	if(c == 'e') return "1110";
	if(c == 'f') return "1111";
	return "invalid character!";	
}

string inst2bin(string inst)
{
	string value = "";
	for(int i = 0; i <8; i++)
	{
	value.append(ch2bin(inst[i]));
	}
	return value;
}

int bin2int(string bin)
{
	int value = 0;
	int len = (int)bin.length();
	int adder = 0;
	for(int i = 0; i < len; i++)
	{
	adder = ((int)bin[i] - 48) * power(2,len-1-i);
	value += adder;
	}
	return value;
}

void printstr(string str)
{
	cout << endl << endl << "printstr" << endl;
	for (int i = 0; i < (int)str.length(); i++) cout << str[i];
	cout << endl << endl;
}

int sbin2int(string bin)
{
	if (bin[0] == '0')
	{
		bin = bin.substr(1,bin.length()-1);
		return bin2int(bin) + 1;
	}
	if (bin[0] == '1')
	{
		for (int i = 0; i < int(bin.length()); i++)
		{
			if (bin[i] == '1')
			{
				bin[i] = '0';
				continue;
			}
			if (bin[i] == '0') bin[i] ='1';
		}
		return -1 * bin2int(bin);
	}
	cout << "error on sbin2int!" << endl;
	return 0;
}

int instruction(string inst, int counter)
{
	string bin = inst2bin(inst);
	
	if (bin.substr(0,6) == "000010")
	{
		//cout << "instruction j" << endl;
		return sbin2int(bin.substr(6,26)) - 1;
	}
	//if (bin.substr(0,6) == "000000") return sbin2int(bin.substr(6,26)) - 1;
	if (bin.substr(0,6) == "000011")
	{
		//cout << "instruction jal" << endl;
		return sbin2int(bin.substr(6,26)) - 1;
	}
	if (bin.substr(0,6) == "000100") 
	{
		//cout << "instruction beq" << endl;
		return counter + sbin2int(bin.substr(16,16));
	}
	if (bin.substr(0,6) == "000101")
	{
		//cout << "instruction bne" << endl;
		return counter + sbin2int(bin.substr(16,16));
	}
	return counter + 1;
}

void simulate(int len, string code[], int max)
{
	int counter = 0;
	bool start_switch = true;
	for(int i = 0; i < max; i++)
	{
		if(counter >= len) break; 
		//other break conditions...

		if(start_switch == false) cout << endl << endl;
		if(start_switch == true) start_switch = false;

		cout << "Cycle " << i+1 << endl;
		cout << "PC: " << fhd(counter * 4) << endl;
		cout << "Instruction: " << code[counter];

		counter = instruction(code[counter], counter);
	}

}

int main(int argc, char* argv[])
{
	if (argc < 3) cout << "invalid file option!" << "\n";
	
	char* source_loc = argv[1];
	int max = string_to_int(argv[2]);

	ifstream file;
	file.open(source_loc);
	
	string source = "";
	string str = "";
	int len = 0;
	while(getline(file,str))
	{
		source.append(str);
		len++;
	}
	file.close();

	string code[len];
	for(int i = 0; i < len; i++)
	{
		code[i] = source.substr(8*i,8);
	}

	simulate(len,code,max);
	

	return 0;
}
