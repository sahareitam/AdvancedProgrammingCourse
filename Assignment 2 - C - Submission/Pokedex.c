#include <stdbool.h>
#include <ctype.h>
#include "Pokemon.h"



#define MAX_BUFFER_SIZE 300


int main(int argc, char *argv[] ){

    //Parse the command-line arguments
    int numberOfTypes = atoi(argv[1]);
    int numberOfPokemons = atoi(argv[2]);
    char *configurationFile = argv[3];
    FILE *fPointer = fopen(configurationFile, "r");

//int main() {
//    int numberOfTypes = 6;
//    int numberOfPokemons = 14;
//    char *configurationFile = "/home/ise/Desktop/cof_ex/FullRun_Data.txt";

//    int numberOfTypes = 6;
//    int numberOfPokemons = 16;
//    char *configurationFile = "/home/ise/Desktop/cof_ex/FullRun_Data 1.txt";

//    int numberOfTypes = 9;
//    int numberOfPokemons = 14;
//    char *configurationFile = "/home/ise/Desktop/cof_ex/FullRun_Data 2.txt";

//    int numberOfTypes = 9;
//    int numberOfPokemons = 18;
//    char *configurationFile = "/home/ise/Desktop/cof_ex/FullRun_Data 3.txt";
//
//    int numberOfTypes = 11;
//    int numberOfPokemons = 20;
//    char *configurationFile = "/home/ise/Desktop/cof_ex/FullRun_Data 4.txt";

//    FILE *fPointer = fopen(configurationFile, "r");


    char *line = NULL;
    size_t size = MAX_BUFFER_SIZE;
    PokemonType *allTypes[numberOfTypes];


    //first call to skip the first line
    getline(&line, &size, fPointer);

    //second call to get the line with the allTypes
    getline(&line, &size, fPointer);


    char *token = strtok(line, ",");
    int type_count = 0;
    while (token != NULL && type_count < numberOfTypes) {
        allTypes[type_count] = createPokemonType(token);
        type_count++;
        token = strtok(NULL, ","); // Move to the next segment
        trimNewline(token);
    }

    int j;
    int z;
    char *me = "effective-against-me";
    char *other = "effective-against-other";


    // add efeectivnes
    while (getline(&line, &size, fPointer) && strcmp(line, "Pokemons\r\n") != 0) {
        char *the_effective_type_name = strtok(line, " ");
        removeLeadingTabs(the_effective_type_name);

        for (j = 0; j < numberOfTypes; j++) {
            if (the_effective_type_name != NULL) {
                if (strcmp(the_effective_type_name, allTypes[j]->type_name) == 0) {
                    char *me_or_other = strtok(NULL, ":");
                    if (strcmp(me_or_other, me) == 0) {
                        while (the_effective_type_name != NULL) {
                            the_effective_type_name = strtok(NULL, ",");
                            if (the_effective_type_name != NULL) {
                                trimNewline(the_effective_type_name);
                                for (z = 0; z < numberOfTypes; z++) {
                                    if (strcmp(the_effective_type_name, allTypes[z]->type_name) == 0) {
                                        add_to_effective_against_meList(allTypes[j], allTypes[z]);
                                        break;
                                    }
                                }
                            }
                        }

                    } else if (strcmp(me_or_other, other) == 0) {
                        while (the_effective_type_name != NULL) {
                            the_effective_type_name = strtok(NULL, ",");
                            if (the_effective_type_name != NULL) {
                                trimNewline(the_effective_type_name);
                                for (z = 0; z < numberOfTypes; z++) {
                                    if (strcmp(the_effective_type_name, allTypes[z]->type_name) == 0) {
                                        add_to_effective_against_othersList(allTypes[j], allTypes[z]);
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int e;
    char *pt_1;
    Pokemon **All_pokemons = (Pokemon**) malloc(numberOfPokemons* sizeof(Pokemon*));
    if(All_pokemons == NULL){
        free(All_pokemons);
        printf("Memory Problem");
        return failure;
    }
    //runs on all receiving Pokemones
    for (e = 0; e < numberOfPokemons; e++) {
        getline(&line, &size, fPointer);

        //name
        pt_1 = strtok(line, ",");
        char *name = malloc(strlen(pt_1) + 1);
        if (name == NULL) {
            printf("Memory Problem");
            return failure;
        }
        strcpy(name, pt_1);
        pt_1 = strtok(NULL, ",");

        //species
        char *species = malloc(strlen(pt_1) + 1);
        if (species == NULL) {
            free(name);
            free(species);
            printf("Memory Problem");
            return failure;
        }
        strcpy(species, pt_1);
        pt_1 = strtok(NULL, ",");

        //height
        float height = atof(pt_1);
        pt_1 = strtok(NULL, ",");

        //weight
        float weight = atof(pt_1);
        pt_1 = strtok(NULL, ",");

        //attack
        int attack = atoi(pt_1);
        pt_1 = strtok(NULL, "");

        //name_type
        trimNewline(pt_1);
        char *name_type = malloc(strlen(pt_1) + 1);
        if (name_type == NULL) {
            free(name);
            free(species);
            free(name_type);
            printf("Memory Problem");
            return failure;
        }
        strcpy(name_type, pt_1);
        int i;
        for (i = 0; i < numberOfTypes; i++) {
            if (strcmp(allTypes[i]->type_name, name_type) == 0) {
                allTypes[i]->poke_in_type++;

                PokemonBioInfo *bio = createPokemonBioInfo( height, weight, attack);
                Pokemon *pokemon_1 = createPokemon( name, species, allTypes[i], bio);
                All_pokemons[e] = pokemon_1;
                free(bio);
            }
        }
        free(name_type);
        free(species);
        free(name);
    }

    fclose(fPointer);
    int choice;
    while (1) {
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Add type to effective against me list\n");
        printf("4 : Add type to effective against others list\n");
        printf("5 : Remove type from effective against me list\n");
        printf("6 : Remove type from effective against others list\n");
        printf("7 : Print Pokemon by name\n");
        printf("8 : Print Pokemons by type\n");
        printf("9 : Exit\n");

        char the_input[2];
        // Get user choice
        scanf("%s", the_input);
        if (isdigit(the_input[0])) {
            choice = the_input[0] - '0';
            if (choice > 0 && choice < 10) {
            } else {
                printf("Please choose a valid number.\n");
                  // Display the menu again
            }
        } else if (!isdigit(the_input[0])) {
            printf("Please choose a valid number.\n");
            continue;
              // Display the menu again
        }
        switch (choice) {
            case 1:
                // Print all Pokemons
                for (int c = 0; c < numberOfPokemons; c++) {
                    printPokemon(All_pokemons[c]);
                }
                break;
            case 2:
                // Print all Pokemon allTypes
                for (int d = 0; d < numberOfTypes; d++) {
                    printPokemonType(allTypes[d]);
                }
                break;
            case 3:
                // Add type to effective against me list
                printf("Please enter type name:\n");
                char *type_name_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (type_name_temp == NULL){
                    free(type_name_temp);
                    return failure;
                }
                scanf("%s", type_name_temp);
                char *type_name_1 = realloc(type_name_temp, strlen(type_name_temp) + 3);
                if(type_name_1 == NULL){
                    free(type_name_temp);
                    printf("Memory Problem");
                    return failure;
                }
                bool flag_1 = false;
                int number_in_against_me_1;
                int counter_in_types_1;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfTypes; h++) {
                    if (strcmp(allTypes[h]->type_name, type_name_1) == 0) {
                        counter_in_types_1 = h;
                        number_in_against_me_1 = allTypes[h]->count_Poke_in_against_me;
                        flag_1 = true;
                        break;
                    }
                }

                if (flag_1 == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                printf("Please enter type name to add to %s effective against me list:\n", type_name_1);
                free(type_name_1);
                char *effective_type_name_1_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (effective_type_name_1_temp == NULL){
                    free(effective_type_name_1_temp);
                    return failure;
                }

                scanf("%s", effective_type_name_1_temp);
                char *effective_type_name_1 = realloc(effective_type_name_1_temp, strlen(effective_type_name_1_temp) + 3);
                if(effective_type_name_1 == NULL){
                    free(effective_type_name_1_temp);
                    printf("Memory Problem");
                    return failure;
                    }
                char *effective_name_1;
                bool the_flag = false;
                int counter_of_the_effec_in_types_1;
                // Find the effective type in the array of allTypes
                for (int t = 0; t < type_count; t++) {
                    if (strcmp(allTypes[t]->type_name, effective_type_name_1) == 0) {
                        counter_of_the_effec_in_types_1 = t;
                        effective_name_1 = allTypes[t]->type_name;
                        the_flag = true;
                        break;
                    }
                }
                free(effective_type_name_1);

                if (the_flag == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                // Check if the effective type is already in the effective against me list
                bool already_in = false;

                for (int r = 0; r < number_in_against_me_1; r++) {
                    if (strcmp(allTypes[counter_in_types_1]->effective_against_me[r]->type_name,effective_name_1) == 0) {
                        already_in = true;
                        break;
                    }
                }
                if (already_in == true) {
                    printf("This type already exist in the list.\n");
                    break;
                }else {

                    // Add the effective type to the effective against me list
                    add_to_effective_against_meList(allTypes[counter_in_types_1],allTypes[counter_of_the_effec_in_types_1]);

                    // Print the updated type
                    printPokemonType(allTypes[counter_in_types_1]);
                    break;
                }

            case 4:
                // Add type to effective against other list
                printf("Please enter type name:\n");
                char *type_name_temp_1 = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (type_name_temp_1 == NULL){
                    return failure;
                }
                scanf("%s", type_name_temp_1);
                char *type_name_2 = realloc(type_name_temp_1, strlen(type_name_temp_1) + 3);
                if(type_name_2 == NULL){
                    free(type_name_temp_1);
                    printf("Memory Problem");
                    return failure;
                }
                bool flag_2 = false;
                int number_in_against_me_2;
                int counter_in_types_2;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfTypes; h++) {
                    if (strcmp(allTypes[h]->type_name, type_name_2) == 0) {
                        counter_in_types_2 = h;
                        number_in_against_me_2 = allTypes[h]->count_Poke_in_against_others;
                        flag_2 = true;
                        break;
                    }
                }

                if (flag_2 == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                printf("Please enter type name to add to %s effective against others list:\n", type_name_2);
                free(type_name_2);
                char *effective_type_name_2_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (effective_type_name_2_temp == NULL){
                    free(effective_type_name_2_temp);
                    return failure;
                }

                scanf("%s", effective_type_name_2_temp);
                char *effective_type_name_2 = realloc(effective_type_name_2_temp, strlen(effective_type_name_2_temp) + 3);
                if(effective_type_name_2 == NULL){
                    free(effective_type_name_2_temp);
                    printf("Memory Problem");
                    return failure;
                }
                char *effective_name_2;
                bool the_flag_2 = false;
                int counter_of_the_effec_in_types_2;
                // Find the effective type in the array of allTypes
                for (int t = 0; t < type_count; t++) {
                    if (strcmp(allTypes[t]->type_name, effective_type_name_2) == 0) {
                        counter_of_the_effec_in_types_2 = t;
                        effective_name_2 = allTypes[t]->type_name;
                        the_flag_2 = true;
                        break;
                    }
                }
                free(effective_type_name_2);

                if (the_flag_2 == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                // Check if the effective type is already in the effective against me list
                bool already_in1 = false;

                for (int r = 0; r < number_in_against_me_2; r++) {
                    if (strcmp(allTypes[counter_in_types_2]->effective_against_others[r]->type_name,effective_name_2) == 0) {
                        already_in1 = true;
                        break;
                    }
                }
                if (already_in1 == true) {
                    printf("This type already exist in the list.\n");
                    break;
                }

                // Add the effective type to the effective against me list
                add_to_effective_against_othersList(allTypes[counter_in_types_2],allTypes[counter_of_the_effec_in_types_2]);

                // Print the updated type
                printPokemonType(allTypes[counter_in_types_2]);
                break;


            case 5:
                printf("Please enter type name:\n");
                char *source_type_name_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (source_type_name_temp == NULL) {
                    free(source_type_name_temp);
                    return failure;
                }
                scanf("%s", source_type_name_temp);

                char *source_type_name = realloc(source_type_name_temp, strlen(source_type_name_temp) + 3);
                if(source_type_name == NULL){
                    free(source_type_name_temp);
                    printf("Memory Problem");
                    return failure;
                }
                bool flag_source = false;
                int counter_in_types_source;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfTypes; h++) {
                    if (strcmp(allTypes[h]->type_name, source_type_name) == 0) {
                        counter_in_types_source = h;
                        flag_source = true;
                        break;
                    }
                }

                if (flag_source == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                printf("Please enter type name to remove from %s effective against me list:\n", source_type_name);
                free(source_type_name);
                char *effective_type_name_remove_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (effective_type_name_remove_temp == NULL){
                    free(effective_type_name_remove_temp);
                    return failure;
                }

                scanf("%s", effective_type_name_remove_temp);
                char *effective_type_name_remove = realloc(effective_type_name_remove_temp, strlen(effective_type_name_remove_temp) + 3);
                if(effective_type_name_remove == NULL){
                    free(effective_type_name_remove_temp);
                    printf("Memory Problem");
                    return failure;
                }
                bool is_remove = false;
                int counter_of_the_effec_in_types_to_remove;
                // Find the effective type in the array of allTypes
                for (int t = 0; t < numberOfTypes; t++) {
                    if (strcmp(allTypes[t]->type_name, effective_type_name_remove) == 0) {
                        counter_of_the_effec_in_types_to_remove = t;
                        is_remove = true;
                        break;
                    }
                }


                if (is_remove == false) {
                    printf("Type name doesn't exist in the list.\n");
                    break;
                }

                // Check if the effective type to remove is in the effective against me list
                bool type_remove_in = false;

                for (int r = 0; r < allTypes[counter_in_types_source]->count_Poke_in_against_me; r++) {
                    if (strcmp(allTypes[counter_in_types_source]->effective_against_me[r]->type_name,effective_type_name_remove) == 0) {
                        type_remove_in = true;
                        break;
                    }
                }
                free(effective_type_name_remove);
                if (type_remove_in == true) {
                    // remove the effective type from the effective against me list
                    removeFromMeAgainstEffectiveList(allTypes[counter_in_types_source],allTypes[counter_of_the_effec_in_types_to_remove]->type_name);
                    printPokemonType(allTypes[counter_in_types_source]);
                    break;
                }else{
                    printf("Type name doesn't exist in the list.\n");
                    break;
                }

            case 6:
                printf("Please enter type name:\n");
                char *source_type_name_temp_2 = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (source_type_name_temp_2 == NULL){
                    free(source_type_name_temp_2);
                    return failure;
                }
                scanf("%s", source_type_name_temp_2);



                char *source_type_name_2 = realloc(source_type_name_temp_2, strlen(source_type_name_temp_2) + 3);
                if(source_type_name_2 == NULL){
                    free(source_type_name_temp_2);
                    printf("Memory Problem");
                    return failure;
                }
                bool flag_source_2 = false;
                int counter_in_types_source_2;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfTypes; h++) {
                    if (strcmp(allTypes[h]->type_name, source_type_name_2) == 0) {
                        counter_in_types_source_2 = h;
                        flag_source_2 = true;
                        break;
                    }
                }

                if (flag_source_2 == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }

                printf("Please enter type name to remove from %s effective against others list:\n", source_type_name_2);
                free(source_type_name_2);
                char *effective_type_name_remove_temp_2 = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (effective_type_name_remove_temp_2 == NULL){
                    free(effective_type_name_remove_temp_2);
                    return failure;
                }

                scanf("%s", effective_type_name_remove_temp_2);
                char *effective_type_name_remove_2 = realloc(effective_type_name_remove_temp_2, strlen(effective_type_name_remove_temp_2) + 3);
                if(effective_type_name_remove_2 == NULL){
                    free(effective_type_name_remove_temp_2);
                    printf("Memory Problem");
                    return failure;
                }
                bool is_remove_2 = false;
                int counter_of_the_effec_in_types_to_remove_2;
                // Find the effective type in the array of allTypes
                for (int t = 0; t < numberOfTypes; t++) {
                    if (strcmp(allTypes[t]->type_name, effective_type_name_remove_2) == 0) {
                        counter_of_the_effec_in_types_to_remove_2 = t;
                        is_remove_2 = true;
                        break;
                    }
                }


                if (is_remove_2 == false) {
                    printf("Type name doesn't exist in the list.\n");
                    break;
                }

                // Check if the effective type to remove is in the effective against me list
                bool type_remove_in_2 = false;

                for (int r = 0; r < allTypes[counter_in_types_source_2]->count_Poke_in_against_others; r++) {
                    if (strcmp(allTypes[counter_in_types_source_2]->effective_against_others[r]->type_name,effective_type_name_remove_2) == 0) {
                        type_remove_in_2 = true;
                        break;
                    }
                }
                free(effective_type_name_remove_2);
                if (type_remove_in_2 == true) {
                    // remove the effective type from the effective against me list
                    removeFromOthersAgainstEffectiveList(allTypes[counter_in_types_source_2],allTypes[counter_of_the_effec_in_types_to_remove_2]->type_name);
                    printPokemonType(allTypes[counter_in_types_source_2]);
                    break;
                }else{
                    printf("Type name doesn't exist in the list.\n");
                    break;
                }

            case 7:
                // Print Pokemon by name
                printf("Please enter Pokemon name:\n");
                char *pokemon_name_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (pokemon_name_temp == NULL){
                    free(pokemon_name_temp);
                    return failure;
                }
                scanf("%s", pokemon_name_temp);

                char *pokemon_name = realloc(pokemon_name_temp, strlen(pokemon_name_temp) + 3);
                if(pokemon_name == NULL){
                    free(pokemon_name_temp);
                    printf("Memory Problem");
                    return failure;
                }
                // Find the Pokemon in the array of Pokemon
                bool pokemon_in = false;
                int counter_in_pokemones;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfPokemons; h++) {
                    if (strcmp(All_pokemons[h]->name, pokemon_name) == 0) {
                        counter_in_pokemones = h;
                        pokemon_in = true;
                        break;
                    }
                }
                free(pokemon_name);

                if (pokemon_in == false) {
                    printf("The Pokemon doesn't exist.\n");
                    break;
                }else{
                    printPokemon(All_pokemons[counter_in_pokemones]);
                    break;
                }


            case 8:
                // Print Pokemons by type
                printf("Please enter type name:\n");
                char *type_name_last_temp = malloc(300 * sizeof(char)); // Allocate memory on the heap
                if (type_name_last_temp == NULL){
                    free(type_name_last_temp);
                    return failure;
                }
                scanf("%s", type_name_last_temp);

                char *type_name_last = realloc(type_name_last_temp, strlen(type_name_last_temp) + 3);
                if(type_name_last == NULL){
                    free(type_name_last_temp);
                    printf("Memory Problem");
                    return failure;
                }
                // Find the Pokemon in the array of Pokemon
                bool type_in_last = false;
                int counter_in_type_last;
                // Find the type in the array of allTypes
                for (int h = 0; h < numberOfTypes; h++) {
                    if (strcmp(allTypes[h]->type_name, type_name_last) == 0) {
                        counter_in_type_last = h;
                        type_in_last = true;
                        break;
                    }
                }
                free(type_name_last);

                if (type_in_last == false) {
                    printf("Type name doesn't exist.\n");
                    break;
                }else{

                    printf("There are %d Pokemons with this type:\n",allTypes[counter_in_type_last]->poke_in_type);
                    for (int poke = 0;poke < numberOfPokemons; poke++) {
                        if(strcmp(All_pokemons[poke]->type->type_name, allTypes[counter_in_type_last]->type_name) == 0){
                            printPokemon(All_pokemons[poke]);
                        }
                    }
                    break;
                }

            case 9:
                // Clean up memory and exit
                for (int i = 0; i < numberOfTypes; i++) {
                    destroyPokemonType(allTypes[i]);
                }
                for (int i = 0; i < numberOfPokemons; i++) {
                    destroyPokemon(All_pokemons[i]);
                }
                printf("All the memory cleaned and the program is safely closed.\n");
                exit(0);

            default:
                continue;
        }
    }
}