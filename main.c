#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include<time.h> 

struct movie {//set up the blank struct to contain the data
  char *title;
  int year;
  char *languages;
  float rating;

  struct movie *next;
};

struct movie *createList(char *currLine) {
  struct movie *currmovie = malloc(sizeof(struct movie));
  char *saveptr;

  char *temp = strtok_r(currLine, ",", &saveptr); //title of the movie save data into saveptr 
  currmovie->title = calloc(strlen(temp) + 1, sizeof(char));
  strcpy(currmovie->title, temp);

  temp = strtok_r(NULL, ",", &saveptr); // year
  currmovie->year = atoi(temp); //character to int

  temp = strtok_r(NULL, ",", &saveptr); //lang
  currmovie->languages = calloc(strlen(temp) + 1, sizeof(char));
  strcpy(currmovie->languages, temp);

  temp = strtok_r(NULL, ",\n", &saveptr); // rating
  currmovie->rating = atof(temp);

  currmovie->next = NULL;
  return currmovie;
}

struct movie *processFile (char *file) { //link file

  char *temp;
  temp = malloc(100 * sizeof(char));
  strcpy(temp, file);
  FILE *data = fopen(temp,"r"); //data
  if (data == NULL) printf("OPEN FILE Failed\n");
  char line[100];

  struct movie *head = NULL; //create head for the link
  struct movie *tail = NULL; //tail

  if(data != NULL) { //check the data is real
    fgets(line, sizeof line, data); //skip the first line
    while(fgets(line, sizeof line, data) != NULL) { //loop until the file hits the blank
      struct movie *node = createList(line);

      if(head == NULL) { 
        head = node;
        tail = node;
      } else {
        tail->next = node;
        tail = node;
      }
    }
  }

  fclose(data); //cloase the file
  free(temp);

  return head;
}


void select_opt() {
  printf("\n1. Select file to process");
  printf("\n2. Exit the program");
  printf("\n\nEnter a choice from 1 to 2: ");
}

void file_process() {
  printf("\nWhich file you want to process?");
  printf("\nEnter 1 to pick the largest file");
  printf("\nEnter 2 to pick the smallest file");
  printf("\nEnter 3 to specify the name of a file");
  printf("\n\nEnter a choice from 1 to 3: ");
}

int enter() {
  int input;
  scanf("%d", &input);
  return input;
}

void comp(char dirc[], struct movie *mv) {
  struct movie *temp = mv;
  int check = 0;
  FILE *file = NULL;

  if(mv->next != NULL) { //check the struct is the last one
    char dir_n[100];
    sprintf(dir_n, "%s/%d.txt", dirc, temp->year);
    file = fopen(dir_n, "w");

    while(mv != NULL) { //compare until the struct is over
      if(temp->year == mv->year) { //if year is same
        check = 1;
        fprintf(file,"%s\n", mv->title);
      }
      mv = mv->next;
    } 
  }
  fclose(file);
}

void create_movie_list(char f_name[], char f_csv[]) {

  struct movie *mv = processFile(f_csv);
  
  int year[100], i = 0, k = 0;
  comp(f_name, mv);
  year[i] = mv->year; //save the first year into the array
  i++;


  while(mv != NULL) {
    for(int j = 0; j < i; j++) {
      if(mv->year == year[j]) { //check if there is any same year
        k = 1;
      }
    }

    if(k == 1) { //if the computer find the same year then move to the next
      mv = mv->next;
    } else { //if not then save year to the value
      comp(f_name, mv); // run to find the high rate
      year[i] = mv->year;
      i++;
      mv = mv->next;
    }
    k = 0; //reset the status
  }
  printf("\n");
}

void largest() {
  DIR* curr_Dir = opendir(".");
  struct dirent *aDir;
  struct stat fileS;

  unsigned int size = 0;
  char *name;

  char file_name[20];
  char myname[20] = "ohjaeg.movies.";
  srand(time(0));
  int num = rand() % 99999;
  sprintf(file_name, "%s%d", myname, num);

  // Go through all the entries
  while((aDir = readdir(curr_Dir)) != NULL){
    if(aDir) {
      char tmp[strlen(aDir->d_name)];
      for(int i = 0; i < 6; i++) {
        tmp[i] = aDir->d_name[i];
      }
      if (strcmp("movie_", tmp) == 0) { //if the first 6 letters are "movie_"
        for(int i = 0; i < 6; i++) { tmp[i] = '\0';} //reset tmp

        int k = 0;
        for(int i = strlen(aDir->d_name) - 1; i > strlen(aDir->d_name) - 5; i--) {
          tmp[k] = aDir->d_name[i];
          k++;
        }

        if (strcmp("vsc.", tmp) == 0) {  //check it it is the .csv file
          if (!stat(aDir->d_name, &fileS)) {
            if((unsigned int)fileS.st_size > size) {
              name = aDir->d_name;
            }
          }
        }
      } 
    }
  }
  // Close the directory
  closedir(curr_Dir);
  printf("Now processing the chosen file named %s\n", name);
  int make = mkdir(file_name, 0750); //create a directory
  printf("Created directory with name %s\n", file_name);
  create_movie_list(file_name, name);
  printf("\n");
}

void smallest() {
  DIR* curr_Dir = opendir(".");
  struct dirent *aDir;
  struct stat fileS;

  unsigned int size = 999999999;
  char *name;

  char file_name[20];
  char myname[20] = "ohjaeg.movies.";
  srand(time(0));
  int num = rand() % 99999;
  sprintf(file_name, "%s%d", myname, num);

  // Go through all the entries
  while((aDir = readdir(curr_Dir)) != NULL){
    if(aDir) {
      char tmp[strlen(aDir->d_name)];
      for(int i = 0; i < 6; i++) {
        tmp[i] = aDir->d_name[i];
      }
      if (strcmp("movie_", tmp) == 0) { //if the first 6 letters are "movie_"
        for(int i = 0; i < 6; i++) { tmp[i] = '\0';} //reset tmp

        int k = 0;
        for(int i = strlen(aDir->d_name) - 1; i > strlen(aDir->d_name) - 5; i--) {
          tmp[k] = aDir->d_name[i];
          k++;
        }

        if (strcmp("vsc.", tmp) == 0) {  //check it it is the .csv file
          if (!stat(aDir->d_name, &fileS)) {
            if((unsigned int)fileS.st_size < size) {
              name = aDir->d_name;
            }
          }
        }
      } 
    }
  }
  // Close the directory
  closedir(curr_Dir);
  printf("Now processing the chosen file named %s\n", name);
  int make = mkdir(file_name, 0750); //create a directory
  printf("Created directory with name %s\n", file_name);
  printf("\n");
}

void find_name() {
  DIR* curr_Dir = opendir(".");
  struct dirent *aDir;
  struct stat fileS;
  char input[1000];
  bool bol = false;

  char file_name[20];
  char myname[20] = "ohjaeg.movies.";
  srand(time(0));
  int num = rand() % 99999;
  sprintf(file_name, "%s%d", myname, num);

  printf("Enter the complete file name: ");
  scanf("%s", input); 

  while((aDir = readdir(curr_Dir)) != NULL){
    if(aDir) {
      if (strcmp(aDir->d_name, input) == 0) {
        bol = true;
      }
    }
  }

  if(bol) {
    closedir(curr_Dir);
    printf("Now processing the chosen file named %s\n", input);
    int make = mkdir(file_name, 0777); //create a directory
    printf("Created directory with name %s\n", file_name);
    printf("\n");
  } else {
    printf("The file %s was not found. Try again\n", input);
    closedir(curr_Dir);
    printf("\n");

    int inp2;
      file_process();
      inp2 = enter();
      if(inp2 == 1) {
        largest();
      } else if(inp2 == 2) {
        smallest();
      } else if(inp2 == 3) {
        find_name();
      }
  }
}

void start_porg() {
  int input = 0;

  while(input != 2) {
    select_opt();
    input = enter();

    if(input == 1) {
      int inp2;
      file_process();
      inp2 = enter();
      if(inp2 == 1) {
        largest();
      } else if(inp2 == 2) {
        smallest();
      } else if(inp2 == 3) {
        find_name();
      }
    }
  }
}

int main(void) {
  start_porg();

  return 0;
}
