#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <math.h>
#include <fstream>
#include <sys/mman.h>

#define OCC_SAMPLING_DIST 8

uint32_t encode_to_int(const char &string_to_encode)
{
    int encoded_value;
    switch (string_to_encode)
    {
    case 'A':
        encoded_value = 0;
        break;
    case 'C':
        encoded_value = 1;
        break;
    case 'G':
        encoded_value = 2;
        break;
    case 'T':
        encoded_value = 3;
        break;
    }

    return encoded_value;
}


void build_tables(const std::string &reference_string, std::vector<uint32_t> &F_offsets, std::vector<char> &L_column, std::vector<std::vector<uint32_t> > &occ_table)
{
    // rotate and sort

    std::vector<std::string> rotate_and_sort_strings;

    std::string current_rotation = reference_string;
    int reference_string_length = reference_string.length();

    for (int i = 0; i < reference_string_length; ++i)
    {
        current_rotation.push_back(current_rotation[0]);
        current_rotation.erase(current_rotation.begin());
        rotate_and_sort_strings.push_back(current_rotation);
    }
    std::sort(rotate_and_sort_strings.begin(), rotate_and_sort_strings.end());

    

    //create tables

    std::vector<uint32_t> running_occ(4, 0);
    

    for (int i = 0; i < reference_string_length; ++i)
    {
        // create F_offsets
        uint32_t encoded_F = encode_to_int(rotate_and_sort_strings[i][0]);
        if (F_offsets[encoded_F] == reference_string_length)
        {
            F_offsets[encoded_F] = i;
        }

        // create L_column
        char c = rotate_and_sort_strings[i][reference_string_length - 1];
        L_column.push_back(c);

        // create occ_table
        uint32_t encoded_L = encode_to_int(c);
        ++running_occ[encoded_L];
        if (i % OCC_SAMPLING_DIST == 0)
        {
            occ_table.push_back(running_occ);
        }
    }

}

void search_pattern(const std::string &pattern, std::vector<uint32_t> &F_offsets, std::vector<char> &L_column, std::vector<std::vector<uint32_t> > &occ_table)
{
    uint32_t range_min;
    uint32_t range_max;
    uint32_t update_range_min;
    uint32_t update_range_max;
    uint32_t encoded_F = encode_to_int(pattern[pattern.size() - 1]);

    range_min = F_offsets[encoded_F];
    if(pattern.substr(pattern.size() - 1) != "T") range_max = F_offsets[encoded_F + 1] - 1;
    else range_max = L_column.size() - 1;

    // printf("range_min: %d, range_max: %d\n", range_min, range_max);

    for(uint32_t search_round = 0; search_round < pattern.size() - 1; search_round++){

        uint32_t encoded_L = encode_to_int(pattern[pattern.size() - search_round - 2]);

        //update range_min
        update_range_min = F_offsets[encoded_L] + occ_table[range_min / OCC_SAMPLING_DIST][encoded_L] - 1;
        for(uint32_t i = 1; i <= range_min % OCC_SAMPLING_DIST; i++){
            if(L_column[OCC_SAMPLING_DIST * (range_min / OCC_SAMPLING_DIST) + i] == pattern[pattern.size() - search_round - 2]){
                update_range_min += 1;
            }
        }

        if(L_column[range_min] != pattern[pattern.size() - search_round - 2]) update_range_min += 1;

        //update range_min
        update_range_max = F_offsets[encoded_L] + occ_table[range_max / OCC_SAMPLING_DIST][encoded_L] - 1;
        for(uint32_t i = 1; i <= range_max % OCC_SAMPLING_DIST; i++){
            if(L_column[OCC_SAMPLING_DIST * (range_max / OCC_SAMPLING_DIST) + i] == pattern[pattern.size() - search_round - 2]){
                update_range_max += 1;
            }
        }

        // printf("updated range_min: %d, updated range_max: %d\n", update_range_min, update_range_max);

        range_min = update_range_min;
        range_max = update_range_max;

        if(range_min > range_max) break;
    }
    if(range_min <= range_max) std::cout << "Number of pattern " << pattern << " found in the reference string: " << range_max - range_min + 1 << "\n"; 
    else std::cout << "Number of pattern " << pattern << " found in the reference string: 0\n"; 
}



int main()
{
    std::ifstream ReferenceFile("reference_string.txt");

    std::ifstream PatternFile("patterns.txt");

    std::vector<std::string> patterns;

    std::string reference_string;

    getline(ReferenceFile, reference_string);

    for (std::string pattern; getline(PatternFile, pattern);)
    {
        patterns.push_back(pattern);   
    }   

    std::vector<uint32_t> F_offsets(4 , reference_string.size());
    std::vector<char> L_column;
    std::vector<std::vector<uint32_t> > occ_table;

    mremap(0,0,0,1);
    // build tables
    build_tables(reference_string, F_offsets, L_column, occ_table);

    // search patterns
    for(int i = 0; i < patterns.size(); i++){
        search_pattern(patterns[i], F_offsets, L_column, occ_table);
    }
    mremap(0,0,0,1);
}
