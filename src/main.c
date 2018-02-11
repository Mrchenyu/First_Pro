#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "student.h"
char menu(void);
int main(int argc, char **argv)
{
	List head;
	char choice;
	int find=0;
	InitialList(&head); //init pointer 
	while((choice=menu())!='k')
	{
		switch (choice)
		{
			case 'a':AddStu(&head);
				break;
			case 'b':Traverse(head);
				break;
			case 'c':printf("Total students number is %d.\n",ListStuCount(head));
				break;
			case 'd':find=Find(head);
			{
				if(find)
					printf("We have find this student.\n");
				else
					printf("Don't exist this student.\n");
			}
				break;
			case 'e':DeleteStu(&head);
				break;
			case 'f':head=SortList(head);
				break;
			case 'g':head=Reverse(head);
				break;
			case 'h':printf("Average grade of student list is %lf.\n",AverageGrade(head));
				break;
			case 'i':printf("Max grade of student list is %d.\n",MaxGrade(head));
				break;
			case 'j':printf("Total grade of student list is %d.\n",TotGrade(head));
				break;
			default:puts("Switching error!!");
		}
	}
	DestroyList(&head);
	puts("List has been destroyed,Bye!!");
	return 0;
}
char menu(void)
{
	int ch;
	puts("Enter your choice:");
	puts("a) add a student          b) show list of students");
	puts("c) numbers of students    d) find a student");
	puts("e) delete a student       f) sort list of students");
	puts("g) reverse student list   h) average grade of student");
	puts("i) max grade of student   j) total grade of student");
	puts("k) quit");
	while((ch=getchar())!=EOF)
	{
		while(getchar()!='\n')  //scan next character
			continue;
		ch=tolower(ch);  //lower character
		if(strchr("abrcdefghijk",ch)==NULL)
			puts("Please enter an a,b,c,d,e,f,g or h:");
		else
			break;
	}
	return ch;
}
