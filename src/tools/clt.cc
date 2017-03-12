#include "../../include/tools/clt.h"
#include "../../include/sql-compiler/parser.h"
#include "../../include/backend/backend.h"

using namespace std;

int main(int argc, char const *argv[]) {
    string ps1 = ">>> ";
    string inp = "";

    int l = 0;

    for (;;) {
        cout << ps1;
        getline(cin, inp);

        if (inp == "exit") {
            break;
        }

        l = inp.size();

        if (l != 0) {
            cout << parse(inp) << "\n";
        }
    }

    return 0;
}