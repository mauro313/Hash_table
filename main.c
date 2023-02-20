#include "HashTable.h"

/**
 * @brief auxiliar struct
 * 
 */
typedef struct _studentNote{
  char* studentName;
  int calificationFirstExam;
  int calificationSecondExam;
  int calificationThirdExam;  
}StudentNote_t;

/**
 * @brief create a new student.
 * 
 * @param name 
 * @param calificationOne 
 * @param calificationTwo 
 * @param calificationThree 
 * @return StudentNote_t* 
 */
StudentNote_t* studentNote_new(char* name,int calificationOne,int calificationTwo,int calificationThree){
  StudentNote_t* newOne = (StudentNote_t*)malloc(sizeof(StudentNote_t));
  newOne->studentName = name;
  newOne->calificationFirstExam = calificationOne;
  newOne->calificationSecondExam = calificationTwo;
  newOne->calificationThirdExam = calificationThree;
}

/**
 * @brief get student´s name.
 * 
 * @param student 
 * @return char* 
 */
char* studentNote_getName(StudentNote_t* student){
  return student->studentName;  
}

/**
 * @brief get student´s first calification
 * 
 * @param student 
 * @return int 
 */
int studentNote_getCalificationOne(StudentNote_t* student){
  return student->calificationFirstExam;  
}

/**
 * @brief get student´s second calification
 * 
 * @param student 
 * @return int 
 */
int studentNote_getCalificationTwo(StudentNote_t* student){
  return student->calificationSecondExam;  
}

/**
 * @brief get student´s third calification.
 * 
 * @param student 
 * @return int 
 */
int studentNote_getCalificationThree(StudentNote_t* student){
  return student->calificationThirdExam;  
}

/**
 * @brief calculate stunts´s average.
 * 
 * @param student 
 * @return float 
 */
float studentNote_average(StudentNote_t* student){
  return (float)(student->calificationFirstExam+student->calificationSecondExam+student->calificationThirdExam)/3;  
}

/**
 * @brief free memory of a student.
 * 
 * @param student 
 */
void studentNote_free(StudentNote_t** student){
  free(*student);
  *student = NULL;  
}

/**
 * @brief print the variables of a studentNote.
 * 
 * @param student 
 */
void printStudentNote(StudentNote_t* student){
  printf("Student Name: %s\n",studentNote_getName(student));
  printf("First Exam Calification: %d\n",studentNote_getCalificationOne(student));
  printf("Second Exam Calification: %d\n",studentNote_getCalificationTwo(student));
  printf("Third Exam Calification: %d\n",studentNote_getCalificationThree(student));
  printf("The average of the student is %.2f \n",studentNote_average(student));     
}

void freeStudent(void** student);

int main(void){
  //creation of ten students
  StudentNote_t* student1 = studentNote_new("Martin Peztralek",5,7,9);
  StudentNote_t* student2 = studentNote_new("Luna Silva",4,5,10);
  StudentNote_t* student3 = studentNote_new("Carlos Pedraza",8,7,8);
  StudentNote_t* student4 = studentNote_new("Silvina Machado",9,2,6);
  StudentNote_t* student5 = studentNote_new("Lucio Dupoy",7,7,8);
  StudentNote_t* student6 = studentNote_new("Dario Sans",10,5,8);
  StudentNote_t* student7 = studentNote_new("Marina Dross",3,2,7);
  StudentNote_t* student8 = studentNote_new("Esteban Char",2,10,8);
  StudentNote_t* student9 = studentNote_new("Analia Gujarra",3,4,5);
  StudentNote_t* student10 = studentNote_new("Pedro Lucio",7,1,0);

  //creation of hashtable
  HashTable_t* hashTable = hashTable_new(10);
  hashTable_insert(hashTable,"11.544",student1);
  hashTable_insert(hashTable,"21.343",student2);
  hashTable_insert(hashTable,"10.987",student3);
  hashTable_insert(hashTable,"15.434",student4);
  hashTable_insert(hashTable,"9.004",student5);
  hashTable_insert(hashTable,"6.332",student6);
  hashTable_insert(hashTable,"72.423",student7);
  hashTable_insert(hashTable,"8.653",student8);
  hashTable_insert(hashTable,"16.453",student9);
  hashTable_insert(hashTable,"12.798",student10);  
  
  //print the students notes with the ID 16.453 and ID 15.434 
  printStudentNote(hashTable_search(hashTable,"16.453"));
  printf("\n\n");
  printStudentNote(hashTable_search(hashTable,"15.434"));
   
  //free all the used memory.
  hashTable_delete(hashTable,"11.544",freeStudent);
  hashTable_delete(hashTable,"21.343",freeStudent);
  hashTable_delete(hashTable,"10.987",freeStudent);
  hashTable_delete(hashTable,"15.434",freeStudent);
  hashTable_delete(hashTable,"9.004",freeStudent);
  hashTable_delete(hashTable,"6.332",freeStudent);
  hashTable_delete(hashTable,"72.423",freeStudent);
  hashTable_delete(hashTable,"8.653",freeStudent);
  hashTable_delete(hashTable,"16.453",freeStudent);
  hashTable_delete(hashTable,"12.798",freeStudent);
   
   
  hashTable_free(&hashTable);
  return 0;
}

/**
 * @brief free studentNote.
 * 
 * @param student 
 */
void freeStudent(void** student){
  studentNote_free((StudentNote_t**) student);  
}



