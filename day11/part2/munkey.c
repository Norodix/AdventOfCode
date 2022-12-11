#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>


#define INPUTFILE "input.txt"
#define BUFFERSIZE 100

#define CHASEROUNDS 10000

uint64_t add(uint64_t a, uint64_t b){
    return (uint64_t) a + (uint64_t) b;
}


uint64_t mult(uint64_t a, uint64_t b){
    return (uint64_t) a * (uint64_t) b;
}

uint64_t square(uint64_t a, uint64_t b){
    //b is just for compatibility
    return (uint64_t) a * (uint64_t) a;
}


typedef struct monkey{
    int index;
    long int inspection_counter;
    int divisor;
    uint64_t (*operation)(uint64_t, uint64_t);
    int operand;
    int target_true;
    int target_false;
    long long int hand[100];
    int i_hand;
} monkey;

void throw(monkey* m_from, monkey* m_to){
    m_to->i_hand++;
    m_to->hand[m_to->i_hand] = m_from->hand[m_from->i_hand];
    m_from->i_hand--;
}


int main(int argc, char**argv){
    FILE *f = fopen(INPUTFILE, "r");
    char line[BUFFERSIZE];
    int num_monkeys = 0;

    // count the number of monkeys
    while(!feof(f)){
        if (fgets(line, BUFFERSIZE, f)){
            int tmp;
            if(sscanf(line, "Monkey %d:\n", &tmp) != 0){
                num_monkeys++;
            }
        }
    }
    rewind(f);

    monkey* monkeys = (monkey*)malloc(num_monkeys * sizeof(monkey));
    monkey* monkeys_safe = (monkey*)malloc(num_monkeys * sizeof(monkey));
    int m_index = 0;

    while(!feof(f)){
        if (fgets(line, BUFFERSIZE, f)){
            if(sscanf(line, "Monkey %d:\n", &monkeys[m_index].index) != 0){
                // start reading in monkey data
                fgets(line, BUFFERSIZE, f);
                // Starting items: 56, 56, 92, 65, 71, 61, 79
                int i_hand = -1;
                char* token = strtok(line, ":");
                token = strtok(NULL, ",\n");
                while(token != NULL)
                {
                    i_hand++;
                    monkeys[m_index].hand[i_hand] = atoi(token);
                    token = strtok(NULL, ",\n");
                }
                monkeys[m_index].i_hand = i_hand;

                fgets(line, BUFFERSIZE, f);
                // Operation: new = old * 7
                char operation;
                if (sscanf(line, "  Operation: new = old %c %d\n", &operation, &monkeys[m_index].operand) == 2)
                {
                    // this is a 2 arg operation
                    if (operation == '+'){
                        monkeys[m_index].operation = &add;
                    }
                    else if (operation == '*'){
                        monkeys[m_index].operation = &mult;
                    }
                }
                //else scan for a squaring operation
                else if (strcmp(line, "  Operation: new = old * old\n") == 0)
                {
                    monkeys[m_index].operation = &square;
                }
                else 
                {
                    printf("Invalid operation\n"); 
                    return -1;
                }
                
                fgets(line, BUFFERSIZE, f);
                // Test: divisible by 3
                if (sscanf(line, "  Test: divisible by %d\n", &monkeys[m_index].divisor) != 1){
                    printf("Invalid divisor\n");
                    return -1;
                }
                
                fgets(line, BUFFERSIZE, f);
                // If true: throw to monkey 3
                if (sscanf(line, "    If true: throw to monkey %d\n", &monkeys[m_index].target_true) != 1){
                    printf("Invalid true target\n");
                    return -1;
                }
                
                fgets(line, BUFFERSIZE, f);
                // If false: throw to monkey 7
                if (sscanf(line, "    If false: throw to monkey %d\n", &monkeys[m_index].target_false) != 1){
                    printf("Invalid false target\n");
                    return -1;
                }

                m_index++;
            }
        }
    }

    /********** READING MONKEYS COMPLETE, PERFORM THROWS *********/

    memcpy(monkeys_safe, monkeys, num_monkeys * sizeof(monkey));

    uint64_t large_int_div = 1;
    for (int m_index = 0; m_index < num_monkeys; m_index++){
        large_int_div *= (uint64_t) monkeys[m_index].divisor;
    }
    printf("Simplify by taking modulo with %li\n", large_int_div);


    for (int round = 0; round < CHASEROUNDS; round++){
        for (int m_index = 0; m_index < num_monkeys; m_index++){
            while(monkeys[m_index].i_hand >= 0){
                monkeys[m_index].inspection_counter++;
                int target_monkey = -1;
                // DO OPERATION
                uint64_t worry = monkeys[m_index].hand[monkeys[m_index].i_hand];
                worry = monkeys[m_index].operation(worry % large_int_div, monkeys[m_index].operand);
                worry %= large_int_div;
                monkeys[m_index].hand[monkeys[m_index].i_hand] = worry; //overwrite worry value

                // THROW ACCORDINGLY
                if (worry % monkeys[m_index].divisor == 0){
                    target_monkey = monkeys[m_index].target_true;
                }
                else
                {
                    target_monkey = monkeys[m_index].target_false;
                }
                throw(&monkeys[m_index], &monkeys[target_monkey]);
            }
        }
    }


    // Print results
    for (int m_index = 0; m_index < num_monkeys; m_index++){
        printf("Monkey %i inspection count: %li\n", m_index, monkeys[m_index].inspection_counter);
    }
    
}