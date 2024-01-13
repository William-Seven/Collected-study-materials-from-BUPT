#include <stdio.h>
#include <stdlib.h>

struct Student
{
    char studentID[10];
    char name[20];
    // int age; // ���������
    char age[3];
} students[5];

// ������1���Ӽ�������ѧ����Ϣ
void input_five()
{
    printf("Please enter the information of 5 students:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("ID of student%d: ", i + 1);
        scanf("%s", students[i].studentID);
        printf("NAME of student%d: ", i + 1);
        scanf("%s", students[i].name);
        printf("AGE of student%d: ", i + 1);
        scanf("%d", &students[i].age);
    }
    printf("DONE!\n\n");
}

// ������2����ѧ����Ϣ���浽input.dat�ļ���
void data_sav()
{
    FILE *file;
    file = fopen("input.dat", "wb");
    if (file != NULL)
    {
        fwrite(students, sizeof(struct Student), 5, file);
        fclose(file);
        printf("DONE!\n\n");
    }
    else
    {
        printf("cannot open file input.dat\n");
        exit(EXIT_FAILURE);
    }
}

// ������3����input.dat�ļ��ж�ȡѧ����Ϣ������˳�������output.dat�ļ���
void reverse()
{
    FILE *fpin, *fpout;
    fpin = fopen("input.dat", "rb");
    fpout = fopen("output.dat", "wb");
    if (fpin != NULL && fpout != NULL)
    {
        fseek(fpin, 0L, SEEK_END); // ���ļ�ָ���ƶ����ļ�ĩβ
        long size = ftell(fpin);   // ��ȡ�ļ���С
        rewind(fpin);              // ���ļ�ָ�����õ��ļ���ͷ

        int numStudents = size / sizeof(struct Student); // ����ѧ����Ϣ������
        struct Student *students = (struct Student *)malloc(sizeof(struct Student) * numStudents);
        if (students == NULL)
        {
            printf("�ڴ����ʧ��\n");
            return;
        }

        fread(students, sizeof(struct Student), numStudents, fpin); // ��ȡѧ����Ϣ���ڴ���
        for (int i = numStudents - 1; i >= 0; i--)
        {
            fwrite(&students[i], sizeof(struct Student), 1, fpout); // ����˳��д�뵽output.dat�ļ���
        }

        free(students);
        fclose(fpin);
        fclose(fpout);
        printf("DONE!\n\n");
    }
    else
    {
        printf("cannot open file input.dat or output.dat\n");
        exit(EXIT_FAILURE);
    }
}
int main()
{
    int choice;
    while (1)
    {
        printf("Please select your operation:\n");
        printf("1. Enter student information from the keyboard.\n");
        printf("2. Save the data to the input.dat file.\n");
        printf("3. Read information from input.dat file into a structure array, reverse the order and output it to output.dat file.\n");
        printf("4. Exit.\n");
        printf("Enter:");
        scanf("%d", &choice);

        if (choice == 1)
            input_five();
        else if (choice == 2)
            data_sav();
        else if (choice == 3)
            reverse();
        else
            break;
    }
    return 0;
}
