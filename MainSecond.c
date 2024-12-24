/*
 * MainSecond.c
 *
 *  Created on: Dec 21, 2021
 *      Author: ise
 */
#include "Pokemon.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "BattleByCategory.h"

char* pokemonType(element elem){ // move to main
	if(elem == NULL){
		return NULL;
	}
	Poke *tmpoke = ((Poke*)elem);
	return tmpoke->type->name;
}

int biggestattack(element elem1,element elem2, int* elem1attack, int* elem2attack){
	Poke *tmpoke1 = ((Poke*)elem1);
	Poke *tmpoke2 = ((Poke*)elem2);
	int attack;
	int attack1 = tmpoke1->info->attack;
	int attack2 = tmpoke2->info->attack;
	if(searchtype(tmpoke1->type->effective_against_others, tmpoke2->type->name, tmpoke1->type->othercount)!=NULL){
		attack2 = tmpoke2->info->attack - 10;
	}
	else{
		if(searchtype(tmpoke2->type->effective_against_me, tmpoke1->type->name, tmpoke2->type->mecount)){
			attack2 = tmpoke2->info->attack - 10;
		}
	}
	if(searchtype(tmpoke2->type->effective_against_others, tmpoke1->type->name, tmpoke2->type->othercount)!=NULL){
		attack1 = tmpoke1->info->attack - 10;
	}
	else{
		if(searchtype(tmpoke1->type->effective_against_me, tmpoke2->type->name, tmpoke1->type->mecount)){
			attack1 = tmpoke1->info->attack - 10;
		}
	}
	attack = attack2 - attack1;
	if(attack>(*elem2attack - *elem1attack)){
		*elem1attack = attack1;
		*elem2attack = attack2;
	}
	return attack;
}

int main(int argc, char **argv){
	int numberoftypes = atoi(argv[1]);
	int capacity = atoi(argv[2]);
	int types_counter = 0;
	Battle mainbattle = NULL;
	int i;
	Type **listoftypes = (Type**)malloc(numberoftypes*sizeof(Type*));

	void clear(){ // clear function
		destroyBattleByCategory(mainbattle);
		for(i=0;i<numberoftypes;i++){
			freeType(listoftypes[i]);
		}
		free(listoftypes);
		listoftypes=NULL;
		printf("All the memory cleaned and the program is safely closed.\n");
		exit(0);
	}

	if(listoftypes == NULL){
		return 1;
	}
	FILE *text = fopen(argv[3], "r");
	char line[300];
	char* readline;
	char* token;
	int getypes = 0;
	int getpoke = 0;
	while(fgets(line,300,text)){
		readline = strtok(line,"\n\r");
		if(readline == NULL){
			break;
		}
		if(strcmp(readline,"Types")==0){
			getypes=1;
			continue;
		}
		if((strcmp(readline,"Pokemons")==0) && getypes == 1){
			break;
		}
		if(getypes == 1){
			char* categories = (char*)malloc(sizeof(char)*strlen(readline)+1); // need to free at the end
			strcpy(categories,readline);
			mainbattle = createBattleByCategory(capacity, numberoftypes, categories, comparePokemon, CopyPokemon, freePokemon, pokemonType, biggestattack, printPokemon);
			token = strtok(readline, ",");
			while(token!=NULL){
				Error_p newtype = create_type_of_pokemon(listoftypes, token, types_counter);
				if(newtype == 1){
					printf("No memory available.\n");
					clear();
				}
				types_counter++;
				token = strtok(NULL, ",");
			}
			free(categories);
			categories = NULL;
			getypes=0;
			continue;
		}
		if(readline[0] == '\t'){
			readline++;
			token = strtok(readline, " ");
			Type* typeA = searchtype(listoftypes, token, types_counter); // no need for memory check
			while(token != NULL){
				token = strtok(NULL, ":");
				if(strcmp(token,"effective-against-me") == 0){
					token = strtok(NULL, ",");
					while(token != NULL){
						Type * typein = searchtype(listoftypes, token, types_counter);
						Error_p newme = add_to_effective_me(listoftypes, typeA, typein, types_counter);
						if(newme == 1){
							printf("No memory available.\n");
							clear();
						}
						token = strtok(NULL, ",");
					}
					break;
				}
				if(strcmp(token,"effective-against-other") == 0){
					token = strtok(NULL, ",");
					while(token != NULL){
						Type *typein = searchtype(listoftypes, token, types_counter);
						Error_p newother = add_to_effective_others(listoftypes, typeA, typein, types_counter);
						if(newother == 1){
							printf("No memory available.\n");
							clear();
						}
						token = strtok(NULL, ",");
					}
					break;
				}
			}
			continue;
		}
		if(strcmp(readline,"Pokemons") == 0){
			getpoke=1;
			continue;
		}
		if(getpoke == 1){
			token = strtok(readline, ",");
			char* pokename = token;
			token = strtok(NULL, ",");
			char* pokespecies = token;
			token = strtok(NULL, ",");
			double pokeheight = atof(token);
			token = strtok(NULL, ",");
			double pokeweight = atof(token);
			token = strtok(NULL, ",");
			int pokeattack = atoi(token);
			token = strtok(NULL, ",");
			Type* pointer = searchtype(listoftypes, token, types_counter);
			Poke* newpoke = create_pokemon(pokename, pokespecies, pokeheight, pokeweight, pokeattack, pointer);
			if(newpoke == NULL){
				printf("No memory available.\n");
				clear();
			}
			insertObject(mainbattle, newpoke);
			newpoke->type->numberofpokemons++;
			freePokemon(newpoke);
			continue;
		}
	}
	fclose(text);

	char choise = 1;
	char buffer[300];
	char pokename[300];
	char pokespecies[300];
	Type* poketype=NULL;
	double pokeheight=0;
	double pokeweight=0;
	int pokeattack=0;


	while(1)
	{
		printf("Please choose one of the following numbers:\n");
		printf("1 : Print all Pokemons by types\n");
		printf("2 : Print all Pokemons types\n");
		printf("3 : Insert Pokemon to battles training camp\n");
		printf("4 : Remove strongest Pokemon by type\n");
		printf("5 : Fight\n");
		printf("6 : Exit\n");
		scanf(" %c", &choise);
		getchar();

		switch(choise)
		{
		case '1':
			displayObjectsByCategories(mainbattle);
			break;

		case '2':
			for(i=0;i<numberoftypes;i++){
				print_pokemon_type(listoftypes[i]);

			}
			i = 0;


			break;

		case '3':
			printf("Please enter Pokemon type name:\n");
			scanf("%s",buffer);
			poketype = searchtype(listoftypes, buffer, types_counter);
			if(poketype == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			if(poketype->numberofpokemons >= capacity){
				printf("Type at full capacity.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s",pokename);
			printf("Please enter Pokemon species:\n");
			scanf("%s",pokespecies);
			printf("Please enter Pokemon height:\n");
			scanf("%lf",&pokeheight);
			printf("Please enter Pokemon weight:\n");
			scanf("%lf",&pokeweight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d",&pokeattack);
			Poke* newpoke = create_pokemon(pokename, pokespecies, pokeheight, pokeweight, pokeattack, poketype);
			insertObject(mainbattle,newpoke);
			printf("The Pokemon was successfully added.\n");
			newpoke->type->numberofpokemons++;
			printPokemon(newpoke);
			freePokemon(newpoke);
			newpoke = NULL;
			break;

		case '4':
			printf("Please enter type name:\n");
			scanf("%s",buffer);
			poketype = searchtype(listoftypes, buffer, types_counter);
			if(poketype == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			if(poketype->numberofpokemons < 1){
				printf("There is no Pokemon to remove.\n");
				break;
			}
			printf("The strongest Pokemon was removed:\n");
			printPokemon(removeMaxByCategory(mainbattle, poketype->name));
			poketype->numberofpokemons--;

			break;
		case '5':
			printf("Please enter Pokemon type name:\n");
			scanf("%s",buffer);
			poketype = searchtype(listoftypes, buffer, types_counter);
			if(poketype == NULL){
				printf("Type name doesn't exist.\n");
				break;
			}
			printf("Please enter Pokemon name:\n");
			scanf("%s",pokename);
			printf("Please enter Pokemon species:\n");
			scanf("%s",pokespecies);
			printf("Please enter Pokemon height:\n");
			scanf("%lf",&pokeheight);
			printf("Please enter Pokemon weight:\n");
			scanf("%lf",&pokeweight);
			printf("Please enter Pokemon attack:\n");
			scanf("%d",&pokeattack);
			Poke* newpoke1 = create_pokemon(pokename, pokespecies, pokeheight, pokeweight, pokeattack, poketype);
			element max = fight(mainbattle, newpoke1);
			printf("You choose to fight with:\n");
			printPokemon(newpoke1);
			if(max == NULL){
				printf("There are no Pokemons to fight against you.\n");
				break;
			}
			int* attack1 = (int*)malloc(sizeof(int));
			if(attack1 == NULL){
				printf("No memory available.\n");
				clear();
			}
			int* attack2 = (int*)malloc(sizeof(int));
			if(attack2 == NULL){
				printf("No memory available.\n");
				clear();
			}
			*attack1 = 999;
			*attack2 = 0;
			int result = biggestattack(newpoke1, max, attack1, attack2);
			printf("The final battle between:\n");
			printPokemon(newpoke1);
			printf("In this battle his attack is :%d\n\n", *attack1);
			printf("against ");
			printPokemon(max);
			printf("In this battle his attack is :%d\n\n", *attack2);
			if(result == 0){
				printf("IT IS A DRAW.\n");
				freePokemon(newpoke1);
				newpoke1 = NULL;
				free(attack1);
				free(attack2);
				attack1 = NULL;
				attack2 = NULL;
				break;
			}
			if(result < 0){
				printf("THE WINNER IS:\n");
				printPokemon(newpoke1);
			}
			else{
				printf("THE WINNER IS:\n");
				printPokemon(max);
			}
			freePokemon(newpoke1);
			free(attack1);
			free(attack2);
			break;

		case '6':
			clear();
		default:
			printf("Please choose a valid number.\n");
		}
	}
	return 1;

	return 0;
}
