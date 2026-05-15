#include<stdio.h>
struct Student{
    int roll;
    char name;
    float marks;
};

void storeRecords(){
    FILE *fp;
    int n,i;
    struct Student s;
    fp = fopen("students.dat","wb");
    if(fp == NULL){
        printf("File cannot be opened");
        return;
    }

    printf("Enter number of records: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter the details of student %d\n",i+1);

        printf("Enter Roll Number: ");
        scanf("%d",&s.roll);

        printf("Enter name: ");
        scanf("%s",s.name);

        printf("Enter Marks: ");
        scanf("%f",&s.marks);

        fwrite(&s,sizeof(struct Student),1,fp);

    }
    fclose(fp);
    printf("Records stored successfully");

}

void getRecord(int m){
    FILE *fp;
    struct Student s;
    fp = fopen("students.dat","rb");
    
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    fseek(fp,(m-1) * sizeof(struct Student),SEEK_SET);

    fread(&s,sizeof(struct Student),1,fp);

    
    printf("\nDetails of Record %d\n", m);
    printf("Roll Number : %d\n", s.roll);
    printf("Name        : %s\n", s.name);
    printf("Marks       : %.2f\n", s.marks);

    fclose(fp);
}

void deleteRecord(int delRoll){
    FILE *fp, *temp;
    struct Student s;
    int found = 0;

    fp = fopen("students.dat","rb");
    temp = fopen("temo.dat","wb");

    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.roll == delRoll)
        {
            found = 1;
            continue; // Skip this record
        }

        fwrite(&s, sizeof(struct Student), 1, temp);
    }

    fclose(fp);
    fclose(temp); 


    fclose(fp);
    fclose(temp);

    
    remove("students.dat");

    
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nRecord deleted successfully.\n");
    else
        printf("\nRecord not found.\n");
}

void displayAll()
{
    FILE *fp;
    struct Student s;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    printf("\nAll Records\n");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("\nRoll Number : %d", s.roll);
        printf("\nName        : %s", s.name);
        printf("\nMarks       : %.2f\n", s.marks);
    }

    fclose(fp);
}

int main()
{
    int m, delRoll;

    storeRecords();

    displayAll();

    printf("\nEnter record number to fetch: ");
    scanf("%d", &m);

    getRecord(m);

    printf("\nEnter roll number to delete: ");
    scanf("%d", &delRoll);

    deleteRecord(delRoll);

    displayAll();

    return 0;
}