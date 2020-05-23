//
//  main.cpp
//  Brainfuck Interpreter
//
//  Created by Pedro Francescon Cittolin on 20/05/20.
//  Copyright © 2020 Pedro Francescon Cittolin. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#define MEMORY_SIZE 100

using namespace std;

string file2String(ifstream *file)
{
    string code;
    short loop=0;
    string line;
    
    while (! file->eof() )
    {
        getline (*file,line);
        code += line;
        loop++;
    }
    file->close();
    code.erase(remove(code.begin(), code.end(), ' '),
    code.end());
    
    return code;
}

void run(string code)
{
    int memory[MEMORY_SIZE] = {0};
    int memory_pos = 0;
    stack<string::size_type> open_loop_position;
    
    for(string::size_type i = 0; i < code.size(); ++i)
    {
        
        switch (code[i])
        {
            case '+':
                memory[memory_pos]++;
                break;
            
            case '-':
                memory[memory_pos]--;
                break;
            
            case '>':
                memory_pos++;
                break;
            
            case '<':
                memory_pos--;
                break;
            
            case '[':
                if (memory[memory_pos] == 0)
                {
                    int open_loops = 1;
                    
                    while (!(code[i] == ']' && open_loops == 0))
                    {
                        
                        i++;
                        if (code[i] == '[')
                            open_loops++;
                        else if (code[i] == ']')
                            open_loops--;
                    }
                    break;
                }
                
                open_loop_position.push(i);
                break;
            
            case ']':
                i = open_loop_position.top() - 1;
                open_loop_position.pop();
                break;
            
            case '.':
                cout << char(memory[memory_pos]);
                break;
                
            case ',':
                char temp;
                cin >> temp;
                memory[memory_pos] = int(temp);
                break;
                
            default:
                break;
        }
    }
}

int main(int argc, const char * argv[])
{
    if (argc == 2)
    {
        ifstream file (argv[1]);
        
        if (!file.is_open())
        {
            cout << "Unable to open file";
            return 0;
        }
        
        string code = file2String(&file);
        run(code);
        
        cout << endl;
    }
    
    else if (argc == 1)
        cout << "Missing file!";
    
    return 0;
}
