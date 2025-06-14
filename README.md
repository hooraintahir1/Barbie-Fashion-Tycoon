# 🎀 Barbie-Fashion-Tycoon
A simulation game built using Object-Oriented Programming concepts where players manage a fashion boutique with Barbie as the lead designer. Design outfits, handle customer orders, organize fashion shows, and grow your fashion empire.

# Architecture
## Diagram
![High-Level Diagram](https://github.com/hooraintahir1/Barbie-Fashion-Tycoon/blob/main/docs/Project.drawio.svg)

## 👗 Game Concept
You start with a fixed amount of money and a list of fashionable outfits to choose from. Select outfits by name, purchase them, and store them in your inventory. Enter fashion shows to display your outfits—more expensive outfits earn more points and money. As you gain fame and funds, you unlock new levels with premium fashion collections.

## ✨ Core Features
- Purchase stylish outfits with in-game currency
- Store and manage outfits using an inventory system
- Compete in fashion shows to earn rewards
- Progress through levels and unlock new outfits
- Demonstrates real OOP concepts: classes, objects, encapsulation, and inheritance

## OOP Classes
| Classes   | Purpose |
| -------   | ------- |
|**Outfits**| Defines outfit properties like name, price, and score|
|**Inventory**| Stores and manages outfits selected by the player, including total score computation and category checks |
|**Shoes**| Represents a shoe item with name, style category, image, and bonus value.|
|**GameManager**| Controls game logic and flow|
|**FashionShow**| Reveals the personality type of the player with the description.|
|**MainScreen**| Handles the game's welcome screen UI, logo, background, and Play button interaction.|
|**Play**| Maintains the player’s current game state, including inventory, money, score, and level progression.|
|**FinalFashionShow**| The ultimate challenge level; evaluates full outfit-shoe combinations for style synergy and bonuses.|
|**Screen1, Screen2, Screen4**| Represent different game levels/screens with unique rules and interaction logic (e.g., selecting outfits or shoes).|
|**OutfitCatalog**| Provides the list of all purchasable outfits in the game.|
|**ShoeCatalog**| Provides the list of available shoes for selection in the shoe selection screen.|

## UML
![UML](https://github.com/hooraintahir1/Barbie-Fashion-Tycoon/blob/main/docs/uml.svg)

## 👠 How To Play
1. Click Start to begin your fashion journey!
2. Explore the Outfit Catalog and purchase outfits by name.
3. Your purchases are saved in your personal Inventory.
4. Enter Fashion Shows to showcase your style and earn money.

## ⭐ Level 1
1) Browse the Outfit Catalog and select any 1 outfit you like.
2) Your selected outfit reveals your Fashion Personality.
3) Watch the fashion show to see how your choice reflects your style identity.

## 🌟 Level 2
1) Players must select exactly 2 outfits to continue.
2) After selecting outfits, players must choose exactly 2 shoes.
3) Each shoe has a matching outfit type.
4) The first selected outfit is matched with the first selected shoe, and the second with the second.
5) If an outfit matches its paired shoe, the player earns bonus points.
6) If they don't match, the player receives no bonus.

## Technologies Used
- C++
- Object-Oriented Design
- Console I/O (GUI version)
- Flowchart created with [draw.io](https://draw.io)
- Raylib

