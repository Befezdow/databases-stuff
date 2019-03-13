#ifndef SERVICE_H
#define SERVICE_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

template <typename T>
class Service {

    std::string fileName;

public:
    Service(std::string fileName) {
        this->fileName = fileName;
    }

    void insertOne(T value) {
        std::ofstream file;
        file.open(fileName.c_str(), std::ios_base::app);
        if (!file.is_open()) {
            std::cerr << "File not opened"<<std::endl;
        }

        file << value;

        file.close();
    }

    void insertMany(std::vector<T> values) {
        std::ofstream file;
        file.open(fileName.c_str(), std::ios_base::app);
        if (!file.is_open()) {
            std::cerr << "File not opened"<<std::endl;
        }

        for (int i = 0; i < values.size(); ++i) {
            file << values[i];
        }

        file.close();
    }

    std::vector<T> getAll() {
        std:: ifstream file;

        file.open(fileName.c_str());
        if (!file.is_open()) {
            std::cerr << "File not opened"<<std::endl;
        }

        std::vector<T> result;
        while (1) {
            T temp;
            file >> temp;

            if (!file) {
                break;
            } else {
                result.push_back(temp);
            }
        }

        return result;
    }
};

#endif // SERVICE_H
