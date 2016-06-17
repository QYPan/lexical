#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <string>
#include <map>
#include <deque>
#include <iomanip>
#include <iostream>
#define STR_SIZE 1000
using namespace std;
typedef pair<char, char> mpair;

map<mpair, string> anltable; // ������
deque<char> st;

char anstr[STR_SIZE];
char Vn[] = {"ETFAB"}; // ���ս����A��ʾE',B��ʾT'
char Vt[] = {"i*()+@"}; // �ս��
char empch = '@';
char S = 'E'; // �ķ���ʼ��
char fch = '#'; // ��Ƿ�
int step;
int top;
int width1 = 6;
int width2 = 9;
int width3 = 8;
int width4 = 9;
int width5 = 8;

void buile_anltable()
{
	mpair mp;
	string str;
	mp = make_pair('E', 'i');
	str = "TA";
	anltable[mp] = str;
	mp = make_pair('T', 'i');
	str = "FB";
	anltable[mp] = str;
	mp = make_pair('F', 'i');
	str = "i";
	anltable[mp] = str;
	mp = make_pair('A', '+');
	str = "+TA";
	anltable[mp] = str;
	mp = make_pair('B', '+');
	str = "@";
	anltable[mp] = str;
	mp = make_pair('B', '*');
	str = "*FB";
	anltable[mp] = str;
	mp = make_pair('E', '(');
	str = "TA";
	anltable[mp] = str;
	mp = make_pair('T', '(');
	str = "FB";
	anltable[mp] = str;
	mp = make_pair('F', '(');
	str = "(E)";
	anltable[mp] = str;
	mp = make_pair('A', ')');
	str = "@";
	anltable[mp] = str;
	mp = make_pair('B', ')');
	str = "@";
	anltable[mp] = str;
	mp = make_pair('A', '#');
	str = "@";
	anltable[mp] = str;
	mp = make_pair('B', '#');
	str = "@";
	anltable[mp] = str;
}

void input_string(string &instr)
{
	cout << "input the string:\n";
	cin >> instr;
	instr.append(1, fch); // ��ӱ�Ƿ�
}

bool is_Vt(char ch)
{
	int len = strlen(Vt);
	for(int i = 0; i < len; i++){
		if(ch == Vt[i]){
			return true;
		}
	}
	return false;
}

// ��������
void reverse_push(string str)
{
	for(int i = str.length()-1; i >= 0; i--){
		if(str[i] != empch){ // ����ʽ�Ҳ���Ϊ��
			st.push_front(str[i]);
		}
	}
}

void print_table(int cur, string instr, char Left, string Right)
{
	string str = "";
	string tmp = "";
	string LR;
	tmp.append(1, Left);
	if(Right != "successed"){
		LR = tmp + "->" + Right;
	}
	else{
		LR = Right;
	}
	for(int i = st.size()-1; i >= 0; i--){
		str.append(1, st[i]);
	}
	str.append(1, Left);
	step++;
	cout << left << setw(width1) << step << setw(width2) << str << setw(width3) << 
instr[cur]
		<< setw(width4) << instr.substr(cur) << setw(width5) << (Right==""?"":LR) 
<< endl;
}

int analyze_string(string instr)
{
	st.push_front(fch);
	st.push_front(S);
	int slen = instr.length();
	for(int i = 0; i < slen; i++){
		char term = instr[i]; // ��ǰ�ս��
		char topch = st.front(); // ��ջ��Ԫ��
		st.pop_front();
		bool f = is_Vt(topch);
		if(f == true){ // ջ��Ԫ�����ս��
			if(topch == term){
				print_table(i, instr, topch, "");
				continue;
			}
			else
				return 1;
		}
		else{
			if(topch == fch){ // �������
				if(topch == term){
					print_table(i, instr, topch, "successed");
					return 0;
				}
				else
					return 2;
			}
			else{ // �Ƶ�
				mpair mp;
				mp = make_pair(topch, term);
				map<mpair, string>:: iterator it;
				it = anltable.find(mp);
				if(it != anltable.end()){
					print_table(i, instr, topch, it->second);
					reverse_push(it->second);
					i--;
				}
				else
					return 3;
			}
		}
	}
	return 0;
}

void print_title()
{
	cout << endl << left << setw(width1) << "STEP" << setw(width2) << "STACK" << setw
(width3)
		<< "CURRENT" << setw(width4) << "LEFTOVER" << setw(width5) << "PRODUCTION" 
<< endl;
	cout << "---------------------------------------------------" << endl;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	string instr;
	input_string(instr);
	print_title();
	buile_anltable();
	bool ans = analyze_string(instr);
	if(ans){
		cout << "failed" << ans << endl;
	}
	return 0;
}

