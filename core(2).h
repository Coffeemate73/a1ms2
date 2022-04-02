#ifndef CORE_H_
#define CORE_H_

// -----------------------------------------
// Function Prototypes

// Clear the standard input buffer

void clearInputBuffer(void);

// Wait for the user to input the "enter" key to continue

void suspend(void);

// Get a valid integer from keyboard

int inputInt(void);

// Get a valid integer from keyboard and validate if greater than 0

int inputIntPositive(void);

// Get a valid integer from keyboard and validate if within a range of values

int inputIntRange(int lower_limit, int upper_limit);

// Get a single character from keyboard and validate if it matches any character in a given string

char inputCharOption(const char *valid_characters);

// Get a C string from keyboard and validate if its length is within a given range

void inputCString(char *inputString, int minLen, int maxLen);

// Display an array of 10 character digits as a formatted phone number

void displayFormattedPhone(const char *phone_number);

#endif /* CORE_H_ */
