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
    - answer part 2: 2585
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
        - part II
          - need fix memory leaks (OK!)
          - need simplify the code (OK!)

# Day 4
    - answer: 542
    - answer part 2: 900
    - TIPS:
        - Math is very cool

# Day 5
    - answer: VWLCWGSDQ
    - answer part 2: TCGLQSLPW
    - TIPS: fuck!
        - need to read more about type castaing. I have some troubles with round and floor functions...

# Day 6
    - answer: 1140
    - TIPS: TDD men!
