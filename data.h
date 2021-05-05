//Shang-Chun, Lin CS202 assignment#3
#include <iostream>
#include <cctype>
#include <cstring>

//This class interface includes an abtract base class info and two derived classes for different expressions.
class word;
class emoji;

class info
{
	public:
		info();
		virtual ~info();
		virtual info & operator = (const info & source);
		virtual info & operator += (const info & source);

		friend bool operator ==(const info &,const char *);
		friend bool operator ==(const char *,const info &);
		friend bool operator ==(const info &,const info &);

		friend bool operator !=(const info &,const char *);
		friend bool operator !=(const char *,const info &);
		friend bool operator !=(const info &,const info &);

		friend std::ostream& operator <<(std::ostream &,const info &);
		friend std::istream& operator >>(std::istream &,info &);

		virtual void insert(std::istream &) = 0;		//serve for >>
		virtual void display(std::ostream &)const = 0;		//serve for <<
		virtual void remove_all() = 0;				//serve for destructor
		virtual bool compare(const char *)const;		//serve for ==,!=
		virtual bool compare(const word &)const;		//serve for ==,!=
		virtual bool compare(const emoji&)const;		//serve for ==,!=
};

class word : public info	//like string
{
	public:
		word();
		word(const word &);
		~word();
		word & operator = (const word & source);
		word & operator += (const word & source);

		void insert(std::istream &);			//serve for >>
		void display(std::ostream &)const;		//serve for <<
		void remove_all();				//serve for destructor
		bool compare(const word &)const;		//serve for ==,!=
		bool compare(const char *)const;		//serve for ==,!=
	protected:
		char * talk;
};

class emoji : public info
{
	public:
		emoji();
		emoji(const emoji &);
		~emoji();
		emoji & operator = (const emoji & source);
		emoji & operator += (const emoji & source);

		void insert(std::istream &);			//serve for >>
		void display(std::ostream &)const;		//serve for <<
		void remove_all();				//serve for destructor
		bool compare(const emoji &)const;		//serve for ==,!=
		bool compare(const char *)const;		//serve for ==,!=
	protected:
		char * face;
};
