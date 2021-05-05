//Shang-Chun, Lin CS202 assignment#3
#include "data.h"

using namespace std;
//The purpose of this file is to implement each function in the data.h file

class word;
class emoji;

info::info()
{
}

info::~info()
{
}

info& info::operator = (const info & source)
{
	return *this;
}

info& info::operator += (const info & source)
{
	return *this;
}

bool operator ==(const info & op1,const char * source)
{
	if(op1.compare(source))
	{
		return true;
	}
	return false;
}

bool operator ==(const char * source,const info & op2)
{
	if(op2.compare(source))
	{
		return true;
	}
	return false;
}

bool operator ==(const info & op1,const info & op2)
{
	const word * pword = dynamic_cast<const word *>(&op2);
	const emoji * pemoji = dynamic_cast<const emoji *>(&op2);

	if(pword)
	{
		if(op1.compare(*pword))
		{
			return true;
		}
	}
	else if(pemoji)
	{
		if(op1.compare(*pemoji))
		{
			return true;
		}
	}
	return false;
}

bool operator !=(const info & op1,const char * source)
{
	if(!op1.compare(source))
	{
		return true;
	}
	return false;
}

bool operator !=(const char * source,const info & op2)
{
	if(!op2.compare(source))
	{
		return true;
	}
	return false;
}

bool operator !=(const info & op1,const info & op2)
{
	const word * pword = dynamic_cast<const word *>(&op2);
	const emoji * pemoji = dynamic_cast<const emoji *>(&op2);

	if(pword)
	{
		if(op1.compare(*pword))
		{
			return false;
		}
	}
	else if(pemoji)
	{
		if(op1.compare(*pemoji))
		{
			return false;
		}
	}
	return true;
}

std::ostream& operator <<(std::ostream & out,const info & op2)
{
	op2.display(out);
	return out;
}

std::istream& operator >>(std::istream & in,info & op2)
{
	op2.insert(in);
	return in;
}

bool info::compare(const char *)const
{
	return true;
}

bool info::compare(const word &)const
{
	return true;
}

bool info::compare(const emoji&)const
{
	return true;
}

word::word()
{
	talk = NULL;
}

word::word(const word & source)
{
	if(source.talk)
	{
		talk = new char[strlen(source.talk)+1];
		strcpy(talk,source.talk);
	}
}

void word::remove_all()		//serve for destructor
{
	if(talk)
	{
		delete []talk;
	}
	talk = NULL;
}

word::~word()
{
	remove_all();
}

word & word::operator = (const word & source)
{
	if(this == &source)
	{
		return *this;
	}
	if(talk)
	{
		delete []talk;
	}
	talk = new char[strlen(source.talk)+1];
	strcpy(talk,source.talk);

	return *this;
}

word & word::operator += (const word & source)
{
	char * temp;
	if(!talk)
	{
		temp = new char[strlen(source.talk)+1];
		strcpy(temp,source.talk);
	}
	else
	{
		temp = new char[strlen(talk)+strlen(source.talk)+1];
		strcpy(temp,talk);
		strcat(temp,source.talk);
	}

	if(talk)
	{
		delete []talk;
	}
	talk = temp;

	return *this;
}

void word::insert(std::istream & in)	//serve for >>
{
	char * temp = new char[100];
	in>>temp;
	if(talk)
	{
		delete []talk;
	}
	talk = new char[strlen(temp)+1];
	strcpy(talk,temp);

	delete []temp;
	temp = NULL;

	return;
}

void word::display(std::ostream & out)const	//serve for <<
{
	if(talk)
	{
		out<<talk;
	}
	return;
}

bool word::compare(const word & source)const	//serve for ==,!=
{
	if(!talk || !source.talk)
	{
		return false;
	}
	if(strcmp(talk,source.talk) == 0)
	{
		return true;
	}
	return false;
}

bool word::compare(const char * source)const	//serve for ==,!=
{
	if(!talk || !source)
	{
		return false;
	}
	if(strcmp(talk,source) == 0)
	{
		return true;
	}
	return false;
}

emoji::emoji()
{
	face = NULL;
}

emoji::emoji(const emoji & source)
{
	if(source.face)
	{
		face = new char[strlen(source.face)+1];
		strcpy(face,source.face);
	}
}

void emoji::remove_all()	//serve for destructor
{
	if(face)
	{
		delete []face;
	}
	face = NULL;
}

emoji::~emoji()
{
	remove_all();
}

emoji & emoji::operator = (const emoji & source)
{
	if(this == &source)
	{
		return *this;
	}
	if(face)
	{
		delete []face;
	}
	face = new char[strlen(source.face)+1];
	strcpy(face,source.face);

	return *this;
}

emoji & emoji::operator += (const emoji & source)
{
	char * temp;
	if(!face)
	{
		temp = new char[strlen(source.face)+1];
		strcpy(temp,source.face);
	}
	else
	{
		temp = new char[strlen(face)+strlen(source.face)+1];
		strcpy(temp,face);
		strcat(temp,source.face);
	}

	if(face)
	{
		delete []face;
	}
	face = temp;

	return *this;
}

void emoji::insert(std::istream & in)	//serve for >>
{
	char * temp = new char[100];
	in>>temp;
	if(face)
	{
		delete []face;
	}
	face = new char[strlen(temp)+1];
	strcpy(face,temp);

	delete []temp;
	temp = NULL;

	return;
}

void emoji::display(std::ostream & out)const	//serve for <<
{
	if(face)
	{
		out<<face;
	}
	return;
}

bool emoji::compare(const emoji & source)const	//serve for ==,!=
{
	if(!face || !source.face)
	{
		return false;
	}
	if(strcmp(face,source.face) == 0)
	{
		return true;
	}
	return false;
}

bool emoji::compare(const char * source)const	//serve for ==,!=
{
	if(!face || !source)
	{
		return false;
	}
	if(strcmp(face,source) == 0)
	{
		return true;
	}
	return false;
}
