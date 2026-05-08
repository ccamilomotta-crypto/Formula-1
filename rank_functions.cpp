#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "rank_functions.h"

// load data from the file stream into a vector
//   input format := <time> <country> <number> <name>
//   examples:
//     32.7 AUS 81 Piastri
//     36.5 NED 1  Verstappen
//   rank should be initialized to 0 for each driver
// returns a vector of drivers, or an empty vector if any input is invalid
std::vector<driver> load_driver_data(std::ifstream& in) {
    std::vector<driver> drivers;
    double time;
    std::string country;
    int number;  // Use int to check for negative values
    std::string lastname;
    
    while(in >>time >>country >> number>>lastname){
        // Check time (must be positive)
        if(time <=0){
            return std::vector<driver>();
        }
        
        // Check country (must be exactly 3 uppercase letters)
        if(country.length()!=3) {
            return std::vector<driver>();
        }
        for (size_t i = 0; i < 3; i++) {
            if (country[i]<'A'||country[i]>'Z'){
                return std::vector<driver>();
            }}
        // Check number (must be between 0 and 99)
        if(number <0||number>99){
            return std::vector<driver>();
        }
        // Check last name (must contain only letters and spaces, at least 2 chars)
        if(lastname.length()< 2) {
            return std::vector<driver>();
        }
        for(size_t i= 0; i< lastname.length();i++){
            char c =lastname[i];
            if (!((c>='A' &&c<='Z')||(c>='a'&&c<='z')||c ==' ')){
                return std::vector<driver>();
            }}      
        driver d;
        d.time= time;
        d.country =country;
        d.number =static_cast<unsigned int>(number);
        d.lastname =lastname;
        d.rank =0;
        
        drivers.push_back(d);
    }
    if(!in.eof()){
        return std::vector<driver>();
    }
    
    if(drivers.empty()){
        return std::vector<driver>();
    }   
    return drivers;
}

// return a copy of the input vector with ranks set based on the time for each driver.
//   the fastest/minimum time is ranked 1
// the order of the elements in the vector should not be changed
std::vector<driver> set_rankings(std::vector<driver> drivers) {
    if(drivers.size() ==0){
        return drivers;
    }
    
    std::vector<int>indices;
    for (size_t i = 0;i <drivers.size();i++){
        indices.push_back(static_cast<int>(i));
    }
    
    for (size_t i =0;i< indices.size()-1; i++){
        int minIndex =i;
        for(size_t j =i +1;j<indices.size();j++){
            if(drivers[indices[j]].time < drivers[indices[minIndex]].time){
                minIndex =static_cast<int>(j);
            }}
        if(minIndex !=static_cast<int>(i)){
            int temp =indices[i];
            indices[i] =indices[minIndex];
            indices[minIndex] =temp;
        }}
    
    for(size_t i =0;i < indices.size();i++){
        drivers[indices[i]].rank = static_cast<unsigned int>(i + 1);
    }
    return drivers;
}
// returns a copy of the input string with whitespace removed from the front and back
std::string trim(std::string str) {
    if(str.length() == 0){
        return str;
    }
    int start =0;
    int end =static_cast<int>(str.length()) -1;
    
    while(start <=end &&(str[start] ==' '||str[start] =='\t' ||str[start]=='\r')){
        start++;
    }
    
    while(end>=start && (str[end]==' '|| str[end]== '\t' ||str[end]== '\r')){
        end--;
    } 
    if(start >end){
        return "";
    }   
    return str.substr(start, end - start+1);
}
// print the results of the race
void print_results(const std::vector<driver>& drivers){
    // get the fastest time
    double best_time;
    for(const driver& driver: drivers){
        if(driver.rank ==1){
            best_time =driver.time;
            break;
        }}
    std::cout <<"Final results!";
    std::cout <<std::setprecision(2)<<std::showpoint<<std::fixed <<std::endl;
    for(unsigned rank =1; rank <= drivers.size();rank++) {
        for(const driver& driver :drivers) {
            if(driver.rank ==rank){
                std::string rank_str ="["+std::to_string(rank)+ "]";
                std::cout<< std::setw(4) <<std::left<<
                    rank_str <<" "<< driver.time<< " "<<
                    std::setw(15)<< std::left<<
                    driver.lastname << " (" << driver.country << ")"<<
                    " +" << (driver.time - best_time) << std::endl;
            }}}}
