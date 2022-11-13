#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
//---------------------------------------------------------------------------------------------------------------------------------------------------
class simulator;
class train;
class passenger;
class station;
//---------------------------------------------------------------------------------------------------------------------------------------------------
class station {
public:
	station(string station_name_, int taffy_price_);
	bool is_same(string station_name_);
	int get_price(void);
	string get_name();
private:
	string station_name;
	int taffy_price;
};

class simulator {
public:
	void add_station(string station_name, int taffy_price);
	void add_train(string station1_name, string station2_name, int travel_time, int cooldown_time);
	void add_passenger(int taffy_addiction, vector <string> road);
	void advance_time(void);
	void show_passenger_info(int passenger_id);
	void show_train_info(int train_id);
	bool all_are_arrived(void);
private:
	vector <train> trains;
	vector <station> stations;
	vector <passenger> passengers;
	station* find_station_by_name(string station_name)
	{
		for (int i = 0; i < stations.size(); i++)
			if (stations[i].is_same(station_name))
				return &(stations[i]);
	}
};

class train {
public:
	train(string station1_name_, string station2_name_, int travel_time_, int cooldown_time_, int train_id_);
	string is_waiting_in(void);
	string is_going_to(void);
	int get_status(void);
	int get_remaining_time(void);
	void set_remaining_time(int new_remaining_time);
	void set_status(int new_status);
	void evacuate(void);
	void add_passenger(passenger* new_passenger);
	int get_id(void);
	void show_info(void);
private:
	string station1_name;
	string station2_name;
	int travel_time;
	int cooldown_time;
	int status;
	int train_id;
	vector<passenger*> passengers;
	int remaining_time;
};

class passenger {
public:
	passenger(int taffy_addiction, vector <station*> road, int passenger_id);
	bool is_waiting(void);
	bool is_in_train(void);
	bool is_in_destination(void);
	station* get_current_station(void);
	station* get_next_station(void);
	void set_status(int new_status);
	void set_cur_train(train* new_train);
	void increase_spent(int price);
	train* get_cur_train();
	void increse_current_station_index(void);
	int get_spent(void);
	int get_status(void);
	string get_destination_name(void);
private:
	int status;
	int passenger_id;
	int spent;
	int taffy_addiction;
	vector <station*> road;
	int current_station_index;
	train* cur_train;
};

//---------------------------------------------------------------------------------------------------------------------------------------------------
station::station(string station_name_, int taffy_price_)
{
	station_name = station_name_;
	taffy_price = taffy_price_;
}
bool station::is_same(string station_name_)
{
	if (station_name == station_name_)
		return true;
	return false;
}
int station::get_price(void)
{
	return taffy_price;
}
string station::get_name(void)
{
	return station_name;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
train::train(string station1_name_, string station2_name_, int travel_time_, int cooldown_time_, int train_id_)
{
	station1_name = station1_name_;
	station2_name = station2_name_;
	travel_time = travel_time_;
	cooldown_time = cooldown_time_;
	train_id = train_id_;
	status = 0;
	remaining_time = cooldown_time;
}
string train::is_waiting_in(void)
{
	if (status == 0 || status == 6 || status == 7)
		return station1_name;
	else if (status == 4 || status == 3 || status == 2)
		return station2_name;
	else
		return "";
}
string train::is_going_to(void)
{
	if ((status == 0) || (status == 1) || (status == 2) || (status == 7))
		return station2_name;
	else if ((status == 3) || (status == 4) || (status == 5) || (status == 6))
		return station1_name;
}
int train::get_status(void)
{
	return status;
}
int train::get_remaining_time(void)
{
	return remaining_time;
}
void train::set_remaining_time(int new_remaining_time)
{
	if (new_remaining_time == 0)
		remaining_time--;
	else if (new_remaining_time == 1)
		remaining_time = travel_time;
	else if (new_remaining_time == 2)
		remaining_time = cooldown_time;
}
void train::set_status(int new_status)
{
	status = new_status;
}
void train::evacuate(void)
{
	passengers.clear();
}
void train::add_passenger(passenger* new_passenger)
{
	passengers.push_back(new_passenger);
}
int train::get_id()
{
	return train_id;
}
void train::show_info(void)
{
	cout << "status : ";
	if ((status == 1) || (status == 2) || (status == 5) || (status == 6))
		cout << "moving" << endl;
	else if ((status == 0) || (status == 3) || (status == 4) || (status == 7))
		cout << "resting" << endl;
	cout << "estimated remaining time : " << remaining_time << endl;
	cout << "next station : ";
	if ((status == 0) || (status == 1) || (status == 2) || (status == 7))
		cout << station2_name << endl;
	else if ((status == 0) || (status == 3) || (status == 4) || (status == 7))
		cout << station1_name << endl;
	cout << "passengers count : " << passengers.size() << endl;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
passenger::passenger(int taffy_addiction_, vector <station*> road_, int passenger_id_)
{
	taffy_addiction = taffy_addiction_;
	road = road_;
	spent = 0;
	status = 0;
	current_station_index = 0;
	passenger_id = passenger_id_;
}
bool passenger::is_waiting(void)
{
	if (status == 0)
		return true;
	return false;
}
bool passenger::is_in_train(void)
{
	if (status == 1)
		return true;
	return false;
}
bool passenger::is_in_destination(void)
{
	if ((status == 2) || (current_station_index >= road.size() - 1))
		return true;
	return false;
}
station* passenger::get_current_station(void)
{
	return road[current_station_index];
}
station* passenger::get_next_station(void)
{
	return road[current_station_index + 1];
}
void passenger::set_status(int new_status)
{
	status = new_status;
}
void passenger::set_cur_train(train* new_train)
{
	cur_train = new_train;
}
void passenger::increase_spent(int price)
{
	spent += price*taffy_addiction;
}
train* passenger::get_cur_train()
{
	return cur_train;
}
void passenger::increse_current_station_index(void)
{
	current_station_index++;
}
int passenger::get_spent(void)
{
	return spent;
}
int passenger::get_status(void)
{
	return status;
}
string passenger::get_destination_name(void)
{
	return ((road[road.size() - 1])->get_name());
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void simulator::add_station(string station_name, int taffy_price)
{
	stations.push_back(station(station_name, taffy_price));
}
void simulator::add_train(string station1_name, string station2_name, int travel_time, int cooldown_time)
{
	trains.push_back(train(station1_name, station2_name, travel_time, cooldown_time, trains.size() + 1));
}
void simulator::add_passenger(int taffy_addiction, vector <string> station_names)
{
	vector <station*> road;
	for (int i = 0; i < station_names.size(); i++)
	{
		road.push_back(find_station_by_name(station_names[i]));
	}
	passengers.push_back(passenger(taffy_addiction, road, passengers.size() + 1));
}
void simulator::advance_time(void)
{
	for (int i = 0; i < passengers.size(); i++)
	{
		if ((passengers[i]).is_in_destination())
		{
			(passengers[i]).set_status(2);
		}
		else
		{
			if ((passengers[i]).is_waiting())
			{
				bool waiting_for_evacuate = true;
				for (int j = 0; j < trains.size(); j++)
				{
					if ((passengers[i]).get_current_station()->is_same((trains[j]).is_waiting_in()))
					{
						if ((passengers[i]).get_next_station()->is_same((trains[j]).is_going_to()))
						{
							if ((trains[j].get_status() != 2) && (trains[j].get_status() != 6))
							{
								(passengers[i]).set_status(1);
								(passengers[i]).set_cur_train(&(trains[j]));
								(trains[j]).add_passenger(&(passengers[i]));
								waiting_for_evacuate = true;
								break;
							}
							else
							{
								waiting_for_evacuate = false;
							}
						}
					}
				}
				if (((passengers[i]).is_waiting()) && (waiting_for_evacuate == true))
				{
					(passengers[i]).increase_spent(((passengers[i]).get_current_station())->get_price());
				}
			}
			else if ((passengers[i]).is_in_train())
			{
				if (((((passengers[i]).get_cur_train())->get_status()) == 2) || ((((passengers[i]).get_cur_train())->get_status()) == 6))
				{
					(passengers[i]).set_status(0);
					(passengers[i]).increse_current_station_index();
				}
			}
		}
	}
	for (int i = 0; i < trains.size(); i++)
	{
		int train_status = (trains[i]).get_status();
		if ((train_status == 0) || (train_status == 4))
		{
			if ((trains[i]).get_remaining_time() == 1)
			{
				(trains[i]).set_status(train_status + 1);
				(trains[i]).set_remaining_time(1);
			}
			else
				(trains[i]).set_remaining_time(0);
		}
		else if ((train_status == 1) || (train_status == 5))
		{
			if ((trains[i]).get_remaining_time() == 2)
			{
				(trains[i]).set_status(train_status + 1);
			}
			(trains[i]).set_remaining_time(0);
		}
		else if ((train_status == 2) || (train_status == 6))
		{
			(trains[i]).set_status(train_status + 1);
			(trains[i]).set_remaining_time(2);
			(trains[i]).evacuate();
		}
		else if ((train_status == 3) || (train_status == 7))
		{
			(trains[i]).set_status((train_status + 1) % 8);
			(trains[i]).set_remaining_time(0);
		}
	}
}
void simulator::show_passenger_info(int passenger_id)
{
	passenger sample = passengers[passenger_id - 1];
	cout << "status : ";
	if (sample.is_in_destination())
		cout << "arrived" << endl;
	else if (sample.is_waiting())
		cout << "in station" << endl;
	else if (sample.is_in_train())
		cout << "on train" << endl;
	cout << "spent : " << sample.get_spent() << endl;
	cout << "current ";
	if (sample.is_in_destination())
		cout << "station " << sample.get_destination_name() << endl;
	else if (sample.is_waiting())
		cout << "station " << (sample.get_current_station())->get_name() << endl;
	else if (sample.is_in_train())
		cout << "train " << (sample.get_cur_train())->get_id() << endl;
}
void simulator::show_train_info(int train_id)
{
	train sample = trains[train_id - 1];
	sample.show_info();
}
bool simulator::all_are_arrived(void)
{
	for (int i = 0; i < passengers.size(); i++)
	{
		if (!(passengers[i].is_in_destination()))
		{
			return false;
		}
	}
	return true;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void parse_line(string line, vector<string>& strings)
{
	stringstream ss(line);
	string word;
	while (ss >> word)
	{
		strings.push_back(word);
	}
}
void run_commands(string command, simulator* Simulator)
{
	if (command == "add_station")
	{
		string station_name;
		int taffy_price;
		cin >> station_name >> taffy_price;
		Simulator->add_station(station_name, taffy_price);
		cout << "OK" << endl;
	}
	else if (command == "add_train")
	{
		string station1_name;
		string station2_name;
		int travel_time;
		int cooldown_time;
		cin >> station1_name >> station2_name >> travel_time >> cooldown_time;
		Simulator->add_train(station1_name, station2_name, travel_time, cooldown_time);
		cout << "OK" << endl;
	}
	else if (command == "add_passenger")
	{
		int taffy_addiction;
		string input_line;
		vector <string> station_names;
		cin >> taffy_addiction;
		getline(cin, input_line);
		parse_line(input_line, station_names);
		Simulator->add_passenger(taffy_addiction, station_names);
		cout << "OK" << endl;
	}
	else if (command == "advance_time")
	{
		int time_steps;
		cin >> time_steps;
		for (int i = 0; i < time_steps; i++)
		{
			Simulator->advance_time();
		}
		cout << "OK" << endl;
	}
	else if (command == "finish")
	{
		while (!(Simulator->all_are_arrived()))
		{
			Simulator->advance_time();
		}
		cout << "OK" << endl;
	}
	else if (command == "show_passenger_info")
	{
		int passenger_id;
		cin >> passenger_id;
		Simulator->show_passenger_info(passenger_id);
	}
	else if (command == "show_train_info")
	{
		int train_id;
		cin >> train_id;
		Simulator->show_train_info(train_id);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
	simulator Simulator;
	string command;
	while (cin >> command)
	{
		run_commands(command, &Simulator);
	}
	return 0;
}