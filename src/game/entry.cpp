#include "../engine/engine.h"

int main(int argc, char **argv)
{
    engine::engine_instance* eng = new engine::engine_instance();
    //register any additional types
    eng->Run();

    return 0;
}
