#include <iostream>
#include <string>
using namespace std;

int main()
{
    string aString = "";
    while (getline(cin, aString))
    {
        char *cstr = new char[aString.length() + 1];
        strcpy(cstr, aString.c_str());

        int tempTime = 0;
        int tempLen = 0;

        char *pch;
        pch = strtok(cstr, ", ");
        for (int i = 0; pch != nullptr; i++)
        {
            if (i == 0)
                tempTime = atoi(pch);
            else if (i == 1)
                tempLen = atoi(pch);

            pch = strtok(nullptr, ", ");
        }

        //cout << tempTime << tempLen << endl;
    }

    return 0;
}