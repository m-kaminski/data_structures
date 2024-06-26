

#include <fstream>
#include <iostream>
#include <any>
#include <cassert>
#include <sstream>
#include <functional>

namespace lc_util
{
    using av_t = std::vector<std::any>;
    using si_t = std::string::const_iterator;

    int stoi(si_t begin, const si_t end)
    {
        int s = 1;
        if (*begin == '-') {
            s = -1;
            begin++;
        }
        int res = 0;
        for (; begin != end; begin++)
        {
            res *= 10;
            res += *begin - '0';
        }
        return res * s;
    }

    // recursively parse vector of vectors of ints
    std::pair<av_t, si_t> parse_any_vector(const si_t begin, const si_t end)
    {
        av_t res;
        si_t it = begin;

        *it++;
        while (*it != ']' && it < end)
        {
            if (*it == '[')
            {
                // this is an any-vector
                auto tmp = parse_any_vector(it + 1, end);
                res.emplace_back(std::move(tmp.first));
                it = tmp.second + 1;
            }
            else if (*it == '"')
            {
                // this is a string
                it++;
                auto e = find(it, end, '"');
                res.emplace_back(std::string(it, e));
                it = e + 1;
            }
            else
            {
                // this is an int
                auto e = find_if(it, end, [](char c){return c == ',' || c == ']';});
                assert(*e == ',' || *e == ']'); // && next(e) == end));
                int i = stoi(it, e);
                res.emplace_back(i);
                it = e;
            }
            if (*it == ',')
            {
                it++;
            }
        }
        it++;
        return make_pair(res, it);
    }

    av_t parse_any_vector(const std::string &arg)
    {
        assert(arg.front() == '[' && arg.back() == ']');
        return parse_any_vector(arg.begin(), arg.end()).first;
    }

    void print_any_vector(const av_t &v, std::ostream &s)
    {
        s << '{';
        for (auto &a : v)
        {
            if (a.type() == typeid(int))
            {
                s << std::any_cast<int>(a);
            }
            else if (a.type() == typeid(std::string))
            {
                const std::string &sr = std::any_cast<const std::string &>(a);
                s << ",," << sr << "''";
            }
            else
            {
                const av_t &nested = std::any_cast<const av_t &>(a);
                print_any_vector(nested, s);
            }
            if (&a != &v.back())
            {
                s << ", ";
            }
        }

        s << '}';
    }

    // vectors or ints
    av_t read_any_vector(const std::string &path)
    {
        std::vector<std::any> res;
        std::vector<std::string> values;

        std::ifstream fs(path);
        if (fs.fail())
        {
            std::cerr << "Failed to open file: " << path << std::endl;
            exit(1);
        }

        std::string actual;
        while (1)
        {

            if (std::getline(fs, actual).fail())
            {
                break;
            }
            else
            {
                return lc_util::parse_any_vector(actual);
                //
            }
        }

        return res;
    }
}