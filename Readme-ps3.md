# PS3: Sokoban

## Contact
Name: Soon Thao
Section: 203
Time to Complete: 4 Hours


## Description
Sokoban is a box pushing game, PS3a creates the ui or interface needed to draw the level to a window for the games proper implementation. PS3a implements this by taking tiles from a spritesheet and drawing them to a window that is defined by a .txt file which holds the height, width and layout of the level through character reads. PS3a implements parts of the Sokoban class such as defining player location as well as the overloaded << and >> operators to read and write the level layout for further use and to read proper level layouts from a file. 

### Features
One of the major decisions was first understanding what private variables the class would need for part a at the least. I decided that the only variables the class needs to hold for fast access in both class function calls and how it interacts with the window, there was only a need for three variables, a vector2u playerpos which holds the player position, a spritesheet which holds the tiles for quick access by the draw function, and a matrix of characters to hold output from the opened file.

The playerpos variable mainly is used to hold the player position for possible movement in a direction more easily in the later part. I had decided that the class should hold a spritesheet class as instead of opening and creating a spritesheet object every single time the draw function is called, a spritesheet class object doesn't need to be created everytime that draw needs to be called, as when drawing to the window, it'd have to loop through and create a sprite for each tile before the draw. This was done with concern for time, as SpriteSheets.tosprite operation is not only expensive but can be taxing in terms of runtime so I thought it was best to have each game object have access to its own spritesheet.

Matrix is held by the class as its necessary to keep track of the game state in case the game state ever wants to be copied over to say a text file or something else using the >> operator, but it is also useful for shortening the function calls for width() and height(), while also simplifying making the << overloaded operator much easier to write, as all you'd need to do is loop through the file and resize the matrix and take output. 

(BELOW IS WHAT WAS ADDED IN PART B):

To make reset and other functions easier to implement, such as isWon(), an additional OriginalMap variable and goals member were added to track the original amount of storage spaces to compare without having to iterate through the matrix every time isWon is called to simplify it. An originalmap function is also needed to ensure that storage area spaces are properly changed to either a floor or storage area tile in both the matrix member so that whenever you move over one it correctly replaces it with a storage area tile or floor tile. 

#### Part a
part a specifically implemented the << and >> overloaded operators for game read and write of lvl and other text files, the width() and height() functions which return the dimensions of the game, the playerloc() function which returns the player position, and the main thing being the draw() function which takes from the matrix private member variable and uses the read file characters to draw sprites to a given window. 

printmatrix in the sokoban.cpp was just used to check that the matrix was reading from the file fully and correctly during implementation. 
#### Part b



### Memory
The level data was stored using a vector of vectors of characters. The outer vector holds the amount of rows along with the inner vector which holds all the values for each column of that specific row. This simplifies writing the function calls needed for part a, but also made creating the draw function easy, as vectors through the size and [] operator allow you to access the column and row sizes without ever needing to call width() or height(). By storing it this way as well, you don't need to have a member variable that holds height and width either, and direct access can be done through the vector structure. 

In terms of what the vectors hold, filling the vector was done using the << overloaded operator, where an input file from the commandline or a path to a .lvl text file was read character by character and input into the specific part of the matrix in row-major order. I also created a matrix print function called printmatrix to check the matrix during implementation to make sure its reading the file correctly as well. The level data in this way, is stored identical to the level data read in the .txt file, so each index of the vector will hold a character such as @,.,a,A,etc. that can be read when the draw function is called to then create a sprite dependent on the character and be drawn to the given window. 

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

### Issues
One of the knacks with my implementation is that if a file is written in a way where there is whitespace inbetween spots, that part of the matrix will be skipped as the matrix is filled using the << operator to read from a text file, which will inherently skip white space and newlines. I can imagine that in some scenarios if you were to say write the lvl file in a way where there are spaces inbetween characters the indexes in the vector that should hold those white spaces would just hold nothing. I don't think with the way that its being chosen to be implemented though that this should be a problem.

### Extra Credit
Anything special you did.  This is required to earn bonus points.


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

SFML Documentation: https://www.sfml-dev.org/documentation/3.0.2/
Dr. Daly's Discord: Student questions and others answers
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
Font (used for victory Message): https://www.dafont.com/pixel-arial-11.font
