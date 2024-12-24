
#include <stdio.h>
#include "Pokemon.h"
#include <stdlib.h>
#include "Defs.h"
#include <string.h>

Type* newtype;
char* newname, newspecies;
Poke* newpoke = NULL;
Binfo* newbio;

Poke* create_pokemon(char* name, char* species, double height, double weight, int attack, Type *type){
	Poke* newpoke = (Poke*)malloc(sizeof(Poke));
	if(newpoke == NULL) // fail with memeory
		return NULL;
	newpoke->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if(newpoke->name == NULL){ // fail with memory
		free(newpoke->name);
		return NULL;
	}
	strcpy(newpoke->name,name);
	newpoke->species = (char*)malloc(sizeof(char)*(strlen(species) + 1));
	if(newpoke->species == NULL){ // fail with memory
		free(newpoke->name);
		free(newpoke);
		return NULL;
	}
	strcpy(newpoke->species,species);
	newbio = create_bioinfo_of_pokemon(weight,height,attack );
	newpoke->info = newbio;
	newpoke->type = type;
	return newpoke;
}



Error_p create_type_of_pokemon(Type** list, char* name, int counter){
	Type* newtype = (Type*)malloc(sizeof(Type));
	if(newtype == NULL)
		return MEMORY_PROBLEM;
	newtype->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
	if (newtype->name == NULL){
		free(newtype);
		newtype=NULL;
		return MEMORY_PROBLEM;
	}
	strcpy(newtype->name,name);
	newtype->numberofpokemons=0;
	newtype->effective_against_me = NULL;
	newtype->effective_against_others = NULL;
	newtype->othercount=0;
	newtype->mecount=0;
	list[counter] = newtype;
	return SUCCESS;
}
Type* searchtype(Type** list, char* name, int counter){
	int i = 0;
	for(i=0;i<counter;i++){
		if(strcmp(name,list[i]->name) == 0)
			return list[i];
	}
//	printf("Type name doesn't exist.");
	return NULL;
}
Poke* searchpoke(Poke** list, char* name, int counter){
	int i = 0;
	for(i=0;i<counter;i++){
		if(strcmp(name,list[i]->name)==0)
			return list[i];
	}
	return NULL;
}
Error_p add_to_effective_me(Type** list, Type *typeA, Type *typein, int counter){
	if(typeA->mecount == 0){ // empty list
		typeA->effective_against_me = (Type**)malloc(sizeof(Type*));
		if(typeA->effective_against_me == NULL)
			return MEMORY_PROBLEM;
		typeA->effective_against_me[0] = typein;
		typeA->mecount++;
		return SUCCESS;
	}
	typeA->mecount++;
	typeA->effective_against_me = (Type**)realloc(typeA->effective_against_me,(typeA->mecount)*sizeof(Type*));
	if(typeA->effective_against_me == NULL)
		return MEMORY_PROBLEM;
	typeA->effective_against_me[typeA->mecount - 1] = typein;
	return SUCCESS;
}

Error_p add_to_effective_others(Type** list, Type *typeA, Type *typein, int counter){
	if(typeA->effective_against_others == NULL){
		typeA->effective_against_others = (Type**)malloc(sizeof(Type*));
		if(typeA->effective_against_others == NULL)
			return MEMORY_PROBLEM;
		typeA->effective_against_others[0] = typein;
		typeA->othercount++;
		return SUCCESS;
	}
	typeA->othercount++;
	typeA->effective_against_others = (Type**)realloc(typeA->effective_against_others,(typeA->othercount)*sizeof(Type*));
	if(typeA->effective_against_others == NULL)
		return MEMORY_PROBLEM;
	typeA->effective_against_others[typeA->othercount - 1] = typein;
	return SUCCESS;
}

Error_p remove_from_effective_me(Type** list, Type* typeA, char *typeB, int counter){
	if(typeA->mecount == 0)
		return EMPTY_LIST;
	int i = 0;
	int place = 0;
	for(i=0;i< typeA->mecount; i++){
		if(strcmp(typeB,typeA->effective_against_me[i]->name) == 0)
			place=i;
	}
	for(i=place; i< typeA->mecount; i++){ //moving all the types need one block back
		typeA->effective_against_me[i] = typeA->effective_against_me[i+1];
	}
	typeA->mecount--;
	typeA->effective_against_me = (Type**)realloc(typeA->effective_against_me,(typeA->mecount)*sizeof(Type*));
	if(typeA->effective_against_me == NULL){
		if(place == 0)
			return EMPTY_LIST;
		return MEMORY_PROBLEM;
	}

	return SUCCESS;
}

Error_p remove_from_effective_others(Type** list, Type* typeA, char *typeB, int counter){
	if(typeA->effective_against_others == NULL)
		return EMPTY_LIST;
	int i = 0;
	int place = 0;
	for(i=0;i< typeA->othercount; i++){
		if(strcmp(typeB,typeA->effective_against_others[i]->name) == 0)
			place=i;
	}
	for(i=place; i< typeA->othercount; i++){ //moving all the types need one block back
		typeA->effective_against_others[i] = typeA->effective_against_others[i+1];
	}
	typeA->othercount--;
	typeA->effective_against_others = (Type**)realloc(typeA->effective_against_others,(typeA->othercount)*sizeof(Type*));
	if(typeA->effective_against_others == NULL){
		if(place == 0)
			return EMPTY_LIST;
		return MEMORY_PROBLEM;
	}
			// send to clear function need to add later.
	return SUCCESS;
}

Binfo* create_bioinfo_of_pokemon( double weight, double height, int attack ){
	Binfo *newbio = (Binfo*)malloc(sizeof(Binfo));
	if(newbio == NULL)
		return NULL;
	newbio->attack=attack;
	newbio->height=height;
	newbio->weight=weight;
	return newbio;

}

Error_p print_pokemon_info(Poke* poke){
	printf("%s :\n",poke->name);
	printf("%s, %s Type.\n",poke->species,poke->type->name);
	printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", poke->info->height, poke->info->weight, poke->info->attack);
	return SUCCESS;
}

Error_p print_pokemon_type(Type* type){
	printf("Type %s -- %d pokemons\n", type->name, type->numberofpokemons);
	if(type->effective_against_me != NULL){ // check if there is info inside
		printf("\tThese types are super-effective against %s:%s", type->name, type->effective_against_me[0]->name);
		int i = 1;
		for(i = 1;i<type->mecount;i++){
			printf(" ,%s",type->effective_against_me[i]->name);
		}
		printf("\n");
	}
	if(type->effective_against_others != NULL){
			printf("\t%s moves are super-effective against:%s", type->name, type->effective_against_others[0]->name);
			int i = 1;
			for(i = 1;i<type->othercount;i++){
				printf(" ,%s",type->effective_against_others[i]->name);
			}
			printf("\n\n");
			return SUCCESS;
		}
	printf("\n");
	return SUCCESS;
}

Error_p clearbio(Binfo* poketoclear){
	free(poketoclear);
	return CLEARED;
}

element CopyType(element elem){
	if(elem == NULL){
		return NULL;
	}
	Type *newtype = (Type*)malloc(sizeof(Type));
	*newtype = *(Type*)elem;
	if(newtype!=NULL){
		return newtype;
	}
	return NULL;
}

status freeType(element elem){
	Type *tmptype = ((Type*)elem);
	free(tmptype->effective_against_me);
	free(tmptype->effective_against_others);
	free(tmptype->name);
	tmptype->effective_against_me=NULL;
	tmptype->effective_against_others=NULL;
	tmptype->name=NULL;
	free(tmptype);
	tmptype=NULL;
	return success;
}

status printType(element elem){
	Type *tmptype = ((Type*)elem);
	printf("Type %s -- %d pokemons\n", tmptype->name, tmptype->numberofpokemons);
	if(tmptype->effective_against_me != NULL){ // check if there is info inside
		printf("\tThese types are super-effective against %s:%s", tmptype->name, tmptype->effective_against_me[0]->name);
		int i = 1;
		for(i = 1;i<tmptype->mecount;i++){
			printf(" ,%s",tmptype->effective_against_me[i]->name);
		}
		printf("\n");
	}
	if(tmptype->effective_against_others != NULL){
			printf("\t%s moves are super-effective against:%s", tmptype->name, tmptype->effective_against_others[0]->name);
			int i = 1;
			for(i = 1;i<tmptype->othercount;i++){
				printf(" ,%s",tmptype->effective_against_others[i]->name);
			}
			printf("\n\n");
			return success;
		}
	printf("\n");
	return success;
}

int compareType(element elem1,element elem2){
	Type *tmptype1 = ((Type*)elem1);
	Type *tmptype2 = ((Type*)elem2);
	if(strcmp(tmptype1->name,tmptype2->name) == 0){
		return 0;
	}
	return 1;
}
int comparePokemon(element elem1,element elem2){
	Poke *tmpoke1 = ((Poke*)elem1);
	Poke *tmpoke2 = ((Poke*)elem2);
	if(tmpoke1->info->attack == tmpoke2->info->attack){
		return 0;
	}
	if(tmpoke1->info->attack > tmpoke2->info->attack){
		return 1;
	}
	return -1;
}
element CopyPokemon(element elem){ // need to fix this
	if(elem == NULL){
		return NULL;
	}
	Poke *newpoke = (Poke*)malloc(sizeof(Poke));
	Poke *original = ((Poke*)elem);
	newpoke->name = (char*)malloc(sizeof(strlen(original->name)+1));
	if(newpoke->name == NULL){
		return NULL;
	}
	strcpy(newpoke->name,original->name);
	newpoke->species = (char*)malloc(sizeof(strlen(original->species)+1));
	if(newpoke->species == NULL){
		return NULL;
	}
	strcpy(newpoke->species,original->species);
	newpoke->type = original->type;
	newpoke->info = (Binfo*)malloc(sizeof(Binfo));
	if(newpoke->info == NULL){
		return NULL;
	}
	newpoke->info->attack = original->info->attack;
	newpoke->info->height = original->info->height;
	newpoke->info->weight = original->info->weight;
	return newpoke;
}
status freePokemon(element elem){
	Poke *tmpoke = ((Poke*)elem);
	free(tmpoke->name);
	free(tmpoke->species);
	clearbio(tmpoke->info);
	free(tmpoke);
	tmpoke=NULL;
	return success;
}
status printPokemon(element elem){
	Poke *tmpoke = ((Poke*)elem);
	printf("%s :\n",tmpoke->name);
		printf("%s, %s Type.\n",tmpoke->species,tmpoke->type->name);
		printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", tmpoke->info->height, tmpoke->info->weight, tmpoke->info->attack);
		return success;
}

//char* pokemonType(element elem){ // move to main
//	if(elem == NULL){
//		return NULL;
//	}
//	Poke *tmpoke = ((Poke*)elem);
//	return tmpoke->type->name;
//}
//
//int pokemonAttack(element elem){ // move to main
//	if(elem == NULL){
//		return -1;
//	}
//	Poke *tmpoke = ((Poke*)elem);
//	return tmpoke->info->attack;
//}
