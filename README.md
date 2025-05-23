# Disassembling the Windows Application License Key

<p align="center">
  <img src="https://github.com/user-attachments/assets/db10c382-01a6-41bb-8a80-89dec288e2b0" alt="Wydział Elektroniki i Informatyki - Politechnika Rzeszowska">
</p>

## Project Objective

The aim of the above mentioned project topic was to create a simple window application for any Microsoft Windows system. The general idea was to create a simple application, which after compilation is a simple window asking the user to enter a license key, the user presses the button to send the key and it is verified.

The main part of the task, however, concerns the creation of a crack, which goes through the compiled verify_key.dll file and allows to make changes in it, which means that we can plant a new key, which will be accepted by the application.

## Appearance of the application window

<p align="center">
    <img src="https://github.com/user-attachments/assets/cf02ad10-522c-48eb-a2ab-4ae6d686a4bd" alt="Okienko Aplikacji">
</p>

## License key acceptance message

<p align="center">
    <img src="https://github.com/user-attachments/assets/37d2f04b-2f07-4613-9b25-0892914faa61" alt="Klucz weryfikacyjny poprawny">
</p>

## Necessary things for the application to work

The first thing that is needed for the application to work correctly is to download the **MinGW - Minimalist GNU for Windows** graphics library available at:

https://sourceforge.net/projects/mingw/

In the case of the MinGW library. You need to install it and select all possible options that will be displayed in the installation window. Then click "Apply Changes" and wait until the installation process is complete. Then we need to edit the environment variables and add the path: **C:\MinGW\bin**

Then, to check if the library is already on your computer, open **cmd** and enter the following command:

```gcc --version```

<div style="text-align: center;">
    <img src="https://github.com/user-attachments/assets/b5a2db0f-9a32-42d3-95d5-180a84ce2912" alt="MinGW">
</div>

This message means that the path has been successfully added to the environment variables and the application will now be able to build.

Another important thing is the environment for writing code. Although I am a big fan of Visual Studio Code, in this case I had to use **Visual Studio 2022**. I recommend downloading it from:

https://visualstudio.microsoft.com/pl/

## Programming tools used in the project

- C++ programming language
- Makefile for compilation automation

## Commands to build the application

First, go to the project directory and run the command:

```mingw32-make```

This will start the process of building the windowed application via a configuration Makefile, which automates the building of the application without having to build this part of the application manually folder by folder.

Then, after executing this command, two files app.exe and verify_key.dll appear in the project's main directory.

app.exe is the main file of the entire application and it is the window in the pictures above shown in the chapter [click here](#appearance-of-the-application-window). And the verify_key.dll file is the file containing the Assembler code that stores the verification key.

The last thing to do is to type the command:

```gcc -o Crack.exe Crack\crack.app```

This will generate the Crack.exe file, which when double-clicked and run will replace the license key with another one that we want to assign ourselves and cause the application to work.

## Summary

This project was created as part of a course for a college degree program specializing in Cybersecurity and is intended to show how easy it is to cheat and gain unauthorized access to various applications. The project is also a low-level programming activity. However, when creating similar things ourselves, we should remember that cracking license keys for applications, whether web or desktop, is completely illegal and punishable. Let's remember that there is a lack of respect for the creators and companies that create better and newer software, and the work put into it should make us respect the actions of the Developers and not commit such frauds, and buy legal applications in stores.
