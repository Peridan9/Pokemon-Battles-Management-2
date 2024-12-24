# 🏆 Pokémon Battle Training System ⚔️
This project was developed as part of my Advanced Programming course at Ben-Gurion University. It builds upon the Pokédex system by introducing a Battle Training Camp for Pokémon. This system features advanced data structures, dynamic memory management, and logic to simulate Pokémon battles by types and attributes.

---
## ✨ Features

- 🧬 Pokédex Integration: Import Pokémon and types from configuration files.
- 🗂️ Generic Data Structures: Utilize a generic linked list, max heap, and categorical battle manager for data organization.
- ⚔️ Battle Logic: Simulate battles with type effectiveness and attack attributes.
- 📂 Configuration Support: Load Pokémon and type data seamlessly.
- 💡 Interactive Menu: Engage with a menu for managing and battling Pokémon.
---
## ⚙️ Prerequisites
To run this project, ensure you have the following installed:

- ✅ GCC or any compatible C compiler
- ✅ Valgrind for memory leak testing
---

## 🖍️ Usage Instructions

1. Compile the project using the provided `makefile`:

```bash
make
```

2. Run the program with the required arguments:

```bash
./PokemonsBattles <numberOfTypes> <capacityInType> <configurationFile>
```
- `<numberOfTypes>`: Total Pokémon types to load (e.g., 3).
- `<capacityInType>`: Maximum Pokémon allowed per type (e.g., 20).
- `<configurationFile>`: Path to the configuration file.

3. Use the interactive menu to:

- View Pokémon by type.
- Add or remove Pokémon.
- Simulate Pokémon battles.
- Exit with memory cleanup.
---

## 🛠 File Structure
- `LinkedList.h/c`: Implements a generic linked list.
- `MaxHeap.h/c`: Implements a generic max heap.
- `BattleByCategory.h/c`: Implements the battle training camp logic.
- `Defs.h`: General definitions and utility functions.
- `MainSecond.c`: Main menu logic for user interaction.
---
## 🤾 Example Configuration File
```text
Types  
Fire,Water,Electric,Grass  

Fire effective-against-me:Water  
Fire effective-against-other:Grass,Electric  
Electric effective-against-other:Fire  

Pokemons  
Pikachu,MousePokemon,0.4,6,55,Electric  
Charmander,LizardPokemon,0.6,8.5,52,Fire  
Ponyta,FireHorsePokemon,1.0,30.0,85,Fire  
Squirtle,TinyTurtlePokemon,0.5,9,48,Water  
Psyduck,DuckPokemon,0.8,19.6,52,Water
```
---  
## 🔍 Additional Notes
- Ensure memory management with tools like Valgrind.
- Refer to the project documentation for detailed implementation details.
- Follow configuration file formatting strictly.
Feel free to explore, enhance, and train your Pokémon system! 🎮
