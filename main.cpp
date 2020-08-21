#include <iostream>
#include <cstdint>
#include <vector>

int add(int a, int b) {
    int c = a & b; // find carries
    int d = a ^b; // find addition without carries
    c = c << 1; // carries shifts one
    if ((d & c) == 0) { // If there is no carries then it is found!
        return (d ^ c);
    } else { // There are carries still add again.
        return add(d, c);
    }

};

void
find_largest_sum(unsigned int T, const std::vector<unsigned int> &I, std::vector<unsigned int> &M, unsigned int &S) {
    if (I.size() == 1) { // Input vector size 1 then no need for calculations.
        if (I[0] <= T) { // We have a solution set outputs
            M.push_back(I[0]);
            S = I[0];
        }
        return;
    }
    unsigned int maxS = 0; // Max number total found from subset
    std::vector<unsigned int> maxM; // Vector of Max Number
    for (int i = I.size() - 1; i >= 0; i--) {
        std::vector<unsigned int> M2; // Init recursive output
        unsigned int S2 = 0; //Init recursive output
        if (I[i] < T) {
            std::vector<uint32_t> I2;
            I2.reserve(i);
            for (size_t j = 0; j < i; j++) { // Construct subset of smaller numbers
                I2.push_back(I[j]);
            }
            find_largest_sum(T - I[i], I2, M2, S2); // recursive call to find subset of the input
            M2.push_back(I[i]); // M2 should contain the I[i] it is part of the solution
            S2 += I[i]; // S2 solution should contain I[i] it is part of the solution
        } else if (I[i] == T) { // I[i] is the solution dont have to look no more return the set and the number.
            S = I[i];
            M.push_back(I[i]);
            return;
        }
        if (maxS < S2 && S2 <= T) { // find maximum of the current solutions.
            maxS = S2;
            maxM.clear();
            for (unsigned int & j : M2) {
                maxM.push_back(j);
            }
        }
    }
    if (maxS == 0) { // Solution not found return
        return;
    }
    for (unsigned int & j : maxM) { // Set the output vector to solution subset
        M.push_back(j);
    }
    S = maxS; // Set the output subset total.
};

int main() {
    for (int a = 0; a < 10000; ++a) {
        for (int b = 0; b < 10000; ++b) {
            if (add(a,b) != a+b) {
                std::cout << "Error a: " << a << "b: " << b << std::endl;
            }
        }
    }
    for (int T = 5; T < 30 ; ++T) {
        std::vector<unsigned int> I = {2, 3, 4, 6, 7, 8, 9, 10};
        std::vector<unsigned int> solution;
        unsigned int S = 0;
        find_largest_sum(T, I, solution, S);
        std::cout << "solution:" << std::endl;
        for (unsigned int i : solution) {
            std::cout << i << std::endl;
        }
        std::cout << "total: " << S << std::endl;
    }
    return 0;
}
