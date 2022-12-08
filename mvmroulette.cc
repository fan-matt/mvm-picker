#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <unordered_set>

#define DEBUG

int* gen_map_array(int size)
{
    int* to_return = new int[size]{0};
    return  to_return;
}

int* arr_cpy(int* to_copy, int size)
{
    int* to_return = new int[size];

    for(int i = 0; i < size; i ++)
    {
        to_return[i] = to_copy[i];
    }

    return to_return;
}

std::string arr_to_str(int* to_string, int size)
{
    std::string to_return = "";
    for(int i = 0; i < size; i ++)
    {
        to_return += to_string[i];
    }

    return to_return;
}

std::vector<std::string> comb_to_names(int* comb, const std::string* mapping, int size)
{
    std::vector<std::string> to_return;

    for(int i = 0; i < size; i ++)
    {
        if(comb[i])
        {
            to_return.push_back(mapping[i]);
        }
    }

    return to_return;
}

std::vector<int*> c(int n, int k)
{
    std::vector<int*> combinations;

    std::unordered_set<std::string> exists;

    // This gets very big very quickly
    for(int i = 0; i < k; i ++)
    {
        std::vector<int*> new_additions;

        for(auto comb: combinations) {
            for(int j = 0; j < n; j ++)
            {
                int* temp = arr_cpy(comb, n);

                if(temp[j] != 1)
                {
                    temp[j] = 1;

                    // Create a string representation for table lookup
                    std::string lookup_key = arr_to_str(temp, n);

                    // If doesn't already exist
                    if(exists.find(lookup_key) == exists.end())
                    {
                        exists.insert(lookup_key);
                        new_additions.push_back(temp);
                    }    
                }
            }
        }

        // Add new additions to existing combinations array
        combinations = new_additions;

        // Cover the case where we're just starting out
        if(combinations.size() == 0)
        {
            for(int j = 0; j < n; j ++)
            {
                int* temp = gen_map_array(n);
                temp[j] = 1;
                combinations.push_back(temp);
            }
        }
    }

    return combinations;
}

void full_print_comb(std::vector<int*> combinations, int choice, int size, const std::string* mapping, std::string end = "\n")
{
    int* comb = combinations[choice];

    for(int i = 0; i < size; i ++)
    {
        std::cout << comb[i];
    }

    std::vector<std::string> names = comb_to_names(comb, mapping, size);

    std::cout << " ";
    for(auto name: names)
    {
        std::cout << name << " ";
    }

    std::cout << end;
}

int main()
{
    int MVM_SIZE = 6;
    const std::string PLAYERS[] = {"Ben", "Cameron", "Daniel", "Devon", "Matt", "Ming", "Rivu", "Sean", "Tim"};
    int pool_size = sizeof(PLAYERS) / sizeof(std::string);

    std::vector<int*> combinations = c(pool_size, MVM_SIZE);

#ifdef DEBUG
    // Print
    std::cout << "Total Combinations: " << combinations.size() << std::endl;
    for(int i = 0; i < combinations.size(); i ++)
    {
        full_print_comb(combinations, i, pool_size, PLAYERS, "\n\n");
    }
#endif

    srand(time(0));
    int random_choice = rand() % combinations.size();

    std::cout << "Random choice of friends to play MVM: Combination #" << random_choice << " of " << combinations.size() << std::endl;
    full_print_comb(combinations, random_choice, pool_size, PLAYERS);

    return 0;
}