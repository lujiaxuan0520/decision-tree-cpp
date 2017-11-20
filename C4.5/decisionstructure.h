#ifndef DECISIONSTRUCTURE_H__
#define DECISIONSTRUCTURE_H__

#include <iostream>
#include <string>
#include <vector>

class Information
{
public:
	std::string id;
	std::string satisfaction_level;
	std::string number_project;
	std::string average_monthly_hours;
	std::string Work_accident;
	std::string promotion_last_5years;
	std::string salary;
	std::string left_or_remained;

	friend
	std::ostream& operator<<(std::ostream& os, const Information& wm)
	{
		os << wm.id << " " << wm.satisfaction_level << " " << wm.number_project << " "
		   << wm.average_monthly_hours << " " << wm.Work_accident << " " << wm.promotion_last_5years << " "
		   << wm.salary << " " << wm.left_or_remained;
		os << std::endl;
		return os;
	}
};

struct Node
{
	std::string attribute;
	std::string edgeValue;
	std::vector<Node*> childs;
	Node() : attribute(""), edgeValue("") { }
};

template <typename T>
using Ptr = T*;
using TreeRoot = Ptr<Node>;

#endif // DECISIONSTRUCTURE_H__
