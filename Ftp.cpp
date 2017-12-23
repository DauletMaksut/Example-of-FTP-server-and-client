
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string>
#include <string.h>
#include<cstring>
using namespace std;
//This function asks for input from user reagarding ftp site name, Username, Password, and file to be downloaded
//Then writes it into a file called commands.bin
//The file commands.bin is given as input to the ftp cli so that each line in the file acts as one command and it will bw executed
//Once all commands are executed and all files are downloaded from ftp server the file commands.bin is deleted
int main()
{
	char FtpSite[100],Pass[100],UserName[100],File_Download[100],c;
	string Password;
	cout << "Enter ftp site :";
	cin >> FtpSite;
	cout << "Enter username :";
	cin >> UserName;
	cout << "Enter password :";
	cin >> Password;
	strcpy(Pass, Password.c_str()); //copying string to charactor array
	cout << "Enter filename to be downloaded :";
	cin >> File_Download;
	FILE * fp = fopen("commands.bin","wb+"); //opening a binary file commands.bin in write and read mode 
	fprintf(fp, "open %s\n", FtpSite); //writing ftp site name to commands.bin
	fprintf(fp, "%s\n", UserName); //writinlg username to commands.bin
	fprintf(fp, "%s\n", Pass); //writing password to commands.bin
	fprintf(fp, "get %s\n", File_Download); //writing name of file to be downloaded to commands.bin
	fprintf(fp, "bye\n");
	rewind(fp); //Taking file pointer to the beginning of the file so that file pointer is at the start
	cout << "Contacting FTP site.....\n" << endl;
	system("ftp -s:commands.bin > logfile.txt"); //executing ftp request command and reading commands from commands.bin and writing output to logfile.txt
	fclose(fp); //closing file
	FILE * dump = fopen("logfile.txt","r"); //opening logfile in read mode
	cout << "------------------------------" << endl;
	cout << "Data from the logfile.txt" << endl;
	cout << "------------------------------" << endl;
	while ((c = getc(dump)) != EOF)
	{
		putchar(c);
	}

	cout << "------------------------------\n" << endl;
	system("del commands.bin"); //deletes commands.bin
	