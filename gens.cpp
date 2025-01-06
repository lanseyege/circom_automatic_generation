#include "gens.h"

CodeGenerator::CodeGenerator() {
    operators = new char[8];
    operators_priorty = new char[8];
    operators[0] = '+'; operators[1] = '-';
    operators[2] = '*'; operators[3] = '/';
    operators[4] = '^'; operators[5] = '=';
    operators[6] = '('; operators[7] = ')';
    operators_priorty[0] = 0; 
    operators_priorty[1] = 0; 
    operators_priorty[2] = 1; 
    operators_priorty[3] = 1; 
    operators_priorty[4] = 2; 
    operators_priorty[6] = 3; 
    ope_map["+"] = 0; ope_map["-"] = 0; ope_map["*"] = 1; ope_map["/"] = 1;
    ope_map["^"] = 2; ope_map["("] = -1; 
    ope_map["="] = -1; ope_map[")"] = -1;
}

void CodeGenerator::get_equations() {
    cout << "input amount of equations: " << endl;
    cin >> num_equas;
    char temp_a; cin.get(temp_a);
    int i = 0;
    equations = new string[num_equas];
    while (i < num_equas) {
        getline(cin, equations[i]);
        i ++ ;
    }
    for (i = 0; i < num_equas; i ++) 
        cout << i << " , len: " << equations[i].length() << " , " << equations[i] << endl;
}

void CodeGenerator::get_equations_from_file(string file_name) {
    ifstream fin; 
    fin.open(file_name, ios::in);
    if (! fin.is_open()) {cerr << "cannot open the file" ;}
    char c ;
    while ((c = fin.get()) != '\n') {
        num_equas = c - '0';
    }
    cout << "num_equas: " << num_equas << endl;
    equations = new string[num_equas];
    char _buf[lens] = {0}; int i = 0;
    while (fin.getline(_buf, sizeof(_buf))) {
        equations[i++] = _buf;
    }
    for (i = 0; i < num_equas; i ++) 
        cout << i << " , len: " << equations[i].length() << " , " << equations[i] << endl;
    fin.close();  
}

vector<string> CodeGenerator::suffix(string equation) {
    int n = equation.length();
    string ch, last_ch = "", _temp ; int last = -1; 
    vector <string> opes, equas;
    for (int i = 0; i < n; i++) {
        ch = equation.substr(i, 1); 
        //cout << "ch: " << ch << endl;
        iter = ope_map.find(ch);
        if (iter != ope_map.end()) {
            /**
              cout << "iter second: " << iter->second << endl;
              if ( !opes.empty()) {
              cout << "opes top: " << opes.back() << endl; 
              cout << "back: " << ope_map.at(opes.back()) << endl;
              }
              cout << "find it" << endl;  **/
            last = 0;
            if (last_ch != "") {
                equas.push_back(last_ch);
                last_ch = "";
            }
            if (opes.empty()) {
                opes.push_back(ch);
            } else if (ch == ")") {
                while ( 1 ) {
                    _temp = opes.back() ; 
                    opes.pop_back(); 
                    if (_temp != "(")
                        equas.push_back(_temp);
                    else break;
                }
            } else if (ch == "(" )  {
                opes.push_back("(") ;
            } else if (opes.size() > 0 && iter->second <= ope_map.at(opes.back()) ) {
                while (opes.size() > 0 && iter->second <= ope_map.at(opes.back()) ) {
                    equas.push_back(opes.back());
                    opes.pop_back();
                }
                opes.push_back(ch); 
            }
            else {
                opes.push_back(ch);
            }
        }
        else {
            //cout << "no find it" << endl;
            if (ch == " ") { 
                continue;
            }
            else if (last == 1) {
                last_ch = last_ch + ch;
                last = 1;
            }else {
                last_ch = ch; 
                last = 1;
            }
        }
    }
    if (last_ch != "") equas.push_back(last_ch);
    while (opes.size() > 0) {
        equas.push_back(opes.back());
        opes.pop_back();
    }
    //cout <<" pop back: " << equas.size() << endl;
    vector<string> ::iterator iter2;
    for (iter2 = equas.begin(); iter2 != equas.end(); iter2 ++) {
        cout << *iter2 << " " ;
    } 
    cout << endl;
    return equas;
}

string CodeGenerator::_generate(vector<string> &_temp, int _equas_id) {
    stack<string> stk;
    vector<string> ::iterator it; 
    string _t1, _t2, code = "\n", _out, _ts1;  
    for ( it = _temp.begin(); it != _temp.end(); it++) {
        cout << "*it " << *it << endl;
        iter = ope_map.find( *it) ;
        if (iter != ope_map.end()) {
            _t1 = stk.top(); stk.pop(); 
            _t2 = stk.top(); stk.pop(); 
            _ts1 = _t2 + " " + *it + " " + _t1;
            _code_signal_iter = _code_signal.find(_ts1);
            if (_code_signal_iter != _code_signal.end()) {
                _out = _code_signal_iter->second ;
            }
            else {
                if (*it != "/" && *it != "-") {
                    _ts1 = _t1 + " " + *it + " " + _t2;
                    _code_signal_iter = _code_signal.find(_ts1);
                    if (_code_signal_iter != _code_signal.end()) {
                        _out = _code_signal_iter->second ;
                    }
                    else { 
                        if (it + 1 == _temp.end() ) {
                            _out = "out_" + to_string(_equas_id);
                        } else {
                            _out = "int_" + to_string(out_i++);
                        }
                        _code_signal[_t1 + " " + *it + " " + _t2] = _out;
                        _code_signal[_t2 + " " + *it + " " + _t1] = _out;
                    }
                }
            }
            if (_set.find(_t1) == _set.end()) {
                try {
                    stoi(_t1, nullptr, 0);
                } catch(const exception& e){
                    code += "\tsignal input " + _t1 + "; \n";
                    _set.insert(_t1);
                }
            } 
            if (_set.find(_t2) == _set.end()) {
                try {
                    stoi(_t2, nullptr, 0);
                } catch(const exception& e) {
                    code += "\tsignal input " + _t2 + "; \n";
                    _set.insert(_t2);
                }
            }
            if (_set.find(_out) == _set.end()) {
                if (it + 1 == _temp.end()) {
                    code += "\tsignal output " + _out + "; \n"; 
                }else{
                    code += "\tsignal " + _out + "; \n"; 
                }
                _set.insert(_out);
            }
            if (_set.find(_out + " <== " + _t2 + " " + *it + " " + _t1 + ";") == _set.end() ) {
                code += "\t" + _out + " <== " + _t2 + " " + *it + " " + _t1 + ";\n";
                _set.insert(_out + " <== " + _t2 + " " + *it + " " + _t1 + ";");
            }
            stk.push(_out) ;
        } else {
            stk.push( *it) ;
        }
    }
    return code;
}

vector<string> CodeGenerator::_change_power(vector<string> & _temp) {
    vector<string> _temp2; string _t1 = "", _t2 = ""; int _it1;
    for (auto i = _temp.begin(); i != _temp.end() ; i++) {
        if ( *i != "^" ){
            _temp2.push_back( *i );
        }else {
            _t1 = _temp2.back(); _temp2.pop_back();
            cout << _t1 << endl;
            _t2 = _temp2.back(); _temp2.pop_back();
            cout << _t2 << endl;
            try {
                _it1 = stoi(_t1, nullptr, 0); 
            } catch (const exception& e) {
                cerr << "exception happend for stoi" << endl;
            }
            _temp2.push_back(_t2);
            for (int j = 0; j < _it1 - 1 ; j ++) {
                _temp2.push_back(_t2);
                _temp2.push_back("*");
            }
        }
    }
    return _temp2;
}

void CodeGenerator::_main(const char *_argv, const char *_argv2) {
    get_equations_from_file(_argv);
    vector<string> _temp, _temp2; 
    string _res = "pragma circom 2.0.0;\n\ntemplate Multiplier () {\n";
    for (int i = 0; i < num_equas; i++) {
        cout <<"equation " << i << " " << equations[i] << endl;
        _temp = suffix(equations[i]); 
        _temp2 = _change_power(_temp);
        cout << "generate " << i << endl;
        _res += _generate(_temp2, i);
    }
    _res += "}\n\ncomponent main = Multiplier();";
    cout << "res: " << endl;
    cout << _res << endl; 
    ofstream fout(_argv2);
    fout << _res;
    fout.close();
}

int main(int argc, char const *argv[]) {
    CodeGenerator cg;
    //cg.get_equations();
    //cg.get_equations_from_file(argv[1]);
    cg._main(argv[1], argv[2]);
}

