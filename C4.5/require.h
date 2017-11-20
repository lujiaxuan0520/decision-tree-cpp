#ifndef REQUIRE_H__
#define REQUIRE_H__

#include "decisionstructure.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <string>
#include <map>
#include <vector>

inline void assure(std::ifstream& in,
                   const std::string& filename = "")
{
	using namespace std;
	if (!in) {
		fprintf(stderr, "Could not open file: %s\n", filename.c_str());
		exit(1);
	}
}

inline void assure(std::ofstream& out,
                   const std::string& filename = "")
{
	using namespace std;
	if (!out) {
		fprintf(stderr, "Could not open file: %s\n", filename.c_str());
	}
}

void load_file(std::vector<Information>& datas,
               std::vector<std::string>& attributes,
               const std::string& filename)
{
	std::ifstream istrm(filename);
	assure(istrm, filename);

	if (istrm.is_open()) {
		char buffer[128];
		bool firstline = true;
		while (!istrm.eof()) {
			istrm.getline(buffer, 128);
			const char* id = strtok(buffer, "\t");
			const char* satisfaction_level = strtok(NULL, "\t");
			const char* number_project = strtok(NULL, "\t");
			const char* average_monthly_hours = strtok(NULL, "\t");
			const char* Work_accident = strtok(NULL, "\t");
			const char* promotion_last_5years = strtok(NULL, "\t");
			const char* salary = strtok(NULL, "\t");
			const char* left_or_remained = strtok(NULL, "\t");

			// Check if the first line.
			// The first line contains attributes of datas.
			//
			if (firstline) {
				attributes.push_back(std::string(id));
				attributes.push_back(std::string(satisfaction_level));
				attributes.push_back(std::string(number_project));
				attributes.push_back(std::string(average_monthly_hours));
				attributes.push_back(std::string(Work_accident));
				attributes.push_back(std::string(promotion_last_5years));
				attributes.push_back(std::string(salary));
				attributes.push_back(std::string(left_or_remained));
				firstline = false;
			}
			else {
				Information data;
				data.id = std::string(id);
				data.satisfaction_level = std::string(satisfaction_level);
				data.number_project = std::string(number_project);
				data.average_monthly_hours = std::string(average_monthly_hours);
				data.Work_accident = std::string(Work_accident);
				data.promotion_last_5years = std::string(promotion_last_5years);
				data.salary = std::string(salary);
				data.left_or_remained = std::string(left_or_remained);
				datas.push_back(data);
			}
		}
	}
}

void match_properties(std::vector<Information> datas,
                      std::vector<std::string> attributes,
                      std::map<std::string, std::vector<std::string>>& map_attr)
{
	int index = 0;
	for (auto attribute : attributes) {
		std::vector<std::string> attrTmp;
		for (auto data : datas) {
			switch (index) {
			case 0:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.id) == attrTmp.end()) {
					attrTmp.push_back(data.id);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.id);
				}
				break;
			case 1:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.satisfaction_level) == attrTmp.end()) {
					attrTmp.push_back(data.satisfaction_level);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.satisfaction_level);
				}
				break;
			case 2:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.number_project) == attrTmp.end()) {
					attrTmp.push_back(data.number_project);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.number_project);
				}
				break;
			case 3:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.average_monthly_hours) == attrTmp.end()) {
					attrTmp.push_back(data.average_monthly_hours);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.average_monthly_hours);
				}
				break;
			case 4:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.Work_accident) == attrTmp.end()) {
					attrTmp.push_back(data.Work_accident);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.Work_accident);
				}
				break;
			case 5:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.promotion_last_5years) == attrTmp.end()) {
					attrTmp.push_back(data.promotion_last_5years);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.promotion_last_5years);
				}
				break;
			case 6:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.salary) == attrTmp.end()) {
					attrTmp.push_back(data.salary);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.salary);
				}
				break;
			case 7:
				if (!attrTmp.empty() &&
				        std::find(attrTmp.begin(), attrTmp.end(), data.left_or_remained) == attrTmp.end()) {
					attrTmp.push_back(data.left_or_remained);
				}
				else if (attrTmp.empty()) {
					attrTmp.push_back(data.left_or_remained);
				}
				break;
			default:
				break;
			}
		}
		index++;
		map_attr[attribute] = attrTmp;
	}
}

bool belongs_same_label(std::vector<Information> datas,
                        std::string label = "left")
{
	if (datas.empty()) {
		std::cout << "the datas is empty" << std::endl;
		exit(1);
	}

	for (auto iter = datas.begin(); iter != datas.end(); ++iter) {
		if (iter->left_or_remained != label) {
			return false;
		}
	}

	return true;
}

std::string majority_of_category(std::vector<Information> datas)
{
	int positivecategory = 0;
	int negativecategory = 0;

	for (auto data : datas) {
		if (data.left_or_remained == "left") {
			++positivecategory;
		}
		else if (data.left_or_remained == "remained") {
			++negativecategory;
		}
	}
	return (positivecategory > negativecategory ? "left" : "remained");
}

double calculate_information_entropy(std::vector<Information> datas,
                                     std::string mapAttr = "",
                                     std::string attribute = "left_or_remained")
{
	// Ent(D) = -∑(k=1, |Y|) p_k * log2(p_k)
	//
	int size = 0;
	double entropy = 0;
	int positive = 0;
	int negative = 0;

	// Beacuse of the datas only have two label.
	// So entropy = positiveSample + negativeSample
	//
	if (attribute == "satisfaction_level") {
		for (auto data : datas) {
			if (data.satisfaction_level == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "number_project") {
		for (auto data : datas) {
			if (data.number_project == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "average_monthly_hours") {
		for (auto data : datas) {
			if (data.average_monthly_hours == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "Work_accident") {
		for (auto data : datas) {
			if (data.Work_accident == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "promotion_last_5years") {
		for (auto data : datas) {
			if (data.promotion_last_5years == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "salary") {
		for (auto data : datas) {
			if (data.salary == mapAttr) {
				if (data.left_or_remained == "left") {
					++positive;
				}
				else {
					++negative;
				}
				++size;
			}
		}
	}
	else if (attribute == "left_or_remained") {
		size = datas.size();
		auto judget = [&](Information wm) { if (wm.left_or_remained == "left") { ++positive; } else { ++negative; }};
		for_each(datas.begin(), datas.end(), judget);
	}

	if (positive == 0 || negative == 0) {
		return 0;
	}
	else {
		entropy = -(((double)positive / size) * log2((double)positive / size) + ((double)negative / size) * log2((double)negative / size));
	}

	return entropy;
}

double proportion(std::vector<Information>& datas,
                  std::string mapAttr = "",
                  std::string attribute = "")
{
	int size = datas.size();
	double proportion = 0;

	if (attribute == "satisfaction_level") {
		for (auto data : datas) {
			if (data.satisfaction_level == mapAttr) {
				++proportion;
			}
		}
	}
	else if (attribute == "number_project") {
		for (auto data : datas) {
			if (data.number_project == mapAttr) {
				++proportion;
			}
		}
	}
	else if (attribute == "average_monthly_hours") {
		for (auto data : datas) {
			if (data.average_monthly_hours == mapAttr) {
				++proportion;
			}
		}
	}
	else if (attribute == "Work_accident") {
		for (auto data : datas) {
			if (data.Work_accident == mapAttr) {
				++proportion;
			}
		}
	}
	else if (attribute == "promotion_last_5years") {
		for (auto data : datas) {
			if (data.promotion_last_5years == mapAttr) {
				++proportion;
			}
		}
	}
	else if (attribute == "salary") {
		for (auto data : datas) {
			if (data.salary == mapAttr) {
				++proportion;
			}
		}
	}

	proportion /= size;

	return proportion;
}

double calculate_information_gain(std::vector<Information>& datas,
                                  std::string attribute,
                                  std::map<std::string, std::vector<std::string>> map_attr)
{
	// Gain(D, a) = Ent(D) - ∑(v=1, V) |D^|/|D| * Ent(D)
	//
	double gain = calculate_information_entropy(datas);
	std::vector<std::string> attrs = map_attr[attribute];

	for (auto attr : attrs) {
		gain -= proportion(datas, attr, attribute) * calculate_information_entropy(datas, attr, attribute);
	}

	return gain;
}

double calculate_information_gain_ratio(std::vector<Information>& datas,
                                        std::string attribute,
                                        std::map<std::string, std::vector<std::string>> map_attr)
{
	// Gain_ratio(D, a) = Gain(D, a) / IV(a)
	//
	double gain = calculate_information_gain(datas, attribute, map_attr);

	double iv = 0;
	std::vector<std::string> attrs = map_attr[attribute];
	for (auto attr : attrs) {
		iv -= proportion(datas, attr, attribute) * log2(proportion(datas, attr, attribute));
	}

	double gain_ratio = gain / iv;

	return gain_ratio;
}

std::pair<std::string, std::vector<std::string>> optimal_attribute(std::vector<Information>& datas,
        std::vector<std::string>& attributes,
        std::map<std::string, std::vector<std::string>> map_attr)
{
	std::map<std::string, double> map_gains;
	std::map<std::string, double> map_gains_ratio;
	for (auto attribute : attributes) {
		map_gains[attribute] = calculate_information_gain(datas, attribute, map_attr);
		map_gains_ratio[attribute] = calculate_information_gain_ratio(datas, attribute, map_attr);
	}

	// Sort the information gain and select the attribute of the maximum
	// information gain.The biggest value is in the first.
	//
	std::vector<std::pair<std::string, double>> vec_map_gains(map_gains.begin(), map_gains.end());
	std::vector<std::pair<std::string, double>> vec_map_gains_ratios(map_gains_ratio.begin(), map_gains_ratio.end());
	auto compare_x_y = [](const std::pair<std::string, double> x, const std::pair<std::string, double> y) {
		return x.second > y.second;
	};
	std::sort(vec_map_gains.begin(), vec_map_gains.end(), compare_x_y);
	std::sort(vec_map_gains_ratios.begin(), vec_map_gains_ratios.end(), compare_x_y);

	// Find information gain greater than average.
	//
	std::vector<std::string> vec_map_gains_name;
	int vec_map_gains_size = vec_map_gains.size() / 2;
	for (int i = 0; i < vec_map_gains_size; ++i) {
		vec_map_gains_name.push_back(vec_map_gains[i].first);
	}

	std::string best_attribute;
	for (auto vec_map_gains_ratio : vec_map_gains_ratios) {
		if (std::find(vec_map_gains_name.begin(), vec_map_gains_name.end(), vec_map_gains_ratio.first)
		        != vec_map_gains_name.end()) {
			best_attribute = vec_map_gains_ratio.first;
			break;
		}
	}

	if (!best_attribute.empty()) {
		auto search = map_attr.find(best_attribute);
		if (search != map_attr.end()) {
			return std::make_pair(search->first, search->second);
		}
		else {
			return std::make_pair(std::string(""), std::vector<std::string>());
		}
	}
	else {
		return std::make_pair(std::string(""), std::vector<std::string>());
	}
}

std::vector<Information> remain_Information_datas(std::vector<Information> datas,
        std::string mapAttr,
        std::string attribute)
{
	std::vector<Information> tmp;

	if (attribute == "satisfaction_level") {
		for (auto data : datas) {
			if (data.satisfaction_level == mapAttr) {
				tmp.push_back(data);
			}
		}
	}
	else if (attribute == "number_project") {
		for (auto data : datas) {
			if (data.number_project == mapAttr) {
				tmp.push_back(data);
			}
		}
	}
	else if (attribute == "average_monthly_hours") {
		for (auto data : datas) {
			if (data.average_monthly_hours == mapAttr) {
				tmp.push_back(data);
			}
		}
	}
	else if (attribute == "Work_accident") {
		for (auto data : datas) {
			if (data.Work_accident == mapAttr) {
				tmp.push_back(data);
			}
		}
	}
	else if (attribute == "promotion_last_5years") {
		for (auto data : datas) {
			if (data.promotion_last_5years == mapAttr) {
				tmp.push_back(data);
			}
		}
	}
	else if (attribute == "salary") {
		for (auto data : datas) {
			if (data.salary == mapAttr) {
				tmp.push_back(data);
			}
		}
	}

	return tmp;
}

void print_tree(TreeRoot pTree, int depth)
{
	for (int i = 0; i < depth; ++i) {
		std::cout << '\t';
	}

	if (!pTree->edgeValue.empty()) {
		std::cout << "--" << pTree->edgeValue << "--" << std::endl;
		for (int i = 0 ; i < depth; ++i) {
			std::cout << '\t';
		}
	}

	std::cout << pTree->attribute << std::endl;
	for (auto child : pTree->childs) {
		print_tree(child, depth + 1);
	}
}

#endif // REQUIRE_H__
