#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <array>
#include <unordered_map>
#include <functional>
#include <string>
#include <thread>
#include <unordered_set>
#include <set>
#include <algorithm>
#include <vector>
#define central_i 0 
#define central_j 0
using CoordinateMap = std::set<std::pair<int,int>>;
inline int manhantanDistance(int x1, int y1, int x2, int y2)
{
	return std::abs(x1-x2) + std::abs(y1-y2);
}
static void populateRoute(const std::vector<std::string>& map, CoordinateMap& coordinates){
	std::pair<int,int> position(0,0);
	std::pair<int,int> currentPosition(central_i,central_j);

	std::unordered_map<char, std::function<void()>> table({
			{'L',[&position]() { position.first = -1;}},
			{'R',[&position]() { position.first = 1;}},
			{'U',[&position]() { position.second = 1;}},
			{'D',[&position]() { position.second = -1;}},
			});
	for(const auto& move : map)
	{
		position = { 0, 0 };
		int distance = std::stoi(move.substr(1));
		table[move[0]]();
		while(distance)
		{
			currentPosition.first += position.first;
			currentPosition.second += position.second;
			//std::cout << "Current position " << currentPosition.first << ", " << currentPosition.second << "\n";
			coordinates.insert(currentPosition);
			--distance;
		}
	}
}
inline CoordinateMap getCommonIntersections(const CoordinateMap& a, const CoordinateMap& b)
{
	CoordinateMap intersection;
	std::set_intersection(a.begin(),a.end(),b.begin(),b.end(),std::inserter(intersection,intersection.begin()));
	return intersection;
}
template <class T>
void printVector(std::vector<T> vec)
{
	std::cout << "Vector is \n";
	for(auto& e : vec)
	{
		std::cout << e << " " ;
	}
	std::cout << "\n";
}
void getTokens(std::string input,std::string delimeter,std::vector<const char*>& output)
{
	size_t pos = 0;
	std::string token;
	while((pos = input.find(delimeter)) != std::string::npos)
	{
		token = input.substr(0,pos);
		output.push_back(token.c_str());
		input.erase(0,pos+delimeter.length());
	}
}
int shortestInteresection(const std::vector<std::string>& map1, const std::vector<std::string>& map2)
{
	CoordinateMap mapA{};
	CoordinateMap mapB{};
	printVector(map1);
	printVector(map2);
	populateRoute(map1,mapA);
	populateRoute(map2,mapB);
	CoordinateMap intersections = getCommonIntersections(mapA,mapB);
	int shortest_distance = std::numeric_limits<int>::max();
	for(const auto& intersection : intersections)
	{
		shortest_distance = std::min(shortest_distance,manhantanDistance(0,0,intersection.first,intersection.second));
	}
	return shortest_distance;
}
int main(int argc, char** argv)
{
	if(argc < 2 )
	{
		std::cout << "Usage solver <inputfile.txt> \n" ;
		return -1;
	}
	std::string inputfile(argv[1]);
	std::ifstream infile(inputfile.c_str());
	if(!infile)
	{
		std::cout << "Failed to load the file : " << inputfile << "\n" ;
		return -2;
	}
	std::string line;
	int i = 0;
	std::string wire1,wire2;
	std::vector<std::string> map1,map2;
	while(std::getline(infile,line))
	{
		std::string operation;
		if(i==0)
		{
			size_t pos = 0;
			while((pos = line.find(","))!=std::string::npos)
			{
				operation = line.substr(0,pos);
				map1.push_back(operation);
				line.erase(0,pos+1);
			}
			map1.push_back(line);
		}
		if(i==1)
		{
			size_t pos = 0;
			while((pos = line.find(","))!=std::string::npos)
			{
				operation = line.substr(0,pos);
				map2.push_back(operation);
				line.erase(0,pos+1);
			}
			map2.push_back(line);
		}
		i++;
	}
	infile.close();
	int answer = shortestInteresection(map1,map2);
	std::cout << "closest manhantanDistance is " << answer << "\n";
	return 0;
}
