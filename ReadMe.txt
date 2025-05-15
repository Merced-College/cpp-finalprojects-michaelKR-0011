CODEX Terminal - File Decryption System
=======================================
//////////////////////////////////MICHAEL_SANTOS-5-14-2025---1:46AM

Overview:
---------
CODEX is a government-style terminal simulation designed to decrypt encrypted files with secure authentication.
Users select a file, enter a password if required, and view the decrypted contents directly within the terminal.

How It Works:
-------------
1. Launch the program.
2. The system prompts: "WELCOME - PRESS ENTER" to begin.
3. Available files are displayed:
   - File1 - Standard file (no authentication required).
   - File2, File3, File4 -  Restricted (authentication required).
4. Select a file by typing its name (e.x., file1).
5. If the file is restricted, enter the authentication code when prompted.
6. If access is granted, the program decrypts and displays the file contents.
7. Press ENTER to return to the main menu or type 'exit' to quit.

Features:
---------
 Terminal-style UI for an immersive experience.
 File authentication system for restricted documents.
 Decryption functionality ensures access to encrypted content.
 User-friendly prompts guide interaction without unnecessary complexity.

System Requirements:
--------------------
- Operating System: Windows (Recommended)
- Compiler: g++ / MinGW (for C++ compilation)
- Dependencies: Crypto.h (custom encryption/decryption module)

Installation:
-------------
1. Download the source code files.
2. Ensure Crypto.h is included in the directory.
3. Compile using:
   g++ -o codex_program main.cpp Crypto.cpp
4. Run the program:
   ./codex_program

Notes:
------
- Authentication codes for restricted files are required for access.
- This program does NOT perform encryption—only decryption.
- Ensure encrypted files follow the correct format for proper decryption.
-----PROGAM WORK PERFECTLY MY ONLY FLAW IS THE STORY IT NON EXISTANT AND ALL OVER THE PLACE 
-----I WAS ABLE TO SEED PASS KEY HINTS SO ITS STILL PLAYABLE 
- all txt files holding relivent data to password are encrypted to prevent cheating
