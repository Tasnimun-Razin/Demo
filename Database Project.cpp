#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct emp
{	int id;
	char name[25]; //*name *(n+0)  n[0]
	int salary;
};

void append();
void display();
void displayAll();
void modify();
void del();
void search();
void rename();
void remove();

//char getch();

char fname[]={"mydb.dat"};

main()
{	int ch;

	while(1)
	{	system("cls");
		
		printf("==================== Employee Management System ====================\n\n");
		
		printf("1. Append\n");
		printf("2. Modify\n");
		printf("3. Display\n");
		printf("4. Display All\n");
		printf("5. Search\n");
		printf("6. Rename\n");
		printf("7. Remove\n");
		printf("8. Delete File\n");
		printf("0. Exit\n\n");
		
		printf("===================================\n\n");
		
		printf("\t Please Enter Your Choice :");
		scanf("%d", &ch);
		
		switch(ch)
		{	case 1: append();
					break;
			case 2: modify();
					break;
			case 3: display();
					break;
			case 4: displayAll();
					break;
			case 5: search();
					break;
			case 6: rename();
					break;
			case 7: remove();
					break;
			case 8: del();
					break;
			case 0: exit(0);
			default:printf("\n Wrong choice, please try again.");
		}
		
		getch();
	}
}


void append()
{	FILE *fp;
	struct emp t1;
	
	fp=fopen(fname, "ab");
	
	printf("\n Enter ID:");
	scanf("%d", &t1.id);
	printf("\n Enter name:");
	scanf("%s", t1.name);
	printf("\n Enter salary:");
	scanf("%d", &t1.salary);
	
	fwrite(&t1, sizeof(t1), 1, fp);
	
	fclose(fp);
}


void modify()
{	FILE *fp, *fp1;
	struct emp t;
	int id, found=0;
	
	fp=fopen(fname, "rb"); //main_file
	fp1=fopen("temp.dat", "wb"); //intermediate_file
	
	printf("\n Enter the employee-ID you want to modify :");
	scanf("%d", &id);
	
	while(1)
	{	fread(&t, sizeof(t), 1, fp);
	
		if(feof(fp))
			break;
		if(t.id==id)
		{	found=1;
			printf("\n Enter employee-ID :");
			scanf("%d", &t.id);
			
			fflush(stdin);
			
			printf("\n Enter employee-name :");
			scanf("%s", t.name);
			printf("\n Enter employee-salary :");
			scanf("%d", &t.salary);
			fwrite(&t, sizeof(t), 1, fp1);
		}
		else
			fwrite(&t, sizeof(t), 1, fp1);
	}
	
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
		printf("\n Sorry, no record found.");
	else
	{	fp=fopen(fname, "wb");
		fp1=fopen("temp.dat", "rb");
		
		while(1)
		{	fread(&t, sizeof(t), 1, fp1);
		
			if(feof(fp1))
				break;
			
			fwrite(&t, sizeof(t), 1, fp);
		}
	}
		
	fclose(fp);
	fclose(fp1);
}


void display()
{	FILE *fp;
	struct emp t;
	int id, found=0;
	
	fp=fopen(fname, "rb");
	
	printf("\n Enter the employee-ID : ");
	scanf("%d", &id);
	
	while(1)
	{	fread(&t, sizeof(t), 1, fp);
	
		if(feof(fp))
			break;
		if(t.id==id)
		{	found=1;
			printf("\n===================================\n\n");
			printf("\t\t Employee Details of : %d \n\n", t.id);
			printf("=================================== \n\n");
			
			printf("Name : \t Salary : \n\n");
			
			printf("%s \t", t.name);
			printf("%d \t\n\n", t.salary);
			
			printf("===================================");
		}
	}
	
	if(found==0)
		printf("\n Sorry, no record found.");
		
	fclose(fp);
}


void displayAll()
{	FILE *fp;
	struct emp t;
		
	fp=fopen(fname, "rb");
		
	printf("\n===================================\n\n");
	printf("\t\t All Employee Details \n\n");
	printf("=================================== \n\n");
			
	printf("ID: \t Name : \t Salary : \n\n");
			
	while(1)
	{	fread(&t, sizeof(t), 1, fp);
	
		if(feof(fp))
			break;
			
		printf("%d \t", t.id);
		printf("%s \t", t.name);
		printf("%d \t\n\n", t.salary);
	}
	
	printf("===================================\n\n");
	
	fclose(fp);
}


void search()
{	FILE *fp;
	struct emp t;
	int id, found=0;
	char name[25];
	
	fp=fopen(fname, "rb");
	
	printf("\n Enter the employee-name :");
	scanf("%s", &name);
	
	while(1)
	{	fread(&t, sizeof(t), 1, fp);
	
		if(feof(fp))
			break;
				
		if(strcmp(name, t.name)==0)
		{	printf("\n===================================\n\n");
			printf("\t\t Employee Details of : %d \n\n", t.id);
			printf("=================================== \n\n");
			
			printf("Name : \t Salary : \n\n");
			
			printf("%s \t", t.name);
			printf("%d \t\n\n", t.salary);
			
			printf("===================================");
			found++;
		}
	}
	
	if(found==0)
		printf("\n Sorry, no record found.");
	
	fclose(fp);
}


void rename()
{	char name[25];
	
	printf("\n\n Enter the new file-name :");
	
	fflush(stdin);
	
	scanf("%[^\n]", name);
	
	rename(fname, name);
	
	strcpy(fname, name);
}


void remove()
{	FILE *fp, *fp1;
	struct emp t;
	
	char name[25];
	char val[10];
	
	printf("\n Do you want to make copy of it? (Y/N) :");
	scanf("%s", val);
	
	if(strcmp(val, "Y")==0)
	{	printf("\n\n Enter the new file-name :");
	
		scanf("%s", name);
	
		fp1=fopen(fname, "rb"); //main_file
		fp=fopen(name, "wb"); //copied_file
			
		while(1)
		{	fread(&t, sizeof(t), 1, fp1); //only binary
	
			if(feof(fp1))
				break;
		
			fwrite(&t, sizeof(t), 1, fp); //only binary
		}
	
		fclose(fp);
		fclose(fp1);
	
		remove(fname);
	
		strcpy(fname, name);
	}
	
	else
		remove(fname);
}


void del()
{	FILE *fp, *fp1;
	struct emp t;
	int id, found=0;
	
	fp=fopen(fname, "rb");
	fp1=fopen("temp.dat", "wb");
	
	printf("\n Enter the employee-ID you want to delete :");
	scanf("%d", &id);
		
	while(1)
	{	fread(&t, sizeof(t), 1, fp);
	
		if(feof(fp))
			break;
	
		if(t.id==id)
			found==1;
			
		else
			fwrite(&t, sizeof(t), 1, fp1);
	}
	
	fclose(fp);
	fclose(fp1);
	
	if(found=0)
		printf("\n Sorry, no record found.");
	else
	{	fp=fopen(fname, "wb");
		fp1=fopen("temp.dat", "rb");
		
		while(1)
		{	fread(&t, sizeof(t), 1, fp1);
			
			if(feof(fp1))
				break;
				
			fwrite(&t, sizeof(t), 1, fp1);
		}
	}
	
	fclose(fp);
	fclose(fp1);
}



//char getch()
//{	char val;
//	char rel;
//	
//	scanf("%c", &val);
//	//scanf("%c", &rel);	
//	return(val);
//}
