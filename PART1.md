# Part 1

## Video Demo

[Video Demo](https://youtu.be/dvGX2Kzxn78)

## Minimum Requirements

### Completed

1. Customising game board according to user input.
2. Alien’s movement. (Continuously move up, down, left and right)
3. Alien’s trail. 
4. Alien’s interaction with game objects such as health packs, pods and arrows.
5. Halting Alien’s movement when interacting with rocks, zombies and borders.
6. Changing direction of arrows.
7. Changing direction of the alien when interacting with arrows.
8. Generating multiple zombies. (Within acceptable limit)
9. Randomized zombie’s attributes (Health, Attack, Range, Positions and Heading)
10. Zombie’s Movement.

### To Do

1. Functions of pod, health pack, rock, and arrow.
2. Alien attacks a zombie.
3. Accumulation of Alien’s attack when interacting with arrows. 
4. Zombies attack the alien.
5. Resetting trail of alien
6. Save, load, pause game.
7. Checking zombie’s range from aliens.
8. Defeated/Undefeated zombies.

## Additional Features

1. Show zombie attributes to user

## Contributions

### Asyrani Syazwan

1. Randomly generate gameboard.
2. Editing video.
3. Documentation for part 1.

### Nur Aisyah Nabila

1. Alien movement and interactions with game objects.
2. Implementing game objects such as arrow, health packs, rocks, and pods.
3. Implementing the direction change of the arrow.

### Luqman Hakim

1. Generating multiple zombies with randomized attributes.
2. Moving the zombies randomly for each turn.

## Problems Encountered & Solutions

<ins>Problems encountered during coding for part 1.</ins>

Problem 1: Centering Alien in the gameboard.
Solution: We found the center of the gameboard by adding 1 and dividing 2 to the X and Y dimension of the gameboard. After finding the center, we used the coordinates to create the if statement for the Alien's initial position. 

Problem 2: Alien does not move even though there is an arrow. 
Solution: From the long if statement, we split it according to each condition. Each condition has their own if statement.

Problem 3: We had trouble generating multiple zombies because although the zombies were successfully created, there were never any way to access them individually.
Solution: Instead of filling the parameters while creating the zombies, instead we created a list of zombies first and then assign the parameters/attributes later (we did not know much about Object and Classes back then).

Problem 4: Another problem with the zombies was that it could not detect the presence of other zombies and alien.
Solution: So instead we just make a condition for each object.

<ins>Unsolved problems.</ins>
1. Zombie 
  - After each move, zombies struggle with checking for aliens in range.
3. System(“clear”)
  - Cannot display help.
  - Cannot display zombie attributes.


