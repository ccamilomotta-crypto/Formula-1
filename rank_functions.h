#ifndef PROVIDED_RANK_FUNCTIONS_H_
#define PROVIDED_RANK_FUNCTIONS_H_

#include <string>
#include <vector>
#include <fstream>

struct driver {
    std::string lastname;
    std::string country;
    unsigned int number;
    double time;
    unsigned int rank;
};

std::string trim(std::string);
std::vector<driver> load_driver_data(std::ifstream&);
std::vector<driver> set_rankings(std::vector<driver>);
void print_results(const std::vector<driver>&);

#endif  // PROVIDED_RANK_FUNCTIONS_H_
