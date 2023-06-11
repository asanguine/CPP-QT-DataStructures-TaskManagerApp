#include "User.h"


User::User(std::string _userName) : userName(_userName){}


void User::setUserName(std::string _username) {
	userName = _username;
}

std::string User::getUserName() const {
	return userName;
}