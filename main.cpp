#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Student
{
	string surname;
	string faculty;
	string course;
	int point;
};

ifstream OpenFile()
{
	ifstream fin("database.txt");
	if (!fin.is_open())
	{
		cout << "File is not open\n";
	}
	return fin;
}

int GetCountWord(string & str)
{
	istringstream ss(str);
	string word;
	int cout = 0;
	while (ss >> word)
	{
		cout++;
	}
	return cout;
}

void SaveData(Student & student, string row)
{
	istringstream rowRead(row); //Превращаем строку в поток для >>
	string word;
	int i = 0;
	while (rowRead >> word)
	{
		++i;
		if (i == 2)
		{
			student.faculty = word;
		}
		else if (i == 3)
		{
			student.course = word;
		}
		else if (i == 4)
		{
			student.point = stoi(word);
		}
	}
}

int CompareStrings(string const& a, string const& b) 
{
	return !(strcmp(a.c_str(), b.c_str()));
}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream inputFile = OpenFile();
	ifstream::pos_type position = inputFile.tellg();
	ofstream sortFile("sort.txt");
	string row;
	string massivFaculty[2] = { "ПС", "БИС" };
	Student student;
	for (int i = 0; i != 2; i++)
	{
		while (getline(inputFile, row))
		{
			if (GetCountWord(
				row) != 4)
			{
				continue;
			}
			SaveData(student, row);

			if (CompareStrings(massivFaculty[i], student.course))
			{
				sortFile << student.course << "\n";
			}
			cout << "gdsg" << endl;
		}
		inputFile.clear();
	}

    return 0;
}

