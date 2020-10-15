#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

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

void largest() {
  DIR* curr_Dir = opendir(".");
  struct dirent *aDir;
  struct stat fileS;

  unsigned int size = 0;
  char *name;

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
  int make = mkdir("ohjaeg.movies.random#", 0777); //create a directory
  printf("Created directory with name chaudhrn.movies.89383\n");
  printf("\n");
}

void smallest() {
  DIR* curr_Dir = opendir(".");
  struct dirent *aDir;
  struct stat fileS;

  unsigned int size = 999999999;
  char *name;

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
  int make = mkdir("ohjaeg.movies.random#", 0777); //create a directory
  printf("Created directory with name chaudhrn.movies.89383\n");
  printf("\n");
}

int enter() {
  int input;
  scanf("%d", &input);
  return input;
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

      }
    }
  }
}

int main(void) {
  start_porg();

  return 0;
}
