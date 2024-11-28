
#ifndef ASSIGNMENT2_C_POKEMON_H
#define ASSIGNMENT2_C_POKEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"


// Pokemon Type struct
typedef struct Pokemon_Type {
    char *type_name;
    int poke_in_type ;
    int count_Poke_in_against_me;
    int count_Poke_in_against_others;
    struct Pokemon_Type **effective_against_me;
    struct Pokemon_Type **effective_against_others;
}PokemonType;

// Pokemon Bio Info struct
typedef struct Pokemon_Bio_Info {
    float height;
    float weight;
    int attack;
}PokemonBioInfo;

// Pokemon structure
typedef struct Pokemon_1{
    char *name;
    char *species;
    PokemonType *type;
    PokemonBioInfo *bio_info;
} Pokemon;



// Function to create Pokemon
Pokemon* createPokemon( char *name, char *species, PokemonType *type,PokemonBioInfo *bio_info);


// Function to create PokemonType
PokemonType* createPokemonType( char *type_name);


// Function to create Pokemon Bio Info
PokemonBioInfo* createPokemonBioInfo( float height, float weight, int attack);


// Function to add Pokemon type to effective_against_me list
status add_to_effective_against_meList(PokemonType *source, PokemonType *type_to_add);


// Function to add Pokemon type to effective_against_others list
status add_to_effective_against_othersList(PokemonType *source, PokemonType *type_to_add);


// Function to remove Pokemon type from effective_against_me list
status removeFromMeAgainstEffectiveList(PokemonType *source, char *name_to_remove);


// Function to remove Pokemon type from effective_against_others list
status removeFromOthersAgainstEffectiveList(PokemonType *source, char *name_to_remove);

// Function to print Pokemon
status printPokemon(Pokemon *pokemon);


// Function to print Pokemon type
status printPokemonType(PokemonType *type);


// Function to destroy Pokemon
void destroyPokemon(Pokemon *pokemon);


// Function to destroy Pokemon Type
void destroyPokemonType(PokemonType *type);

// Function to remove Leading Tabs
void removeLeadingTabs(char *str);

// Function to remove Unnecessary signs
void trimNewline(char *str);


// Function to destroy Destroy Bio Info
void DestroyBioInfo(PokemonBioInfo *bioInfo);




#endif
