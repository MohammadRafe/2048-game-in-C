#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 4

int board[BOARD_SIZE][BOARD_SIZE];
int score = 0;

void init_board()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = 0;
        }
    }
    score = 0;
}

void add_random_tile()
{
    int i, j;
    int num_empty = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                num_empty++;
            }
        }
    }
    if (num_empty == 0)
    {
        return;
    }
    int random_index = rand() % num_empty;
    int count = 0;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                if (count == random_index)
                {
                    board[i][j] = (rand() % 2 + 1) * 2;
                    return;
                }
                count++;
            }
        }
    }
}

void print_board()
{
    int i, j;
    printf("Score: %d\n", score);
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %d\t", board[i][j]);
        }
        printf("\n");
    }
}

void merge_tiles(int *tiles, int num_tiles)
{
    int i, j;
    for (i = 0; i < num_tiles - 1; i++)
    {
        if (tiles[i] == tiles[i + 1])
        {
            tiles[i] *= 2;
            score += tiles[i];
            for (j = i + 1; j < num_tiles - 1; j++)
            {
                tiles[j] = tiles[j + 1];
            }
            tiles[num_tiles - 1] = 0;
            break;
        }
    }
}

void move_left()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        int tiles[BOARD_SIZE] = {0};
        int num_tiles = 0;
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] != 0)
            {
                tiles[num_tiles] = board[i][j];
                num_tiles++;
            }
        }
        merge_tiles(tiles, num_tiles);
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (j < num_tiles)
            {
                board[i][j] = tiles[j];
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void move_right()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        int tiles[BOARD_SIZE] = {0};
        int num_tiles = 0;
        for (j = BOARD_SIZE - 1; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                tiles[num_tiles] = board[i][j];
                num_tiles++;
            }
        }
        merge_tiles(tiles, num_tiles);
        for (j = BOARD_SIZE - 1; j >= 0; j--)
        {
            if (BOARD_SIZE - 1 - j < num_tiles)
            {
                board[i][j] = tiles[BOARD_SIZE - 1 - j];
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void move_up()
{
    int i, j;
    for (j = 0; j < BOARD_SIZE; j++)
    {
        int tiles[BOARD_SIZE] = {0};
        int num_tiles = 0;
        for (i = 0; i < BOARD_SIZE; i++)
        {
            if (board[i][j] != 0)
            {
                tiles[num_tiles] = board[i][j];
                num_tiles++;
            }
        }
        merge_tiles(tiles, num_tiles);
        for (i = 0; i < BOARD_SIZE; i++)
        {
            if (i < num_tiles)
            {
                board[i][j] = tiles[i];
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

void move_down()
{
    int i, j;
    for (j = 0; j < BOARD_SIZE; j++)
    {
        int tiles[BOARD_SIZE] = {0};
        int num_tiles = 0;
        for (i = BOARD_SIZE - 1; i >= 0; i--)
        {
            if (board[i][j] != 0)
            {
                tiles[num_tiles] = board[i][j];
                num_tiles++;
            }
        }
        merge_tiles(tiles, num_tiles);
        for (i = BOARD_SIZE - 1; i >= 0; i--)
        {
            if (BOARD_SIZE - 1 - i < num_tiles)
            {
                board[i][j] = tiles[BOARD_SIZE - 1 - i];
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }
}

int is_game_over()
{
    int i, j;
    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == 0)
            {
                return 0;
            }
            if (i < BOARD_SIZE - 1 && board[i][j] == board[i + 1][j])
            {
                return 0;
            }
            if (j < BOARD_SIZE - 1 && board[i][j] == board[i][j + 1])
            {
                return 0;
            }
        }
    }
    return 1;
}

int main()
{
    srand(time(NULL));
    init_board();
    add_random_tile();
    add_random_tile();
    print_board();
    while (!is_game_over())
    {
        char input;
        printf("Enter move (w/a/s/d): ");
        scanf(" %c", &input);
        switch (input)
        {
        case 'a':
            move_left();
            break;
        case 'd':
            move_right();
            break;
        case 'w':
            move_up();
            break;
        case 's':
            move_down();
            break;
        default:
            continue;
        }
        add_random_tile();
        print_board();
    }
    printf("\n\nGame over! Final score: %d\n", score);
    return 0;
}
