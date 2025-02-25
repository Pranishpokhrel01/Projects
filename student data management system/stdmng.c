#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 2000
#define MAX_NAME_LENGTH 100
#define MAX_FACULTY_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    char faculty[MAX_FACULTY_LENGTH];
    int roll_no;
    float marks[5]; // marks for 5 subjects
    float total_marks;
    float percentage;
    float gpa;
    char grade[3]; // to store grade
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void calculate_grade(Student *student) {
    student->total_marks = 0;
    for (int i = 0; i < 5; i++) {
        student->total_marks += student->marks[i];
    }
    student->percentage = student->total_marks / 5;

    // Calculate GPA and Grade
    for (int i = 0; i < 5; i++) {
        if (student->marks[i] >= 90) {
            student->gpa += 4.0;
            strcpy(student->grade, "A+");
        } else if (student->marks[i] >= 80) {
            student->gpa += 3.6;
            strcpy(student->grade, "A");
        } else if (student->marks[i] >= 70) {
            student->gpa += 3.2;
            strcpy(student->grade, "B+");
        } else if (student->marks[i] >= 60) {
            student->gpa += 2.8;
            strcpy(student->grade, "B");
        } else if (student->marks[i] >= 50) {
            student->gpa += 2.4;
            strcpy(student->grade, "C");
        } else if (student->marks[i] >= 40) {
            student->gpa += 2.0;
            strcpy(student->grade, "D");
        } else {
            student->gpa += 0.0;
            strcpy(student->grade, "NG");
        }
    }
    student->gpa /= 5; // Average GPA
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students.\n");
        return;
    }
    Student *student = &students[student_count];
    printf("Enter name: ");
    scanf("%s", student->name);
    printf("Enter faculty: ");
    scanf("%s", student->faculty);
    printf("Enter roll number: ");
    scanf("%d", &student->roll_no);
    printf("Enter marks for Mathematics, Physics, Workshop, Electrical and Electronics, Drawing, Computer Programming:\n");
    for (int i = 0; i < 5; i++) {
        scanf("%f", &student->marks[i]);
    }
    calculate_grade(student);
    student_count++;
    printf("Student added successfully.\n");
}

void view_students() {
    for (int i = 0; i < student_count; i++) {
        Student *student = &students[i];
        printf("Name: %s, Faculty: %s, Roll No: %d, Total Marks: %.2f, Percentage: %.2f, GPA: %.2f, Grade: %s\n",
               student->name, student->faculty, student->roll_no, student->total_marks, student->percentage, student->gpa, student->grade);
    }
}

void save_to_file() {
    FILE *file;
    file= fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    for (int i = 0; i < student_count; i++) {
        Student *student = &students[i];
        fprintf(file, "Name: %s, Faculty: %s, Roll No: %d, Total Marks: %.2f, Percentage: %.2f, GPA: %.2f, Grade: %s\n",
                student->name, student->faculty, student->roll_no, student->total_marks, student->percentage, student->gpa, student->grade);
    }
    fclose(file);
    printf("Data saved to students.txt\n");
}

int main() {
    int choice;
    do {
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Save to File\n");
        printf("4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                view_students();
                break;
            case 3:
                save_to_file();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}