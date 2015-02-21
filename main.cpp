#include "header.h"

int main()
{
	string userInput;
        string inputs[100];
        string param;

        do
        {
                cout << "dash>";
                getline(cin, userInput);
                stringstream ss(userInput);

                int i = 0;
                while(ss)
                {
                        ss >> inputs[i];
                        i++;
                }

                param = GetParam(userInput);

                if(!userInput.find("cmdnm"))
                        StringFromPid(param);

                else if(!userInput.find("pid"))
                        PidFromString(param);

                else if(!userInput.find("systat"))
                        Systat();

                else
                {
                        char* args[i + 1];
                        for(int j = 0; j < i; j++)
                                args[i] = const_cast<char*>(inputs[i].c_str());

                        args[i] = '\0';

                        print_cpu_time();
                }

        }while(userInput != "exit");

	return 0;
}
