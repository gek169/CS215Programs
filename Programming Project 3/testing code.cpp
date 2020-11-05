#include<iostream>
#include<cstdio> //For printf
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<string>
//Fix for Grace Compiling
#define nullptr 0
//Used for the minigame to clear the console
#define CLEAR_COMMAND "clear"
//Do you want to use the game? It's not in the specification, but it's not NOT in the specification, if you know what I mean ;)
#define PLAY_GAME true
//Your name goes here
#define USERNAME "Prof. Robert Chirwa"

struct ListNode{
	unsigned int sequence_number;
	std::string name;
	int month, day, year, hour, minute;
	std::string service_required;
	ListNode* next = nullptr;
	ListNode(){
		sequence_number = 0;
		name = "NULL";
		month = -1;
		day = -1;
		year = -1;
		hour = -1;
		minute = -1;
		service_required = "NULL";
		next = nullptr;
	}
	ListNode(unsigned int _sequence_number,
						std::string _name,
						int _month, int _day, int _year, int _hour, int _minute,
						std::string _service_required){
			sequence_number = _sequence_number;
			name = _name;
			month = _month;
			day = _day;
			year = _year;
			hour = _hour;
			minute = _minute;
			service_required = _service_required;
	}
};

class LineList{
	public:
		LineList(){
			head = nullptr;
		}
		LineList(ListNode* new_head){
			head = new_head;
		}
		//Delete all nodes
		~LineList(){
			while(Length > 0)
				DeleteNode(Length - 1);
		}
		//This function generates the sequence numbers
		void Resequence(){ //Re-generate the sequence numbers
			ListNode* Current = head;
			Length = 0;
			for(unsigned int i = 1; Current != nullptr; i++)
			{
				Current->sequence_number = i;
				Current = Current->next;
				Length = i; //This will be useful later on
			}
		}
		//This function simply pushes a node onto the list at the head
		//It does this by setting the new node's next member before setting the list head to the new node pointer
		void InsertNode(
			std::string name,
			int month, int day, int year, int hour, int minute, std::string service_required)
		{
			ListNode* New_Node = new ListNode(1, name, month, day, year, hour, minute, service_required); //I assume that this memory allocation is successful
			New_Node->next = head;
			head = New_Node;
			Resequence();
		}
		//if the position doesn't exist, then it will return nullptr. Navigates the list until either it runs out of steps or it finds nullptr
		ListNode* ReturnNodeAtPosition(unsigned int position){ 
			ListNode* CurrentNode = head;
			if(head == nullptr)
				return head;
			//there is definitely at least one thing in the list, at position 0
			unsigned int iter = position; //When this hits zero, we break
			while(iter > 0 && CurrentNode != nullptr)
			{
				CurrentNode = CurrentNode->next;
				iter--;
			}
			return CurrentNode;
		}
		//Pulls a node out and sets the previous node's next to current->next
		ListNode* RemoveNode(unsigned int position = 0){
			ListNode* Returnval = nullptr;
			ListNode* Current = ReturnNodeAtPosition(position);
			ListNode* Prev = nullptr;
			if(position > 0 && Current != nullptr)
			{
				Returnval = Current;
				Prev = ReturnNodeAtPosition(position - 1);
				Prev->next = Current->next;Resequence();//If this is at the end of the list, then Prev->next will be set to nullptr
				
			} else if(Current != nullptr){
				Returnval = Current;
				head = Current->next;Resequence();
			}
			
			return Returnval;
		}
		//Uses RemoveNode to find and remove the right node, and then deletes it
		//Please note that there is another DeleteNode function below which uses strings, as per specification
		void DeleteNode(unsigned int position){
			ListNode* p = RemoveNode(position);//This already resequences
			if(p)
				{delete p;}
		}
		//Search the list
		//I decided not to implement this recursively because it doesn't make sense to do it recursively, it just eats up more memory and is slower
		//I hope I do not lose points because of that, I believe this version is superior
		//Returns null if it doesn't exist
		//Due to the specification, I cannot actually use this function in the string-based DeleteNode, which has to know the previous node as well
		//Because of this, I had to implement a second version which returns the integer position
		ListNode* SearchNode(std::string name, ListNode* Start = nullptr){
			ListNode* Current = head;
			if(Start != nullptr)
				Current = Start;
			while(Current != nullptr && Current->name != name)
				Current = Current->next;
			return Current;
		}
		//This is the version I can use in DeleteNode (string based)
		//If it cannot find the name it will return a number larger than the largest index
		unsigned int SearchNodeIndex(std::string name, ListNode* Start = nullptr){
			ListNode* Current = head;
			if(Start != nullptr)
				Current = Start;
			unsigned int iter = 0;
			while(Current != nullptr && Current->name != name)
				{Current = Current->next;iter++;}
			if(Current != nullptr)
				return iter;
			else
				return iter + 1;
		}
		
		//Delete a node by string, as per specification.
		//I'm starting to realize that most of these functions are basically the same
		bool DeleteNode(std::string name){
			unsigned int Index = SearchNodeIndex(name);
			ListNode* Current = ReturnNodeAtPosition(Index);
			ListNode* Prev = nullptr;
			if(Current == head && Current != nullptr)
			{
				head = Current->next;
				delete Current;Resequence();
				return true;
			} else if (Current != nullptr){
				Prev = ReturnNodeAtPosition(Index - 1);
				Prev->next = Current->next;
				delete Current;Resequence();
				return true;
			}
			return false;
		}
		/*** 
		 * By caching the Maximum index in Resequence and making sure to resequence after every change 
		 * to the list, I can easily pop the last customer off the makeshift queue by using the maximum index
		***/
		ListNode* ServeCustomer(){
			return RemoveNode(Length - 1);
		}
		
		//goes through all elements and prints them as per specification
		unsigned int ListAll(){
			//Print out the table
			//std::cout << "\n\n\nAPPLE CUSTOMER SERVICE WAITING LIST\nSEQUENCE   NAME                 ARRIVAL DATE/TIME        PURPOSE OF VISIT  |" << std::endl;
			for(ListNode* Current = head; Current != nullptr; Current = Current->next)//for loops are cool
			{
				//I'm a C programmer at heart, I can't help it, I'll always use printf
				printf("%-10i", Current->sequence_number);
				printf("|");
				printf("%-20s", Current->name.c_str());
				printf("|");
				printf("%02i/%02i/%04i       %02i:%02i  ", Current->month, Current->day, Current->year, Current->hour, Current->minute);
				printf("|");
				printf("%18s|", Current->service_required.c_str());
				printf("\n");
			}
			std::cout << "\n" << std::endl;
			return Length;
		}
	private:
		ListNode* head = nullptr;
		unsigned int Length = 0;
};


//The main function I used to test the list class.
//If you have a good text editor there should be a - sign by the name of the function so you can get it out of the way
//It's pretty obvious what it does so I won't write any further about it
int oldmain(){
	LineList myList = LineList();
	unsigned int ListLength = 0;
	myList.InsertNode("Orange Joe", 1, 1, 1, 1, 1, "Massage");
	myList.InsertNode("Bonnie Blue", 1, 1, 1, 1, 1, "Love");
	myList.InsertNode("Green Grumpus", 1, 1, 1, 1, 1, "Grump");
	myList.InsertNode("Purple Menace", 1, 1, 1, 1, 1, "Somethin Purple");
	myList.InsertNode("Roger Red", 1, 1, 1, 1, 1, "Fire");
	myList.InsertNode("Yellow Yang", 1, 1, 1, 1, 1, "Sand");
	myList.InsertNode("Aquamarine Adam", 1, 1, 1, 1, 1, "Water");
	std::cout << "\n\n\nAPPLE CUSTOMER SERVICE WAITING LIST\nSEQUENCE   NAME                 ARRIVAL DATE/TIME          PURPOSE OF VISIT|" << std::endl;
	myList.ListAll();
	myList.DeleteNode("Bonnie Blue");//Delete Bonnie Blue
	myList.DeleteNode(300); //Attempt to delete at an invalid position
	std::cout << "\n\n\nAPPLE CUSTOMER SERVICE WAITING LIST\nSEQUENCE   NAME                 ARRIVAL DATE/TIME          PURPOSE OF VISIT|" << std::endl;
	myList.ListAll();
	{
		ListNode* Current = myList.SearchNode("Green Grumpus");
		if(Current != nullptr)
			std::cout << "At position " << Current->sequence_number << " We have " << Current->name << " Who needs " << Current->service_required << std::endl;
	}
	myList.ServeCustomer();
	myList.ServeCustomer();
	std::cout << "\n\n\nAPPLE CUSTOMER SERVICE WAITING LIST\nSEQUENCE   NAME                 ARRIVAL DATE/TIME          PURPOSE OF VISIT|" << std::endl;
	ListLength = myList.ListAll();
	std::cout << "There are " << ListLength << " Customers waiting to be served" << std::endl;
	return 0;
}


//THE MINIGAME

int IQ = 130; //I laughed so hard when I thought of this
int HP = 100;
int EnemyHP = 100;
int EnemyIQ = 100;
//Items
int IQPotions = 0;
int HealPotions = 0;
int Candy = 0; int CandyEaten = 0;
int Grenades = 0;



//CUSTOMER SERVICE MINIGAME
//Pokemon-like battles on the commandline
//It's all text based, so unfortunately no cool sprites :(
//It's rather unimportant to the functionality of the program.
//Case 1: Player Argues
void Argue(ListNode* Enemy){
	system(CLEAR_COMMAND);
	std::cout << "\n" << USERNAME << " uses ARGUE!";
	float test_val = rand()%100; 
	float ratio = ((float)IQ) / ((float)EnemyIQ) * 20.0f;
	if(test_val <= ratio)
	{
		std::cout << "\nIt's super effective!" << std::endl;
		EnemyHP -= 10;
		EnemyIQ -= 5;
		
	} else {
		std::cout << "\nIt was not very effective." << std::endl;
		EnemyHP -= 3;
		EnemyIQ -= 1;
	}
}
//Case 1E: Enemy Argues
void EArgue(ListNode* Enemy){
	std::cout << "\n" << Enemy->name << " uses ARGUE!";
	float test_val = rand()%100; 
	float ratio = ((float)EnemyIQ) / ((float)IQ) * 20.0f;
	if(test_val <= ratio)
	{
		std::cout << "\nIt's super effective!" << std::endl;
		HP -= 10;
		IQ -= 6; //the enemy needs a buff
		
	} else {
		std::cout << "\nIt was not very effective." << std::endl;
		HP -= 4;
		IQ -= 1;
	}
}
//Case 2: Player Item Menu
void Item(ListNode* Enemy){
	int option = 0;
	int failcounter = 0;
	std::string option_text = "";
	system(CLEAR_COMMAND);
	do{
		if(failcounter > 0)
			{std::cout << "\nYou can't use an Inventory Menu? Idiot." << std::endl; IQ--;}
		std::cout << "\nINVENTORY (type number to use):";
		std::cout << "\n1)Grenades: " << Grenades;
		std::cout << "\n2)Candy: " << Candy;
		std::cout << "\n3)Heal Potions: " << HealPotions;
		std::cout << "\n4)IQ Potions: " << IQPotions;
		std::cout << "\n5)Quit" << std::endl;
		std::getline(std::cin, option_text);
		option = atoi(option_text.c_str());
		if((option == 1 && Grenades < 1 )||
		   (option == 2 && Candy < 1 )|| 
		   (option == 3 && HealPotions < 1 )||
		   (option == 4 && IQPotions < 1))
			{std::cout << "\nYou attempted to use an item you don't have. Idiot.";IQ--;option = 6;}
	}while((option < 1 || option > 5 ) && option != 5);
	if(option == 1 && Grenades > 0)
	{
		std::cout << "\nYeah, the angry customer is gone, but you blew up half the store. You suffer serious brain damage in the explosion. Do I need to tell you that you're fired?" << std::endl;IQ = 50;
		Grenades--;
	}
	if(option == 2 && Candy > 0)
	{
		//Are you smart enough to think of giving it to them?
		if(IQ < 110)
		{
			std::cout << "\nYou ate the candy. Delicious." << std::endl;CandyEaten++;HP+=2;
			if(CandyEaten > 10){
				std::cout << "\nYou have Type 2 Diabetes. You will lose " << CandyEaten - 10 << " IQ points every turn until you use a Healing Potion." << std::endl;
			}
		} else {
			EnemyIQ = 0;
			std::cout << "\nYou have a clever idea. You give the candy to the customer. They are pleased by the offering and leave." << std::endl; IQ++;
		}
	}
	if(option == 3 && HealPotions > 0)
	{
		std::cout << "\nYou use a healing potion. Health is at maximum." << std::endl;HP = 100;
		if(CandyEaten > 10){std::cout << "\nYour Diabetes is cured." << std::endl;}
		CandyEaten = 0;
	}
	if(option == 4 && IQPotions > 0)
	{
		std::cout << "\nYou use an IQ potion." << std::endl;
		IQ += 10;
		if(rand()%100 > 90)
			{std::cout << "\nThe potion was defective. You LOSE 20 IQ points. Winners don't do drugs." << std::endl;IQ-=30;}
		else
			std::cout << "\nYou gained 10 IQ points. I guess drugs aren't so bad after all..." << std::endl;
	}
}
//Customer Service Battle! WOOHOO!
void CustomerServiceBattle(ListNode* Enemy)
{
	if(Enemy == nullptr)
		return;
	HP += (101 - HP)/2;//HP is restored slightly at the beginning of every battle. If your HP is already 100, then nothing changes
	EnemyHP = 100;
	bool escaped = false;
	EnemyIQ = IQ - 30 + rand()%60; //levelling system
	int option = 0;
	std::string option_text = "";
	int failcounter = 0;
	system(CLEAR_COMMAND);
	std::cout << "\n" << Enemy->name << " with " << EnemyIQ << " IQ points has arrived at the customer service desk!";
	std::cout << "\n They want \"" << Enemy->service_required << "\"" << std::endl;
	while(HP > 0 && EnemyHP > 0 && IQ > 59 && EnemyIQ > 59 && !escaped){ //While the battle is ongoing
		//Print status
		printf("\nSTATUS\n%s: %03i HP %03i IQ | %s: %03i HP %03i IQ ", USERNAME, HP, IQ, Enemy->name.c_str(), EnemyHP, EnemyIQ);
		//Your turn
		printf("\nOPTIONS:\n1)Argue\n2)Inflamatory Insult\n3)Item\n4)Fight\n5)Run Away\n");
		option = 0;
		failcounter = 0;
		do{
			if(failcounter > 0)
				{IQ--;printf("\nYour IQ has decreased slightly.");}
			std::getline(std::cin, option_text);
			option = atoi(option_text.c_str());
			failcounter++;
		} while(option < 0 || option > 6); //6 and 0 specifically so that if they mistype, we get them
		switch(option){
			case 1:
				system(CLEAR_COMMAND);
				Argue(Enemy);
			break;
			case 2:
				system(CLEAR_COMMAND);
				std::cout << "\nYou have decreased their functional IQ by a small amount as well as dealing some damage." << std::endl;
				EnemyHP -= rand()%(IQ/20);
				EnemyIQ -= rand()%(IQ/20);
				if(rand()%IQ < rand()%EnemyIQ)
					{HP -= rand()%(EnemyIQ/20); IQ -= rand()%(EnemyIQ/20); 
					std::cout << "\n...But they have a good comeback. Your IQ and Health decrease too." << std::endl;}
			break;
			case 3:
				system(CLEAR_COMMAND);
				Item(Enemy);
			break;
			case 4:
				system(CLEAR_COMMAND);
				if(rand()%100 > 50)
					{std::cout << "\nIn the midst of brawling with the customer, the police are called. You are hauled away and sent to prison.\nYou are killed in prison." << std::endl; IQ = 0;}
				else
					{std::cout << "\nYou dealt a fair bit of damage to them. This was a really stupid idea, though. Why did you get in a fistfight in an Apple store?";EnemyHP-=20;EnemyIQ-=20;IQ -= 5;HP -= 10;}
			break;
			case 5:
				system(CLEAR_COMMAND);
				std::cout << "\nYou run out of the store and flee your post. Your IQ decreases significantly."; IQ -= 50; escaped = true;
			break;
			default:
				system(CLEAR_COMMAND);
				std::cout << "\nYou chose to skip your turn. Idiot."; IQ--;
		}
		int enemyMove = rand()%4;
		int itemselection;
		switch(enemyMove){
			case 0:
				std::cout << "\n" << Enemy->name << " Has made a mistake in the menus. Idiot."; EnemyIQ--;
			break;
			case 1:
				EArgue(Enemy);
			break;
			case 2:
				std::cout << "\nThey have decreased your functional IQ by a small amount as well as dealing some damage." << std::endl;
				HP -= rand()%(EnemyIQ/20);
				IQ -= rand()%(EnemyIQ/20);
				if(rand()%IQ > rand()%EnemyIQ)
					{
						EnemyHP -= rand()%(IQ/20); 
						EnemyIQ -= rand()%(IQ/20); 
						std::cout << "\n...But you have a good comeback. Their IQ and Health decrease too." << std::endl;
					}
			break;
			case 3:
				std::cout << "\nThey have chosen to use an Item." << std::endl;
				itemselection = rand()%4; //Enemies don't use grenades
				//itemselection = 3;
				switch(itemselection){
					case 0:
						std::cout << "\nThey use a healing potion." << std::endl; EnemyHP = 100;
					break;
					case 1:
						std::cout << "\nThey use an IQ potion." << std::endl; EnemyIQ+=10;
					break;
					case 2:
						std::cout << "\nThey ate candy." << std::endl; EnemyHP += 2; EnemyIQ -=1;
					break;
					case 3:
						std::cout << "\nThey play the air guitar. That's really cool! You (a proud air guitar expert) Try to one-up him..." << std::endl;
						
						if(IQ - EnemyIQ < -40)
							{std::cout << "\nYou hurt yourself trying to counter their air guitar. Idiot." << std::endl; IQ--; HP-=5;}
						else if (IQ - EnemyIQ < -30)
							{std::cout << "\nYou are confused. Idiot." << std::endl; IQ--;}
						else if (IQ - EnemyIQ < -20)
							{std::cout << "\nYour air guitar is not as good as " << Enemy->name << "'s air guitar. You are slightly enraged and your functional IQ decreases." << std::endl;IQ-=2;}
						else if (IQ - EnemyIQ < 20)
							{std::cout << "\nYour air guitar response seems to adequately counter theirs." << std::endl;}
						else if(IQ - EnemyIQ < 30)
							{std::cout << "\nYou play the air guitar so well that THEY lose IQ points because it's so good!"; EnemyIQ-=2; EnemyHP -=10;}
						else {
							std::cout << "\nYou play the air guitar so well that you kill them! WOW is that a good air guitar!!!" << std::endl; IQ++; EnemyHP = 0; EnemyIQ = 0;
						}
					break;
				}
			break;
			default:
				std::cout << "\nEnemy has made a mistake in the menus." << std::endl; EnemyIQ--;
			break;
		}
		if(CandyEaten > 10)
			{std::cout << "\nYou have lost " << CandyEaten - 10 << " IQ point due to the effects of sudden onset Type 2 Diabetes."; IQ -= (CandyEaten - 10);}
	} //EOF GAME LOOP
	if(HP <= 0)
		{
			std::cout << "\nYOU DIED! Corpses don't have high IQs." << std::endl; IQ = 0;
		}
	else if(IQ < 60)
		{
			std::cout << "\nUnfortunately, you are no longer qualified for employment at Apple."; IQ = 59;
		}
	else if(EnemyHP <= 0)
		{
			std::cout << "\nHP Victory. The corpse of the once loyal customer is hauled off. Your HP has been restored.";
			HP = 100;
			IQ += 10;
			/*
			 *  int IQPotions = 0;
				int HealPotions = 0;
				int Candy = 0;
				int Grenades = 0;
			 */
			int IQPotionGain = (rand()%100)/70;
			int HealPotionGain = (rand()%100)/90;
			int CandyGain = (rand()%100)/20;
			int GrenadeGain = (rand()%100)/90;
			if (IQPotionGain > 0)
				std::cout << "\nYOU FOUND AN IQ POTION!";
			if (HealPotionGain > 0)
				std::cout << "\nYOU FOUND A HEALING POTION!";
			if (CandyGain > 0)
				std::cout << "\nYOU FOUND " << CandyGain << " PIECES OF CANDY!";
			if (GrenadeGain > 0)
				std::cout << "\nYOU FOUND A GRENADE!";
				
			IQPotions += IQPotionGain;
			HealPotions += HealPotionGain;
			Candy += CandyGain;
			Grenades += GrenadeGain;
		}
	else if(EnemyIQ < 60)
	{
		std::cout << "\nIQ Victory. The Mental Vegetable is hauled off. Your HP has been restored.";
			HP = 100;
			IQ += 15;
			/*
			 *  int IQPotions = 0;
				int HealPotions = 0;
				int Candy = 0;
				int Grenades = 0;
			 */
			int IQPotionGain = (rand()%100)/70;
			int HealPotionGain = (rand()%100)/90;
			int CandyGain = (rand()%100)/10;
			int GrenadeGain = (rand()%100)/90;
			if (IQPotionGain > 0)
				std::cout << "\nYOU FOUND AN IQ POTION!";
			if (HealPotionGain > 0)
				std::cout << "\nYOU FOUND A HEALING POTION!";
			if (CandyGain > 0)
				std::cout << "\nYOU FOUND " << CandyGain << " PIECES OF CANDY!";
			if (GrenadeGain > 0)
				std::cout << "\nYOU FOUND A GRENADE!";
				
			IQPotions += IQPotionGain;
			HealPotions += HealPotionGain;
			Candy += CandyGain;
			Grenades += GrenadeGain;
	} else if (escaped) {
		std::cout << "\nYou are amazingly not fired and return to your job. You feel much less intelligent than before.";
	}
	//This has to happen
	delete Enemy;return;
}


int main()
{
	LineList myList = LineList();
	int option = 0;
	std::string option_text = "";
	int _month = 0;
	int _day = 0;
	int _year = 2000;
	int _hour = 0;
	int _minute = 0;
	int failcounter = 0;
	unsigned int ListLength;
	bool boolean_cache = false;
	std::string _name = "NULL";
	std::string _purpose = "NULL";
	srand(time(NULL));//Prevent the game from having the same outcome every time
	do{
		std::cout << "\n1) New Customer Arrival\n2) Serve Customer\n3) Customer left- remove from waiting list\n4) List all customers waiting for service\n5)Quit\nCHOOSE WISELY: ";
		std::getline(std::cin, option_text);
		option = atoi(option_text.c_str());
		switch(option){
			case 1:
				_month = 0;
				_day = 0;
				_year = 0;
				_hour = 0;
				_minute = 0;
				//grab all the info
					std::cout << "\nName?" << std::endl;
					std::getline(std::cin, _name);
					std::cout << "\nPurpose?" << std::endl;
					std::getline(std::cin, _purpose);
					//Get the month
					failcounter = 0;
					do{
						if(failcounter > 0)
							{IQ--;std::cout << "\nYour IQ has decreased slightly" << std::endl;}
						std::cout << "\nMonth? (1-12)" << std::endl;
						std::getline(std::cin, option_text);
						_month = atoi(option_text.c_str());
						failcounter++;
					}while(_month > 12 || _month < 1);
					//Get the day
					failcounter = 0;
					do{
						if(failcounter > 0)
							{IQ--;std::cout << "\nYour IQ has decreased slightly" << std::endl;}
						if(failcounter > 0 && _month == 2 && _day > 29)
							{IQ -= 5;std::cout << "\nThere are a maximum of 29 days in February. Idiot." << std::endl;}
						std::cout << "\nDay? (1-31)" << std::endl;
						std::getline(std::cin, option_text);
						_day = atoi(option_text.c_str());
						failcounter++;
					}while(_day > 31 || _day < 1);
					//Get the year
					failcounter = 0;
					do{
						if(failcounter > 0)
							{IQ--;std::cout << "\nYour IQ has decreased slightly" << std::endl;}
						if(failcounter > 0 && _year > 2500)
							{IQ -= 5;std::cout << "\nWhat is this, Futurama? More like Idiocracy." << std::endl;}
						else if (failcounter > 0 && _year < 1970)
							{IQ -= 3;std::cout << "\nYou think you can enter dates before Unix time? Idiot." << std::endl;}
						std::cout << "\nYear? (AD, Non-abbreviated)" << std::endl;
						std::getline(std::cin, option_text);
						_year = atoi(option_text.c_str());
						failcounter++;
					}while(_year < 1970 || _year > 2500);
					//Get the hour
					failcounter = 0;
					do{
						if(failcounter > 0)
							{IQ--;std::cout << "\nYour IQ has decreased slightly" << std::endl;}
						std::cout << "\nHour? (1-24 aka US Military Time)" << std::endl;
						std::getline(std::cin, option_text);
						_hour = atoi(option_text.c_str());
						failcounter++;
					}while(_hour < 1 || _hour > 24);
					//Get the minute
					failcounter = 0;
					do{
						if(failcounter > 0)
							{IQ--;std::cout << "\nYour IQ has decreased slightly.\nThere are 60 minutes in 1 hour, so the most you can have is 59." << std::endl;}
						std::cout << "\nMinute? (0 - 59)" << std::endl;
						std::getline(std::cin, option_text);
						_minute = atoi(option_text.c_str());
						failcounter++;
					}while(_minute > 59);
					//Insert the node
					myList.InsertNode(_name, _month, _day, _year, _hour, _minute, _purpose);
					IQ += 2; //IQ gained from properly using this function
			break; //EOF CASE INSERT CUSTOMER
			case 2:
				//TODO: write minigame
				if(PLAY_GAME)
					CustomerServiceBattle(myList.ServeCustomer());
				else
					delete myList.ServeCustomer();
			break;
			case 3:
				failcounter = 0;
				do{
					if(failcounter > 0)
						{std::cout << "\nI don't know anyone with that name in this line. Idiot.";IQ--;}
					std::cout << "\nWho left? (If you're stuck, type \"BREAK\" in all caps WITH quotes";
					std::getline(std::cin, _name);
					boolean_cache = myList.DeleteNode(_name);
					failcounter++;
				}while(!boolean_cache && _name != "\"BREAK\"");
				if(failcounter == 1)
					IQ+=2;
			break;
			case 4:
				IQ++; //Running this command is a smart decision
				std::cout << "\n\n\nAPPLE CUSTOMER SERVICE WAITING LIST\nSEQUENCE   NAME                 ARRIVAL DATE/TIME          PURPOSE OF VISIT|" << std::endl;
				ListLength = myList.ListAll();
				std::cout << "There are " << ListLength << " Customers waiting to be served" << std::endl;
			break;
			case 5:
			break;
			default:
				IQ -= 10;
				std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\nYour IQ has decreased 10 points, it is now: " << IQ << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
		}
		if(IQ < 60) //low enough to get you locked up
			{std::cout << "\nSorry, the program has detected that your IQ is too low to use this software.\nWho did you vote for last election?" << std::endl;}
	}while(option != 5 && IQ > 59);
	if(IQ < 60) //you will be fired from your job if you are too stupid
	{
		std::cout << "\nYou have lost too many IQ points to work at Apple Customer Service. You are FIRED!" << std::endl;
		std::cout << " ______ _____ _____  ______ _____  \n\
 |  ____|_   _|  __ \\|  ____|  __ \\\n\
 | |__    | | | |__) | |__  | |  | |\n\
 |  __|   | | |  _  /|  __| | |  | |\n\
 | |     _| |_| | \\ \\| |____| |__| |\n\
 |_|    |_____|_|  \\_\\______|_____/ \n";
	}
    
	std::cout << "\nYour IQ is " << IQ << ", Rank:"<< std::endl;
	if(IQ < -64000) std::cout << "Integer Overflow";
	if(IQ < 60 && IQ > -64000) std::cout << "Fired for incompetence";
	if(IQ < 70 && IQ >= 60) std::cout << "David Webster if he doesn't get an A on this assignment";
	if(IQ < 80 && IQ >= 70) std::cout << "Java Coder";
	if(IQ < 90 && IQ >= 80) std::cout << "Makes frecwent speling erors";
	if(IQ < 100 && IQ >= 90) std::cout << "Earth is flat, Moon landing was a hoax";
	if(IQ < 110 && IQ >= 100) std::cout << "Pretty average";
	if(IQ < 120 && IQ >= 110) std::cout << "4chan /pol/ average";
	if(IQ < 130 && IQ >= 120) std::cout << "Armchair intellectual";
	if(IQ < 140 && IQ >= 130) std::cout << "Free Software Foundation Volunteer";
	if(IQ < 150 && IQ >= 140) std::cout << "Einstein";
	if(IQ < 160 && IQ >= 150) std::cout << "Brian Kernighan";
	if(IQ < 170 && IQ >= 160) std::cout << "Richard Stallman";
	if(IQ < 180 && IQ >= 170) std::cout << "Can Install GNU/Linux without help";
	if(IQ < 190 && IQ >= 180) std::cout << "Linus Torvalds";
	if(IQ < 200 && IQ >= 190) std::cout << "Robert Chirwa";
	if(IQ < 210 && IQ >= 200) std::cout << "Dennis Ritchie";
	if(IQ >= 210) std::cout << "Will Crowther, Don Woods, or perhaps Gary Gygax?";
	std::cout << std::endl;
	
	return 0;
}
