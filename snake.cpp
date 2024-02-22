#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>       // Include Fl_Box for displaying images
#include <FL/fl_ask.H>       // Include fl_ask.H for message box
#include <FL/Fl_PNG_Image.H> // Include Fl_PNG_Image for PNG images
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

const int BOARD_SIZE = 10;
const int SQUARE_SIZE = 57;
const int BORDER_X = 31;
const int BORDER_Y = 31;
const int WINDOW_WIDTH = BOARD_SIZE * SQUARE_SIZE + 200 + 2 * BORDER_X;
const int WINDOW_HEIGHT = BOARD_SIZE * SQUARE_SIZE + 2 * BORDER_Y;
// TODO: Need a way to figure out if the current player position has a snake or ladder without explicitly checking
// possibly can use a hashmap of positions to boardelements
// Should individual classes inherit from a drawable class that has a virtual draw method
// Or the drawing stuff of each class be done in a separate class
// like player class having a draw method that delegates drawing task to playerGUI's draw method (bridge? observer?)
// separates drawing logic from player logic
struct Square
{
    int x, y;
    int number;
    int destination;
    Square(int x, int y, int number, int destination = -1) : x(x), y(y), number(number), destination(destination) {}
};
class Dice
{
public:
    unsigned int nextRoll();
};

class Player
{
    int position;
    Fl_Color color;

public:
    Player(Fl_Color col) : color(col) {}
    void updatePosition(int pos) { position = pos; }
};

class BoardElement
{
protected:
    int m_start, m_end;

public:
    BoardElement(int start, int end) : m_start(start), m_end(end) {}
    virtual void action(Player &pl) = 0; // performs the action on the given player
    virtual void getPosition() = 0;      // returns the position at where the element is active
};
class Board
{
    // will have a hashmap of positions to board elements
public:
    BoardElement *getBoardElementAtPosition(int pos); // query the hashmap to return the board element if present
};
class Game // singleton + composite
{
    // encapsulate the game logic
    // rolling die, updating player position
};
class GUI
{
    // support the drawing of the game
};

class BoardWidget : public Fl_Widget
{
private:
    std::vector<Square> squares;
    int playerPosition;
    int diceRoll;
    Fl_Box *diceBox, *boardBox, *playerBox;
    Fl_Box *diceRollLabel;
    Fl_PNG_Image *dicePNG[6];
    Fl_PNG_Image *boardPNG;
    bool gamePaused;

public:
    BoardWidget(int x, int y, int w, int h, const char *label = nullptr)
        : Fl_Widget(x, y, w, h, label), playerPosition(0), diceRoll(0), gamePaused(false)
    {
        bool reverse = false;
        int square_number = 1;
        for (int i = BOARD_SIZE - 1; i >= 0; --i)
        {
            if (reverse)
            {
                for (int j = BOARD_SIZE - 1; j >= 0; --j)
                {
                    squares.push_back(Square(j * SQUARE_SIZE + BORDER_X, i * SQUARE_SIZE + BORDER_Y, square_number++));
                }
            }
            else
            {
                for (int j = 0; j < BOARD_SIZE; ++j)
                {
                    squares.push_back(Square(j * SQUARE_SIZE + BORDER_X, i * SQUARE_SIZE + BORDER_Y, square_number++));
                }
            }
            reverse = !reverse;
        }
        squares[3].destination = 55;
        squares[11].destination = 49;
        squares[13].destination = 54;
        squares[21].destination = 57;
        squares[27].destination = 9;
        squares[36].destination = 2;
        squares[40].destination = 78;
        squares[47].destination = 15;
        squares[53].destination = 87;
        squares[74].destination = 31;
        squares[93].destination = 70;
        squares[95].destination = 41;

        // Load dice images
        for (int i = 0; i < 6; ++i)
        {
            std::string filename = "dice_" + std::to_string(i + 1) + ".png";
            dicePNG[i] = new Fl_PNG_Image(filename.c_str());
        }
        boardPNG = new Fl_PNG_Image("board.png");
        boardBox = new Fl_Box(FL_NO_BOX, 0, 15, 0, 0, "");
        playerBox = new Fl_Box(0, 0, 0, 0, "");
        playerBox->color(FL_RED);
        playerBox->box(FL_FLAT_BOX); // Set the box type to FL_FLAT_BOX for a flat appearance
        // Create dice roll label
        diceRollLabel = new Fl_Box(x + w + 10, 10, 100, 20, "");
        diceRollLabel->labelfont(FL_ENGRAVED_BOX);
        diceRollLabel->color(FL_WHITE); // Set the background color of the box

        diceRollLabel->labelsize(16);

        // Create box for displaying dice image
        diceBox = new Fl_Box(x + w + 10, y + h / 2 - 50, 0, 0, "");
        diceBox->box(FL_FLAT_BOX); // Set the box type to FL_FLAT_BOX for a flat appearance
        diceBox->color(FL_WHITE);  // Set the background color of the box
    }

    void draw() override
    {
        boardBox->image(boardPNG);
        boardBox->size(boardPNG->w(), boardPNG->h());
        for (const auto &square : squares)
        {
            int x = square.x;
            int y = square.y;
            if ((square.number + BOARD_SIZE) % 2 == 0)
                fl_color(230, 230, 230);
            else
                fl_color(255, 255, 255);
            fl_rectf(x, y, SQUARE_SIZE, SQUARE_SIZE);
            fl_color(FL_BLACK);
            fl_rect(x, y, SQUARE_SIZE, SQUARE_SIZE);
            // if (square.destination != -1)
            // {
            //     fl_color(FL_RED);
            //     fl_line(x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 2, squares[square.destination].x + SQUARE_SIZE / 2, squares[square.destination].y + SQUARE_SIZE / 2);
            // }
            // Draw number text in the center of the cell
            fl_font(FL_HELVETICA, 16);
            fl_color(FL_BLACK);
            fl_draw(std::to_string(square.number).c_str(), x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 2);
        }
        fl_color(FL_BLUE);
        fl_pie(squares[playerPosition].x + 5, squares[playerPosition].y + 5, SQUARE_SIZE - 10, SQUARE_SIZE - 10, 0, 360);
        playerBox->resize(squares[playerPosition].x + 5, squares[playerPosition].y + 5, SQUARE_SIZE - 10, SQUARE_SIZE - 10);
    }

    int handle(int event) override
    {
        if (!gamePaused && event == FL_PUSH)
        {
            diceRoll = (rand() % 6) + 1;
            redraw();
            playerPosition += diceRoll;
            if (squares[playerPosition].destination != -1)
                playerPosition = squares[playerPosition].destination;
            redraw();
            std::string rollStr = "Dice Roll: " + std::to_string(diceRoll);
            diceRollLabel->copy_label(rollStr.c_str());
            //  Draw dice image
            if (diceRoll > 0 && diceRoll <= 6)
            {
                Fl_PNG_Image *diceImage = dicePNG[diceRoll - 1];
                diceBox->image(dicePNG[diceRoll - 1]);
                diceBox->size(diceImage->w() + 10, diceImage->h() + 10);
                diceBox->redraw();
            }
            if (playerPosition >= BOARD_SIZE * BOARD_SIZE - 1)
            {
                // diceRollLabel->redraw();
                diceRollLabel->copy_label("Congratulations!");
                gamePaused = true;
            }
        }
        return Fl_Widget::handle(event);
    }
};

int main()
{
    srand(time(nullptr));

    Fl_Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Snake and Ladder");

    BoardWidget board(0, 0, WINDOW_WIDTH - 200, WINDOW_HEIGHT);
    window.resizable(&board);
    window.end();

    window.show();
    return Fl::run();
}
