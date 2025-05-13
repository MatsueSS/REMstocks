#include <cstdlib>

//launch_script_without output
bool launch_script_WO()
{
    int out = system("bash -c 'python3 ../py_scripts/example.py'");

    if(WIFEXITED(out))
        return WEXITSTATUS(out) == 0;

    return 0;
}