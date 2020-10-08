#include <ostream>

using namespace std;

#define PRINT_VALUES(out, x, y) print_values(out, x, y)

template<typename T1, typename T2>
void print_values(ostringstream &out, T1 x, T2 y) {
    out << x << endl << y << endl;
}
