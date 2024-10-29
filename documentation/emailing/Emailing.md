# Emailing System Documentation

## Overview

This document describes the emailing system used in our application, focusing on the code responsible for generating verification codes and sending emails.
This documentation provides a comprehensive overview of the `generate_code()` and `send_email()` functions, including their purpose, usage, implementation details, and security considerations. It offers insights into how these functions work together to implement the emailing system in our application.

## Table of Contents

1. [Function Descriptions](#function-descriptions)
2. [Implementation Details](#implementation-details)
3. [Security Considerations](#security-considerations)
4. [Usage Examples](#usage-examples)

## Function Descriptions

### generate_code()

Purpose:
Generates a random 4-digit verification code for email authentication.

Parameters:
None

Return Value:
An integer representing a random 4-digit number between 1000 and 9999.

Description:
This function uses the `rand()` function to generate a pseudo-random number. It calculates the remainder of the division of this random number by 9000, then adds 1000 to ensure the result is always a 4-digit number.

Example Usage:
```
int verification_code = generate_code(); 
printf("Verification code: %d\n", verification_code);
```

### send_email()

Purpose:
Sends an email to the provided recipient with a generated verification code.

Parameters:
- `name`: A constant character pointer containing the recipient's name.
- `email`: A constant character pointer containing the recipient's email address.

Return Value:
None (void function)

Description:
This function performs the following steps:
1. Calls `generate_code()` to produce a 4-digit verification code.
2. Prints the generated code to the console for debugging purposes.
3. Constructs a command to execute a Python script called `send_email.py`.
4. Uses the `system()` function to execute the Python script with the generated code, name, and email as arguments.

Note:
The comment `// STORE THE CODE TO COMPARE WHAT THE CLIENT INPUTS` is a placeholder point for saving the code to compare with what the client user provides to the server.

## Implementation Details

1. **Random Number Generation**:
   - The `generate_code()` function relies on the `rand()` function, which needs to be seeded for better randomness. Ensure that `srand(time(NULL))` is called before using this function.

2. **Email Sending Mechanism**:
   - The email sending is delegated to a separate Python script (`send_email.py`).
   - This approach allows for separation of concerns and easier maintenance of email-related functionality.



## Usage Examples

Here's an example of how these functions might be called within a larger application:
```
#include <stdio.h> 
#include <stdlib.h>

int main() { 
    srand(time(NULL)); // Seed random number generator

    // Generate the 4 digit number
    int generated_code = generate_code();

    char* name = "Alice Smith";
    char* email = "alice@example.com";

    // Call the Python script
    char command[256];
    // Paramaters to send: Name, email, generated_code
    snprintf(command, sizeof(command), "python3 send_email.py %s %s %d", name, email, generated_code);
    system(command);
}

```