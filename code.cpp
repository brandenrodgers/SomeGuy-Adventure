#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <functional>
#include <map>
#include <stdlib.h> 
#include <map>
#include <typeinfo>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <vector>
using namespace std;


//VARIABLES FOR LEVELING AND TRAINING
//////////////////////////////////////////////////////////////////////////////
bool fightingIntro = true;    //To learn how to fight (true = play it)
bool lvl2Scene = true;         //cut scene at level 2
bool lvl2Scene2 = true;        //cut scene at level 2 and a half
bool lvl3Scene = true;          //cut scene at level 3
bool playTownScene = true;
int fullHealth = 25;          //maximum health (attained through sleep)
int fullWater = 5;             //Max water  (attained by going home)
double experiencePoints = 0;      //Experience points for leveling up

//TYPE CONVERSIONS
//////////////////////////////////////////////////////////////////////////////
//convert int to string 
string intToString(int i){
    string result;
    stringstream ss;  
    
    ss.str(string());
    ss << i;
    result = ss.str(); 
    
    return result;
}

//convert int to string 
string doubleToString(double d){
    string result;
    stringstream ss;  
    
    ss.str(string());
    ss << d;
    result = ss.str(); 
    
    return result;
}

//Convert string to int
int stringToInt(string s){
    int result;
    
    istringstream buffer(s);
    buffer >> result;
    
    return result;
}

string uppercase(const string& s){
  string result(s.length(), '\0');
  transform(
    s.begin(),
    s.end(),
    result.begin(),
    ptr_fun <int, int> (toupper)
    );
  return result;
  }
  
//LOADING BARS AND ANIMATIONS
/////////////////////////////////////////////////////////////////////////////


//Sleep Animation
int sleep(){
    cout << "\nZ\n\n";
           Sleep(500);
           cout << "ZZZ\n\n";
           Sleep(500);
           cout << "ZZZZZZ\n\n";
           Sleep(500);
           cout << "ZZZZZZZZ\n\n";
           Sleep(500);
           cout << "ZZZZZZ\n\n";
           Sleep(500);
           cout << "ZZZ\n\n";
           Sleep(500);
           cout << "Z\n\n";
           Sleep(500);
           cout << "A good night's sleep has returned your health\n\n"
                   "Press ENTER to continue...\n";
           cin.ignore(numeric_limits<streamsize>::max(), '\n');
           return 0;
}

//The coordinates of the string 
void gotoxy (int x, int y){
    COORD coord; // coordinates
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // moves to the coordinates

}

//Retrieves the location of the cursor 
int getCursorY() {
int y;
CONSOLE_SCREEN_BUFFER_INFO csbi;

if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
    y = csbi.dwCursorPosition.Y;
    }
    return y;
}

//Loading bar 
string loadingBar(){
int place = 1;
int replace = 0;
string loading = "IIIIIIIIII";               //initial string
while (true){
      gotoxy(0, getCursorY());               // move to where we want to output
      loading = loading.replace(replace, 1, "*"); // Update the string
      cout << loading;                       // overwrite the current output

      Sleep(250);
      gotoxy(place, getCursorY());           // move back to the start of output
      Sleep(250);
      place = place + 1;                     //Update location within string
      replace = replace + 1;                 //to replace elements in string
      if (place > 10){
                cout << " All Done!\n";
                break;
                }
}
return "";
}

//Animation for selling items
string sellAnimation(){
int startPlace = 1;          // where it starts (and ends)
int endPlace = 14;           //where it changes direction
int insertSpot = 1;         // where to insert the string
bool direction = true;      //true = right
string transaction = "O             O";
while (true){
      gotoxy(0, getCursorY());           // move to where we want to output
      
      if (insertSpot == endPlace){      // Determines if the cursor has made it to 
        direction = false;              //its destination yet
        }
        
      if (direction){
      transaction = transaction.insert(insertSpot, "#");  //going right
      }
      else {
      transaction = transaction.insert(insertSpot, "$");  //going left
      }
      
      cout << transaction; // overwrite the current output

      Sleep(75);
      gotoxy(insertSpot, getCursorY()); // move back to the start of output
      Sleep(75);

      //check to see if done. Figure out which element to erase if not done
      if ((insertSpot == startPlace) && (!direction)){ //if done
           break;
           }
      //erase # because going right
      else if (direction){
           insertSpot = insertSpot + 1; 
           transaction.erase(transaction.find("#"), 1);
           }
      //erase $ because going left
      else {                                             
           insertSpot = insertSpot - 1;
           transaction.erase(transaction.find("$"), 1);
           }
}
return "  Thank you!";
}

//Animation for buying items
string buyAnimation(){
int startPlace = 1;          // where it starts (and ends)
int endPlace = 14;           //where it changes direction
int insertSpot = 1;         // where to insert the string
bool direction = true;      //true = right
string transaction = "O             O";
while (true){
      gotoxy(0, getCursorY());           // move to where we want to output
      
      if (insertSpot == endPlace){      // Determines if the cursor has made it to 
        direction = false;              //its destination yet
        }
        
      if (direction){
      transaction = transaction.insert(insertSpot, "$");  //going right
      }
      else {
      transaction = transaction.insert(insertSpot, "#");  //going left
      }
      
      cout << transaction; // overwrite the current output

      Sleep(75);
      gotoxy(insertSpot, getCursorY()); // move back to the start of output
      Sleep(75);

      //check to see if done. Figure out which element to erase if not done
      if ((insertSpot == startPlace) && (!direction)){ //if done
           break;
           }
      //erase # because going right
      else if (direction){
           insertSpot = insertSpot + 1; 
           transaction.erase(transaction.find("$"), 1);
           }
      //erase $ because going left
      else {                                             
           insertSpot = insertSpot - 1;
           transaction.erase(transaction.find("#"), 1);
           }
}
return "  Thank you!";
}


//Animation for fighting
string fightAnimation(int g, int e){
int end = 10;           //where it ends
int insertGuy = 0;
string guyImage;
string eErase;
string enemyImage;
int insertEnemy = 21;
bool defense = false;
bool trick = false;

//Determine guy image 
if (g == 1){
  guyImage = "O-";
  }
else if (g == 2){
  guyImage = "O)";
  defense = true; 
  }
else {
  guyImage = "_";
  trick = true;
  }  

//Determine enemy image 
//and what to erase 
if (e == 1){
  enemyImage = "-O";
  eErase = "-";
  }
else if (e == 2){
  enemyImage = "(O";
  eErase = "("; 
  defense = true;
  }
else {
  enemyImage = "_";
  eErase = "_";
  trick = true;
  } 
  
string fight = "                        ";
fight = fight.insert(insertGuy, guyImage);
fight = fight.insert(insertEnemy, enemyImage);

while (true){
      
      gotoxy(0, getCursorY());      // move to where we want to output
      
       cout << fight;               // overwrite the current output

      Sleep(30);
      gotoxy(insertGuy, getCursorY()); // move back to the start of output
      Sleep(30);

      //Setting endpoints for method to terminate
      //If both defend
      if ((guyImage == "O)") && (enemyImage == "(O") && (defense)){
           Sleep(1000);
           break;
           }
      //If player defends and enemy attacks
      else if ((guyImage == "O)") && (enemyImage == "-O") && (defense)){
           end = 2;
           defense = false;
           }
      //If player attacks and enemy defends
      else if ((guyImage == "O-") && (enemyImage == "(O") && (defense)){
           end = 20;
           defense = false;
           }
      //If player Tricks and enemy defends
      else if ((guyImage == "_") && (enemyImage == "(O") && (trick)){
           end = 21;
           trick = false;
           }
      //If player defends and enemy tricks
      else if ((guyImage == "O)") && (enemyImage == "_") && (trick)){
           end = 1;
           trick = false;
           }
       //Insertion and Deletion
      //if at end and player did not use trick
      else if (((insertGuy == end) || (insertEnemy == end)) && (guyImage != "_")){
           break;
           }
      //if at end and player used trick
      else if ((insertGuy == end) && (guyImage == "_")){
           break;
           }
      //if player defends and enemy attacks
      else if ((guyImage == "O)") && (enemyImage == "-O")){
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find(eErase), 2);
           fight = fight.insert(insertEnemy, enemyImage);
           }
      //If plyer attacks and enemy defends
      else if ((guyImage == "O-") && (enemyImage == "(O")){
           insertGuy = insertGuy + 1;
           fight.erase(fight.find("O"), 2);
           fight = fight.insert(insertGuy - 1, guyImage);
           }
      //If player tricks and enemy defends
      else if ((guyImage == "_") && (enemyImage == "(O")){
           insertGuy = insertGuy + 1;
           fight.erase(fight.find("_"), 1);
           if (insertGuy == end) {
              guyImage = "O";
              }
           fight = fight.insert(insertGuy, guyImage);
           }
      //If plyer defends and enemy tricks
      else if ((guyImage == "O)") && (enemyImage == "_")){
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find(eErase), 1);
           if (insertEnemy == end) {
              enemyImage = "O";
              }
           fight = fight.insert(insertEnemy, enemyImage);
           }
      //If player tricks and enemy attacks
      else if ((guyImage == "_") && (enemyImage == "-O")){
           insertGuy = insertGuy + 1;
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find("_"), 1);
           fight.erase(fight.find(eErase), 2);
           if (insertGuy == end) {
              guyImage = "O";
              }
           fight = fight.insert(insertGuy, guyImage);
           fight = fight.insert(insertEnemy, enemyImage);
           }
      //If player tricks and enemy tricks
      else if ((guyImage == "_") && (enemyImage == "_")){
           insertGuy = insertGuy + 1; 
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find("_"), 1);
           fight.erase(fight.find(eErase), 1);
           if (insertGuy == end) {
              guyImage = "O";
              enemyImage = "O";
              }
           fight = fight.insert(insertGuy, guyImage);
           fight = fight.insert(insertEnemy, enemyImage);
           }
      //If player attacks and enemy tricks
      else if ((guyImage == "O-") && (enemyImage == "_")){
           insertGuy = insertGuy + 1;
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find("O"), 2);
           fight.erase(fight.find(eErase), 1);
           if (insertGuy == end) {
              enemyImage = "O";
              }
           fight = fight.insert(insertGuy, guyImage);
           fight = fight.insert(insertEnemy + 1, enemyImage);
           
           }
      //If both attack
      else {
           insertGuy = insertGuy + 1; 
           insertEnemy = insertEnemy - 1;
           fight.erase(fight.find("O"), 2);
           fight.erase(fight.find(eErase), 2);
           fight = fight.insert(insertGuy, guyImage);
           fight = fight.insert(insertEnemy + 1, enemyImage);
           }
}
return "\n";
}


//CLASSES
/////////////////////////////////////////////////////////////////////////////
//Weapon Class
//Weapons are weilded by the character
class Weapon {
      public:
      string name;
      int damage, condition, maxCond, wquantity;
      

      Weapon(string, int, int, int, int);
};
//Constructor for Weapon     
Weapon::Weapon(string n, int d, int c, int m, int q){
     name = n;
     damage = d;
     condition = c;
     maxCond = m;
     wquantity = q;
}


//Item Class
//Items are held in the inventory
class Item {
      public:
      string name;
      int price, quantity;
      
      
      Item(string, int, int);
};
//Item Constructor
Item::Item(string n, int p, int q){
      name = n;
      price = p;
      quantity = q;
}
                  

//Main Character Class
class Guy {
      public:
      string name;
      Weapon weapon;
      int health, gold, water, level;
   
      Guy(string, Weapon, int, int, int, int);
};
//Constructor for main character      
Guy::Guy(string s, Weapon w, int h, int g, int wa, int l):weapon("stick", 5, 50, 50, 1){
     name = s;
     weapon = w;
     health = h;
     gold = g;
     water = wa;
     level = l;
}


//Enemy Class
class Enemy {
      public:
      string name;
      int health, damage;
      Item item;
      
      Enemy(string, int, int, Item);
};
//Constructor for Enemy
Enemy::Enemy(string n, int h, int d, Item i):item("temp", 0, 0){ 
       name = n;
       health = h;
       damage = d;
       item = i;
}

//Instruction Class
class Instruction {
      public:
      string name;
      string description;
      string type;
      string special;
      vector<Item> parts;
      
      Instruction(string, string, string, string, vector<Item>);
};
//Constructor for Instruction
Instruction::Instruction(string n, string d, string t, string s, vector<Item> p){ 
       name = n;
       description = d;
       type = t;
       special = s;
       parts = p;
}
    
//WEAPONS (name, damage, condition, maxCondition)
////////////////////////////////////////////////////////////
//Basic starter weapon. Pick one up when weapon breaks
Weapon stick("stick", 5, 50, 50, 1);

//Attainable weapons 
Weapon woodSpear("wooden spear", 8, 100, 100, 1);
Weapon woodSword("wooden sword", 15, 25, 25, 1);
Weapon ironSword("Iron Sword", 15, 50, 50, 1);


//ITEMS (name, price, quantity)
////////////////////////////////////////////////////////////
//some have higher quantity for better item drops 
Item pelt("pelt", 10, 1);
Item pelt5("pelt", 10, 5);
Item claw("claw", 5, 1);
Item wood("wood", 2, 1);
Item scale("scale", 4, 1);

//make sure each item in this array has quantity 1
//so Buy in the shop works the right way
Item storeItems [] = {pelt, claw, wood, scale};


//SAMPLE ENEMIES(name, health, damage, item)
////////////////////////////////////////////////////////////////////////

Enemy wolf("wolf", 10, 5, claw);
Enemy bear("bear", 15, 10, pelt5);
Enemy boar("boar", 15, 3, pelt);
Enemy snake("snake", 5, 5, scale);
Enemy lizard("lizard", 10, 8, scale);

Enemy enemies [] = {wolf, bear, boar, snake, lizard};


//Sample Instructions 
///////////////////////////////////////////////////////////////////////////////

//Leather Armor
Item laa[2] = { pelt5, claw };
vector<Item> lav(&laa[0], &laa[0]+2);
Instruction leatherArmor("Leather Armor", "basic armor crafted from pelts", "armor", "15", lav);

//scale Armor
Item saa[3] = { pelt5, claw, scale };
vector<Item> sav(&saa[0], &saa[0]+3);
Instruction scaleArmor("Scale Armor", "Scale exterior for max protection", "armor", "25", sav);

//Wood Club
Item wca[3] = { pelt, claw, wood };
vector<Item> wcv(&wca[0], &wca[0]+3);
Instruction woodClub("Wood Club", "Spiked wooden club", "weapon", "25/100", wcv);

//iron sword
Item isa[3] = { pelt, claw, scale };
vector<Item> isv(&isa[0], &isa[0]+3);
Instruction ironSwordI("Iron Sword", "Strong, sharp iron blade", "weapon", "30/100", isv);

//leather canteen
Item lca[2] = { pelt5, scale };
vector<Item> lcv(&lca[0], &lca[0]+2);
Instruction leatherCanteen("Leather Canteen", "Leather Canteen to hold water", "supplies", "5", lcv);

//iron canteen
Item ica[2] = { wood, scale };
vector<Item> icv(&ica[0], &ica[0]+2);
Instruction ironCanteen("Iron Canteen", "Iron Canteen to hold more water", "supplies", "10", icv);

Instruction instructionList[] = {leatherArmor, leatherCanteen, woodClub, scaleArmor};

//INVENTORY AND WEAPON MAPS
/////////////////////////////////////////////////////////////////////// 
map<string, Weapon> weapons;
map<string, Item> inv;
map<string, Instruction> instructions;


 //Adds an item to the inventory
//If item does not already exist: adds the item
//If the item does already exist: updates the quantity
//                                of that item
void addToInv(Item i){
pair<map<string,Item>::iterator,bool> ret;
ret = inv.insert(pair<string, Item>(i.name, i));
if (ret.second==false) {
    map<string, Item>::iterator it = inv.find(i.name); 
if (it != inv.end())
    it->second.quantity = it->second.quantity + i.quantity;
  } 
} 

//Adds a weapon to weapons
//If weapon does not already exist: adds the weapon
//If the weapon does already exist: updates the quantity
//                                  of that weapon
void addToWeapons(Weapon w){
pair<map<string,Weapon>::iterator,bool> ret;
ret = weapons.insert(pair<string, Weapon>(w.name, w));
if (ret.second==false) {
    map<string, Weapon>::iterator it = weapons.find(w.name); 
if (it != weapons.end())
    it->second.wquantity = it->second.wquantity + 1;
  } 
}
  

//Updates the inventory
//If item quantity is zero, then it removes the item from the 
// inventory map
void updateInv(){
typedef map<string, Item>::iterator Item; //iterator
for(Item iterator = inv.begin(); iterator != inv.end(); iterator++) {
    if(iterator->second.quantity <= 0){
    inv.erase(iterator->first);
    }
}
} 

//Updates weapons
//If weapon quantity is zero, then it removes the weapon from the 
// weapons map
void updateWeapons(){
typedef map<string, Weapon>::iterator Weapon; //iterator
for(Weapon iterator = weapons.begin(); iterator != weapons.end(); iterator++) {
    if(iterator->second.wquantity <= 0){
    weapons.erase(iterator->second.name);
    break;
    }
}
}

//Updates the quantity of a specific item in the 
//Inventory after a sale is made
void sellInv(Item i, int quant){
     inv.find(i.name)->second.quantity = inv.find(i.name)->second.quantity - quant;
}

//Updates the quantity of a specific weapon in
//weapons after it is equipped
void removeWeapon(Weapon w){
     weapons.find(w.name)->second.wquantity = weapons.find(w.name)->second.wquantity - 1;
}

//Prints out all items in the inventory
//Includes the quantity of each item
string printInv(){
string result; // list of all items
string temp; //temporary string for quantity
typedef map<string, Item>::iterator Item; //iterator
if (inv.empty() != true){
for(Item iterator = inv.begin(); iterator != inv.end(); iterator++) {
    if(iterator->second.quantity > 0){
    temp = intToString(iterator->second.quantity);
    result = result + "(" + temp + ") " + iterator->first + "\n";
    }
}
}
else {
     result = "(empty)\n";
}
return result + "------------------\n\n";
} 

//Prints out all items in the inventory
//for use in the shop. Assigns a number to each item
//for easy user selection
string printInvForShop(){
string result;      // list of all items
string temp;        //temporary string for number
int number = 1;     //So the user can select an item (increments
                    // by 1 each iteration)
typedef map<string, Item>::iterator Item; //iterator
for(Item iterator = inv.begin(); iterator != inv.end(); iterator++) {
    if(iterator->second.quantity > 0){ 
    temp = intToString(number);
    result = result + "(" + temp + ") " + iterator->first + "\n";
    number = number + 1;
    }
}
return result + "\n";
} 

//Prints out all Weapons
//for use in weapon info. Assigns a number to each weapon
//for easy user selection
string printWeapons(){
string result;      // list of all weapons
string temp;        //temporary string for number
int number = 1;     //So the user can select an item (increments
                    // by 1 each iteration)
typedef map<string, Weapon>::iterator Weapon; //iterator
for(Weapon iterator = weapons.begin(); iterator != weapons.end(); iterator++) {
    
    temp = intToString(number);
    result = result + "(" + temp + ") " + iterator->first + "\n";
    number = number + 1;
    
}
return result + "\n";
}


//Finds a specified item in the inventory (used in sell)
Item findInInv(string s){
Item i("temp", 0, 0);
int place = (stringToInt(s) - 1);
int number = 0;
typedef map<string, Item>::iterator Item; //iterator
for(Item iterator = inv.begin(); iterator != inv.end(); iterator++) {
    if((number == place) && (iterator->second.quantity != 0)){
        i = iterator->second;
        break;
    }
    else if (number == place){
         number = number;
    }
    else {
         number = number + 1;
}
}
return i;
} 

//Finds a specified Wepon in weapons (used in Weapons)
Weapon findInWeapons(string s){
Weapon w("temp", 0, 0, 0, 0);
int place = (stringToInt(s) - 1);
int number = 0;
typedef map<string, Weapon>::iterator Weapon; //iterator
for(Weapon iterator = weapons.begin(); iterator != weapons.end(); iterator++) {
    if((number == place) && (iterator->second.wquantity > 0)){
        w = iterator->second;
        break;
    }
    else if (number == place){
         number = number;
    }
    else {
         number = number + 1;
}
}
return w;
}
     

//Adds instrucitons
void addToInstructions(Instruction i){
pair<map<string,Instruction>::iterator,bool> ret;
ret = instructions.insert(pair<string, Instruction>(i.name, i));
} 

//Prints out all armor Instructions 
//for use in the forge. Assigns a number to each instruction
//for easy user selection
string printInstructions(string t){
string result;      // list of all items
string temp;        //temporary string for number
int number = 1;     //So the user can select an item (increments
                    // by 1 each iteration)
typedef map<string, Instruction>::iterator Instruction; //iterator
for(Instruction iterator = instructions.begin(); iterator != instructions.end(); iterator++) {
    if(iterator->second.type == t){ 
    temp = intToString(number);
    result = result + "(" + temp + ") " + iterator->first + "\n";
    number = number + 1;
    }
}
return result + "\n";
} 

//Finds a specified Instruction in instructions (used in forge)
//takes in a number as a string and an instruction type
Instruction findInInstructions(string s, string t){
Item tempa[1] = {pelt};
vector<Item> temp(&tempa[0], &tempa[0]+1);
Instruction i("temp", "temp", "temp", "0", temp);
int place = (stringToInt(s) - 1);
int number = 0;
typedef map<string, Instruction>::iterator Instruction; //iterator
for(Instruction iterator = instructions.begin(); iterator != instructions.end(); iterator++) {
    if((number == place) && (iterator->second.type == t)){
        i = iterator->second;
        break;
    }
    else if (iterator->second.type == t){
         number = number + 1;
    }
}
return i;
}

  
//CUT SCENES
///////////////////////////////////////////////////////////////////////////// 

//Level Two Cut Scene
Guy levelTwoScene(Guy g){
    string input;
    Sleep(1500);
    cout << "\nThe sun is setting as you walk along the trail\n";
    Sleep(2500);
    cout << "\nIts been a long day, but you're not far from home\n";
    Sleep(3000);
    cout << "\n\nYou can hear wolves calling to eachother in the distance\n";
    Sleep(3000);
    cout << "\nThey are too far away to be any danger\n";
    Sleep(2500);
    cout << "\nYou've grown much more confident in your survival skills\n";
    Sleep(3000);
    cout << "\n\n\nYou stop\n";
    Sleep(2000);
    cout << "\n\n\nSomething doesn't feel right...\n";
    Sleep(2000);
    cout << "\nSomeone is watching you\n";
    Sleep(2000);
    cout << "\nThe feeling is so strong, you're frozen in place\n";
    Sleep(3000);
    cout << "\n\n\n\"You're just imagining things " + g.name + "\"\n";
    Sleep(2000);
    cout << "\nYou try to calm yourself down\n";
    Sleep(3000);
    cout << "\nYou hear leaves rustle behind you...\n";
    Sleep(2500);
    cout << "\n\n\n\"WHO'S THERE\"\n";
    Sleep(1000);
    cout << "\n\n\nYou yell as you turn\n";
    Sleep(3000);
    cout << "\n\n\nNo answer\n";
    Sleep(2000);
    cout << "\n\nYou wait, but still no sound\n";
    Sleep(2000);
    cout << "\n\nYou feel as if the presence has vanished\n";
    Sleep(2500);
    cout << "\n\nThe sunlight glimmers off of something leaning on a tree\n";
    Sleep(2000);
    cout << "\n\nShould you check it out or go home?\n\n"
            "(1) Check it out\n"
            "(2) Head home\n\n";
    Sleep(2000);
    getline(cin, input);
    if (input == "1"){
        cout << "\nYou slowly approach the shining item\n";
        Sleep(2000);
        cout << "\nAs you get closer, you can make out what it is\n";
        Sleep(2000);
        cout << "\n\n\n\"A sword?\"\n";
        Sleep(1000);
        cout << "\nYou exclaim in confusion\n";
        Sleep(2000);
        cout << "\nIt's a little beat up, but much better than your stick\n";
        Sleep(3000);
        cout << "\nYou head home, sword in hand\n";
        Sleep(2000);
        cout << "\nToo tired to care where it came from\n";
        Sleep(2500);
        cout << "\n\nYou WERE being watched\n";
        Sleep(2000);
        cout << "\n\n\nYou're sure of it...\n\n\n\n";
        Sleep(3000);
        }
     else {
        cout << "\nYou turn your back and head home\n";
        Sleep(2000);
        cout << "\nTired, you just want to go to bed\n";
        Sleep(2000);
        cout << "\nAs you get home, you notice the door is slightly open\n";
        Sleep(3500);
        cout << "\n\nYou're not concerned though\n";
        Sleep(2500);
        cout << "\nThe wind was strong today\n";
        Sleep(2500);
        cout << "\n\n\nAs you enter, you freeze...\n";
        Sleep(3000);
        cout << "\nSitting on your table is an iron sword\n";
        Sleep(3000);
        cout << "\nYou search your house, but it's empty...\n";
        Sleep(3000);
        cout << "\nWhoever was here is gone now\n";
        Sleep(2500);
        cout << "\nToo tired to panick, you head to bed\n";
        Sleep(2500);
        cout << "\n\nYou'll look into it in the morning\n\n\n\n";
        Sleep(3000);
          }
g.weapon = ironSword;          
return g;
}

//Level Two and a half Cut Scene
Guy levelTwoScene2(Guy g){
    string input;
    Sleep(1500);
    cout << "\n\nYou've become much more comfortable being in the wild\n";
    Sleep(3000);
    cout << "\n\nBut days spent in the woods have started to change you...\n";
    Sleep(3000);
    cout << "\n\nYou have plenty to eat...\n";
    Sleep(2000);
    cout << "\nYet you continue hunting\n";
    Sleep(2000);
    cout << "\n\nTraveling further...\n";
    Sleep(1500);
    cout << "\n\nand further into the wilderness...\n";
    Sleep(2500);
    cout << "\n\n\nYou no longer hunt only to survive\n";
    Sleep(2500);
    cout << "\n\n\nWhat are you looking for?\n";
    Sleep(2000);
    cout << "\n\n\n\nOr who...\n\n\n";
    Sleep(2500);
    return g;
}

//Level Three Cut Scene
Guy levelThreeScene(Guy g){
    string input;
    Sleep(1500);
    cout << "The dreams about her haven't stopped...\n";
    Sleep(2500);
    cout << "\nThey're much worse now\n";
    Sleep(2000);
    cout << "\nThey always seem so real...\n";
    Sleep(2000);
    cout << "\nIt's as if she's trying to tell you something\n";
    Sleep(3000);
    cout << "\n\n\nBut what?\n";
    Sleep(1500);
    cout << "\n\n\nThe deeper into the woods you go..\n";
    Sleep(2000);
    cout << "\nThe closer you feel to an answer\n";
    Sleep(2000);
    cout << "\n\nIt's dangerous to go further without better supplies\n";
    Sleep(3000);
    cout << "\nMaybe it's time to head into town\n";
    Sleep(2500);
    cout << "\nYou've done your best to stay away\n";
    Sleep(2000);
    cout << "\n\n\nYou don't fit in there\n";
    Sleep(2000);
    cout << "\n\nBut if it's the only way to venture deeper...\n";
    Sleep(2500);
    cout << "\n\n\nInto town you go\n\n\n";
    Sleep(2000);
    return g;
} 

//Entering town Cut Scene
Guy townScene(Guy g){
    string input;
    Sleep(1500);
    cout << "In need of better materials, you leave for town\n";
    Sleep(1500);
    cout << "\n\nThe trail is overgrown from years of neglegence\n";
    Sleep(2000);
    cout << "\n\nIt's a nice day out\n";
    Sleep(1500);
    cout << "\nThe sun is shinning\n";
    Sleep(1500);
    cout << "\nThe birds are chirping\n";\
    Sleep(1500);
    cout << "\n\nYou start to feel better about having to make the trip\n";
    Sleep(2500);
    cout << "\n\"Maybe it won't be so bad this time\"\n";
    Sleep(2000);
    cout << "\nYou think to yourself\n";
    Sleep(1500);
    cout << "\nYou walk along the trail, lost in thought...\n";
    Sleep(3000);
    cout << "\n\nSo lost that you don't notice the giraffe sneaking up behind you\n";
    Sleep(2500);
    cout << "\n\n\nWHAM!\n";
    Sleep(1500);
    cout << "\n\n\nThe giraffe hits you in the side with its head!\n";
    Sleep(2500);
    cout << "\n\n\"YOU DONE FUCKED UP NOW NIGGA\"\n";
    Sleep(2000);
    cout << "\nYou scream as you travel through the air\n";
    Sleep(2000);
    cout << "\n\nYou can feel your spine break as your body impacts the tree\n";
    Sleep(2500);
    cout << "\nThe giraffe does a backflip over a big log\n";
    Sleep(2000);
    cout << "\n\nShit just got serious\n";
    Sleep(1500);
    cout << "\n\"Come and get me, bitch\"\n";
    Sleep(1500);
    cout << "\nyou say, wiping blood from your lip\n";
    Sleep(1500);
    cout << "\n\nthe giraffe vanishes\n";
    Sleep(1500);
    cout << "\n\"The FU-\"\n";
    Sleep(1500);
    cout << "\nBefore you can finish the sentence the giraffe appears above you\n";
    Sleep(2500);
    cout << "\n\n\nThis is not good\n";
    Sleep(1500);
    cout << "\nThe giraffe is fast as fuck\n";
    Sleep(1500);
    cout << "\n\nNext thing you know you're 30 feet in the air\n";
    Sleep(2000);
    cout << "\n\n\nYou can faintly hear the giraffe muttering gang shit to himself\n";
    Sleep(3000);
    cout << "\n\n\"Thought I told this nigga not to show his face in my hood no more\"\n";
    Sleep(3500);
    cout << "\n\n\nYou're still in the air somehow\n";
    Sleep(2000);
    cout << "\n\nThink " + g.name + ", THINK!\n";
    Sleep(1500);
    cout << "\n\nBINGO!\n";
    Sleep(1500);
    cout << "\n\nYou remember the glock you packed for the trip\n";
    Sleep(2000);
    cout << "\n\"Night night nigga\" you say as you pull out the fully-auto pistol\n";
    Sleep(3500);
    cout << "\n\nThe giraffe knows he's fucked\n";
    Sleep(2000);
    cout << "\n\nHe makes it two steps before you put one in the back of his head\n";
    Sleep(3000);
    cout << "\n\nBAM! BAM! BAM! BAM!\n";
    Sleep(1500);
    cout << "\nYou unload the whole clip on the fucker\n";
    Sleep(2000);
    cout << "\n\n\nYou fall to your knees in pain\n";
    Sleep(2000);
    cout << "\n\"This is why I fucking hate going into town\"\n";
    Sleep(2500);
    return g;
}

//SCRIPTS FOR ADVENTURES
////////////////////////////////////////////////////////////////////////

//Checks to see if the player or the enemy is dead
//If the enemy is dead, add items to the inventory
bool isDead(Guy g, Enemy e){
    bool result = false;      
          if (g.health <= 0){
              cout << "You died...\n"
                       "Press ENTER to continue...\n";
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              result = true;
              }
          //If the enemy is dead    
          else if(e.health <= 0){
               string itemNum = intToString(e.item.quantity);
               cout << "\nYou killed the " + e.name + "!\n\n";
               Sleep(500);
               cout << "You recieved: " + itemNum + " " + e.item.name + "\n\n";
               Sleep(1000);
               cout << "+ " + intToString(e.damage) + 
                       " experience\n\n"
                       "Press ENTER to continue...\n";
               addToInv(e.item);
               experiencePoints = experiencePoints + e.damage;
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               result = true;
               }
   return result;
}

//Checks if the weapon condition is 
//zero or not. if it is zero it removes the weapon and 
//makes it a stick
Guy checkWeapon(Guy g){
    if (g.weapon.condition <= 0){
       Sleep(500);
       cout << "\nYour " + g.weapon.name + " broke!\n" +
               "you picked up a stick on the ground\n\n";
       Sleep(500);
       g.weapon = stick;
       }
    return g;
}


//Checks if guy hsould level up or not
Guy levelUp(Guy g){
    if (experiencePoints >= ((g.level * 10) + 10)){
       g.level = g.level + 1;
       experiencePoints = 0;
       Sleep(500);
       cout << "\nYou grew to level " + 
               intToString(g.level) + "!\n";
       Sleep(1000);
       }
    return g;
}


//Determine name of enemy move
string nameMove(int i){
       string result;
       if (i == 1){
             result = "Attack\n";
             }
       else if (i == 2){
             result = "Defend\n";
             }
       else if (i == 3){
             result = "Trick\n";
             }
       else {
            result = "---\n";
            }
       return result;      
}

//Checks to see if the player ran out of water
Guy updateWater(Guy g){
    g.water = g.water - 1;
    if (g.water < 0){
       g.health = 0;
       cout << "You died of Dehydration\n";
       }
       return g;
}

//Fighting intro
//Only plays before first fight
int fightIntro(){
    int health = 15;
    bool replay = true;
    string input;
    Sleep(750);
    cout << "Welcome to Fight Training!\n\n";
    Sleep(2000);
    cout << "This is your first battle so it's\n"
            "time for you to learn how to properly fight.\n\n";
    Sleep(4000);
    cout << "During combat, both you and the enemy are\n"
            "presented with three choices:\n\n";
    Sleep(3500);
    cout << "1 Attack\n";
    Sleep(1500);
    cout << "2 Defend\n"; 
    Sleep(1500);
    cout << "3 Trick\n\n";
    Sleep(1500);
    cout << "When it's time to fight, you will both choose\n"
            "one of these actions.\n\n";
    Sleep(3500);
    cout << "Each one has its own strengths and weaknesses.\n\n";
    Sleep(3500);
    cout << "An Attack is very effective against a\n"
            "Trick. This is because a Trick consists\n"
            "of a fake jab, quickly followed by a real\n"
            "attack. A normal attack is faster so it\n"
            "beats Trick.\n\n"
            "Press ENTER to continue...\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Sleep(1000);
    cout << "When using Attack against an opponent who\n"
            "uses Trick, you will deal the full damage\n"
            "of your weapon.\n\n";
    Sleep(6000);
    cout << "Be careful though! Because the same\n"
            "holds true if you use Trick and the\n"
            "enemy Attacks.\n\n";
    Sleep(6000);
    cout << "On the other hand, an Attack is NOT\n"
            "effective against Defend.\n\n\n";
    Sleep(4000); 
    cout << "When using Attack against Defend, the\n"
            "attacker loses health equal to half their own\n"
            "damage. Since the defender was prepared, he\n"
            "does not lose any health.\n\n"
            "Press ENTER to continue...\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    Sleep(1000);
    cout << "I can see you're getting bored of this\n"
            "style of training.\n\n";
    Sleep(4000);
    cout << "Hmmmm, I think this will be much more\n"
            "interesting if I show you how to fight\n"
            "instead of lecture you.\n\n";
    Sleep(5000);
    cout << "First, I'll show you all of the rules,\n"
            "and then, when you think you understand\n"
            "them, we can fight.\n\n\n";
    Sleep(5000);

   
    cout << "FIGHTING RULES\n\n"
            "-During battle, when you are ready to fight, press ENTER.\n\n"
            "-There will be a short delay, and then it will display\n"
            " the enemy's attack choice.\n\n"
            "-Once the enemie's move is displayed, you have 5 seconds\n"
            " to enter your own attack.\n\n"
            "-To choose an attack, simply press the number that\n"
            " corresponds to the attack you want.\n"
            "-After entering your choice, you can either wait until\n"
            " time epires or press ENTER.\n\n"
            "-Once this happens, damage will be dealt accordingly,\n"
            " and you will repeat these steps until the battle is over.\n\n\n"
            
            "EFFECTIVENESS AND DAMAGE:\n\n"
            
            "Attack vs. Defend: Attacker loses 1/2 (their own) damage worth of hp\n"
            "Attack vs.  Trick: Attacker does full damage, and receives no damage\n"
            "Defend vs.  Trick: Defend takes full damage\n\n"
            
            
            "Attack vs. Attack: Both lose 1/2 damage worth of hp\n"
            "Defend vs. Defend: No damage is dealt\n"
            "Trick  vs.  Trick: Both lose 1/2 damage worth of hp\n\n\n"
            
            "Press ENTER if you are ready to practice fighting...\n\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1000);
            cout << "since this is only for practice, there will\n"
                    "not be a time limit on your attacks.\n\n";
            Sleep(4000);
            cout << "But enough talking, lets begin!\n\n";
            Sleep(3000);
            cout << "We will both be using sticks as weapons.\n"
                    "They deal 5 damage.\n\n";
            Sleep(4000);
         while(replay){  
            cout << "------------------";
            cout << "\nHealth: " + intToString(health) + "/15\n";
            cout << "Current weapon damage: 5\n\n";
            cout << "(1) ATTACK\n"
                    "(2) DEFEND\n"
                    "(3) TRICK\n";
            cout << "Press ENTER when ready to fight\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1000);
            cout << "I choose: Attack\n\n";
            Sleep(1500);
            cout << "What will you choose?\n\n";
            getline(cin, input);
            if (input == "1") {
               cout << "Not bad, but not the best move.\n";
               Sleep(2000);
               cout << "You dealt 2 damage and lost 2 health.\n\n";
               Sleep(2000);
               health = health - 2;
               } 
            else if (input == "2") {
               cout << "Great job! That was the best move.\n";
               Sleep(2000);
               cout << "You dealt 2 damage and lost 0 health.\n\n";
               Sleep(2000);
               }
            else if (input == "3") {
               cout << "Ouch! That was the worst choice.\n";
               Sleep(2000);
               cout << "You lost 5 health.\n\n";
               Sleep(2000);
               health = health - 5;
               }
            else {
                 cout << "That's not a valid input.\n"
                         "You lost 5 health.\n\n";
                 health = health - 5;
                 Sleep(2000);
                 }
            Sleep(1000); 
            cout << "Lets try another one!\n\n";
            Sleep(1000);
            cout << "------------------";
            cout << "\nHealth: " + intToString(health) + "/15\n";
            cout << "Current weapon damage: 5\n\n";
            cout << "(1) ATTACK\n"
                    "(2) DEFEND\n"
                    "(3) TRICK\n";
            cout << "Press ENTER when ready to fight\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1000);
            cout << "I choose: Trick\n\n";
            Sleep(1500);
            cout << "What will you choose?\n\n";
            getline(cin, input);
            if (input == "1") {
               cout << "Nice! That was the best option!\n";
               Sleep(2000);
               cout << "You dealt 5 damage and lost 0 health.\n\n";
               Sleep(2000);
               }
            else if (input == "2") {
               cout << "Uh oh! Bad choice!\n";
               Sleep(2000);
               cout << "You dealt 0 damage and lost 5 health.\n\n";
               health = health - 5;
               Sleep(2000);
               }
             else if (input == "3"){
               cout << "Not the best, but not the worst.\n";
               Sleep(2000);
               cout << "You dealt 2 damage and lost 2 health.\n\n";
               health = health - 2;
               Sleep(2000);
               }
             else {
                cout << "That's not a valid input.\n"
                        "You lost 5 health.\n\n";
                health = health - 5;
                Sleep(2000);
               }
            Sleep(1000); 
            cout << "Lets try one more!\n\n";
            Sleep(1000);
            cout << "------------------";
            cout << "\nHealth: " + intToString(health) + "/15\n";
            cout << "Current weapon damage: 5\n\n";
            cout << "(1) ATTACK\n"
                    "(2) DEFEND\n"
                    "(3) TRICK\n";
            cout << "Press ENTER when ready to fight\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            Sleep(1000);
            cout << "I choose: Defend\n\n";
            Sleep(1500);
            cout << "What will you choose?\n\n";
            getline(cin, input);
            if (input == "1") {
               cout << "Are you even trying?!\n";
               Sleep(2000);
               cout << "You dealt 0 damage and lost 5 health.\n\n";
               health = health - 5;
               Sleep(2000);
               }
            else if (input == "2"){
               cout << "Interesting choice.\n";
               Sleep(2000);
               cout << "You dealt 0 damage and lost 0 health.\n\n";
               Sleep(2000);
               }
            else if (input == "3"){
               cout << "Perfect!\n";
               Sleep(2000);
               cout << "You dealt 5 damage and lost 0 health.\n\n";
               health = health - 2;
               Sleep(2000);
               }
            else {
               cout << "That's not a valid input.\n"
                       "You should know this by now!\n\n";
               health = health - 5;
               }
            Sleep(1000);
            //check to see if player did well enough
            if (health <= 6){
               cout << "You did not do well enough\n"
                       "Please try again.\n\n";
               health = 15;
               Sleep(2000);
               }
            else {
               cout << "Congrats! You finished training!\n\n";
               Sleep(3000);
               cout << "You know everything that you need to know\n"
                       "to be a successful fighter.\n\n";
               Sleep(3500);
               cout << "Now, if I remember correctly you were\n"
                       "in the middle of a fight!\n\n";
               Sleep(3500);
               cout << "Good Luck!\n\n\n";        
               break;
               }
            }      
    return 0;
}
//Fight simulator
//Doesnn't add items to the inventory 
//Look up how I did it in SomeGuy before transferring code
//should be in the check for death section
Guy fight(Guy g, Enemy e){
  int eChoice;        //The enemies attack (random)
  string hitpoints;   //hitpoints dealt by player
  string ehitpoints;  //hitpoints dealt by enemy
  string itemNum;     //What item you get
  int seconds;     //time that has passed since timer start
  cout << "\n\n";
  while((g.health > 0) && (e.health > 0)){
       if (fightingIntro){
          fightIntro();
          fightingIntro = false;
          }
       string input = "";       //The player's attack
       Sleep(1000);
       cout << "------------------";
       cout << "\nHealth: " + intToString(g.health) + "/" +
               intToString(fullHealth) + "\n\n";
       cout << "(1) ATTACK\n"
               "(2) DEFEND\n"
               "(3) TRICK ATTACK\n";
       cout << "Press ENTER when ready to fight\n";
       cin.ignore(numeric_limits<streamsize>::max(), '\n');
       Sleep(1000);
       srand (time(NULL));
       eChoice = rand() % 3 + 1;
       cout << "Enemy Chose: " + nameMove(eChoice);

 //A timer for the user input
 while(true){
       // expire in 5 seconds.
       time_t expiry = time(NULL) + 3;
       while(true)
       {
           if (time(NULL) > expiry)
           {
               break;
           }
           if (_kbhit())
           {
               char ch = (char)_getch();
               _putch(ch); // echo character back to the screen
               if (ch == '\n' || ch == '\r') break;
               else input.insert(input.end(), 1, ch);
           }
           else
           {
               Sleep(1);
           }
       }
       cout << "\nYou chose: " + nameMove(stringToInt(input));
       cout << "^^^^^^^^^^^^^^^^^^^^^^\n";
       Sleep(500);
       break;
   }

          // If the user does not input anything
          if(input == ""){     
                   cout << "You were too slow!\n";
                   Sleep(1000);
                   if ((eChoice == 1) || (eChoice == 3)){
                      g.health = g.health - e.damage;
                      cout << "You lost " + intToString(e.damage) +
                              " health.\n";
                      }
                   else {
                       cout << "You're lucky the " + e.name + " defended.\n";
                       Sleep(1000);
                       }
             } 
/////////// Player Attacks
       //Both Attack
          else if((input == "1") && (eChoice == 1)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          e.health = e.health - (g.weapon.damage / 2);
          g.health = g.health - (e.damage / 2);
          g.weapon.condition = g.weapon.condition - 5;
          //Outputting damage dealt
          hitpoints = intToString(g.weapon.damage / 2);
          ehitpoints = intToString(e.damage / 2);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       //Player Attacks: Enemy Defends
       else if ((input == "1") && (eChoice == 2)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          g.health = g.health - (g.weapon.damage / 2);
          g.weapon.condition = g.weapon.condition - 5;
          //Outputting damage dealt
          hitpoints = intToString(0);
          ehitpoints = intToString(g.weapon.damage / 2);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       //Player Attacks: Enemy Trick Attacks
       else if ((input == "1") && (eChoice == 3)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          e.health = e.health - (g.weapon.damage);
          g.weapon.condition = g.weapon.condition - 5;
          //Outputting damage dealt
          hitpoints = intToString(g.weapon.damage);
          ehitpoints = intToString(0);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
/////////// Player Defends
       //Player Defends: Enemy Attacks
       else if ((input == "2") && (eChoice == 1)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          e.health = e.health - (e.damage / 2);
          //Outputting damage dealt
          hitpoints = intToString(e.damage / 2);
          ehitpoints = intToString(0);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       //Player Defends: Enemy Defends
       else if ((input == "2") && (eChoice == 2)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //No damage dealt
          //Outputting damage dealt
          hitpoints = intToString(0);
          ehitpoints = intToString(0);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          Sleep(500);
          }
       //Player Defends: Enemy Attacks
       else if ((input == "2") && (eChoice == 3)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          g.health = g.health - (e.damage);
          //Outputting damage dealt
          hitpoints = intToString(0);
          ehitpoints = intToString(e.damage);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
/////////// Player Trick Attacks
       //Player Trick Attacks: Enemy Attacks
       else if ((input == "3") && (eChoice == 1)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          g.health = g.health - (e.damage);
          //Outputting damage dealt
          hitpoints = intToString(0);
          ehitpoints = intToString(e.damage);
          g.weapon.condition = g.weapon.condition - 5;
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       //Player Trick Attacks: Enemy Defends
       else if ((input == "3") && (eChoice == 2)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          e.health = e.health - (g.weapon.damage);
          g.weapon.condition = g.weapon.condition - 5;
          //Outputting damage dealt
          hitpoints = intToString(g.weapon.damage);
          ehitpoints = intToString(0);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       //Player Trick Attacks: Enemy Trick Attacks
       else if ((input == "3") && (eChoice == 3)){
          cout << fightAnimation(stringToInt(input), eChoice);
          //Updates health
          g.health = g.health - (e.damage / 2);
          e.health = e.health - (g.weapon.damage / 2);
          g.weapon.condition = g.weapon.condition - 5;
          //Outputting damage dealt
          hitpoints = intToString(g.weapon.damage / 2);
          ehitpoints = intToString(e.damage / 2);
          Sleep(500);
          cout << "\nYou dealt " + hitpoints + " damage\n";
          cout << "You lost " + ehitpoints + " health\n";
          //Checks if weapon is still useable
          g = checkWeapon(g);
          //Check for a death
          if (isDead(g, e)){
              break;
              }
          Sleep(500);
          }
       else {
           cout << "Invalid Entry\n\n";
           cout << "Please enter: \n";
           cout << "(1) to Attack (Efective against trick attack)\n";
           cout << "(2) to Defend (Effective against attack)\n";
           cout << "(3) to Trick Attack ( Effective against defend)\n  \n";
           Sleep(500);
           }
       }
          
          return g;
}

//Adventure method
Guy adventure(Guy g){
   string input;
   int rightTimes = 0;
   int leftTimes = 0;
   Enemy enemy("temp", 0, 0, pelt);
  while((input != "home") && (g.health > 0)){ 
   cout << "\nYou come across a fork in the road\n"
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
           "Health: " + intToString(g.health) + "/" + intToString(fullHealth) +
           "    Water: " + intToString(g.water) + "\n\n"
           "(left)  go LEFT\n" 
           "(right) go RIGHT\n" 
           "(home)  go HOME\n";
   getline(cin, input);
   srand (time(NULL));
   int randomEvent = rand() % 5;  //determines if you fight or not
   
   if (input == "home") { 
          cout << "\nYou head home\n\n\n";
          g.water = fullWater;
          break;
   }
   //Encounter an enemy
   else if((randomEvent < 3) && ((input == "left") || (input == "right"))){
           int randomEnemy = rand() % 5;  
           enemy = enemies[randomEnemy];
           cout << "\n\nYou've been attacked by a " + enemy.name + "!\n";
           Sleep(500);
           //update left/right count
           if (input == "left"){
               leftTimes = leftTimes + 1;
           } else {
               rightTimes = rightTimes + 1; 
               }
                    
           g = fight(g, enemy);
           g = updateWater(g);
           g = levelUp(g);
   }
   //do not encounter an enemy
   else if((randomEvent >= 3) && ((input == "left") || (input == "right"))){
           g = updateWater(g);
           int randomItem = rand() % 11;  //determines of you get an instuction or not
           
           //Find water, find item, or continue on path
           if ((randomItem <= 3) && (g.level != 1)){
               addToInstructions(instructionList[randomItem]);
               Sleep(500);
               cout << "\nYou found a " + instructionList[randomItem].name +
                       " instruction!\n";
               Sleep(500);
               }
           else if (randomItem > 8) {
                g.water = fullWater;
                Sleep(500);
                cout << "\nYou came across a stream. You fill up your water\n"; 
                Sleep(500);
           } else {
               Sleep(500);
               cout << "\nThe path continues...\n";
               Sleep(500);
               }
           
           //update left/right count
           if (input == "left"){
               leftTimes = leftTimes + 1;
               } else {
               rightTimes = rightTimes + 1; 
               }
           leftTimes = leftTimes + 1;
   } else { 
          cout << "\n\nInvalid Entry \n\n";
          cout << "Please Type: \n";
          cout << "(left) to take the left path\n";
          cout << "(right) to take the right path\n";
          cout << "(home) to go home\n";
          Sleep(500);
          }
          
}
    return g;
}

//SCRIPTS FOR STORE
///////////////////////////////////////////////////////////////////////////////

//Sell Items
Guy sell(Guy g){
  string input;   //Which item to sell
  string quant;   //How many of that item to sell
  int iquant;     //how many of each item the user sells
  string yesno;   //to confirm transaction
  int price;      //int version of price
  Item item("temp", 0, 0); //temp item
   
   cout << "\nWhat would you like to sell?\n\n";
   cout << printInvForShop() + "(back) Back\n";
   getline(cin, input);
   while(input != "back"){
       item = findInInv(input);
       cout << "\nHow many " + item.name + " do you want to sell?\n\n";
       getline(cin, quant);
       iquant = stringToInt(quant);
       cout << "\nYou want to sell " + quant + " " + item.name + " for " + 
           intToString((item.price * iquant)) + " gold? \n(yes/no)\n\n";
      getline(cin, yesno);
      //for yes
      if ((yesno == "yes") && (item.quantity >= iquant)){
         sellInv(item, iquant);
         g.gold = g.gold + (item.price * iquant);
         cout << "\n";
         cout << sellAnimation();
         cout << "\n\nPress ENTER to continue...\n";
         updateInv();
         break;
         }
      //for yes, but not enough money
      else if(yesno == "yes"){
         cout<< "\nSorry, you do not have enough " + item.name + "\n\n"
                "Press ENTER to continue...\n";
         break;
         }
      //for no
      else {
         cout << "\nTransaction Cancelled\n\n"
                 "Press ENTER to continue...\n";
         break; 
         }
}  
    return g;
}

//Purchase Items
Guy purchase(Guy g){
  int input;         //What item the user wants
  int quant;         //how many of each item the user buys
  string yesno;      //Confirm purchase
  int price;         //int version of price
  Item i("temp", 0, 0); //
  while(typeid(input) == typeid(int)){ 
  cout << "\nWhat would you like?\n\n" //The order that the items appear in the 
           "(1) Pelt  (10 gold)\n"     //Array is the same, so you can just
           "(2) Claw  (5 gold)\n"      //use the input as an index 
           "(3) Wood  (2 gold)\n"
           "(4) Scale (4 gold)\n"
           "(5) Back\n\n";
   cin >> input;
   i = storeItems[input - 1];  //subtract 1 because index starts at 0 in array
   //to go back
   if (input == 5){
        break;
   }
   //to buy items
   else if ((input > 0) && (input < 5)) { 
        //To buy 1 of the selected item
        string price1 = intToString(i.price);
        //To buy 5 of the selected item
        string price5 = intToString(i.price * 5);
        //To buy 10 of the selected item
        string price10 = intToString(i.price * 10);
        
        cout << "\nHow many " + i.name + " do you want to buy?\n\n" +
                "(1) 1 " + i.name + " for " + price1 + " gold\n" +
                "(2) 5 " + i.name + " for " + price5 + " gold\n" +
                "(3) 10 " + i.name + " for " + price10 + " gold\n\n";
        
     cin >> quant; 
     //calculations for each quantity 
     while(typeid(quant) == typeid(int)){   
        if ((quant == 1) && (g.gold >= i.price)){
            i.quantity =  1;
            addToInv(i);
            g.gold = g.gold - i.price;
            cout << "\n";
            cout << buyAnimation();
            cout << "\n";
            break;
            }
        else if ((quant == 2) && (g.gold >= (i.price * 5))){
            i.quantity = 5;
            addToInv(i);
            g.gold = g.gold - (i.price * 5);
            cout << "\n";
            cout << buyAnimation();
            cout << "\n";
            break;
            }
        else if ((quant == 3) && (g.gold >= (i.price * 10))){
            i.quantity = 10;
            addToInv(i);
            g.gold = g.gold - (i.price * 10);
            cout << "\n";
            cout << buyAnimation();
            cout << "\n";
            break;
            }
        else if ((quant >= 1) && (quant <= 3)){
            cout << "\nYou don't have enough gold!\n";
            break;
            }
        else {
            cout << "\nInvalid Entry\n";
            break;
            }
            }   
}
   else { 
          cout << "\nInvalid Entry \n";
   }
          
}
    return g;
}            
               

//store method
//Contains sell and purchase
Guy store(Guy g){
   string input;   //What the user wants to do in the store
   string yesno;   //user yes or no inputs
   int price;      //price of repairing weapon
  while(input != "home"){ 
   cout << "\n-----STORE-----\n"
           "\nHowdy " + g.name + ", what can I do for you?\n\n" 
           "(1) Repair Weapon\n" 
           "(2) Buy\n"
           "(3) Sell\n"
           "(4) Town\n\n";
   getline(cin, input);
   //Repair Weapon
   if(input == "1"){
        price = (g.weapon.maxCond - g.weapon.condition) / 2;
        
        cout << "\nIt will cost " + intToString(price) + " gold to repair your " + 
                g.weapon.name + ".\nDo you wish to repair it? (Yes/No)\n\n";
                getline(cin, yesno);
                //successfully purchased weapon
                if (yesno == "yes" && (g.gold >= price)){
                    g.weapon.condition = g.weapon.maxCond;
                    g.gold = g.gold - price;
                    cout << "\n";
                    loadingBar();
                    cout << "\nYour Weapon is fixed!\n\n";
                    }
                //If the player has insufficient funds
                else if (g.gold < price){
                     cout << "\nSorry, you do not have enough gold\n\n";
                     }
                //If the user decides not to repair weapon
                else {
                     cout << "\nYou did not repair your weapon.\n\n";
                     }                    
             cout << "Press ENTER to continue...";
             cin.ignore(numeric_limits<streamsize>::max(), '\n');      
   }
   //Purchase Items
   else if(input == "2"){
            g = purchase(g);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
   //Sell Items
   else if(input == "3"){
            g = sell(g);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
   //Go Home
   else if (input == "4") { 
          cout << "\nSee you soon!\n\n";
          break;
   } else { 
          cout << "Invalid Entry \n";
          }
          
}
    return g;
}  


//FORGE
///////////////////////////////////////////////////////////////////////////////
//finds the damage of the wepon from instructions
string findDamage(string s){
string result;
for (unsigned int n = 0; n < s.size(); n++) {
  if(s.at(n) == '/'){
      break;
      }
  result = result + s.at(n);
  }
  return result;
}

//finds the condition of the wepon from instructions
string findCondition(string s){
string result;

bool cond = false;
for (unsigned int n = 0; n < s.size(); n++) {
  if(s.at(n) == '/'){
      cond = true;
      }
  else if (cond){
  result = result + s.at(n);
  }
}
  return result;
}

//determines if the player has sufficient items
//to craft the instruction
bool canBuild(Instruction i){
     bool result = true;
     string s;
     for (unsigned int n = 0; n < i.parts.size(); n++) {
     if (inv.find(i.parts[n].name) != inv.end()){
        if (i.parts[n].quantity <= inv.find(i.parts[n].name)->second.quantity){
           result = result;
           }
           else {
           result = false; 
           }  
        } 
        else {
        result = false;
        }
     }
return result;
}

//removes the instruction
void buildInvRemove(Instruction i){
     for (unsigned int n = 0; n < i.parts.size(); n++) {
          inv.find(i.parts[n].name)->second.quantity = 
              inv.find(i.parts[n].name)->second.quantity - i.parts[n].quantity;
          }
}


//Remove an instruction after it is used
void removeInstruction(Instruction i){
     instructions.erase(i.name);
}

//Crafts the weapon from the instruction
Weapon buildWeapon(Instruction i){
       int damage = stringToInt(findDamage(i.special));
       int condition = stringToInt(findCondition(i.special));
       Weapon w(i.name, damage, condition, condition, 1);

return w;
}


//to build instructions
Guy forge(Guy g){
  string input;   //User Input
  string input2;   //other input
  Item tempa[1] = {pelt};
  vector<Item> temp(&tempa[0], &tempa[0]+1);
  Instruction i("temp", "temp", "temp", "0", temp);
   while(input != "back"){
   cout << "\n#-----#---#-#-#---#-----#\n";
   cout << "What do you want to make:\n\n";
   cout << "(1) Armor\n"
           "(2) Weapons\n"
           "(3) Supplies\n"
           "(back) Back\n\n";
   getline(cin, input);
       //To make Armor
       if (input == "1"){
         cout << "Craft Armor:\n\n";
         cout << printInstructions("armor") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i = findInInstructions(input2, "armor");
         if (canBuild(i)){
            //remove items from inventory
            buildInvRemove(i);
            //remove intstruction from map
            removeInstruction(i);
            //add the built armor
            fullHealth = fullHealth + stringToInt(i.special);
            cout << "Built " + i.name + "!\n\n";
            }
            else {
            cout << "Cannot Build. Insufficient materials.\n\n";
            //determine what items the player is lacking and how many
            }
         cout << "Press ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }       
         }
      //To make Weapons
      else if(input == "2"){
         cout << "Craft Weapons:\n\n";
         cout << printInstructions("weapon") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i = findInInstructions(input2, "weapon");
         if (canBuild(i)){
            //remove items from inventory
            buildInvRemove(i);
            //remove intstruction from map
            removeInstruction(i);
            //add the built weapon
            addToWeapons(buildWeapon(i));
            cout << "Built " + i.name + "!\n\n";
            }
            else {
            cout << "Cannot Build. Insufficient materials.\n\n";
            //determine what items the player is lacking and how many
            }
         cout << "Press ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }  
         }
      //To make supplies
      else if(input == "3"){
         cout << "Craft Supplies:\n\n";
         cout << printInstructions("supplies") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i = findInInstructions(input2, "supplies");
         if (canBuild(i)){
            //remove items from inventory
            buildInvRemove(i);
            //remove intstruction from map
            removeInstruction(i);
            //add the built supply
            fullWater = fullWater + stringToInt(i.special);
            g.water = fullWater;
            cout << "Built " + i.name + "!\n\n";
            }
            else {
            cout << "Cannot Build. Insufficient materials.\n\n";
            //determine what items the player is lacking and how many
            }
         cout << "Press ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }  
         }
      //For Back
      else if(input == "back"){
         break;
         }
      //For invalid Entry
      else {
         cout << "Invalid Entry\n\n"
                 "Press ENTER to continue...\n";
         }
}  
    return g;
}


//Main town method
////////////////////////////////////////////////////////////////////////////
Guy town(Guy g){
   string input;   //What the user wants to do in the store
   string yesno;   //user yes or no inputs
   int price;      //price of repairing weapon
  
  if (playTownScene){
    g = townScene(g);
    playTownScene = false;
   } 
   
  while(input != "home"){ 
   cout << "\n-*-*-Town-*-*-\n"
           "\nWelcome back\n\n" 
           "(1) Store\n" 
           "(2) Forge\n"
           "(3) Casino\n"
           "(4) Home\n\n";
   getline(cin, input);
   //Store
   if(input == "1"){
        g = store(g);
        }
   //Forge
   else if(input == "2"){
            g = forge(g);
            updateInv();
   }
   //Casino
   else if(input == "3"){
            cout << "Casino not coded yet\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
   }
   //Go Home
   else if (input == "4") { 
          cout << "\nGood luck out there\n\n";
          break;
   } else { 
          cout << "Invalid Entry \n";
          }
          
}
    return g;
}  
//INSTRUCTION INFO
///////////////////////////////////////////////////////////////////////////////

//Prints the items required to build the thing
string printArray(Instruction i){
string s;
for (unsigned int n = 0; n < i.parts.size(); n++) {
  s = s + intToString(i.parts[n].quantity) + " " + i.parts[n].name + ", ";
  }
  return s.erase(s.size()-2, 1) + "\n";
}



//Instruction info for main menu
Guy instructionInfo(Guy g){
  string input;   //User Input
  string input2;   //to other input
  Item tempa[1] = {pelt};
  vector<Item> temp(&tempa[0], &tempa[0]+1);
  Instruction i("temp", "temp", "temp", "0", temp);
   while(input != "back"){
   cout << "\nSelect Type:\n\n";
   cout << "(1) Armor\n"
           "(2) Weapons\n"
           "(3) Supplies\n"
           "(back) Back\n\n";
   getline(cin, input);
       //To view Armor
       if (input == "1"){
         cout << "Armor Instructions:\n\n";
         cout << printInstructions("armor") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i = findInInstructions(input2, "armor");
         cout << "\n" + i.name + ":\n" + i.description + "\n\n"
                "Health: +" + i.special + "\n"
                "Requires: " + printArray(i);
         cout << "\n\nPress ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }       
         }
      //To view Weapons
      else if(input == "2"){
         cout<< "Weapons Instructions:\n\n";
         cout << printInstructions("weapon") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i = findInInstructions(input2, "weapon");
         
         string damage = findDamage(i.special);
         string condition = findCondition(i.special);
         
         cout << "\n" + i.name + ":\n" + i.description + "\n\n"
                "Damage: " + damage + "\n"
                "Max Cond: " + condition + "\n"
                "Requires: " + printArray(i);
         cout << "\n\nPress ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
         }
      //To view supplies
      else if(input == "3"){
         cout<< "Supplies Instructions:\n\n";
         cout << printInstructions("supplies") + 
                 "(back) Back\n";
         getline(cin, input2);
         if(input2 != "back"){
         i =findInInstructions(input2, "supplies");
         cout << "\n" + i.name + ":\n" + i.description + "\n\n"
                "Water: +" + i.special + "\n"
                "Requires: " + printArray(i);
         cout << "\n\nPress ENTER to continue...\n";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
         }
      //For Back
      else if(input == "back"){
         break;
         }
      //For invalid Entry
      else {
         cout << "Invalid Entry\n\n"
                 "Press ENTER to continue...\n";
         }
}  
    return g;
}   


//WEAPON INFO  
///////////////////////////////////////////////////////////////////////////////
// View and equip weapons
Guy weaponInfo(Guy g){
    string input;
    string equip;
    Weapon w("temp", 0, 0, 0, 1);
    while (input != "back"){
    cout << "<<<<<<<<<<<<>>>>>>>>>>>>\n"
            "\nCurrent Weapon: " + g.weapon.name + "\n"
            "     Hitpoints: " + intToString(g.weapon.damage) + "\n"
            "     Condition: " + intToString(g.weapon.condition) +
            "/" + intToString(g.weapon.maxCond) + "\n"
            "________________________\n"
            "Arsenal:\n\n";
            cout << printWeapons() + "(back) Back\n\n";
            getline(cin, input);
            if (input != "back"){
            w = findInWeapons(input);
            cout << "--|--->\n"
                    "   Weapon: " + w.name + "\n"
                    "Hitpoints: " + intToString(w.damage) + "\n"
                    "Condition: " +  intToString(w.condition) +
                    "/" +  intToString(w.maxCond) + "\n"
                    " Quantity: " +  intToString(w.wquantity) + "\n\n";
            cout << "(1) Equip\n"
                    "(2) Back\n"
                    "---|------->\n\n";
            getline(cin, equip);
            if (equip == "1"){
            addToWeapons(g.weapon);
            g.weapon = w;
            removeWeapon(w);
            updateWeapons();
            }
            }
}               
return g;

}


//Main Method
///////////////////////////////////////////////////////////////////////////////
int main(){
    //Starting inventory items (for testing)
    addToInv(claw);
    addToInv(claw);
    addToInv(claw);
    addToInv(pelt5);
    addToInv(scale);
    addToInv(wood);
    addToInv(wood);
    addToInv(wood);

 
   
    addToInstructions(woodClub);
    
    //Variables
    string name;            //Player name  
    int health = 25;       //Current Health (also at top, must match)
    int gold = 0;          //Starting gold
    int water = 5;         //Starting water capacity (also at top, must match))
    int level = 1;         //Starting level
    string task;            //Action inputted by the user (1,2,3,4...etc)
    int percentExp = 0;
    
    //GAME START SCRIPT 
    cout << "Welcome to SomeGuy \n \n"
            "Notes: \n"
            "- Only press ENTER when prompted to or when entering a menu option\n"
            "- In menus, type what is between the parenthesis to select that option\n\n"
            "Example:\n\nto select \"(1) Adventure\"\ntype \"1\" and press enter\n\n"
            "Please type a name for your character: \n";
    getline (cin, name);
    Guy guy(name, ironSword, health, gold, water, level);
    Sleep(2000);

    cout << "\nIt's dark...\n";
   Sleep(1500);
   cout << "\nYou stumble over something that you cannot see at your feet\n";
   Sleep(3000);
   cout << "\nWhere are you?\n";
   Sleep(2000);
   cout << "\nWhy does it feel as if you've been here before?\n";
   Sleep(3500);
   cout << "\nA voice calls from the distance...\n";
   Sleep(1500);
   cout << "\n\"" + guy.name + "\"\n";
   Sleep(2000);
   cout << "\nIt's a girl...\n";
   Sleep(1500);
   cout << "\n\"" + guy.name + "!\"\n";
   Sleep(1500);
   cout << "\nSo familiar...\n";
   Sleep(1500);
   cout << "\n\"" + uppercase(guy.name) + "\"\n";
   Sleep(1500);
   cout << "\nYou pick up your pace...\n";
   Sleep(1500);
   cout << "\n\"" + uppercase(guy.name) + "!\"\n";
   Sleep(1500);
   cout << "\nIt's too dark to see where she is...\n";
   Sleep(2000);
   cout << "\n\"" + uppercase(guy.name) + "!..." + 
           uppercase(guy.name) + "!..." +
           uppercase(guy.name) + "!\"\n";
   Sleep(2500);
   cout << "\nYou snap awake\n";
   Sleep(1500);
   cout << "\nIt was that dream again\n";
   Sleep(2000);
   cout << "\nIt's times like this you wish you didn't live in the woods\n";
   Sleep(3000);
   cout << "\nYou push it out of your mind as you get ready\n";
   Sleep(2000);
   cout << "\nNo time to lose, gotta start the day!\n\n\n\n\n";
   Sleep(2500);
 



//MAIN MENU   
while(guy.health > 0){
      if(guy.level >= 3){
          percentExp = (int) (((experiencePoints/((guy.level * 10) + 10)) * 100) + 0.5);
          if (lvl3Scene){
             guy = levelThreeScene(guy);
             lvl3Scene = false;
             }
          cout << "||||||||||||||||||||||||||||||||\n"
                  "Health: " + intToString(guy.health) + "/" + 
                  intToString(fullHealth) + "     Gold: " + 
                  intToString(guy.gold) + "\n"
                  "Level: " + intToString(guy.level) + " ( " +
                   intToString(percentExp) +
                   "% to " + intToString(guy.level + 1) + " )\n\n";
         cout << "Choose an action: \n\n"
                  "(1) Adventure   (4) Intructions\n"
                  "(2) Sleep       (5) Weapons\n"
                  "(3) Town        (6) Inventory\n\n"
                  "(quit) to Exit\n"
                  "||||||||||||||||||||||||||||||||\n\n";
          getline(cin, task);
          //Adventure
          if (task == "1"){
               guy = adventure(guy);
               } 
          //Sleep
          else if (task == "2"){
               sleep();
               guy.health = fullHealth;
               }
          //Store
          else if (task == "3"){
               guy = town(guy);
               }
          //Player Stats
          else if (task == "4"){
               instructionInfo(guy);
               }
          //Weapon Info
          else if (task == "5"){
               guy = weaponInfo(guy);
               }
          //Inventory
          else if (task == "6"){
               cout << "\n------------------";
               cout << "\n" + guy.name + "'s Inventory:\n\n";
               cout << printInv();
               cout << "Press ENTER to continue...\n";
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
          //Quit game
          else if (task == "quit"){
               break;
               }
          //Invalid entry in the menu
          else {
               cout << "You have chosen an invalid command\n\n"
               "Please type a number that correlates to a menu option.\n\n"
               "Press ENTER to continue...\n\n";
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
      //Level 2 menu
     } else if(guy.level == 2){
          percentExp = (int) (((experiencePoints/((guy.level * 10) + 10)) * 100) + 0.5);
          if ((lvl2Scene2) && (experiencePoints >= 15)){
              guy = levelTwoScene2(guy);
              lvl2Scene2 = false;
              }
          else if (lvl2Scene){
              guy = levelTwoScene(guy);
              lvl2Scene = false;
             }
          cout << "||||||||||||||||||||||||||||||||\n"
                  "Health: " + intToString(guy.health) + "/" + 
                  intToString(fullHealth) + "     Gold: " + 
                  intToString(guy.gold) + "\n"
                  "Level: " + intToString(guy.level) + " ( " +
                   intToString(percentExp) +
                   "% to " + intToString(guy.level + 1) + " )\n\n";
          cout << "Choose an action: \n\n"
                  "(1) Adventure   (3) Weapons\n"
                  "(2) Sleep       (4) Inventory\n"
                  "(quit) to Exit\n"
                  "||||||||||||||||||||||||||||||||\n\n";
          getline(cin, task);
          //Adventure
          if (task == "1"){
               guy = adventure(guy);
               } 
          //Sleep
          else if (task == "2"){
               sleep();
               guy.health = fullHealth;
               }
          //Weapons
          else if (task == "3"){
               guy = weaponInfo(guy);
               }
          //Player Stats
          else if (task == "4"){
               cout << "\n------------------";
               cout << "\n" + guy.name + "'s Inventory:\n\n";
               cout << printInv();
               cout << "Press ENTER to continue...\n";
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
          //Quit game
          else if (task == "quit"){
               break;
               }
          //Invalid entry in the menu
          else {
               cout << "You have chosen an invalid command\n\n"
                       "Please type a number that correlates to a menu option.\n\n"
                       "Press ENTER to continue...\n\n";
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
      //Level 1 menu
      } else {
          percentExp = (int) (((experiencePoints/((guy.level * 10) + 10)) * 100) + 0.5);
          cout << "||||||||||||||||||||||||||||||||\n"
                  "Health: " + intToString(guy.health) + "/" + 
                  intToString(fullHealth) + "     Gold: " + 
                  intToString(guy.gold) + "\n"
                  "Level: " + intToString(guy.level) + " ( " +
                   intToString(percentExp) +
                   "% to " + intToString(guy.level + 1) + " )\n\n";
          cout << "Choose an action: \n\n"
                  "(1) Adventure\n"
                  "(2) Sleep\n\n"
                  "(quit) to Exit\n"
                  "||||||||||||||||||||||||||||||||\n\n"; 
          getline(cin, task);
          //Adventure
          if (task == "1"){
           guy = adventure(guy);
           } 
          //Sleep
          else if (task == "2"){
               sleep();
               guy.health = fullHealth;
               }
          //Quit game
          else if (task == "quit"){
               break;
               }
          //Invalid entry in the menu
          else {
               cout << "You have chosen an invalid command\n\n"
              "Please type a number that correlates to a menu option.\n\n"
               "Press ENTER to continue...\n\n";
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
               }
           }   
}  
    
//Final Stats to show at end of game
//Also used to test new methods
cout << "\n\nGAME OVER\n\n";
cout << "Final Stats and Test Results:\n\n"
        "Name:   " + guy.name + "\n"
        "Health: " + intToString(guy.health) + "\n"
        "Gold:   " + intToString(guy.gold) + "\n"
        "Weapon: " + guy.weapon.name + "\n\n";

cout << "Press ENTER to continue...";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
return 0;

}
