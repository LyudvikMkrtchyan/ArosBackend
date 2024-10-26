#pragma once
#include <string>
#include <ctime> 
#include <iostream> 
#include <sstream> 
#include <iomanip> 
#include <ctime>      

class Time{
public:
  std::string getTodaysDate();
  std::string addDaysToDate(std::string dateStr, int daysToAdd);
};