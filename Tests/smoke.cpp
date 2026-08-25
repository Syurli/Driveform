#include <driveform/driveform.h>

#include <cassert>
#include <cmath>

int main() {
    const DF_Version version = dfGetVersion();
    assert(version.major == 0);
    assert(version.minor == 1);

    DF_WorldHandle world = dfCreateWorld(1.0F / 120.0F);
    assert(world != nullptr);

    dfWorldStep(world, 1.0F / 60.0F);
    assert(dfWorldGetStepCount(world) == 2);
    assert(std::fabs(dfWorldGetFixedStep(world) - (1.0F / 120.0F)) < 0.00001F);

    dfDestroyWorld(world);
    return 0;
}
