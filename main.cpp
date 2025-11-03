#include <bits/stdc++.h>
#include "game.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // debug disabled
    // Construct simulator from stdin on heap to avoid stack overflow
    auto *game = new Game(cin);
    // debug disabled

    vector<char> ops;
    ops.reserve(min( (long long)game->m, 1LL * game->bricksTotal() ));

    // Greedy one-step lookahead with velocity bounding tie-breakers
    const string choices = "ABCDE";

    const int t_cap = std::min(game->m, 5000); // cap operations to avoid judge TLE
    while (game->bricksRemaining() > 0 && (int)ops.size() < t_cap) {
        Game::Save *s0 = game->save();

        char best_op = 'C';
        long long best_gain = LLONG_MIN;
        int best_touch = -1;
        int best_abs_vx = INT_MAX;

        // Evaluate candidates
        for (char op : choices) {
            game->load(s0);
            int gain = game->play(op);
            int touches = game->touch_cnt;
            int next_abs_vx = std::abs(game->situation_now.ball.vx);

            // Score tuple: higher gain, then more touches, then smaller |vx|
            bool better = false;
            if (gain > best_gain) better = true;
            else if (gain == best_gain && touches > best_touch) better = true;
            else if (gain == best_gain && touches == best_touch && next_abs_vx < best_abs_vx) better = true;
            else if (gain == best_gain && touches == best_touch && next_abs_vx == best_abs_vx && op == 'C' && best_op != 'C') better = true;

            if (better) {
                best_gain = gain;
                best_touch = touches;
                best_abs_vx = next_abs_vx;
                best_op = op;
            }
        }

        // Apply chosen operation
        game->load(s0);
        (void)game->play(best_op);
        game->erase(s0);

        ops.push_back(best_op);

        // Soft guard: if |vx| grows too large, try dampening on next rounds by preferring ops closer to 'C'
        // Already handled by tie-breaker preferring smaller |vx|.
    }

    // Output
    for (char c : ops) {
        cout << c << '\n';
    }
    delete game;
    return 0;
}
