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
const int SQUARE_SIZE = 50;
const int WINDOW_WIDTH = BOARD_SIZE * SQUARE_SIZE + 200;
const int WINDOW_HEIGHT = BOARD_SIZE * SQUARE_SIZE;

struct Square
{
    int x, y;
    int number;
    int destination;
    Square(int x, int y, int number, int destination = -1) : x(x), y(y), number(number), destination(destination) {}
};

class BoardWidget : public Fl_Widget
{
private:
    std::vector<Square> squares;
    int playerPosition;
    int diceRoll;
    Fl_Box *diceBox;
    Fl_Box *diceRollLabel;
    Fl_PNG_Image *dicePNG[6];
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
                    squares.push_back(Square(j * SQUARE_SIZE, i * SQUARE_SIZE, square_number++));
                }
            }
            else
            {
                for (int j = 0; j < BOARD_SIZE; ++j)
                {
                    squares.push_back(Square(j * SQUARE_SIZE, i * SQUARE_SIZE, square_number++));
                }
            }
            reverse = !reverse;
        }
        squares[12].destination = 2;
        squares[23].destination = 15;
        squares[35].destination = 5;
        squares[45].destination = 30;
        squares[18].destination = 33;
        squares[29].destination = 40;
        squares[41].destination = 59;
        squares[50].destination = 66;

        // Load dice images
        for (int i = 0; i < 6; ++i)
        {
            std::string filename = "dice_" + std::to_string(i + 1) + ".png";
            dicePNG[i] = new Fl_PNG_Image(filename.c_str());
        }

        // Create dice roll label
        diceRollLabel = new Fl_Box(x + w + 10, 10, 100, 20, "");
        diceRollLabel->labelfont(FL_ENGRAVED_BOX);
        diceRollLabel->color(FL_WHITE); // Set the background color of the box

        diceRollLabel->labelsize(16);

        // Create box for displaying dice image
        diceBox = new Fl_Box(x + w + 10, y + h / 2 - 50, 100, 100, "");
        diceBox->box(FL_FLAT_BOX); // Set the box type to FL_FLAT_BOX for a flat appearance
        diceBox->color(FL_WHITE);  // Set the background color of the box
    }

    void draw() override
    {
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
            if (square.destination != -1)
            {
                fl_color(FL_RED);
                fl_line(x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 2, squares[square.destination].x + SQUARE_SIZE / 2, squares[square.destination].y + SQUARE_SIZE / 2);
            }
            // Draw number text in the center of the cell
            fl_font(FL_HELVETICA, 16);
            fl_color(FL_BLACK);
            fl_draw(std::to_string(square.number).c_str(), x + SQUARE_SIZE / 2, y + SQUARE_SIZE / 2);
        }
        fl_color(FL_BLUE);
        fl_pie(squares[playerPosition].x + 5, squares[playerPosition].y + 5, SQUARE_SIZE - 10, SQUARE_SIZE - 10, 0, 360);
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
                diceBox->size(diceImage->w(), diceImage->h() + 20);
                diceBox->redraw();
            }
            if (playerPosition >= BOARD_SIZE * BOARD_SIZE - 1)
            {
                //diceRollLabel->redraw();
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
