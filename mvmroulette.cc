#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>


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

std::vector<std::string> perm_to_names(int* perm, const std::string* mapping, int perm_size)
{
    std::vector<std::string> to_return;

    for(int i = 0; i < perm_size; i ++)
    {
        if(perm[i])
        {
            to_return.push_back(mapping[i]);
        }
    }

    return to_return;
}

int main()
{
    int MVM_SIZE = 6;
    const std::string PLAYERS[] = {"Ben", "Cameron", "Daniel", "Devon", "Matt", "Ming", "Rivu", "Sean", "Tim"};
    int pool_size = 9;

    std::vector<int*> permutations;

    std::unordered_set<std::string> exists;

    // This gets very big very quickly
    for(int i = 0; i < MVM_SIZE; i ++)
    {
        std::vector<int*> new_additions;

        for(auto perm: permutations) {
            for(int j = 0; j < pool_size; j ++)
            {
                int* temp = arr_cpy(perm, pool_size);

                if(temp[j] != 1)
                {
                    temp[j] = 1;

                    // Create a string representation for table lookup
                    std::string lookup_key = arr_to_str(temp, pool_size);

                    // If doesn't already exist
                    if(exists.find(lookup_key) == exists.end())
                    {
                        exists.insert(lookup_key);
                        new_additions.push_back(temp);
                    }    
                }
            }
        }

        // Add new additions to existing permutations array
        permutations = new_additions;

        // Cover the case where we're just starting out
        if(permutations.size() == 0)
        {
            for(int j = 0; j < pool_size; j ++)
            {
                int* temp = gen_map_array(pool_size);
                temp[j] = 1;
                permutations.push_back(temp);
            }
        }
    }

    // Print
    std::cout << "Size: " << permutations.size() << std::endl;
    for(auto perm: permutations)
    {
        for(int i = 0; i < pool_size; i ++)
        {
            std::cout << perm[i];
        }

        std::vector<std::string> names = perm_to_names(perm, PLAYERS, pool_size);

        std::cout << " ";
        for(auto name: names)
        {
            std::cout << name << " ";
        }

        std::cout << "\n" << std::endl;
    }

    return 0;
}