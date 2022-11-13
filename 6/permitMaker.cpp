#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
//=============================================================================
string tabs(int tabs_count);

class Organization;
class Document	// subject, publisher
{
public:
	Document(string _name)
	{
		name = _name;
		status = false;	
	}

	void add_org(Organization* _org)
	{
		orgs.push_back(_org);
	}

	virtual void confirm()
	{
		status = true;
		notify();
	}

	void notify();

	virtual void print_info(int tabs_count)
	{

	}

	bool is_ok()
	{
		return status;
	}

	bool is_same(string _name)
	{
		if (name == _name)
			return true;
		return false;
	}

	virtual void set_origin(Organization* _origin_org)
	{
		cout << "ure fucked baby :(" << endl;     //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

	virtual void set_final(bool _is_final)
	{

	}

protected:
	string name;
	bool status;
	vector<Organization*> orgs;
};
//-----------------------------------------------------------------------------
class Form : public Document
{
public:
	Form(string _name, string _content)
	:Document(_name)
	{
		content = _content;
	}

	void print_info(int tabs_count)
	{
		cout << tabs(tabs_count) << "Name: " << name << endl;
		cout << tabs(tabs_count) << "Content: " << content << endl;
	}

	void set_origin(Organization* _origin_org)
	{
		cout << "ure fucked babe :(" << endl;     //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	}

private:
	string content;
};
//-----------------------------------------------------------------------------
class Permition : public Document
{
public:
	Permition(string _name)
	: Document(_name){};

	void set_origin(Organization* _origin_org)
	{
		origin_org = _origin_org;
	}

	void print_info(int tabs_count);

	void confirm()
	{
		status = true;
		if (!(is_final))
		{
			notify();
		}
		else
		{
			print_info(0);
			exit(0);
		}
	}

	void set_final(bool _is_final)
	{
		is_final = _is_final;
	}

private:
	Organization* origin_org;
	bool is_final;
};
//=============================================================================
class Organization  // observer 
{
public:
	Organization(string _name, char _sign_type, Document* _permit, string _manager, string _ceo)
	{
		name = _name;
		sign_type = _sign_type;
		permit = _permit;
		manager = _manager;
		ceo = _ceo;
	}

	void add_requirment(Document* new_req)
	{
		requirments.push_back(new_req);
	}


	void update()
	{
		for (auto x : requirments)
		{
			if (!(x->is_ok()))
			{
				return;
			}
		}
		issue_permit();
	}

	void issue_permit()
	{
		permit->confirm();
	}

	string get_signature()
	{
		if (sign_type == 'm')
		{
			return manager;
		}
		else if (sign_type == 'c')
		{
			return ceo;
		}
		else
		{
			return name;
		}
	}

	void print_info(int tabs_count)
	{
		for (int i = 0; i < requirments.size(); i++)
		{
			cout << tabs(tabs_count) << "#" << i+1 << endl;
			requirments[i]->print_info(tabs_count);
		}
		cout << tabs(tabs_count-1) << "}" << endl;
		cout << tabs(tabs_count-1) << "Signature: " << this->get_signature() << endl;
	}

private:
	string name;
	char sign_type;
	Document* permit;
	vector <Document*> requirments;
	string manager;
	string ceo;
};
//=============================================================================
void Document::notify()
{
	for (auto x : orgs)
		x->update();
}

void Permition::print_info(int tabs_count)
{
	cout << tabs(tabs_count) << "Name: " << name << endl;
	cout << tabs(tabs_count) << "This permit consists of: {" << endl;
	origin_org->print_info(tabs_count+1);
}

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

//=============================================================================
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