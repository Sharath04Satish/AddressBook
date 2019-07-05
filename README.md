# AddressBook
The following project demonstrates the concept of File Structures in C++.

## Description
File Structures is the Organization of Data in Secondary Storage Device in such a way that minimize the access time and the storage space.
It is a combination of representations for data in files and of operations for accessing the data and allows applications to read, write and modify data.

The various operations that can be performed on a file are:
- Open
- Read
- Write
- Append
- Truncate
- Close

## Objective
The primary outcome of this software is to present an efficient search based Address book for the end users such that they can communicate with other people who live in the same city to improve their social circles.

## Data
The following program works with the inputs provided by the users for various attributes such as First Name, Last Name, ID, Phone number, Office phone number, Area, Occupation and Email-ID. These fields are stored as variable length records that the file can operate upon.
The records are represented as a class object, with the corresponding class variables.

## Operations
The program allows the users to
- add their data to the address book.
- modify their data.
- delete their data.
- modify their data.
- display the data of all the registered users.
- search other users.

The program constructs a hash table, to navigate to the records stored in the file at a time complexity of O(1), as compared to sequential search using index which corresponds to a time complexity of O(n), where n is the number of users.

