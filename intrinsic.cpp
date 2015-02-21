/**************************************************************
 * 			Diagnostic Shell
 *
 * file:	dash.cpp
 * author:	Hafiza Farzami
 * date:	February 06, 2015
 * class:	Operating Systems
 * professor:	Dr. Karlsson
 *
 * description:	
 * 		this is a simple program that introduces UNIX
 * 		environment
 *
 * compile:	g++ -o dash dash.cpp
 * run:		./dash
 * note:	I have used the /comm file instead of /cmdline
 * 		file, because some of the /cmdline files are
 * 		empty 
 *
 *************************************************************/

/* libraries */
#include "header.h"

 /**************************************************************
 * name: 	StringFromPid
 * author:	H. Farzami
 *
 * purpose:	given a process ID (pid), this function prints
 * 		out the name of the process 
 */
void StringFromPid(string input)
{
	string line = "";
	ifstream commandString(("/proc/" + input + "/comm").c_str());

	if(!commandString)
		cout << "Could not open the file. Invalid pid." << endl;
	
	else
	{
		while(getline(commandString, line))
			cout << line << endl;
	}

	cout << endl;
	commandString.close();
} /* StringFromPid */

/**************************************************************
 * name:	Systat
 * author:	H. Farzami
 *
 * purpose:	Systat function displays some information about
 * 		the system 
 */
void Systat()
{
	string filenames[4] = {"version", "uptime", "meminfo", "cpuinfo"};
	
	for(int i = 0; i < 4; i++)
	{
		cout << endl << filenames[i] << ":" << endl << endl;
		string line;
		ifstream info(("/proc/" + filenames[i]).c_str());

		if( i != 3)
		{
			while(getline(info, line))
				cout << line << endl;
		}
		
		/* cpu info part */
		else
		{
			bool print = true;

			while(getline(info, line))
			{
				string subString = line.substr(0, 6);

				if(subString == "vendor")
					print = false;
			
				if(subString == "cache ")
				{
					cout << line << endl;
					cout << endl;
					print = true;
				}

				if(!print)
					cout << line << endl;
			}
		}

		cout << endl;
		info.close();
	}
} /* Systat */

/**************************************************************
 * name:	Usage
 * author:	H. Farzami
 *
 * purpose:	display the usage of the program	
 */
void Usage()
{
	cout << endl << "Usage - you can do the following:" << endl << endl;
	cout << "1. cmdnm <pid> - \t\t to get command string from pid" << endl;
	cout << "2. pid <command string> - \t to get pid from command string" << endl;
	cout << "3. systat - \t\t\t to get stats on the system" << endl;
	cout << "4. exit - \t\t\t to leave the program" << endl << endl;
} /* Usage */

/**************************************************************
 * name:	GetParam
 * author:	H. Farzami
 *
 * purpose:	this function takes in the user input and sepa-
 * 		rates the command from the input and returns
 * 		the user input
 *
 * return:	temp - the parameter part of the user input	
 */
string GetParam(string input)
{
	int pos = 0;
	string temp = input;

	pos = temp.find(" ");
	temp.erase(0, pos + 1);

	return temp;	
} /* GetParam */

/**************************************************************
 * name: 	PidFromString
 *	
 * purpose:	given a name, this function lists the pid's 
 * 		associated with that name	
 *
 * Note: 	adapted from 
 * 		http://www.cplusplus.com/forum/beginner/9173/
 */
void PidFromString(string input)
{
	DIR *directories;
	struct dirent *entry;
	string line;

	if(directories = opendir("/proc"))
	{
		while(entry = readdir(directories))
		{
			ifstream commandString(("/proc/" + (string)entry->d_name + "/comm").c_str());
			getline(commandString, line);		

			if(entry->d_name != "." && entry->d_name != ".." && (!line.find(input)))
				cout << entry->d_name << endl;

			commandString.close();
		}

		closedir(directories);
	}
}

void print_cpu_time()
{
  	struct rusage usage;
  	getrusage (RUSAGE_SELF, &usage);
  	printf ("CPU time: %ld.%06ld sec user, %ld.%06ld sec system\n",
	  	usage.ru_utime.tv_sec, usage.ru_utime.tv_usec,
	  	usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
}
