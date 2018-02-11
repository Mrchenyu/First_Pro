#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
static char *s_gets(char *st,int n);
static void showstudent(Student s);
static List FindPre(List p,char *str);
/*
 * function name :InitalList
 * function :initialize head pointer
 * parameter :List *p
*/
void InitialList(List *p)
{
	*p=NULL;
}

/*
 * function name :Find
 * function :search element in list
 * parameter :List p
 */ 
int Find(List p)
{
	List current;
	char str[SLEN];
	printf("Please enter the name you want to find:");
	s_gets(str,SLEN);
	current=p;
	if(!current)
		return 0;
	else
	{
		while(current)
		{
			if(!strcmp(current->stu.name,str))
				return 1;
			else
				current=current->next;
		}
	}
	return 0;
}
/*
 * function name :FindPre
 * function :find previous pointer of str
 * parameter :List p, char *str
 */
static List FindPre(List p,char *str)
{
	List tmp;
	tmp=p;
	while(tmp->next!=NULL&&strcmp(p->stu.name,str))
		tmp=tmp->next;
	return tmp;
}
/*
 * function name :DeleteStu
 * function :delete student list
 * parameter :List p
 */
void DeleteStu(List *p)
{
	char temp[SLEN];
	List pt1,pt2;
	if(!*p)
		puts("List is null,nothing to delete!!");
	puts("Please enter the name of student to delete:");
	s_gets(temp,SLEN);
	pt1=*p;
	if(pt1==NULL)
		printf("list is null!\n");
	else if(!strcmp(pt1->stu.name,temp)) //if element is head no previous pointer
	{
		pt2=pt1;
		*p=pt1->next;
		free(pt2);
		printf("We have delete %s,this student.\n",temp);
	}
	else
	{
		pt1=FindPre(pt1,temp);  //not head need to find previous pointer
		if(pt1->next==NULL)
			printf("Don't exist %s!\n",temp);
		else
		{
			pt2=pt1->next;
			pt1->next=pt1->next->next;
			free(pt2);
			printf("We have delete %s,this student.\n",temp);
		}
	}
}
/*
 * function name :ListStuCount
 * function :list the total of student
 * parameter :List p
 */
int ListStuCount(const List p)
{
	int total=0;
	List current=p;
	while(current)
	{
		total++;
		current=current->next;
	}
	return total;
}
/*
 * function name :Traverse
 * function :traverse the student list
 * parameter :List p
 */
void Traverse(const List p)
{
	List current=p;
	if(!current)
		printf("List is null!!");
	while(current)
	{
		showstudent(current->stu);
		current=current->next;
	}
}
/*
 * function name :showstudent
 * function :show current studnet information
 * parameter :Student s
 */
static void showstudent(Student s)
{
	printf("Name is %s,subject is %s,ID is %s,grade is %d.\n",s.name,s.subject,s.stuID,s.grade);
}
/*
 * function name :SortList
 * function :sort the student list according to grade
 * paramemter :List P
 */
List SortList(List P)
{
	List first,t,p,q;
	if(P==NULL)
	{	
		printf("List is NULL!");
	}
	else
	{
		first=P->next;
		P->next=NULL;
		while(first!=NULL)
		{
			for(t=first,q=P;(q!=NULL)&&(q->stu.grade<t->stu.grade);p=q,q=q->next)
				;
			first=first->next; //insert this node into sorted list
			if(q==P)
			{
				t->next=P;
				P=t;
			}
			else
			{
				t->next=q;
				p->next=t;
			}
		}
	}
	printf("We have sort list according to student's grade!!");
	return P;
}
/*
 * function name:AddStu
 * function :Add studnet node 
 * parameter :List *p
 */
void AddStu(List *p)
{
	List pt,current;
	pt=(List)malloc(sizeof(Node));
	puts("Please enter students name:");
	s_gets(pt->stu.name,SLEN);
	puts("Please enter students subject:");
	s_gets(pt->stu.subject,SLEN);
	puts("Please enter students ID:");
	s_gets(pt->stu.stuID,SLEN);
	puts("Please enter students grade:");
	scanf("%d",&(pt->stu.grade));
	getchar(); //use scanf to read grade, there is '\n' at end of the string
	pt->next=NULL; //put node of next to NULL
	if(*p==NULL)
	{
		*p=pt;
	}
	else
	{
		current=*p;
		while(current->next!=NULL)
		{
			current=current->next;
		}
		current->next=pt;
	}
}
/*
 * function name :DestroyList
 * function :destroy the student list
 * parameter :List *p
 */
void DestroyList(List *p)
{
	List current,tmp;
	current=*p;
	while(current!=NULL)
	{
		tmp=current;
		current=current->next;
		free(tmp);
	}
    *p=NULL;		
}
/*
 * function name :Reverse
 * function : reverse the student list by using queue structure
 * parameter :List p
 */
List Reverse(List P)
{
	List stack[100],tmp;
	int i=0;
	int j=0;
	tmp=P;
	while(tmp!=NULL)
	{
		stack[i++]=tmp;
		tmp=tmp->next;
	} //loop out tmp is equal to NULL
	while(j<i)
	{
		stack[j]->next=tmp;
		tmp=stack[j];
		j++;
	}
	printf("Now the student list have been reversed!!");
	return tmp;
}
/*
 * function name :MaxGrade
 * function :calculate the max grade
 * parameter :List p
 */
int MaxGrade(List p)
{
	List temp;
	int max=0;
	temp=p;
	while(temp)
	{
		if(temp->stu.grade>max)
			max=temp->stu.grade;
		temp=temp->next;
	}
	return max;
}
/*
 * function name :TotGrade
 * function :calculate the total grade
 * parameter :List p
 */
int TotGrade(List p)
{
	List temp;
	int total=0; // initialize
	temp=p;
	while(temp)
	{
		total+=temp->stu.grade;
		temp=temp->next;
	}
	return total;
}
/*
 * function name :AvergeGrade
 * function :calculate the average grade
 * parameter :List p
 */
double AverageGrade(List p) 
{
	List temp;
	int count=0;//calculate the total number of student
	double total=0;
	temp=p;
	while(temp)
	{
		count++;
		total+=temp->stu.grade;
		temp=temp->next;
	}
	return (total/count);
}
/*
 * function name :s_gets
 * function :scan n bytes from stdin
 * parameter :char *st, int n
 */
static char *s_gets(char *st,int n) 
{
	char *ret_val;
	char *find;
	ret_val=fgets(st,n,stdin);
	if(ret_val)
	{
		find=strchr(st,'\n');
		if(find)
			*find='\0';
		else
			while(getchar()!='\n')
				continue;
	}
	return ret_val;
}
