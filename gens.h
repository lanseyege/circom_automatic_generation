#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
#include <set>

using namespace std;

class CodeGenerator{
    public :
        CodeGenerator();
        void get_equations();
        void get_equations_from_file(string file_name);
        string _generate(vector<string> &_temp, int _equas_id);
        void _main(const char *file_name, const char *file_name2);
    private:
        int num_equas, lens = 100, out_i = 0;
        //char equations[num_equas][lens];
        string * equations;
        void lexical_analyzer(string equation);
        vector<string> suffix(string equation);
        vector<string> _change_power(vector<string> &_temp);
        char *operators;
        char *operators_priorty;
        char *num_const;
        char *brackets;
        char assignment;
        map<string, int> ope_map;
        map<string, int> ::iterator iter;

        map<string, string> _code_signal;
        map<string, string> ::iterator _code_signal_iter;
        set<string> _set;
};
