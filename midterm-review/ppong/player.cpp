/*
 * player.cpp -- Process Pong Player
 * ----------------------------------
 * A single tennis player process. This program is fully provided to students.
 *
 * Usage: ./player <player_number> <skill>
 *   player_number: 1 or 2 (Player 1 serves first)
 *   skill: double between 0.0 and 1.0
 *
 * Communication:
 *   - Uses read(STDIN_FILENO, ...) to read opponent's shot quality (via pipe).
 *   - Uses write(STDOUT_FILENO, ...) to write own shot quality (via pipe).
 *   - Uses fprintf(stderr, ...) to print human-readable play-by-play.
 *
 * Termination:
 *   - On miss or net hit: prints result to stderr, then exits.
 *     Closing stdout causes the opponent to receive EOF.
 *   - On EOF from stdin: opponent has exited, so this player exits silently.
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

/**
 * player_hit
 * ----------
 * Given a player's skill (0.0-1.0) and the difficulty of the previous shot
 * (0.0 = easy, 1.0 = impossible), returns the quality of the player's shot.
 * A return value < 0.5 means the player missed.
 */
static double player_hit(double skill, double prev_shot_quality)
{
    double r = (double)rand() / RAND_MAX;
    return skill * 0.5f + (1.0f - prev_shot_quality) * 0.2f + r * 0.3f;
}

/**
 * over_net
 * --------
 * Given a player's skill and the quality of their shot, returns true if the
 * ball clears the net, false otherwise.
 */
static bool over_net(double skill, double shot_quality)
{
    double r = (double)rand() / RAND_MAX;
    return (shot_quality * 0.6f + skill * 0.1f + r * 0.3f) > 0.5f;
}

/**
 * attempt_shot
 * ------------
 * Computes a shot, checks if it clears the net, and either writes the result
 * to stdout or prints a failure message and returns false.
 */
static bool attempt_shot(int player_num, int opponent, double skill, double prev_quality)
{
    double shot = player_hit(skill, prev_quality);

    if (shot < 0.5f)
    {
        fprintf(stderr, "Player %d misses the ball.\n", player_num);
        fprintf(stderr, "Player %d wins the point!\n", opponent);
        return false;
    }

    if (!over_net(skill, shot))
    {
        fprintf(stderr, "Player %d hits the net.\n", player_num);
        fprintf(stderr, "Player %d wins the point!\n", opponent);
        return false;
    }

    fprintf(stderr, "Player %d hits the ball.\n", player_num);
    // Write the shot quality to stdout (which is connected to a pipe via dup2).
    char buf[8];
    int len = snprintf(buf, sizeof(buf), "%.2f\n", shot);
    write(STDOUT_FILENO, buf, len);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <player_number> <skill>\n", argv[0]);
        return 1;
    }

    int player_num = atoi(argv[1]);
    double skill = atof(argv[2]);
    int opponent = (player_num == 1) ? 2 : 1;

    // Seed RNG with time + pid so both players get different sequences.
    srand(time(NULL) + getpid());

    if (player_num == 1)
    {
        if (!attempt_shot(player_num, opponent, skill, 0.0))
            return 0;
    }

    // rally loop which read opponent's shot from stdin (pipe), then respond.
    char buf[8];
    int bytes;
    while ((bytes = read(STDIN_FILENO, buf, sizeof(buf) - 1)) > 0)
    {
        buf[bytes] = '\0';
        double incoming = atof(buf);
        if (!attempt_shot(player_num, opponent, skill, incoming))
        {
            // exits the program with status 0!
            return 0;
        }
    }
    return 0;
}
