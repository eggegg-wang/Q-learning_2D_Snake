#include <backward/strstream>
#include "Q.h"
#include "env.h"
#include "ctime"
#include "windows.h"
#include "Vector2D.h"


int main() {
    unsigned seed;
    seed = time(0);
    srand(seed);
    Vector2D v;

    v.run();

}


