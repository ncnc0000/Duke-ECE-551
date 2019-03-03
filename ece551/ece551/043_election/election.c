#include "election.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

int isDigit(char * array_of_pointer[3]) {
  if (strlen(array_of_pointer[2]) == 0 || strlen(array_of_pointer[1]) == 0) {
    perror("no population and electoralvotes!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 1; i < 3; i++) {
    for (size_t j = 0; j < strlen(array_of_pointer[i]); j++) {
      if (isdigit(array_of_pointer[i][j]) == 0) {
        return 1;
      }
    }
  }
  return 0;
}
state_t pass_value(state_t s, char ** array_to_pointer) {
  //strcpy(s.name, array_to_pointer[0]);
  strcpy(s.name, array_to_pointer[0]);
  s.population = atoi(array_to_pointer[1]);
  s.electoralVotes = atoi(array_to_pointer[2]);
  if (s.population < s.electoralVotes) {
    perror("population is small than electoralvotes!\n");
    exit(EXIT_FAILURE);
  }
  return s;
}
state_t parseLine(const char * line) {
  //STEP 1: write me
  char str[100], str0[100], str1[100], str2[100];
  char * array_to_pointer[3] = {str0, str1, str2};
  char * rest_str = NULL;
  int i = 0, count = 0, flag = 0;
  char * strr = NULL;
  state_t stat_info = {{0}, 0, 0};
  strcpy(str, line);
  //copy the input string to the strr;
  //count the number of ':' in the input string, if the number is not equal to 2, EXIT;
  while (*(str + i) != '\0') {
    if (*(str + i) == ':') {
      count++;
    }
    i++;
  }
  if (count != 2) {
    perror("Invaild input string");
    exit(EXIT_FAILURE);
  }
  //if input state name equal to NULL, exit
  else if ((strchr(line, ':') - line) == 0) {
    perror("No input state name!\n");
    exit(EXIT_FAILURE);
  }
  else {
    i = 0;
    strr = str;
    //use function strtok_r to seperate the input string.
    while ((array_to_pointer[i] = strtok_r(strr, ":", &rest_str)) != NULL) {
      i++;
      strr = NULL;
    }
    //judge if the last two of string contains only number, if not, exit
    flag = isDigit(array_to_pointer);
    if (flag == 1) {
      perror("Invalid input file");
      exit(EXIT_FAILURE);
    }
    else {
      //pass the value of seperate string to the struct.
      stat_info = pass_value(stat_info, array_to_pointer);
      return stat_info;
    }
  }
}
unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int electoral_vote = 0;
  for (size_t i = 0; i < nStates; i++) {
    float num = stateData[i].population / voteCounts[i];
    if (num < 2) {
      //if num < 2, then add the electoralvotes of this state to candidate A.
      electoral_vote += stateData[i].electoralVotes;
    }
  }
  return electoral_vote;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    //compute num * 100 (transfer to percentage expression)
    float num = ((float)voteCounts[i] / (float)stateData[i].population) * 100;
    if ((num >= 49.5) && (num <= 50.5)) {
      printf(
          "%s requires a recount (Candidate A has %.2f%% of the vote.)\n", stateData[i].name, num);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  float largest = 0.00;
  int ind = 0;
  for (size_t i = 0; i < nStates; i++) {
    float num = ((float)voteCounts[i] / (float)stateData[i].population) * 100;
    if (num > largest) {
      largest = num;
      ind = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n", stateData[ind].name, largest);
}
