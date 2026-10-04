class Solution {
public:
    bool checkValidString(string s) {
        stack<int> openSt;
        stack<int> starSt;

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                openSt.push(i);
            }
            else if (s[i] == '*') {
                starSt.push(i);
            }
            else {
                if (!openSt.empty()) {
                    openSt.pop();
                }
                else if (!starSt.empty()) {
                    starSt.pop();
                }
                else {
                    return false;
                }
            }
        }

        while (!openSt.empty() && !starSt.empty()) {
            if (openSt.top() < starSt.top()) {
                openSt.pop();
                starSt.pop();
            }
            else {
                return false;
            }
        }

        return openSt.empty();
    }
};