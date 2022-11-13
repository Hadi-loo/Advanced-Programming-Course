#include "document.hpp"
#include "organization.hpp"
#include "main.hpp"

Document::Document(string _name)
{
	name = _name;
	status = false;	
}

void Document::add_org(Organization* _org)
{
	orgs.push_back(_org);
}

void Document::confirm()
{
	status = true;
	notify();
}

void Document::print_info(int tabs_count)
{

}

bool Document::is_ok()
{
	return status;
}

bool Document::is_same(string _name)
{
	if (name == _name)
		return true;
	return false;
}

void Document::set_origin(Organization* _origin_org)
{

}

void Document::set_final(bool _is_final)
{

}

void Document::notify()
{
	for (auto x : orgs)
		x->update();
}

Form::Form(string _name, string _content)
:Document(_name)
{
	content = _content;
}

void Form::print_info(int tabs_count)
{
	cout << tabs(tabs_count) << "Name: " << name << endl;
	cout << tabs(tabs_count) << "Content: " << content << endl;
}

void Form::set_origin(Organization* _origin_org)
{

}



Permition::Permition(string _name)
: Document(_name){};

void Permition::set_origin(Organization* _origin_org)
{
	origin_org = _origin_org;
}

void Permition::confirm()
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

void Permition::set_final(bool _is_final)
{
	is_final = _is_final;
}

void Permition::print_info(int tabs_count)
{
	cout << tabs(tabs_count) << "Name: " << name << endl;
	cout << tabs(tabs_count) << "This permit consists of: {" << endl;
	origin_org->print_info(tabs_count+1);
}