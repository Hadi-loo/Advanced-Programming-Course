#include "organization.hpp"
#include "main.hpp"

Organization::Organization(string _name, char _sign_type, Document* _permit, string _manager, string _ceo)
{
	name = _name;
	sign_type = _sign_type;
	permit = _permit;
	manager = _manager;
	ceo = _ceo;
}

void Organization::add_requirment(Document* new_req)
{
	requirments.push_back(new_req);
}


void Organization::update()
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

void Organization::issue_permit()
{
	permit->confirm();
}

string Organization::get_signature()
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

void Organization::print_info(int tabs_count)
{
	for (int i = 0; i < requirments.size(); i++)
	{
		cout << tabs(tabs_count) << "#" << i+1 << endl;
		requirments[i]->print_info(tabs_count);
	}
	cout << tabs(tabs_count-1) << "}" << endl;
	cout << tabs(tabs_count-1) << "Signature: " << this->get_signature() << endl;
}