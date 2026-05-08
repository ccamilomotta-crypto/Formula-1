#include <iostream>
#include <string>
#include <fstream>
#include "rank_functions.h"

int main() {
    std::string file_name;
    std::cin >> file_name;
    std::ifstream in{file_name};

    std::vector<driver> drivers = load_driver_data(in);

    if(drivers.size()== 0||!in.is_open()){
        std::cout<<"Bad input"<<std::endl;
        return 1;
    }
    drivers=set_rankings(drivers);
    print_results(drivers);
    return 0;
}
