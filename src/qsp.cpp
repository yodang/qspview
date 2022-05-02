#include<fstream>
#include<array>
#include<algorithm>
#include<iostream>

#include"qsp.hpp"

std::string QSPStringToStd(const std::vector<char>& data, bool coded)
{
    std::string r{};
    r.reserve(data.size()/2);

    for(auto i=0;i<data.size(); i+=2)
        r.push_back(data[i]+(coded?QSP_CODE_OFFSET:0));//can overflow

    return r;
}

constexpr std::array<char,4> delimiter{'\r', 0, '\n', 0};

std::vector<char> readNextQSPString(std::istream& in)
{
    std::vector<char> r{};
    std::array<char,4> lookahead{};
    lookahead.fill(0);

    in.read(lookahead.data(), lookahead.size());

    while(!std::equal(lookahead.begin(), lookahead.end(), delimiter.begin()))
    {
        r.push_back(lookahead[0]);
        r.push_back(lookahead[1]);
        lookahead[0]=lookahead[2];
        lookahead[1]=lookahead[3];
        in.read(lookahead.begin()+2, 2);
        if(in.gcount()<2)
            break;
    }

    return r;
}

QSPGame buildGame(const std::vector<std::vector<char>>& strings)
{
    auto numLocs=atoi(QSPStringToStd(strings[3], true).data());
    QSPGame game{};
    game.locs.reserve(numLocs);
    int i=4;
    while(i+2<strings.size())
    {
        QSPLocation loc{
            name:QSPStringToStd(strings[i++], true),
            desc:QSPStringToStd(strings[i++], true),
            lines:QSPStringToStd(strings[i++], true),
            actions:{}
        };
        auto actsCount=atoi(QSPStringToStd(strings[i++], true).data());
        i+=actsCount*3;
        game.locs.push_back(loc);
    }

    return game;
}

// int main(int argc, char** argv)
// {
//     std::ifstream in(argv[1]);
//     std::vector<std::vector<char>> strings{};

//     while(!in.eof())
//     {
//         auto string=readNextQSPString(in);
//         strings.push_back(string);
//     }

//     std::cout<<"Found "<<strings.size()<<" strings\n";
//     auto game=buildGame(strings);
//     std::cout<<"Locations: "<<game.locs.size()<<"\n";
//     for(const auto& location: game.locs)
//     {
//         std::cout<<location.name<<"\n";
//     }
//     return 0;
// }