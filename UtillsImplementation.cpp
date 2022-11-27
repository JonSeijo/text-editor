#include "Utills.h"

std::string Implementation::WorkingDirection(const std::string& str) {

	int i = str.find_last_of('/');

	return str.substr(0, i + 1);
}