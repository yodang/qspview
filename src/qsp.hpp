#ifndef QSP_HPP
#define QSP_HPP

#include<string>
#include<vector>

struct QSPAction{
    std::string image;
    std::string description;
    std::string lines;
};

struct QSPLocation{
    std::string name;
    std::string desc;
    std::string lines;
    std::vector<QSPAction> actions;
};

struct QSPGame{
    std::vector<QSPLocation> locs;
};

constexpr int QSP_CODE_OFFSET=5;

std::vector<char> readNextQSPString(std::istream& in);
QSPGame buildGame(const std::vector<std::vector<char>>& strings);
#endif //QSP_HPP