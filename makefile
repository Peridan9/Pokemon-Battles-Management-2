prog: LinkedList.o MaxHeap.o BattleByCategory.o Pokemon.o MainSecond.o
	gcc LinkedList.o MaxHeap.o BattleByCategory.o Pokemon.o MainSecond.o -o PokemonsBattles

LinkedList.o: LinkedList.c LinkedList.h
	gcc -c LinkedList.c
	
maxHeap.o: MaxHeap.c MaxHeap.h
	gcc -c MaxHeap.c
	
BattleByCategory.o: BattleByCategory.c BattleByCategory.h LinkedList.h MaxHeap.h
	gcc -c BattleByCategory.c

Pokemon.o: Pokemon.c Pokemon.h
	gcc -c Pokemon.c	
			
MainSecond.o: MainSecond.c BattleByCategory.h Pokemon.h
	gcc -c MainSecond.c

clean: 
	rm -f *.o
