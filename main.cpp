#include <iostream>

#include "gtest/gtest.h"
#include "include/AppStarter.h"


/*int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "AED 2021/2022 - Aula Pratica 11" << std::endl << std::endl;

    return RUN_ALL_TESTS();
}*/

int main(){
    AppStarter appStarter;
    appStarter.start();
    return 0;
}

