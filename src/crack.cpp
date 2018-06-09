#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


vector<size_t> calcShift(ifstream &, ifstream &);
void sortVectorPair(vector<pair<char, size_t>> &);


int main(int argc, char * argv[]) {

    ifstream file_encr, file_freq;
    vector<size_t> possible_shifts;

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <encrypted file> <char frequency file>" << endl;
        return 1;
    }

    file_encr.open(argv[1]);
    file_freq.open(argv[2]);

    possible_shifts = calcShift(file_encr, file_freq);

    
    cout << "Shift: " << possible_shifts[0] << endl; // For the sake of simplicity, we will assume the first result is the correct one!

    return 0;
}



vector<size_t> calcShift(ifstream &file_encr, ifstream &file_freq) {

    static const size_t distanceASCII = 32;
    size_t freq;
    char chr;
    vector<pair<char, size_t>> lang_freq, encr_freq;
    vector<size_t> possible_shifts;


    /**
     * Get chr frequency from strictly formatted sample file.
     * NOTE: Percentage converted to integer * 10^4 
     * */
    while (file_freq >> chr >> freq) {
        lang_freq.push_back(make_pair(chr, freq));
        encr_freq.push_back(make_pair(chr, 0));
    }


    /**
     * Get chr frequency from encrypted file.
     * NOTE: Percentage converted to integer * 10^4
     * */
    do {
        file_encr.get(chr);
        
        if (chr - lang_freq[0].first >= 0 && (size_t)(chr - lang_freq[0].first) < lang_freq.size()) {
            encr_freq[chr - lang_freq[0].first].second++;
        }
        else if (chr - lang_freq[0].first + distanceASCII >= 0 && chr - lang_freq[0].first + distanceASCII < lang_freq.size()) {
            encr_freq[chr - lang_freq[0].first + distanceASCII].second++;
        }

    } while (!file_encr.eof());

    for(size_t i = 0; i < encr_freq.size(); i++) {
        encr_freq[i].second = (size_t)(((double)encr_freq[i].second / encr_freq.size()) * 10000);   // calculate percentage * 10^4
    }


    /**
     * Sort vectors by char to match language frequency.
     * NOTE: Sorts whole vector, not necessary
     * */
    sortVectorPair(lang_freq);
    sortVectorPair(encr_freq);

    for(size_t i = 0; i < lang_freq.size(); i++) {
        possible_shifts.push_back(encr_freq[i].first - lang_freq[i].first);
    }

    return possible_shifts;

}



void sortVectorPair(vector<pair<char, size_t>> &v) {
    int hole;
    pair<char, size_t> temp;

    for(size_t i = 0; i < v.size(); i++) {
        hole = i;
        temp = v[hole];

        while (hole > 0 && v[hole-1].second < temp.second) {
            v[hole] = v[hole-1];
            hole--;
        }

        v[hole] = temp;
    }

}
