#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
    int exitCode = system(argv[1]);

    cout<<"Program exited with the code :"<<exitCode<<endl;
    system("pause");

    return exitCode;
}

