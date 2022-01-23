#include <iostream>
#include <cmath>

#include "gtest/gtest.h"
#include "include/Data.h"

static double haversine(double lat1, double lon1, double lat2, double lon2, int decimal_places=2) {
    const double multiplier = std::pow(10.0, decimal_places);
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return round((rad * c) * multiplier) / multiplier;
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::cout << "AED 2021/2022 - Aula Pratica 11" << std::endl << std::endl;

    return RUN_ALL_TESTS();
}