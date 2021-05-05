//Shang-Chun, Lin CS202 assignment#3
#include "data.h"

//This file has the classes for managing a chat room, which is implemented by a 2-3 tree and a LLL in each sender.

//A l_node(LLL) node "has a" data class (ABC), and a t_node(2-3 tree) "has a" sender class.

class l_node
{
	public:
		l_node();
		l_node(const l_node & source);
		~l_node();

		l_node & operator = (const l_node & source);

		l_node *& go_next();
		l_node * get_next()const;
		void connect_next(l_node * connection);
		void remove();
		info *& get_data();
		info * use_data()const;

	protected:
		info * data;
		l_node * next;
};

class message
{
	public:
		message();
		message(const message & source);
		~message();

		message & operator = (const message & source);

		int insert();
		int remove();
		void display()const;
		void remove_all();

	protected:
		l_node * head;

		void copy(l_node * & head,const l_node * source);
		void remove_all(l_node * & head);
		int remove(l_node * & head,const char * source);
		void display(const l_node * head)const;
};

class sender : public message
{
	public:
		sender();
		sender(const sender & source);
		~sender();

		sender & operator = (const sender & source);
		friend std::ostream& operator <<(std::ostream &,const sender &);
		friend std::istream& operator >>(std::istream &,sender &);

		friend bool operator ==(const sender &,const char *);
		friend bool operator ==(const char *,const sender &);
		friend bool operator ==(const sender &,const sender &);

		friend bool operator !=(const sender &,const char *);
		friend bool operator !=(const char *,const sender &);
		friend bool operator !=(const sender &,const sender &);

		friend bool operator >(const sender &,const char *);
		friend bool operator >(const char *,const sender &);
		friend bool operator >(const sender &,const sender &);

		friend bool operator >=(const sender &,const char *);
		friend bool operator >=(const char *,const sender &);
		friend bool operator >=(const sender &,const sender &);

		friend bool operator <(const sender &,const char *);
		friend bool operator <(const char *,const sender &);
		friend bool operator <(const sender &,const sender &);

		friend bool operator <=(const sender &,const char *);
		friend bool operator <=(const char *,const sender &);
		friend bool operator <=(const sender &,const sender &);

		void set_name();
		void remove_all();	//delete everything
		void remove();		//delete self
		void display()const;

	protected:
		char * name;
};

class t_node
{
	public:
		t_node();
		t_node(const t_node & source);
		~t_node();

		t_node & operator = (const t_node & source);

		t_node *& go_left();
		t_node * get_left()const;
		t_node *& go_mid();
		t_node * get_mid()const;
		t_node *& go_right();
		t_node * get_right()const;
		t_node *& go_parent();
		t_node * get_parent()const;
		void connect_left(t_node * connection);
		void connect_mid(t_node * connection);
		void connect_right(t_node * connection);
		sender *& get_person1();
		sender * use_person1()const;
		sender *& get_person2();
		sender * use_person2()const;
		
		void remove(const char *);
		void remove_all();
		bool is_full()const;
		bool is_leaf()const;
		bool have_done(const int source);
		bool compare(const t_node &);
		int search(const char *);	//serve for chat()
		int check_direct();	//serve for add_sender in chat_room class

		//if the node is full, then return the mid one and the one which should be split(returned as argument)
		sender* pushup(const sender &,sender *&,int);

	protected:
		sender * person1;
		sender * person2;
		t_node * left;
		t_node * mid;
		t_node * right;
		t_node * parent;
};

class chat_room
{
	public:
		chat_room();
		chat_room(const chat_room & source);
		~chat_room();
		
		chat_room & operator = (const chat_room & source);

		int add_sender(const sender &);
		int chat();
		int display()const;
		void remove_all();

	protected:
		t_node * root;

		int add_sender(t_node * &,const sender &);
		int push_up(t_node * &,int);
		void copy(t_node * &,const t_node *,t_node *,int);
		void remove_all(t_node * &);
		int display(const t_node *)const;
		void go_back(t_node *,const t_node *);
		int search(t_node *,const char *);	//serve for chat()
		int get_height(const t_node *);			//serve for should_rotate()
		bool should_rotate(const t_node *);		//serve for add_sender()
		int check_direct(const t_node *);		//serve for add_sender()
};
















