# String Processing, Structures, and File Handling

## Task
Develop a program in C or C++ that processes information about domestic bus routes:
- Start stop
- End stop
- Day of the week
- Time
- Ticket price

The information about the routes is stored in a text file `db.csv`. Assume that the `db.csv` file is located in the current directory (the directory where the program is located; to access the file, specify only the file name without the directory name). The character encoding used is ANSI.

The data elements in the file are separated by commas, and the routes are separated by newline characters. Real numbers in the file are written with two decimal places, the time is in the format `hh:mm`, and the days of the week are denoted by two letters (Pr, Ot, Tr, Ce, Pt, St, Sv).

Note that the `db.csv` file may contain empty lines and unnecessary space characters (before and after the field values of the structure), as well as incorrect information. Thus, it is necessary to ensure the verification of the entered information, ignoring unnecessary spaces and empty lines. If any line contains incorrect information (missing structure field, too many fields, or incorrect data type), then the corresponding line should be ignored, and the data from the next lines should be attempted to be entered. The incorrect lines should be recorded in a text file named `err.txt`. The `err.txt` file should be placed in the same directory as the program.

For example, the `db.csv` file may look like this:
Ventsplis,8.00,Liepaja,Sv,20:00
Dagda,Sv
Dagda,Kraslava,Ce,18:00,2.50,Sv

The program should process the queries "a", "b", "c", and "d". Until the user enters the letter "e", the program should continually prompt for commands and execute the following actions:

| Query | Action |
|-------|--------|
| a     | Display all routes for the specified route (the user enters the names of the start and end stops) |
| b     | Display all routes for the specified day of the week (the user enters the day abbreviation: Pr, Ot, Tr, Ce, Pt, St, Sv) |
| c     | Display all routes whose ticket price does not exceed the entered amount |
| d     | Display the contents of the `err.txt` file |
| e     | Terminate the program execution |

When processing queries "a", "b", "c", and "d", before displaying the list of routes or the contents of the `err.txt` file, the message "result:" must be displayed. Display information about each route on a separate line, separating data elements with a single space.

For example:

**Input:**
a
Riga
Kraslava
d
e

**Output:**
result:
Riga Kraslava Pr 15:00 11.00
Riga Kraslava Pr 18:00 11.00
result:
Ventsplis,8.00,Liepaja,Sv,20:00
Dagda,Sv
Dagda,Kraslava,Ce,18:00,2.50,Sv

**Input:**
b
Pt
e

**Output:**
result:
Riga Ventspils Pt 09:00 6.70
Liepaja Ventspils Pt 17:00 5.50

**Input:**
c
5.90
e

**Output:**
result:
Kraslava Daugavpils Ot 10:00 3.00
Dagda Kraslava Ce 18:00 2.50
Liepaja Ventspils Pt 17:00 5.50