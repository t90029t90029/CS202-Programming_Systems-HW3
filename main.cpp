//Shang-Chun, Lin CS202 assignment#3
#include "list.h"
using namespace std;

//This file is to test out the hierarchy of the classes created
int main()
{
	chat_room list;

	int * choose = NULL;
	// ---------------------------------------------------------//
	cout<<"Hi, this is a chatting program to record the what they have said for each speaker."<<endl;	

	cout<<"Now, please choose a kind of services you would like to use. You have to enter a number."<<endl
	<<"1 for adding an new sender into the chat room, "<<endl
	<<"2 for starting chatting in the chat room for a specific speaker, "<<endl
	<<"3 for displaying the whole record in the chat room by order of their name, "<<endl
	<<"4 for cleaning up every record in the chat room, "<<endl
	<<"5 for quiting the program."<<endl;

	choose = new int;
	cin>>*choose;
	cin.ignore(100,'\n');
		
	while(*choose < 1 || *choose > 5)
	{
		cout<<"out of range! try again."<<endl;
		cin>>*choose;
		cin.ignore(100,'\n');
	}
	
	//-----------------starting running the main part---------------------//
	while(*choose != 5)
	{	

		if(*choose == 1)
		{
			sender * to_add = new sender;;
			to_add->set_name();

			if(list.add_sender(*to_add))
			{
				cout<<"The instruction of inserting is done."<<endl;
			}

			to_add->remove_all();
			delete to_add;
			to_add = NULL;
		}
		else if(*choose == 2)
		{
			if(list.chat())
			{
				cout<<"The instruction of starting the game is done."<<endl;
			}
		}
		else if(*choose == 3)
		{
			if(list.display())
			{
				cout<<"The instruction of displaying is done."<<endl;
			}
		}
		else if(*choose == 4)
		{
			list.remove_all();
		}

		// ---------------------------------------------------------//
		cout<<"Now, please choose a kind of services you would like to use at the next step. "<<endl
		<<"1 for adding an new sender into the chat room, "<<endl
		<<"2 for starting chatting in the chat room for a specific speaker, "<<endl
		<<"3 for displaying the whole record in the chat room by order of their name, "<<endl
		<<"4 for cleaning up every record in the chat room, "<<endl
		<<"5 for quiting the program."<<endl;

		cin>>*choose;
		cin.ignore(100,'\n');

		while(*choose < 1 || *choose > 5)
		{
			cout<<"out of range! try again."<<endl;
			cin>>*choose;
			cin.ignore(100,'\n');
		}

	}

	if(choose)
	{
		delete choose;
	}
	choose = NULL;

	return 0;
}
