#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
static char *s_gets(char *st,int n);
static void showstudent(Student s);
static List FindPre(List p,char *str);
void InitialList(List *p)
{
	*p=NULL; //初始化头指针
}
int Find(List p) //查找有无当前元素
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
static List FindPre(List p,char *str)  //查找前驱指针
{
	List tmp;
	tmp=p;
	while(tmp->next!=NULL&&strcmp(p->stu.name,str))
		tmp=tmp->next;
	return tmp;
}
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
	else if(!strcmp(pt1->stu.name,temp)) //首元素为待删除的元素 无前驱指针
	{
		pt2=pt1;
		*p=pt1->next;
		free(pt2);
		printf("We have delete %s,this student.\n",temp);
	}
	else
	{
		pt1=FindPre(pt1,temp);  //非首元素 故而需要前驱指针
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
static void showstudent(Student s)
{
	printf("Name is %s,subject is %s,ID is %s,grade is %d.\n",s.name,s.subject,s.stuID,s.grade);
}
List SortList(List P)  //链表排序 根据学生的成绩排序
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
			first=first->next; //无序表中节点离开 插入节点进入有序链表
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
	getchar(); //由于用scanf读取grade 故而留有一个换行字符
	pt->next=NULL; //注意将next置为NULL
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
List Reverse(List P)  //用队列结构来反序
{
	List stack[100],tmp;
	int i=0;
	int j=0;
	tmp=P;
	while(tmp!=NULL)
	{
		stack[i++]=tmp;
		tmp=tmp->next;
	} //退出循环时tmp=NULL
	while(j<i)
	{
		stack[j]->next=tmp;
		tmp=stack[j];
		j++;
	}
	printf("Now the student list have been reversed!!");
	return tmp;
}
int MaxGrade(List p) //计算最高分
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
int TotGrade(List p) //计算总分
{
	List temp;
	int total=0; //初始化
	temp=p;
	while(temp)
	{
		total+=temp->stu.grade;
		temp=temp->next;
	}
	return total;
}
double AverageGrade(List p) //计算均分
{
	List temp;
	int count=0;//统计人数
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
static char *s_gets(char *st,int n) //读取一定长度的字符串
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
