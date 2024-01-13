#include <stdio.h>
#include <stdlib.h>

struct Student
{
    char studentID[10];
    char name[20];
    // int age; // 会出现乱码
    char age[3];
} students[5];

// 功能项1：从键盘输入学生信息
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

// 功能项2：将学生信息保存到input.dat文件中
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

// 功能项3：从input.dat文件中读取学生信息并反向顺序输出到output.dat文件中
void reverse()
{
    FILE *fpin, *fpout;
    fpin = fopen("input.dat", "rb");
    fpout = fopen("output.dat", "wb");
    if (fpin != NULL && fpout != NULL)
    {
        fseek(fpin, 0L, SEEK_END); // 将文件指针移动到文件末尾
        long size = ftell(fpin);   // 获取文件大小
        rewind(fpin);              // 将文件指针重置到文件开头

        int numStudents = size / sizeof(struct Student); // 计算学生信息的数量
        struct Student *students = (struct Student *)malloc(sizeof(struct Student) * numStudents);
        if (students == NULL)
        {
            printf("内存分配失败\n");
            return;
        }

        fread(students, sizeof(struct Student), numStudents, fpin); // 读取学生信息到内存中
        for (int i = numStudents - 1; i >= 0; i--)
        {
            fwrite(&students[i], sizeof(struct Student), 1, fpout); // 反向顺序写入到output.dat文件中
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
