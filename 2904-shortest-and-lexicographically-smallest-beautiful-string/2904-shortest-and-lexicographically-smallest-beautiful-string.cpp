class Solution {
public:
    bool isCurrentSmaller(string &previousSubString,
                          string &currentSubString) {

        for (int i = 0; i < currentSubString.length(); i++) {

            if (previousSubString[i] < currentSubString[i]) {
                return false;
            } else if (previousSubString[i] > currentSubString[i]) {
                return true;
            }
        }

        return true;
    }

    string shortestBeautifulSubstring(string s, int k) {

        int start = 0;
        int end = 0;
        int count = 0;

        vector<int> smallest(3, 0);

        for (int i = 0; i < s.length(); i++) {

            end++;

            if (s[i] == '1') {
                count++;
            }

            while (count >= k && start < end) {

                if (smallest[0] == 0 ||
                    (end - start) < smallest[0]) {

                    smallest[0] = end - start;
                    smallest[1] = start;
                    smallest[2] = end;
                }
                else if ((end - start) == smallest[0]) {

                    string previousSubString =
                        s.substr(smallest[1],
                                 smallest[2] - smallest[1]);

                    string currentSubString =
                        s.substr(start,
                                 end - start);

                    if (isCurrentSmaller(previousSubString,
                                         currentSubString)) {

                        smallest[0] = end - start;
                        smallest[1] = start;
                        smallest[2] = end;
                    }
                }

                if (s[start] == '1') {
                    count--;
                }

                start++;
            }
        }

        return s.substr(smallest[1],
                        smallest[2] - smallest[1]);
    }
};