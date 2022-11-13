#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "organization.hpp"
#include "document.hpp"
#include "main.hpp"
using namespace std;

string tabs(int tabs_count)
{
	string s;
	for (int i = 0; i < tabs_count; i++)
	{
		s += "    ";
	}
	return s;
}

Document* find_permition(string _name, vector <Document*> &documents)
{
	for (auto x : documents)
	{
		if (x->is_same(_name))
		{
			return x;
		}
	}
	Permition* new_doc = new Permition(_name);
	documents.push_back(new_doc);
	return new_doc;
}

Document* find_form(string _name, vector <Document*> documents)
{
	for (auto x : documents)
	{
		if (x->is_same(_name))
		{
			return x;
		}
	}
	return NULL;
}

string to_string(char* a)
{
	string s = a;
	return s;
}

void create_orgs(string orgs_file_name, vector <Document*> &documents, vector <Organization*> &orgs)
{
	ifstream orgs_file(orgs_file_name);
	string line, word, temp, _temp_;
	string name, sign_type, permit_name, doc_name, manager, ceo;
	getline(orgs_file, line);
	bool is_final = true;
	while (getline(orgs_file, line))
	{
		stringstream ss(line);
		getline(ss, name, ',');
		getline(ss, sign_type, ',');
		getline(ss, permit_name, ',');
		Document* permit = find_permition(permit_name, documents);
		permit->set_final(is_final);
		if (is_final)
			is_final = false;
		getline(ss, word, ',');
		getline(ss, manager, ',');
		getline(ss, ceo, ',');
		Organization* new_org = new Organization(name, sign_type[0], permit, manager, ceo);
		orgs.push_back(new_org);
		permit->set_origin(new_org);
		stringstream _ss_(word);
		while (getline(_ss_, doc_name, '-'))
		{
			if (doc_name[0] == 'p')
			{
				Document* temp_permit = find_permition(doc_name, documents);
				new_org->add_requirment(temp_permit);
				temp_permit->add_org(new_org);
			}
			else if (doc_name[0] == 'f')
			{
				Document* temp_form = find_form(doc_name, documents);
				new_org->add_requirment(temp_form);
				temp_form->add_org(new_org);
			}
		}
		
	}
}

void create_docs(string forms_file_name, vector <Document*> &documents)
{
	ifstream forms_file(forms_file_name);
	string line, word, form_name, form_content, temp, permit_name , _temp_;
	getline(forms_file, line);
	while (getline(forms_file, line))
	{
		stringstream ss(line);
		getline(ss, form_name, ',');
		getline(ss, form_content, ',');
		documents.push_back(new Form(form_name, form_content));
	}
}

int main(int argc, char* argv[])
{
	string orgs_file_name = to_string(argv[1]);
	string forms_file_name = to_string(argv[2]);
	vector <Organization*> orgs;
	vector <Document*> documents;
	create_docs(forms_file_name, documents);
	create_orgs(orgs_file_name, documents , orgs);
	string form_name;
	for (int i = 0; i < orgs.size(); i++)
	{
		orgs[i]->update();
	}
	while (cin >> form_name)
	{
		if (form_name == "confirm")
		{
			cin >> form_name;
			(find_form(form_name, documents))->confirm();
		}
	}
	return 0;
}