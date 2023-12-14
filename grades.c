/*
    creating a menu with following options for student records:
    1.add
    2.delete
    3.modify
    4.retrieve
    create a file where the options can be performed.
*/

#include <stdio.h>
#include <string.h>
#define p(x, ...) printf(x "\n", ##__VA_ARGS__)
#define max 30
#define or ||
#define and &&
// just wanted to know how its done so made my own
int len(char str[])
{
    int count = 0;
    for (int i = 0; str[i] != 0; i++) // we can use '\0' as well :)
    {
        count++;
    }
    return count;
}
//made my own instead of using strcmp cause i wanna learn
int strcompare(char str1[], char str2[])
{
    for (int i = 0; i < len(str1) and i < len(str2); i++)
    {
        if (str1[i] == str2[i])
        {
            continue;
        }
        else
        {
            return 1;
        }
    }
    return 0;
}
void validater(FILE *point, char *line, int choice)
{
    char name[max];
    char grade;
    sscanf(line, "%s\t\t%c\n", name, &grade);
    while (1)
    {
        if (choice & 0b01)
        {
            p("Enter the name of the student: full_name");
            fgets(name, max, stdin);
            name[strcspn(name, "\n")] = '\0';
        }
        if (choice & 0b10)
        {
            p("Enter the grade of the student: A/a");
            scanf("%c", &grade);
        }

        if (grade >= 'a' and grade <= 'e')
        {
            grade = grade - ' ';
            fprintf(point, "%s\t\t%c\n", name, grade);
            break;
        }
        else if (grade >= 'A' and grade <= 'E')
        {
            fprintf(point, "%s\t\t%c\n", name, grade);
            break;
        }
        else
        {
            p("current grade is %c", grade);
            p("Please read the NOTE!!!");
        }
    }
    p("Student grade and name successfully added!");
}

void add_to_file()
{
    char line[max];
    FILE *point = fopen("grades.txt", "a");
    if (!point)
    {
        p("Failed to open the file.");
        return;
    }
    p("NOTE: Grade ranges from A to E");
    validater(point, line, 3);
    fclose(point);
}

void delete_from_file()
{
    FILE *before = fopen("grades.txt", "r");
    FILE *after = fopen("temp.txt", "w");
    char ch[max];
    char name[max];
    int u_line, line = 1;
    char dummy;
    if (!before or !after)
    {
        p("Failed to open the file.");
        return;
    }

    p("Enter the name of student you want to delete from file: ");
    fgets(ch, max, before);
    fprintf(after, "%s", ch);
    scanf("%s%c", name, &dummy);

    while (!feof(before))
    {
        fgets(ch, max, before);
        if (strcompare(name, ch) != 0)
        {
            fprintf(after, "%s", ch);
            ch[0] = 0;
        }
    }
    /* using line number to delete from file

    p("Enter the line no you want to delete: ");
    fgets(ch, max, before);
    fprintf(after, "%s", ch);
    scanf("%d%c", &u_line, &dummy);
    while (!feof(before))
    {
        fgets(ch, max, before);
        if (line != u_line)
        {
            fprintf(after, "%s", ch);
            ch[0] = 0; // 0 (NULL terminater) which termintes the string, we utilized to make the remaining character like it's not there.
        }
        line++;
    }*/
    fclose(before);
    fclose(after);
    remove("grades.txt");
    rename("temp.txt", "grades.txt");
}

void modify_file()
{
    char dummy;
    char name[max];
    char grade;
    int choice;
    FILE *before_mdf = fopen("grades.txt", "r");
    FILE *after_mdf = fopen("temp.txt", "w");

    char ch[max];
    int u_line, line = 1;

    if (!before_mdf or !after_mdf)
    {
        p("Failed to open the file.");
        return;
    }
    p("Enter the line no you want to modify: ");
    fgets(ch, max, before_mdf);
    fprintf(after_mdf, "%s", ch);
    scanf("%d%c", &u_line, &dummy);

    while (!feof(before_mdf))
    {
        fgets(ch, max, before_mdf);
        if (line == u_line)
        {
            p("What do you want to change:\
             1) Name\
             2) Grade\
             3) Both? ");
            scanf("%d%c", &choice, &dummy);
            validater(after_mdf, ch, choice);
        }
        else
        {
            fprintf(after_mdf, "%s", ch);
        }
        ch[0] = 0;

        line++;
    }
    fclose(before_mdf);
    fclose(after_mdf);
    remove("grades.txt");
    rename("temp.txt", "grades.txt");
}

void retrieve_data_by_name()
{
    FILE *point = fopen("grades.txt", "r");
    char ch[max];
    char name[max];
    int line = 1;
    int flag = 0;

    if (!point)
    {
        p("Failed to open the file.");
        return;
    }
    p("Enter the name of student you want to retrieve: ");
    scanf("%s", name);
    fgets(ch, max, point);
    p("\n%s", ch);

    while (!feof(point))
    {
        fgets(ch, max, point);
        if (strcompare(name, ch) == 0)
        {
            flag = 1;
            p("%s\n", ch);
            ch[0] = 0;
        }
        line++;
    }
    if (flag == 0)
    {
        p("No-one with name %s found!", name);
    }

    fclose(point);
}

void retrieve_data_by_grade()
{
    FILE *point = fopen("grades.txt", "r");
    char ch[max];
    char name[max];
    char ugrade, grade;
    int line = 1;
    int flag = 0;

    if (!point)
    {
        p("Failed to open the file.");
        return;
    }
    p("Enter the grade of students you want to retrieve: ");
    scanf("%c", &ugrade);
    fgets(ch, max, point);
    p("\n%s", ch);

    while (!feof(point))
    {
        fgets(ch, max, point);
        sscanf(ch, "%s\t\t%c\n", name, &grade);
        if (grade == ugrade or (grade - 'A' == ugrade - 'a'))
        {
            flag = 1;
            p("%s\n", ch);
            ch[0] = 0;
        }
        line++;
    }
    if (flag == 0)
    {
        p("No-onw with grade %c found!", ugrade);
    }
    fclose(point);
}

void retrieve_data()
{
    int choice;
    char dummy;
    while (1)
    {
        p("How do you want to retrieve the data:\n\
             \t1) Using name\
              2) Using grade");
        scanf("%d%c", &choice, &dummy);
        if (choice == 1)
        {
            retrieve_data_by_name();
            return;
        }
        else if (choice == 2)
        {
            retrieve_data_by_grade();
            return;
        }
        else
        {
            p("Please enter a valid choice!");
        }
    }
}

int main()
{
    int choice;
    char dummy;
    while (1)
    {
        p("------MENU------\
        \n1.Add to the file.\
        \n2.Delete from the file.\
        \n3.Modify the previous data.\
        \n4.Retrieve student records.\
        \n5.Exit.");
        scanf("%d%c", &choice, &dummy);

        switch (choice)
        {
        case 1:
            add_to_file();
            break;
        case 2:
            delete_from_file();
            break;
        case 3:
            modify_file();
            break;
        case 4:
            retrieve_data();
            break;
        case 5:
            return 0;
        default:
            p("Please enter a valid option!");
            break;
        }
    }
    p("Thanks for using our database!");
    return 0;
}