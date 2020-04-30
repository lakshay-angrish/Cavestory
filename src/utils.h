#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

class Utils {
    public:
        static unsigned int split(const std::string& txt, std::vector<std::string>& strs, char ch) {
            int initial_pos = 0;
            strs.clear();
            int pos = txt.find(ch);
            while (pos != std::string::npos) {
                strs.push_back(txt.substr(initial_pos, pos - initial_pos + 1));
                initial_pos = pos + 1;
                pos = txt.find(ch, initial_pos);
            }

            strs.push_back(txt.substr(initial_pos, std::min<int>(pos, txt.size() - initial_pos - 1)));
            return strs.size();
        }
};

#endif