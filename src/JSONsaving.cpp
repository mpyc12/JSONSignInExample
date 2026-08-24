#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using json = nlohmann::ordered_json;
using namespace std;

const string& filename = "save_file.json";

void saveFile(const json& data) {
	ofstream file(filename);
	if(file.is_open()) {
		file << data.dump(4);
		file.close();
	} else {
		cerr << "Failed to open file!";
	}
}

json readFile() {
	ifstream file(filename);
	json data;
	if(file.is_open()) {
		file >> data;
		file.close();
	} else {
		data["Users"] = json::array();
		cerr << "Failed to open file!";
	}
	return data;
}

void addUser(string username, string password) {
	json data = readFile();
	json newUser;
	newUser["username"] = username;
	newUser["password"] = password;
	data["Users"].push_back(newUser);
	cout << "Added user" << endl;
	saveFile(data);
}

bool searchForUser(string username, string password) {
	json data = readFile();
	bool userFound = false;
	for (const json& user : data["Users"]) {
		if (user["username"] == username && user["password"] == password) {
			userFound = true;
		}
	}
	if (userFound) {
		return true;
	} else {
		return false;
	}
}

bool searchForUsername(string username) {
	json data = readFile();
	bool usernameFound = false;
	for (const json& user : data["Users"]) {
		if (user["username"] == username) {
			usernameFound = true;
		}
	}
	if (usernameFound) {
		return true;
	} else {
		return false;
	}
}

int main() {
	json data = readFile();
	cout << "Pick 1 option: " << endl;
	cout << "1. Log in" << endl;
	cout << "2. Create User" << endl;
	cout << "Type 1 or 2: " << endl;
	int answer;
	cin >> answer;
	if (answer == 1) {
		cout << "Please type in your username:" << endl;
		string type_user;
		cin >> type_user;
		cout << "Please type in your password:" << endl;
		string type_password;
		cin >> type_password;
		if(searchForUser(type_user, type_password)) {
			cout << "Hello " << type_user << "!";
			return 1;
		} else {
			cout << "Username or password incorrect!";
			return 0;
		}
	} else {
		cout << "Please create a username:" << endl;
		string new_user;
		cin >> new_user;
		if (searchForUsername(new_user)) {
			cout << "Username already found!";
			return 0;
		}
		cout << "Please create a password:" << endl;
		string new_password;
		cin >> new_password;
		addUser(new_user, new_password);
		cout << "Thanks for adding the user" << endl;
		return 1;
	}
}
