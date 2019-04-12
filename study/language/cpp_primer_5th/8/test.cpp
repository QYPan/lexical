#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

istream& MyCout(istream& stream)
{
	while (!stream.eof())
	{
		string str;
		stream >> str;

		cout << str << endl;
	}

	stream.clear();

	return stream;
}

void PrintIstringstream()
{
	string str("lee 123456 0787323 345");
	istringstream is(str);

	MyCout(is);
}

void ReadFileToVector()
{
	string fileName("in.txt");
	ifstream input(fileName);
	vector<string> vec;

	if (input)
	{
		string word;
		while (input >> word)
		{
			vec.push_back(word);
		}
	}
	else
	{
		cerr << "could not open: " + fileName;
	}

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void ReadFileLineToWord()
{
	string fileName("in.txt");
	ifstream input(fileName);
	vector<string> vec;

	if (input)
	{
		string line;
		while (getline(input, line))
		{
			vec.push_back(line);
		}
	}
	else
	{
		cerr << "could not open: " + fileName;
	}

	for (int i = 0; i < vec.size(); i++)
	{
		istringstream is(vec[i]);

		MyCout(is);
	}
}

void GetPersonInfo()
{
	struct PersonInfo
	{
		string name;
		vector<string> phones;
	};

	string line, word;
	vector<PersonInfo> people;

	FILE * inFile;
	freopen_s(&inFile, "in.txt", "r", stdin);

	istringstream record;

	while (getline(cin, line))
	{
		PersonInfo info;
		
		record.clear();
		record.str(line);
		record >> info.name;

		while (record >> word)
		{
			info.phones.push_back(word);
		}

		people.push_back(info);
	}

	for (auto e : people)
	{
		cout << e.name;
		for (auto w : e.phones)
		{
			cout << " " << w;
		}
		cout << endl;
	}
}

struct Sales_data
{
	string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;
	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data add(const Sales_data&, const Sales_data&);
ostream& print(ostream&, const Sales_data&);
istream& read(istream&, Sales_data&);

double Sales_data::avg_price() const
{
	if (units_sold)
	{
		return revenue / units_sold;
	}
	else
	{
		return 0;
	}
}

Sales_data& Sales_data::combine(const Sales_data& rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

Sales_data add(const Sales_data& lhs, const Sales_data& rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);
	return sum;
}

ostream& print(ostream& os, const Sales_data& item)
{
	os << item.isbn() << " " << item.units_sold << " "
		<< item.revenue << " " << item.avg_price();
	return os;
}

istream& read(istream& is, Sales_data& item)
{
	double price = 0;
	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;
	return is;
}

void TestSalesData(const string& inFile, const string& outFile)
{
	ifstream input(inFile);
	ofstream output(outFile, ofstream::app);

	if (input)
	{
		Sales_data total;
		if (read(input, total))
		{
			Sales_data trans;
			while (read(input, trans))
			{
				if (total.isbn() == trans.isbn())
				{
					total.combine(trans);
				}
				else
				{
					print(output, total) << endl;
					total = trans;
				}
			}
			print(output, total) << endl;
		}
		else
		{
			cerr << "No data?!" << endl;
		}
	}
	else
	{
		cerr << "could not open: " + inFile;
	}
}

int main(int argc, char **argv)
{
	/*
	FILE * inFile;
	freopen_s(&inFile, "in.txt", "r", stdin);

	MyCout(cin); // 8.1, 8.2

	ReadFileToVector(); // 8.4, 8.5

	if (argc == 3) // 8.6, 8.7, 8.8
	{
		string inFile(argv[1]);
		string outFile(argv[2]);
		TestSalesData(inFile, outFile);
	}
	

	PrintIstringstream(); // 8.9
	
	ReadFileLineToWord(); // 8.10

	GetPersonInfo(); // 8.11

	*/

	return 0;
}