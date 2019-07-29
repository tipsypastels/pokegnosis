#include "global.h"
#include "random.h"
#include "constants/species.h"

u16 GetRandomizedPokemon(void)
{
    // don't want the ??? mon so we offset by 1
    return (Random() % (NUM_SPECIES - 1)) + 1;
}

u16 AccountForPokemonRandomizer(u16 species)
{
#if RANDOMIZE_MONS
    return GetRandomizedPokemon();
#else
    return species;
#endif
}