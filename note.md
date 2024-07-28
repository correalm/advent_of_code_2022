# Day 1
    - answer: 69912 calories;
    - TIPS:
        - find a better way to deal with fgets comparsion

# Day 2
    - answer: 13924 points
    - answer part 2: 13448 points
    - TIPS:
        - structs and enums are very useful

# Day 3
    - answer: 7917
    - TIPS:
        - need to find a way to cross the values one time only;
        - first implementation takes more than 1M instructions. This is insane!
        - valgrind
          - i need read more about
          - to find memory leaks
            - valgrind -s --leak-check=yes ./executable
          - i can use callgrind to profile the code
            - valgrind --tool=callgrind ./executable
            - callgrind_annotate callgrind.out
