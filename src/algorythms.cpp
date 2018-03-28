#include "include/algorythms.h"


std::vector<float> findSPIBytes(std::vector<float> data, float threshold_voltage, int borders, int spacer) {
    std::vector<float> result;
    int iter;
    for (iter = 0 ; iter < data.size() ; iter++) {
        if (data[iter] > threshold_voltage) {
            for (int i = borders ; i > 0 ; i--) {
                result.push_back(data[iter-i]);
            }
            for (int i = 0; i < 60; i++) {
                result.push_back(data[iter]);
                iter++;
            }
            for (int i = 0 ; i < borders ; i++) {
                result.push_back(data[iter+i]);
            }
            for (int i = 0 ; i < spacer ; i++) {
                result.push_back(threshold_voltage);
            }
        }
    }
    return result;
}

std::vector<double> findAverageMinMax(std::vector<float> *data, int averageSize) {
    std::deque<float> min, max;
    max.push_back(0.0);
    min.push_back(0.0);
    double max_avg = 0.0;
    double min_avg = 0.0;
    int ia = 0;

    for (auto point : *data) {
        std::cout << "At point " << ia << ": " << point << " compare to " << *max.begin() << " and " << *min.begin() << std::endl;
        if (point > *max.begin()) {
            std::cout << "new max: " << point << std::endl;

            for (std::deque<float>::iterator i = max.begin(); i <= max.end(); ++i) {
                if ( ( point > *i && point <= *( i + 1 ) ) && ( i < max.end() ) ) {
                    for (auto ele : max) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
//                    if (!(i == max.end()))
                    ++i;

                    max.insert(i,point);

                    if (max.size() > averageSize) max.pop_front();

                    for (auto easd : max) {
                        std::cout << easd << ",";
                    } std::cout << std::endl;

                    break; }

                if (point > *i && i == max.end()) {
                    for (auto ele : max) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
                    max.push_back(point);
//                    insert(i,point);
                    if (max.size() > averageSize) max.pop_front();
                    for (auto easd : max) {
                        std::cout << easd << ",";
                    } std::cout << std::endl;
                    break;
                }


            }
            std::cout << std::endl;
        }

        if (point < *min.begin()) {
            std::cout << "new min: " << point << std::endl;
            for (std::deque<float>::iterator i = min.begin(); i <= min.end(); ++i) {
                if ((point < *i && point >= *(i+1)) && i < (min.end())) {
                    for (auto ele : min) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
//                    if (!(i == min.end()))
                    ++i;
                    min.insert(i,point);
                    if (min.size() > averageSize) min.pop_front();
                    for (auto ele : min) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
                    break;
                }
                if (point < *i && i == min.end()) {
                    for (auto ele : min) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
                    min.push_back(point);
//                            insert(i,point);
                    if (min.size() > averageSize) min.pop_front();
                    for (auto ele : min) {
                        std::cout << ele << ",";
                    } std::cout << std::endl;
                    break;
                }
            }
        }
        ia++;
    }
    for (auto point : max) {
        max_avg += point;
    }
    for (auto point : min) {
        min_avg += point;
    }
    max_avg /= max.size();
    min_avg /= min.size();

    for (auto element : max) {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    for (auto element : min) {
        std::cout << element << ",";
    }
    std::cout << std::endl;

    std::vector<double> _return;
    _return.push_back(min_avg);
    _return.push_back(max_avg);
    return _return;
}
