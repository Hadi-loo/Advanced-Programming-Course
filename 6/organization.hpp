#ifndef _ORGANIZATION_HPP_
#define _ORGANIZATION_HPP_

#include <iostream>
#include <vector>
#include "document.hpp"
using namespace std;

class Organization
{
public:
	Organization(string _name, char _sign_type, Document* _permit, string _manager, string _ceo);
	
	void add_requirment(Document* new_req);
	
	void update();
	
	void issue_permit();

	string get_signature();

	void print_info(int tabs_count);

private:
	string name;
	char sign_type;
	Document* permit;
	vector <Document*> requirments;
	string manager;
	string ceo;
};

#endif