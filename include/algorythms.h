#ifndef ALGORYTHMS_H
#define ALGORYTHMS_H

#include <vector>
#include <deque>
#include <iostream>
#include <time.h>
#include <memory>
#include <algorithm>
#include <Windows.h>

std::vector<float> findSPIBytes(std::vector<float> data, float threshold_voltage, int borders, int spacer);
std::vector<double> findAverageMinMax(std::vector<float> *data, int averageSize);

#endif // ALGORYTHMS_H
