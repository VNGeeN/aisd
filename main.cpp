#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
//typedef vector<FacultyAndCourse> vectorFaculty;

struct FacultyAndCourse
{
	string faculty;
	string course;
};

struct Student
{
	string surname;
	FacultyAndCourse faculty;
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
			student.faculty.faculty = word;
		}
		else if (i == 3)
		{
			student.faculty.course = word;
		}
		else if (i == 4)
		{
			student.point = stoi(word);
		}
	}
}

int CompareStrings(string const& a, string const& b) 
{
	return (strcmp(a.c_str(), b.c_str()));
}

void vectorGroup(ifstream &file, vector<string> &massivCours)
{
	Student studentData;
	string str;
	bool notIdentical = true;
	while (!file.eof())
	{
		getline(file, str);
		if (GetCountWord(str) != 4)
		{
			continue;
		}
		SaveData(studentData, str);
		if (massivCours.size() == 0)
		{
			massivCours.push_back(studentData.faculty.course);
		}
		else
		{
			bool isIdentefic = false;
			for (int i = 0; i != massivCours.size(); i++)
			{
				if (CompareStrings(massivCours[i], studentData.faculty.course))
				{
					isIdentefic = true;
				}
				else
				{
					isIdentefic = false;
					break;
				}
			}
			if (isIdentefic == true)
			{
				massivCours.push_back(studentData.faculty.course);
			}
		}
	}
}

int writeInFile(ifstream &inFile, vector<string> &massivCours, ofstream &outFile)
{
	int point = 0;
	int j = 0;
	string row;
	Student student;
	bool notIdentical = true;
	for (int i = 0; i != massivCours.size(); i++)
	{
		while (getline(inFile, row))
		{
			if (GetCountWord(row) != 4)
			{
				continue;
			}
			SaveData(student, row);
			if (CompareStrings(massivCours[i], student.faculty.course))
			{
				if (notIdentical)
				{
					outFile << student.faculty.faculty << ' ' << student.faculty.course << ' ';
					notIdentical = false;
				}
				++j;
				point += student.point;
			}
		}
		outFile << point / j << "\n";
		notIdentical = true;
		point = 0;
		j = 0;
		inFile = OpenFile();
	}
	return 0;
}

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream inputFile = OpenFile();
	vector<string> massivFacultet;
	vector<string> massivCours;
	ofstream sortFile("sort.txt");
	ofstream sortGrupFile("grupsort.txt");
	bool notIdentical = true;
	vectorGroup(inputFile, massivCours);
	inputFile = OpenFile();
	writeInFile(inputFile, massivCours, sortFile);
	inputFile.close();
    return 0;
}

