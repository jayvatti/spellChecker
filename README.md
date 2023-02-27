# Spell Checker Program

## Summary
This program uses a hash table with chaining to recursively search for a valid word similar to the user's input. The aim of the program is to either verify the word input by the user or provide suggestions for a similar word in case of misspelling.

## Goal
The primary objective of the Spell Checker program is to verify if the word input by the user is valid or not. If the word is valid, the program returns a confirmation message with the time taken for verification. In case the word is misspelled or incorrect, the program suggests a similar word from the hash table.

## User Instructions
To run the program, make use of the provided makefile and type the command "make run." After launching the program, the user is presented with a menu screen that lists three options:

- Option 0: Ends the program.
- Option 1: Allows the user to input a word or phrase for validation.
- Option 2: Allows the user to input a character.
If the user selects Option 1, they are prompted to input a word or phrase. The program is designed to handle spaces and uppercase/lowercase letters. Three cases may arise:

- Case One: If the user input is a valid word, the program confirms it with a message and also lists all the words in the hash table that start with the first two letters of the user input.
- Case Two: If the user input is invalid but there exists a similar word, the program suggests the correct spelling and asks if it is what the user intended. If the user confirms, the program lists all the words in the hash table that start with the same two letters as the correct spelling.
- Case Three: If the user input is invalid, and there is no similar word in the hash table, the program confirms the absence of a similar word.
If the user selects Option 2, they are prompted to input a character. The program searches the hash table and lists all the words that start with that character (if any). The program also outputs the time taken for searching.

