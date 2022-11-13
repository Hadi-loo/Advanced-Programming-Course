#ifndef _DOCUMENT_HPP_
#define _DOCUMENT_HPP_

#include <iostream>
#include <vector>
using namespace std;

class Organization;
class Document
{
public:
	Document(string _name);

	void add_org(Organization* _org);

	virtual void confirm();

	void notify();

	virtual void print_info(int tabs_count);

	bool is_ok();

	bool is_same(string _name);

	virtual void set_origin(Organization* _origin_org);

	virtual void set_final(bool _is_final);

protected:
	string name;
	bool status;
	vector<Organization*> orgs;
};

class Form : public Document
{
public:
	Form(string _name, string _content);

	void print_info(int tabs_count);

	void set_origin(Organization* _origin_org);

private:
	string content;
};

class Permition : public Document
{
public:
	Permition(string _name);

	void set_origin(Organization* _origin_org);

	void print_info(int tabs_count);

	void confirm();

	void set_final(bool _is_final);

private:
	Organization* origin_org;
	bool is_final;
};

#endif