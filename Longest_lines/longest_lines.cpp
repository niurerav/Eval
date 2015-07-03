//
//  main.cpp
//  Longest_lines
//
//  Created by Ravi Niure on 2015-07-03.
//  Copyright (c) 2015 Ravi Niure. All rights reserved.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

using namespace std;

bool sorting_function(string _first, string _second)
{
    return _first.length() > _second.length();
}

int main(int argc, const char * argv[]) {
    
    vector<string> lines_vec;
    
    ifstream file_path;
    file_path.open(argv[1]);
    
    int total_lines_to_print;
    
    if(file_path.is_open())
    {
        char _lines[256];
        total_lines_to_print = file_path.get() - '0';
        
        do{
            file_path.getline(_lines, 256);
            if(!file_path.eof()) lines_vec.push_back(_lines);
        }while(!file_path.eof());
        file_path.close();
        
    }
    else
    {
        cout << "File didn't open" << endl;
        return 1;
    }
    sort(lines_vec.begin(), lines_vec.end(), sorting_function);
    
    for(int i = 0; i < total_lines_to_print; i++)
        cout << lines_vec[i] << endl;
        
    
    /*
    for (vector<string>::iterator it=lines_vec.begin(); it!=lines_vec.end(); ++it)
    {
        cout << *it << endl;
    }
    */
    return 0;
}
