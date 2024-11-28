#include "Pokemon.h"
#include "Defs.h"


//Function to create Pokemon
Pokemon* createPokemon( char *name, char *species, PokemonType *type,PokemonBioInfo *bio_info){
    if (name==NULL || species==NULL || type==NULL || bio_info==NULL ) {
        printf("Memory Problem");
        exit(EXIT_FAILURE);
    }
    Pokemon *new_pok = (Pokemon *)malloc(sizeof(Pokemon));
    if (new_pok == NULL) {
        printf("Memory Problem");
        free(new_pok);
        exit(EXIT_FAILURE);
    }
    new_pok->name = (char*)malloc(strlen(name) + 1);//create array of name
    if(new_pok->name == NULL){
        printf("Memory Problem");
        free(new_pok->name);
        free(new_pok);
        exit(EXIT_FAILURE);
    }
    strcpy(new_pok->name, name);

    new_pok->species = (char*)malloc(strlen(species) + 1);
    if(new_pok->species == NULL) {
        printf("Memory Problem");
        free(new_pok->name);
        free(new_pok->species);
        free(new_pok);
        exit(EXIT_FAILURE);
    }
    strcpy(new_pok->species, species);

    // Create PokemonType and BioInfo
    new_pok->type = (PokemonType*)malloc(sizeof(PokemonType));
        if(new_pok->type == NULL) {
            printf("Memory Problem");
            free(new_pok->type);
            free(new_pok->name);
            free(new_pok->species);
            free(new_pok);
            exit(EXIT_FAILURE);
        }
    memcpy(new_pok->type, type, sizeof(PokemonType));
    new_pok->bio_info = (PokemonBioInfo*)malloc(sizeof(PokemonBioInfo));
        if(new_pok->type == NULL) {
            printf("Memory Problem");
            free(new_pok->bio_info);
            free(new_pok->type);
            free(new_pok->name);
            free(new_pok->species);
            free(new_pok);
            exit(EXIT_FAILURE);
        }
    memcpy(new_pok->bio_info, bio_info, sizeof(PokemonBioInfo));

    return new_pok;
}



// Function to create PokemonType
PokemonType* createPokemonType( char *type_name){
    if (type_name==NULL) {
        printf("Memory Problem");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for the type
    PokemonType * new_type = (PokemonType *)malloc(sizeof(PokemonType));
    if (new_type == NULL) {
        printf("Memory Problem");
        exit(EXIT_FAILURE);
    }
    // Allocate memory for the type name
    new_type->type_name = (char*)malloc(strlen(type_name) + 1); // create array for name
    if (new_type->type_name == NULL) {
        free(new_type->type_name);
        printf("Memory Problem");
        exit(EXIT_FAILURE);
    }

    // Copy the provided string to the allocated memory
    strcpy(new_type->type_name, type_name);
    new_type->poke_in_type = 0;
    new_type->count_Poke_in_against_me = 0;
    new_type->count_Poke_in_against_others = 0;
    new_type->effective_against_me = NULL;
    new_type->effective_against_others = NULL;

    return new_type;
}



// Function to create Pokemon Bio Info
PokemonBioInfo* createPokemonBioInfo( float height, float weight, int attack){
    PokemonBioInfo * bio_info = (PokemonBioInfo *)malloc(sizeof(PokemonBioInfo));
    if(bio_info==NULL){
        free(bio_info);
        printf("Memory Problem");
        exit(EXIT_FAILURE);
    }
    // Initialization logic
    bio_info->height = height;
    bio_info->weight = weight;
    bio_info->attack = attack;
    return bio_info;
}



// Function to add Pokemon type to effective_against_me list
status add_to_effective_against_meList(PokemonType *source, PokemonType *type_to_add) {
    // Check if source or type_to_add is NULL
    if (source == NULL || type_to_add == NULL) {
        printf("Memory Problem");
        return failure;
    }
    // Increase the size of the effective_against_me array
    if (source->count_Poke_in_against_me == 0) {
        PokemonType **temp = (PokemonType **) malloc( sizeof(PokemonType *));
        if (temp == NULL) {
            printf("Memory Problem");
            return failure;
        }
        source->count_Poke_in_against_me++;
        source->effective_against_me = temp;
        // Add the pointer to type_to_add to the effective_against_me array
        source->effective_against_me[source->count_Poke_in_against_me - 1] = type_to_add;
    }else{
        PokemonType **new_temp = (PokemonType **) realloc(source->effective_against_me,source->count_Poke_in_against_me * sizeof(*type_to_add));
        if (new_temp == NULL){
            printf("Memory Problem");
            return failure;
        }
        source->count_Poke_in_against_me++;
        source->effective_against_me = new_temp;
        // Add the pointer to type_to_add to the effective_against_me array
        source->effective_against_me[source->count_Poke_in_against_me - 1] = type_to_add;
    }
    return success;

}

// Function to add Pokemon type to effective_against_me list
status add_to_effective_against_othersList(PokemonType *source, PokemonType *type_to_add) {
    // Check if source or type_to_add is NULL
    if (source == NULL || type_to_add == NULL) {
        printf("Memory Problem");
        return failure;
    }
    // Increase the size of the effective_against_me array
    if (source->count_Poke_in_against_others == 0) {
        PokemonType **temp = (PokemonType **) malloc(sizeof(PokemonType *));
        if (temp == NULL) {
            printf("Memory Problem");
            return failure;
        }
        source->count_Poke_in_against_others++;
        source->effective_against_others = temp;
        // Add the pointer to type_to_add to the effective_against_me array
        source->effective_against_others[source->count_Poke_in_against_others- 1] = type_to_add;
    }else{
        PokemonType **new_temp = (PokemonType **) realloc(source->effective_against_others,source->count_Poke_in_against_others * sizeof(*type_to_add));
        if (new_temp == NULL){
            printf("Memory Problem");
            return failure;
        }
        source->count_Poke_in_against_others++;
        source->effective_against_others = new_temp;
        // Add the pointer to type_to_add to the effective_against_me array
        source->effective_against_others[source->count_Poke_in_against_others - 1] = type_to_add;
    }
    return success;

}



// Function to remove Pokemon type from effective_against_me list
status removeFromMeAgainstEffectiveList(PokemonType *source, char *name_to_remove) {
    // Check if source or name_to_remove is NULL
    if (source == NULL || name_to_remove == NULL) {
        printf("Memory Problem");
        return failure;
    }
    // Remove typeName from source's effective_against_me list
    for (int i = 0; i < source->count_Poke_in_against_me; ++i) {
        if (strcmp(source->effective_against_me[i]->type_name, name_to_remove) == 0) {
            // Found the type, remove it
            source->count_Poke_in_against_me--;
            if (source->count_Poke_in_against_me == 0){
                source->effective_against_me = NULL;
                return success;
            }
            for (int j = i; j < source->count_Poke_in_against_me; ++j) {
                source->effective_against_me[j] = source->effective_against_me[j + 1];
            }
            // Reallocate memory for the effective_against_me array
            PokemonType **the_temp = realloc(source->effective_against_me,
                                             source->count_Poke_in_against_me * sizeof(PokemonType *));
            if (*the_temp == NULL) {
                printf("Memory Problem");
                return failure;
            } else {
                source->effective_against_me = the_temp;
                return success;
            }
        }
    }
    return success;
}



// Function to remove Pokemon type from effective_against_others list
status removeFromOthersAgainstEffectiveList(PokemonType *source, char *name_to_remove){
    // Check if source or name_to_remove is NULL
    if (source == NULL || name_to_remove == NULL) {
        printf("Memory Problem");
        return failure;
    }
    // Remove typeName from source's effective_against_others list
    for (int i = 0; i < source->count_Poke_in_against_others; ++i) {
        if (strcmp(source->effective_against_others[i]->type_name, name_to_remove) == 0) {
            // Found the type, remove it
            source->count_Poke_in_against_others--;
            if (source->count_Poke_in_against_others == 0){
                source->effective_against_others = NULL;
                return success;
            }
            for (int j = i; j < source->count_Poke_in_against_others; ++j) {
                source->effective_against_others[j] = source->effective_against_others[j + 1];
            }
            // Reallocate memory for the effective_against_others array

            PokemonType **the_temp_2 = realloc(source->effective_against_others,source->count_Poke_in_against_others * sizeof(PokemonType *));
            if (*the_temp_2 == NULL) {
                printf("Memory Problem");
                return failure;
            } else {
                source->effective_against_others = the_temp_2;
                return success;
            }
        }
    }
    return success;
}

// Function to print Pokemon
status printPokemon(Pokemon *pokemon) {
    // Check if the Pokemon pointer is NULL
    if (pokemon == NULL) {
        printf("Memory Problem");
        return failure;
    }
    // Print the Pokemon's information
    printf("%s :\n", pokemon->name);
    printf("%s, %s Type.\n", pokemon->species, pokemon->type->type_name);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", pokemon->bio_info->height, pokemon->bio_info->weight, pokemon->bio_info->attack);

    return success;
}





status printPokemonType(PokemonType *type) {
    // Check if the PokemonType pointer is NULL
    if (type == NULL) {
        printf("Memory Problem");
        return failure;
    }

    // Print the PokemonType's information
    printf("Type %s -- %d pokemons\n", type->type_name, type->poke_in_type);

    // Print the types that are super-effective against this type
    if (type->count_Poke_in_against_me > 0) {
        printf("\tThese types are super-effective against %s:", type->type_name);
        for (int i = 0; i < type->count_Poke_in_against_me; ++i) {
            printf("%s", type->effective_against_me[i]->type_name);
            if (i < type->count_Poke_in_against_me - 1) {
                printf(" ,");
            }
        }
        printf("\n");
    }

    // Print the types that this type is super-effective against
    if (type->count_Poke_in_against_others > 0) {
        printf("\t%s moves are super-effective against:", type->type_name);
        for (int i = 0; i < type->count_Poke_in_against_others; ++i) {
            printf("%s", type->effective_against_others[i]->type_name);
            if (i < type->count_Poke_in_against_others - 1) {
                printf(" ,");
            }
        }
        printf("\n");
    }

    printf("\n");

    return success;
}




void destroyPokemon(Pokemon *pokemon) {
    if (pokemon == NULL) {
        printf("Memory Problem");
        return; // Nothing to free if the pointer is NULL
    }

    // Free dynamically allocated fields
    free(pokemon->name);
    free(pokemon->species);
    free(pokemon->type);
    DestroyBioInfo(pokemon->bio_info);
    // Free the Pokemon structure itself
    free(pokemon);
}

// Function to destroy Pokemon Type
void destroyPokemonType(PokemonType *type) {
    if (type == NULL ) {
        return; // Nothing to free if the pointer is NULL
    }
    // Free dynamically allocated fields
    free(type->type_name);
    free(type->effective_against_me);
    free(type->effective_against_others);

    // Free the PokemonType structure itself
    free(type);
}
void removeLeadingTabs(char *str) {
    if(str == NULL){
        return;
    }
    int i = 0;
    // Iterate over the string until a non-tab character is found
    while (str[i] == '\t') {
        i++;
    }
    // Move the remaining characters to the beginning of the string
    memmove(str, str + i, strlen(str) - i + 1);
}
void trimNewline(char *str) {
    if(str == NULL) {
        return;
    }
    size_t length = strlen(str);

    // Check if the last character is '\n'
    if (length > 0 && str[length - 1] == '\n') {
        str[length - 1] = '\0'; // Replace '\n' with null terminator

        // Check if the second last character is '\r' (for Windows-style newline)
        if (length > 1 && str[length - 2] == '\r') {
            str[length - 2] = '\0'; // Replace '\r' with null terminator
        }
    }
}


void DestroyBioInfo(PokemonBioInfo *bioInfo){
        if(bioInfo !=NULL)
        {
            free(bioInfo);
        }
    }

