#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <streambuf>
#include "ParseSTL.h"
using namespace std;

namespace stl {

    ostream& operator<<(ostream& out, const point p) {
        out << "(" << p.x << ", " << p.y << ", " << p.z << ")" << endl;
        return out;
    }

    ostream& operator<<(ostream& out, const triangle& t) {
        out << "---- TRIANGLE ----" << endl;
        out << t.normal << endl;
        out << t.v1 << endl;
        out << t.v2 << endl;
        out << t.v3 << endl;
        return out;
    }

    float parse_float(ifstream& s) {
        char f_buf[sizeof(float)];
        s.read(f_buf, 4);
        float* fptr = (float*)f_buf;
        return *fptr;
    }

    point parse_point(ifstream& s) {
        float x = parse_float(s);
        float y = parse_float(s);
        float z = parse_float(s);
        return point(x, y, z);
    }

    stl_data parse_stl(const string& stl_path) {
        ifstream stl_file(stl_path.c_str(), ios::in | ios::binary);
        if (!stl_file) {
            cout << "ERROR: COULD NOT READ FILE" << endl;
            assert(false);
        }

        char header_info[80] = "";
        char n_triangles[4];
        stl_file.read(header_info, 80);
        stl_file.read(n_triangles, 4);
        string h(header_info);
        stl_data info(h);
        unsigned int* r = (unsigned int*)n_triangles;
        unsigned int num_triangles = *r;
        for (unsigned int i = 0; i < num_triangles; i++) {
            auto normal = parse_point(stl_file);
            auto v1 = parse_point(stl_file);
            auto v2 = parse_point(stl_file);
            auto v3 = parse_point(stl_file);
            info.triangles.push_back(triangle(normal, v1, v2, v3));
            char dummy[2];
            stl_file.read(dummy, 2);
        }
        return info;
    }

}