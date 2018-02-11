#ifndef _STUDENT_H_
#define _STUDENT_H_
#endif
#define SLEN 20
typedef struct student
{
	char name[SLEN];
	char subject[SLEN];
	char stuID[SLEN];
	int grade;
}Student;
typedef struct node
{
	Student stu;
	struct node *next;
}Node;
typedef Node *List;
void InitialList(List *p);
int Find(const List p);
int ListStuCount(const List p);
void AddStu(List *p);
void DeleteStu(List *p);
List SortList(List p);
void Traverse(const List p);
void DestroyList(List *p);
int MaxGrade(List p);
int TotGrade(List);
List Reverse(List P);
double AverageGrade(List p);
