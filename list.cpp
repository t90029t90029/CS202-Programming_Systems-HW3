//Shang-Chun, Lin CS202 assignment#3
#include "list.h"

using namespace std;
//The purpose of this file is to implement each function in the list.h file

l_node::l_node()
{
	data = NULL;
	next = NULL;
}

l_node::l_node(const l_node & source)
{
	word * w_ptr = dynamic_cast<word*>(source.data);
	emoji * e_ptr = dynamic_cast<emoji*>(source.data);

	if(w_ptr)
	{
		data = new word(*w_ptr);
	}
	else if(e_ptr)
	{
		data = new emoji(*e_ptr);
	}

	next = NULL;
}

void l_node::remove()
{
	if(data)
	{
		data->remove_all();
	}
	data = NULL;

	if(next)
	{
		next = NULL;
	}
}

l_node::~l_node()
{
	remove();
}

l_node& l_node::operator = (const l_node & source)
{
	if(this == &source)
	{
		return *this;
	}
	if(data)
	{
		data->remove_all();
	}
	data = NULL;
	const word * w_ptr = dynamic_cast<const word*>(source.data);
	const emoji * e_ptr = dynamic_cast<const emoji*>(source.data);

	if(w_ptr)
	{
		data = new word(*w_ptr);
	}
	else if(e_ptr)
	{
		data = new emoji(*e_ptr);
	}

	if(next)
	{
		next = NULL;
	}

	return *this;
}

l_node *& l_node::go_next()
{
	return next;
}

l_node * l_node::get_next()const
{
	return next;
}

void l_node::connect_next(l_node * connection)
{
	if(!connection)
	{
		next = NULL;
		return;
	}
	next = connection;
	return;
}

info *& l_node::get_data()
{
	return data;
}

info * l_node::use_data()const
{
	return data;
}

message::message()
{
	head = NULL;
}

void message::copy(l_node * & head,const l_node * source)
{
	if(!source)
	{
		head = NULL;
		return;
	}

	head = new l_node(*source);

	return copy(head->go_next(),source->get_next());
}

message::message(const message & source)
{
	if(source.head)
	{
		copy(head,source.head);
	}	
}

void message::remove_all(l_node * & head)
{
	if(!head)
	{
		return;
	}

	l_node * hold = head->go_next();
	head->remove();
	delete head;
	head = hold;

	return remove_all(head);
}

void message::remove_all()
{
	if(head)
	{
		remove_all(head->go_next());
	}
}

message::~message()
{
	remove_all();
}

message & message::operator = (const message & source)
{
	if(this == &source)
	{
		return *this;
	}
	if(head)
	{
		remove_all();
	}
	
	copy(head,source.head);

	return *this;
}

int message::insert()
{
	cout<<"What kind of expression do you want to type into the chat room?"<<endl
	<<"(W) a word(sentence)."<<endl
	<<"(E) an emoji."<<endl
	<<"The default answer will be W."<<endl
	<<"Here are some examples for you : "<<endl
	<<"( ≧Д≦) (╬ Ò ‸ Ó) ( >д<) ╰（‵□′）╯ ಠ▃ಠ  (¬_¬) Σ( ° △ °|||)  ಥ⌣ಥ  v(￣︶￣)y  (´･ω･`) "<<endl;

	char answer = '\0';
	cin>>answer;
	cin.ignore(100,'\n');
	answer = toupper(answer);

	switch (answer)
	{
		case 'W':if(!head)
			 {
				 head = new l_node;
				 head->get_data() = new word;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(head->get_data());
				 cin.ignore(100,'\n');
				 head->go_next() = NULL;
			 }
			 else
			 {
				 l_node * temp = new l_node;
				 temp->get_data() = new word;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(temp->get_data());
				 cin.ignore(100,'\n');
				 temp->go_next() = head;
				 head = temp;
			 }
			 break;

		case 'E':if(!head)
			 {
				 head = new l_node;
				 head->get_data() = new emoji;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(head->get_data());
				 cin.ignore(100,'\n');
				 head->go_next() = NULL;
			 }
			 else
			 {
				 l_node * temp = new l_node;
				 temp->get_data() = new emoji;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(temp->get_data());
				 cin.ignore(100,'\n');
				 temp->go_next() = head;
				 head = temp;
			 }
			 break;

		default:if(!head)
			{
				 head = new l_node;
				 head->get_data() = new word;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(head->get_data());
				 cin.ignore(100,'\n');
				 head->go_next() = NULL;
			}
			else
			{
				 l_node * temp = new l_node;
				 temp->get_data() = new word;
				 cout<<"Please type in what you would like to say."<<endl;
				 cin>>*(temp->get_data());
				 cin.ignore(100,'\n');
				 temp->go_next() = head;
				 head = temp;
			}
	}

	return 1;
}

int message::remove(l_node * & head,const char * source)
{
	if(!head)
	{
		cout<<"There is no record as same as what you have typed."<<endl;
		return 0;
	}

	if(*(head->get_data()) == source)
	{
		l_node * hold = head->go_next();
		head->remove();
		delete head;
		head = hold;

		return 1;
	}

	return remove(head->go_next(),source);
}

int message::remove()
{
	if(!head)
	{
		cout<<"Your chat record is empty, you can not remove anything!"<<endl;
		return 0;
	}
	cout<<"We will examine the record from the newest to the oldest."<<endl
	<<"Please type in the record that you would like to remove."<<endl;

	char * temp = new char[300];
	cin.get(temp,299,'\n');
	cin.ignore(100,'\n');

	if(remove(head,temp))
	{
		delete temp;
		temp = NULL;
		return 1;
	}
	delete temp;
	temp = NULL;
	return 0;
}

void message::display(const l_node * head)const
{
	if(!head)
	{
		return;
	}

	cout<<*(head->use_data())<<endl;

	return display(head->get_next());
}

void message::display()const
{
	if(!head)
	{
		cout<<"The record is empty. We can not display anything for you."<<endl;
		return;
	}
	return display(head);
}

sender::sender()
{
	name = NULL;
}

sender::sender(const sender & source):message(source)
{
	if(source.name)
	{
		name = new char[strlen(source.name) +1];
		strcpy(name,source.name);
	}
}

void sender::remove_all()
{
	if(name)
	{
		delete [] name;
	}
	name = NULL;
	
	message::remove_all();

	return;
}

void sender::remove()
{
	if(name)
	{
		delete [] name;
	}
	name = NULL;

	return;
}

sender::~sender()
{
	remove();
}

sender & sender::operator = (const sender & source)
{
	if(this == &source)
	{
		return *this;
	}

	remove_all();

	name = new char[strlen(source.name)+1];
	strcpy(name,source.name);

	message::operator = (source);

	return *this;
}

void sender::set_name()
{
	cout<<"Please set a sender's name."<<endl;
	char * hold = new char[51];
	cin.get(hold,50,'\n');
	cin.ignore(100,'\n');

	if(name)
	{
		delete [] name;
		name = NULL;
	}

	name = new char[strlen(hold)+1];
	strcpy(name,hold);

	delete [] hold;
	hold = NULL;

	return;
}

void sender::display()const
{
	if(name)
	{
		cout<<"Name : "<<name<<endl;
		cout<<"Record : "<<endl;
		message::display();
	}
	return;
}

std::ostream& operator <<(std::ostream & out,const sender & op2)
{
	out<<"Name : "<<op2.name<<endl;
	op2.message::display();	
	return out;	
}

std::istream& operator >>(std::istream & in,sender & op2)
{
	char * temp = new char[100];
	in>>temp;
	if(op2.name)
	{
		delete []op2.name;
	}
	op2.name = new char[strlen(temp)+1];
	strcpy(op2.name,temp);

	delete []temp;
	temp = NULL;

	return in;
}

bool operator ==(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) == 0);
}

bool operator ==(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) == 0);
}

bool operator ==(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) == 0);
}

bool operator !=(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) != 0);
}

bool operator !=(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) != 0);
}

bool operator !=(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) != 0);
}

bool operator >(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) > 0);
}

bool operator >(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) > 0);
}

bool operator >(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) > 0);
}

bool operator >=(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) >= 0);
}

bool operator >=(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) >= 0);
}

bool operator >=(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) >= 0);
}

bool operator <(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) < 0);
}

bool operator <(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) < 0);
}

bool operator <(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) < 0);
}

bool operator <=(const sender & op1,const char * source)
{
	return (strcmp(op1.name,source) <= 0);
}

bool operator <=(const char * source,const sender & op2)
{
	return (strcmp(source,op2.name) <= 0);
}

bool operator <=(const sender & op1,const sender & op2)
{
	return (strcmp(op1.name,op2.name) <= 0);
}

t_node::t_node()
{
	person1 = NULL;
	person2 = NULL;
	left = NULL;
	mid = NULL;
	right = NULL;
	parent = NULL;
}

t_node::t_node(const t_node & source)
{
	if(source.person1)
	{
		person1 = new sender(*source.person1);
	}
	if(source.person2)
	{
		person2 = new sender(*source.person2);
	}

	left = NULL;
	mid = NULL;
	right = NULL;
	parent = NULL;
}

void t_node::remove(const char * source)
{
	if(*person1 == source)
	{
		person1->remove_all();
		person1 = NULL;
	}
	else if(*person2 == source)
	{
		person2->remove_all();
		person2 = NULL;
	}
	return;
}

void t_node::remove_all()
{
	if(person1)
	{
		person1->remove_all();
		person1 = NULL;
	}
	if(person2)
	{
		person2->remove_all();
		person2 = NULL;
	}
	if(left)
	{
		left = NULL;
	}
	if(mid)
	{
		mid = NULL;
	}
	if(right)
	{
		right = NULL;
	}
	if(parent)
	{
		parent = NULL;
	}
}

t_node::~t_node()
{
	remove_all();
}

t_node & t_node::operator = (const t_node & source)
{
	if(this == &source)
	{
		return *this;
	}

	if(person1)
	{
		person1->remove_all();
	}
	if(person2)
	{
		person2->remove_all();
	}

	if(source.person1)
	{
		person1 = new sender;
		*person1 = *source.person1;
	}
	if(source.person2)
	{
		person2 = new sender;
		*person2 = *source.person2;
	}

	return *this;
}

t_node *& t_node::go_left()
{
	return left;
}
t_node * t_node::get_left()const
{
	return left;
}

t_node *& t_node::go_mid()
{
	return mid;
}
t_node * t_node::get_mid()const
{
	return mid;
}

t_node *& t_node::go_right()
{
	return right;
}
t_node * t_node::get_right()const
{
	return right;
}

t_node *& t_node::go_parent()
{
	return parent;
}
t_node * t_node::get_parent()const
{
	return parent;
}

void t_node::connect_left(t_node * connection)
{
	if(!connection)
	{
		return;
	}
	left = connection;
	return;
}

void t_node::connect_mid(t_node * connection)
{
	if(!connection)
	{
		return;
	}
	mid = connection;
	return;
}

void t_node::connect_right(t_node * connection)
{
	if(!connection)
	{
		return;
	}
	right = connection;
	return;
}

sender *& t_node::get_person1()
{
	return person1;
}

sender * t_node::use_person1()const
{
	return person1;
}

sender *& t_node::get_person2()
{
	return person2;
}

sender * t_node::use_person2()const
{
	return person2;
}

bool t_node::is_full()const
{
	if(person1 && person2)
	{
		return true;
	}
	return false;
}

int t_node::search(const char * source)		//serve for chat()
{
	if(!source)
	{
		return 0;
	}

	if(person1)
	{
		if(*person1 == source)
		{
			person1->message::insert();
			return 1;
		}
	}
	if(person2)
	{
		if(*person2 == source)
		{
			person2->message::insert();
			return 2;
		}
	}
	return 0;
}

bool t_node::compare(const t_node & source)
{
	if(person1 && source.person1 && !person2 && !source.person2)
	{
		if(*person1 == *source.person1)
		{
			return true;
		}
	}
	
	if(person1 && source.person1 && person2 && source.person2)
	{
		if(*person1 == *source.person1  &&  *person2 == *source.person2)
		{
			return true;
		}
	}
	return false;
}

bool t_node::is_leaf()const
{
	if(!left && !mid && !right)
	{
		return true;
	}
	return false;
}

bool t_node::have_done(const int source)
{
	int count = 0;
	if(left)
	{
		++count;
	}
	if(mid)
	{
		++count;
	}
	if(right)
	{
		++count;
	}

	if(source == count)
	{
		return true;
	}
	return false;
}

int t_node::check_direct()
{
	if(!parent)	//split the this->root
	{
		return 0;
	}
	else if(parent->left == this)
	{
		return 1;
	}
	else if(parent->mid == this)
	{
		return 2;
	}
	else if(parent->right == this)
	{
		return 3;
	}
	return 0;
}

chat_room::chat_room()
{
	root = NULL;
}

void chat_room::go_back(t_node * previous,const t_node * source)
{
	if(source->get_parent()->compare(*previous))
	{
		return;
	}
	previous = previous->go_parent();
	return go_back(previous,source);	
}

void chat_room::copy(t_node * & root,const t_node * source,t_node * previous,int step)
{
	if(!source)
	{
		root = NULL;
		return;
	}
	if(step != 0 && previous->have_done(step))
	{
		go_back(previous,source);
		step = 0;
	}
	root = new t_node(*source);
	root->go_parent() = previous;
	if(this->root == root || !source->is_leaf())
	{
		previous = root;
	}
	else if(source->is_leaf())
	{
		++step;
	}

	copy(root->go_left(),source->get_left(),previous,step);
	copy(root->go_mid(),source->get_mid(),previous,step);
	copy(root->go_right(),source->get_right(),previous,step);
	
	return;
}

chat_room::chat_room(const chat_room & source)
{
	if(source.root)
	{
		copy(root,source.root,root,0);
	}
}

void chat_room::remove_all(t_node * & root)
{
	if(!root)
	{
		return;
	}
	remove_all(root->go_left());
	remove_all(root->go_mid());
	remove_all(root->go_right());

	root->remove_all();
	return;
}

void chat_room::remove_all()
{
	if(!root)
	{
		return;
	}
	return remove_all(root);
}

chat_room::~chat_room()
{
	remove_all();
}

chat_room & chat_room::operator = (const chat_room & source)
{
	if(this == &source)
	{
		return *this;
	}

	if(root)
	{
		remove_all();
	}

	copy(root,source.root,root,0);

	return *this;
}

int chat_room::search(t_node * root,const char * source)	//serve for chat()
{
	if(!root)
	{
		return 0;
	}
	int count = 0;

	if(root->search(source))
	{
		return 1;
	}

	count = search(root->get_left(),source);
	count += search(root->get_mid(),source);
	count += search(root->get_right(),source);

	return count;
}

int chat_room::chat()	//add an new speak for a sender
{
	cout<<"Please enter your name."<<endl;
	char * your_name = new char[101];
	cin.get(your_name,100,'\n');
	cin.ignore(100,'\n');

	char * to_add = new char[strlen(your_name)+1];
	strcpy(to_add,your_name);

	if(!root)
	{
		return 0;
	}
	if(search(root,to_add))
	{
		delete []your_name;
		your_name = NULL;
		delete []to_add;
		to_add = NULL;
		return 1;
	}

	cout<<"The name did not be registered before."<<endl;

	delete []your_name;
	your_name = NULL;
	delete []to_add;
	to_add = NULL;
	return 0;
}

int chat_room::get_height(const t_node * root)
{
	if(!root)
	{
		return 0;
	}
	int left_height = 0;	
	int mid_height = 0;	
	int right_height = 0;	

	left_height += get_height(root->get_left())+1;
	mid_height += get_height(root->get_mid())+1;
	right_height += get_height(root->get_right())+1;

	if(left_height < mid_height || left_height < right_height)
	{
		return max(mid_height,right_height);
	}
	if(mid_height < left_height || mid_height < right_height)
	{
		return max(left_height,right_height);
	}
	return max(left_height,mid_height);
}

bool chat_room::should_rotate(const t_node * root)
{
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	
	if(root)
	{
		if(!root->use_person2())
		{
			count1 = get_height(root->get_left());
			count2 = get_height(root->get_mid());
			if(count1 != count2)
			{
				return true;
			}
		}
		else
		{
			count1 = get_height(root->get_left());
			count2 = get_height(root->get_mid());
			count3 = get_height(root->get_right());
			if(count1 != count2 || count1 != count3 || count2 != count3)
			{
				return true;
			}
		}
	}
	return false;
}

int chat_room::check_direct(const t_node * root)
{
	if(!root->get_parent())
	{
		return 0;
	}
	if(root == root->get_parent()->get_left())
	{
		return 1;
	}
	if(root == root->get_parent()->get_mid())
	{
		return 2;
	}
	if(root == root->get_parent()->get_right())
	{
		return 3;
	}

	return 0;
}

int chat_room::push_up(t_node * & root,int direct)	//rotate
{
	t_node * temp;
	t_node * hold;
	t_node * hold_left;
	int parent_direct;

	if(direct == 1)		//we are from the left pointer of our parent
	{
		if(root->go_parent()->get_person2())	//if our parent is full
		{
			temp = new t_node;
			hold = root->go_parent();		//hold our parent

			temp->get_person1() = hold->get_person2();
			temp->go_left() = hold->go_mid();
			temp->go_mid() = hold->go_right();
			temp->go_left()->go_parent() = temp;
			temp->go_mid()->go_parent() = temp;
			hold->go_mid() = temp;
			temp->go_parent() = hold;
			hold->get_person2() = NULL;
			hold->go_right() = NULL;
			root = hold;
		}
		else		//our parent is not full. After we have inserted a sender, the root must have a !root->person2
		{
			hold = root->go_parent();
			hold_left = root->go_left();

			hold->get_person2() = hold->get_person1();
			hold->go_right() = hold->go_mid();
			hold->go_right()->go_parent() = hold;
			hold->get_person1() = root->get_person1();
			hold->go_mid() = root->go_mid();
			root->go_mid() = NULL;
			hold->go_left() = hold_left;
			hold_left->go_parent() = hold;
			root->remove_all();
			delete root;
			root = hold;
		}
	}
	else if(direct == 2)	//we are from the mid pointer of our parent
	{
		if(root->go_parent()->get_person2())	//if our parent is full
		{
			hold = root->go_parent();
			parent_direct = check_direct(hold);
			root->go_parent() = hold->go_parent();

			if(parent_direct == 1)
			{
				root->go_parent()->go_left() = root;
			}
			if(parent_direct == 2)
			{
				root->go_parent()->go_mid() = root;
			}
			if(parent_direct == 3)
			{
				root->go_parent()->go_right() = root;
			}

			hold->go_mid() = root->go_left();

			temp = new t_node;
			temp->get_person1() = hold->get_person2();
			temp->go_mid() = hold->go_right();
			temp->go_left() = root->go_mid();
			temp->go_mid()->go_parent() = temp;
			temp->go_left()->go_parent() = temp;
			hold->get_person2() = NULL;
			hold->go_right() = NULL;
			root->go_left() = hold;
			root->go_mid() = temp;
			hold->go_parent() = root;
			temp->go_parent() = root;
		}
		else		//if our parent is not full
		{
			hold = root->go_parent();
			hold->go_mid() = root->go_left();
			hold->go_mid()->go_parent() = hold;
			hold->get_person2() = root->get_person1();
			hold->go_right() = root->go_right();
			hold->go_right()->go_parent() = hold;
			root->remove_all();
			delete root;
			root = hold;
		}
	}
	else if(direct == 3)	//we are from the right pointer of our parent
	{
		// in this case, parent is always full
		hold = root->go_parent();
		temp = new t_node;
		temp->get_person1() = hold->get_person1();
		temp->go_left() = hold->go_left();
		temp->go_left()->go_parent() = temp;
		temp->go_mid() = hold->go_mid();
		temp->go_mid()->go_parent() = temp;
		hold->go_left() = temp;
		temp->go_parent() = hold;
		hold->get_person1() = hold->get_person2();
		hold->get_person2() = NULL;
		hold->go_mid() = root;
		hold->go_right() = NULL;
		root = hold;
	}

	// Now we have to check if we need to continue on rotating //
	if(should_rotate(root->go_parent()))
	{
		direct = check_direct(root);	//since we have moved the root pointer, we should get an new direct again.
		return push_up(root,direct);	//we have moved the root pointer in the implemnetation, so pass it again.
	}
	else
	{
		return 1;
	}
}

int chat_room::add_sender(t_node * & root,const sender & source)	//add an new sender
{
	int count = 0;
	int direct = 0;
	if(root->is_leaf())	// we have arrived the leaf ---------> add the new one first
	{
		if(root->is_full())	//(person1 && person2) ----->need to push up
		{
			root->go_left() = new t_node;
			root->go_mid() = new t_node;
		
			if(source < *root->get_person1())		//when source < person1 < person2
			{
				root->go_left()->get_person1() = new sender(source);
				root->go_left()->go_parent() = root;
				root->go_mid()->get_person1() = root->get_person2();
				root->go_mid()->go_parent() = root;
				root->get_person2() = NULL;
			}
			else if(source >= *root->get_person2())	//when person1 < person2 < source
			{
				root->go_left()->get_person1() = root->get_person1();
				root->go_left()->go_parent() = root;
				root->go_mid()->get_person1() = new sender(source);
				root->go_mid()->go_parent() = root;
				root->get_person1() = root->get_person2();
				root->get_person2() = NULL;
			}
			else		// when person1 < source < person2
			{
				root->go_left()->get_person1() = root->get_person1();
				root->go_left()->go_parent() = root;
				root->go_mid()->get_person1() = root->get_person2();
				root->go_mid()->go_parent() = root;
				root->get_person1() = new sender(source);
				root->get_person2() = NULL;
			}

			// after we have inserted it //
			//--------------ask if we should rotate (pass the parent)-------------//
	
			if(should_rotate(root->go_parent()))
			{
				direct = check_direct(root);
				if(push_up(root,direct))
				{
					cout<<"We have rotated the 2-3 tree!"<<endl;
				}
			}
			return 1;
		}
		else	//only when (person1 && !person2)
		{
			if(source >= *root->get_person1())
			{
				root->get_person2() = new sender(source);
			}
			else
			{
				root->get_person2() = root->get_person1();
				root->get_person1() = new sender(source);
			}
			return 1;
		}
	}
	
	//------------------------traverse to the leaf------------------------//
	if(source < *root->get_person1())
	{
		count += add_sender(root->go_left(),source);
	}
	else if(!root->get_person2())
	{
		count += add_sender(root->go_mid(),source);
	}
	else
	{
		if(source < *root->get_person2())
		{
			count += add_sender(root->go_mid(),source);
		}
		else
		{
			count += add_sender(root->go_right(),source);
		}
	}

	return count;	
}

int chat_room::add_sender(const sender & source)
{
	if(!root)
	{
		root = new t_node;
		root->get_person1() = new sender(source);
		return 1;
	}
	return add_sender(root,source);
}

int chat_room::display(const t_node * root)const	//in order display
{
	if(!root)
	{
		return 0;
	}
	int count = 0;

	count = display(root->get_left());

	if(root->use_person1())
	{
		root->use_person1()->display();
		++count;
	}

	count += display(root->get_mid());

	if(root->use_person2())
	{
		root->use_person2()->display();
		++count;
	}

	count += display(root->get_right());

	return count;
}

int chat_room::display()const
{
	if(!root)
	{
		cout<<"The chat room is empty now."<<endl;
		return 0;
	}
	return display(root);
}


