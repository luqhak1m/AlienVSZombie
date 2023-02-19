# Part 2

## Video Demo

Please provide the YouTube link to your [Video Demo](https://youtube.com).

## Minimum Requirements

### Completed

List all the features completed.

1. Customising game board according to user input.
2. Alien’s movement. (Continuously move up, down, left and right)
3. Alien’s trail.
4. Alien’s interaction with game objects such as health packs, pods and arrows.
5. Halting Alien’s movement when interacting with rocks, zombies and borders.
6. Changing direction of arrows.
7. Changing direction of the alien when interacting with arrows.
8. Generating multiple zombies. (Within acceptable limit)
9. Randomising zombie’s attributes (Health, Attack, Range, Positions and Heading)
10. Zombie’s Movement.
11. Reset Alien's trail.
12. Reset Rock.
13. Increase health Alien when interacting with health pack.
14. Increase attack score of Alien when interacting with arrows.
15. Resetting attack score of Alien when it's turn ends.
16. Alien attacks Zombie and health of Zombie decreases according to attack score of zombie.
17. Zombie attacks alien based on its attack score when the alien is in it's range.
18. Save and Load game.

## Additional Features

1. Show zombie attributes to user
2. Pod grants extra turn to user

## Contributions

### Asyrani Syazwan

1. Randomly generate game board.
2. Editing video.
3. Documentation for part 1.
4. Modifying code to correspond to Windows OS.
5. Coding save and load function for Windows OS file.

### Nur Aisyah Nabila 

1. Alien movement and interactions with game objects.
2. Coding function for game objects such as arrow, health packs, rocks, and pods.
3. Coding function for the direction change of the arrow.
4. Coding function for Reset Alien's trail.
5. Coding function for Increase health Alien when interacting with health pack.
6. Coding function for Increase attack score of Alien when interacting with arrows.
7. Coding function for Resetting attack score of Alien when it's turn ends.
8. Coding function for Alien attacks Zombie and health of Zombie decreases according to attack score of zombie.
9. Coding save and load function.

### Luqman Hakim

1. Generating multiple zombies with randomized attributes.
2. Moving the zombies randomly for each turn.
3. Attacking Alien if it's in range.
4. Attacking nearest zombie when Alien encounters pod object.
5. Displaying stats for zombie during Alien and each Zombie's turn.
6. Remove dead zombie from gameboard.
7. Skip dead zombie's turn.

## Problems Encountered & Solutions

Problem: Had trouble finding nearest Zombies (diagonally).
Solution: Pythagoras theorem

Problem : Had trouble loading the game with zombies. The gameboard.txt file didnt save the correct positions of the zombies when loading.
Solution: The heading which was saved in the zombie.txt was data type integer, however the heading in the code was data type char. Thus, we solved this problem by converting int to char by + 48 to the int. 
