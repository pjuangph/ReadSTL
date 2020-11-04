#include <cstdio>
#include <stdlib.h>
#include <iostream> 
#include "ParseSTL.h"

using namespace std;

int main()
{
    string stl_file_name = "./Box1x1x1.stl";

    auto info = stl::parse_stl(stl_file_name);

    vector<stl::triangle> triangles = info.triangles;
    cout << "STL HEADER = " << info.name << endl;
    cout << "# triangles = " << triangles.size() << endl;
    for (auto t : info.triangles) {
        cout << t << endl;
    }
}