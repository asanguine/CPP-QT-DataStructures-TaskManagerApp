#pragma once
#include <string>


class User
{
private:
	std::string userName;



public:
	User(std::string _userName = "");
	~User() {};


	void setUserName(std::string _username);
	std::string getUserName() const;


};

