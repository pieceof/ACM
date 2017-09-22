#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

struct node_t;
typedef std::string String;
typedef std::vector<String> Svector;
typedef std::vector<node_t> Nvector;

struct node_t {
    node_t(){}
    node_t(String const &n):name(n){}
    std::string name;
    Svector addr;
    bool operator<(node_t const &nt) const {
        return name < nt.name;
    }
    bool operator==(String const &str) const {
        return str == name;
    }
    void sort(){
        std::sort(addr.begin(), addr.end());
    }
    void add(String const &n) {
        addr.push_back(n);
    }
    void del(String const &n) {
        addr.erase(std::find(addr.begin(), addr.end(), n));
    }
    void printf() const {
        ::printf("%s\n", name.c_str());
        for (Svector::const_iterator it = addr.begin(); it != addr.end(); ++it)
            ::printf("|---->%s\n", it->c_str());
    }
};

Svector split(String str)
{
    Svector v;
    str.push_back(' ');
    int s(0);
    while (s < str.length()) {
        if (str[s] == ' ')
            ++s;
        else {
            int e = str.find(' ', s);
            v.push_back(str.substr(s, e - s));
            s = e + 1;
        }
    }
    return v;
}

int main(void)
{
    char line[200];
    Nvector nv;

    while (gets(line) != NULL) {
        Svector v(split(String(line)));
        if (v.size() == 1 && v[0] == "prt") {
            for(Nvector::iterator it = nv.begin(); it != nv.end(); ++it) {
                it->printf();
            }
            nv.clear();
            puts("");
        } else {
            switch(v[0][2]) {
                case 'e':
                    nv.push_back(node_t(v[1]));
                    break;
                case 'r':
                    if (v.size() == 2) {
                        nv.push_back(node_t(v[1]));
                    } else {
                        std::find(nv.begin(), nv.end(), v[2])->add(v[1]);
                    }
                    break;
                case 'n':
                    if (v.size() == 1) {
                        std::sort(nv.begin(), nv.end());
                    } else {
                        std::find(nv.begin(), nv.end(), v[1])->sort();
                    }
                    break;
                case 't':
                    std::find(nv.begin(), nv.end(), v[1])->printf();
                    break;
                case 'l':
                    if (v.size() == 2) {
                        nv.erase(std::find(nv.begin(), nv.end(), v[1]));
                    } else {
                        std::find(nv.begin(), nv.end(), v[2])->del(v[1]);
                    }
                    break;
            }
        }
    }
}
