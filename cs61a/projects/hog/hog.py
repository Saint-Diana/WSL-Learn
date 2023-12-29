"""CS 61A Presents The Game of Hog."""

from dice import six_sided, four_sided, make_test_dice
from ucb import main, trace, interact

GOAL_SCORE = 100  # The goal of Hog is to score 100 points.
FIRST_101_DIGITS_OF_PI = 31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679

######################
# Phase 1: Simulator #
######################

# 如果扔了 num_rolls(> 0) 个骰子，就执行这个函数求出得分
def roll_dice(num_rolls, dice=six_sided):
    """Simulate rolling the DICE exactly NUM_ROLLS > 0 times. Return the sum of
    the outcomes unless any of the outcomes is 1. In that case, return 1.

    num_rolls:  The number of dice rolls that will be made.
    dice:       A function that simulates a single dice roll outcome. dice equals the function 'make_fair_dice(sides)'
    """
    # These assert statements ensure that num_rolls is a positive integer.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls > 0, 'Must roll at least once.'
    # BEGIN PROBLEM 1
    total, i, flag = 0, 1, False
    while i <= num_rolls:
        point = dice() # the point of this dice
        if point == 1:
            flag = True
        # calcute the sum
        total += point
        i += 1
    if flag: # if any of the outcomes is 1, then return 1
        total = 1
    return total
    # END PROBLEM 1
# 3 + 1 返回1, 5 + 6 返回 11
# 如果扔了 0 个骰子，就执行这个函数求出得分
def free_bacon(score):
    """Return the points scored from rolling 0 dice (Free Bacon).

    score:  The opponent's current score.
    """
    assert score < 100, 'The game should be over.'
    pi = FIRST_101_DIGITS_OF_PI

    # if score = 0, then return 3.
    # else if score > 0, return k + 3, in which k represents the nth digit of pi. n equals score.
    # so we just need to trim pi to only (score + 1) digit(s)
    # Trim pi to only (score + 1) digit(s)

    # BEGIN PROBLEM 2

    # if score = 0, then pi = 3
    # if score = 1, then pi = 31
    # if score = 2, then pi = 314
    # ······

    # 一个整数 n 有 k + 1 位，则 n 满足 pow(10, k) <= n < pow(10, k + 1)
    # length = len(pi) # TypeError: object of type 'int' has no len()
    length, temp = 0, pi
    while temp > 0:
        temp //= 10
        length += 1
    pi = pi // pow(10, length - (score + 1))
    # END PROBLEM 2
    
    return pi % 10 + 3


def take_turn(num_rolls, opponent_score, dice=six_sided): # 进行一轮
    """Simulate a turn rolling NUM_ROLLS dice, which may be 0 (Free Bacon).
    Return the points scored for the turn by the current player.

    num_rolls:       The number of dice rolls that will be made.
    opponent_score:  The total score of the opponent.
    dice:            A function that simulates a single dice roll outcome.
    """
    # Leave these assert statements here; they help check for errors.
    assert type(num_rolls) == int, 'num_rolls must be an integer.'
    assert num_rolls >= 0, 'Cannot roll a negative number of dice in take_turn.'
    assert num_rolls <= 10, 'Cannot roll more than 10 dice.'
    assert opponent_score < 100, 'The game should be over.'
    # BEGIN PROBLEM 3
    if num_rolls == 0:
        return free_bacon(opponent_score)
    else:
        return roll_dice(num_rolls, dice)
    # END PROBLEM 3


def extra_turn(player_score, opponent_score): # 判断玩家是否能额外多一轮
    """Return whether the player gets an extra turn."""
    return (pig_pass(player_score, opponent_score) or
            swine_align(player_score, opponent_score))


def GCD(m, n):
    """return the GCD of m and n"""
    # 辗转相除法求最大公约数
    while n:
        m, n = n, m % n
    return m

def swine_align(player_score, opponent_score): # rule 1: 如果两个玩家的总分都`> 0`，并且当前玩家总分和对手总分的`GCD(最大公约数) >= 10`，当前玩家可以额外多一轮
    """Return whether the player gets an extra turn due to Swine Align.

    player_score:   The total score of the current player.
    opponent_score: The total score of the other player.

    >>> swine_align(30, 45)  # The GCD is 15.
    True
    >>> swine_align(35, 45)  # The GCD is 5.
    False
    """
    # BEGIN PROBLEM 4a
    if player_score > 0 and opponent_score > 0 and GCD(player_score, opponent_score) >= 10:
        return True
    else:
        return False
    # END PROBLEM 4a


def pig_pass(player_score, opponent_score):
    """Return whether the player gets an extra turn due to Pig Pass.

    player_score:   The total score of the current player.
    opponent_score: The total score of the other player.

    >>> pig_pass(9, 12)
    False
    >>> pig_pass(10, 12)
    True
    >>> pig_pass(11, 12)
    True
    >>> pig_pass(12, 12)
    False
    >>> pig_pass(13, 12)
    False
    """
    # BEGIN PROBLEM 4b
    if player_score < opponent_score and opponent_score - player_score < 3:
        return True
    else:
        return False
    # END PROBLEM 4b


def other(who):
    """Return the other player, for a player WHO numbered 0 or 1.

    >>> other(0)
    1
    >>> other(1)
    0
    """
    return 1 - who


def silence(score0, score1):
    """Announce nothing (see Phase 2)."""
    return silence


def play(strategy0, strategy1, score0=0, score1=0, dice=six_sided,
         goal=GOAL_SCORE, say=silence):
    """Simulate a game and return the final scores of both players, with Player
    0's score first, and Player 1's score second.

    A strategy is a function that takes two total scores as arguments (the
    current player's score, and the opponent's score), and returns a number of
    dice that the current player will roll this turn.
    
    strategy0:  The strategy function for Player 0, who plays first.
    strategy1:  The strategy function for Player 1, who plays second.
    score0:     Starting score for Player 0
    score1:     Starting score for Player 1
    dice:       A function of zero arguments that simulates a dice roll.
    goal:       The game ends and someone wins when this score is reached.
    say:        The commentary function to call at the end of the first turn.
    """
    who = 0  # Who is about to take a turn, 0 (first) or 1 (second)
    # BEGIN PROBLEM 5
    while score0 < goal and score1 < goal:
        if not who: # Player 0's turn
            score0 += take_turn(strategy0(score0, score1), score1, dice)
            say = say(score0, score1)
            # if player 0 can have an extra turn
            while score0 < goal and extra_turn(score0, score1):
                score0 += take_turn(strategy0(score0, score1), score1, dice)
                say = say(score0, score1)
        else: # Player 1's turn
            score1 += take_turn(strategy1(score1, score0), score0, dice)
            say = say(score0, score1)
            while score1 < goal and extra_turn(score1, score0):
                score1 += take_turn(strategy1(score1, score0), score0, dice)
                say = say(score0, score1)
        
        who = 1 - who # 1 -> 0; 0 -> 1
        
        
        # 每次都扔1个
        # 每次都扔到2
        # 目标是3
        # 先后执行echo_0和echo_1
        # 1. score0 = 0 + 2 = 2. >> * 2 >> ** 0
        # 2. score1 = 0 + 2 = 2. >> * 2 >> ** 2
        # 3. score0 = 2 + 2 = 4 > 3. 结束. >> * 4 >> ** 2

    # END PROBLEM 5
    # (note that the indentation for the problem 6 prompt (***YOUR CODE HERE***) might be misleading)
    # BEGIN PROBLEM 6
    # END PROBLEM 6
    return score0, score1


#######################
# Phase 2: Commentary #
#######################


def say_scores(score0, score1):
    """A commentary function that announces the score for each player."""
    print("Player 0 now has", score0, "and Player 1 now has", score1)
    return say_scores


def announce_lead_changes(last_leader=None):
    """Return a commentary function that announces lead changes.

    >>> f0 = announce_lead_changes()
    >>> f1 = f0(5, 0)
    Player 0 takes the lead by 5
    >>> f2 = f1(5, 12)
    Player 1 takes the lead by 7
    >>> f3 = f2(8, 12)
    >>> f4 = f3(8, 13)
    >>> f5 = f4(15, 13)
    Player 0 takes the lead by 2
    """
    def say(score0, score1):
        nonlocal last_leader # add it by myself
        if score0 > score1:
            leader = 0
        elif score1 > score0:
            leader = 1
        else:
            leader = None
        if leader != None and leader != last_leader:
            print('Player', leader, 'takes the lead by', abs(score0 - score1))
        return announce_lead_changes(leader) # 使用一个递归来记录当前的分数领先者
    return say


def both(f, g): # both() 返回值是函数 且 both()()返回值仍然是函数！ 这种设计可以在每次调用之后返回一个新的评论函数！
    """Return a commentary function that says what f says, then what g says.

    NOTE: the following game is not possible under the rules, it's just
    an example for the sake of the doctest

    >>> h0 = both(say_scores, announce_lead_changes())
    >>> h1 = h0(10, 0)
    Player 0 now has 10 and Player 1 now has 0
    Player 0 takes the lead by 10
    >>> h2 = h1(10, 8)
    Player 0 now has 10 and Player 1 now has 8
    >>> h3 = h2(10, 17)
    Player 0 now has 10 and Player 1 now has 17
    Player 1 takes the lead by 7
    """
    def say(score0, score1):
        return both(f(score0, score1), g(score0, score1)) # both(f, g)(score1, score2)的返回值仍然是一个函数，就是 both(f(score0, score1), g(score0, score1)) <==> say
    return say

# really hard to understand
def announce_highest(who, last_score=0, running_high=0):
    """Return a commentary function that announces when WHO's score
    increases by more than ever before in the game.

    NOTE: the following game is not possible under the rules, it's just
    an example for the sake of the doctest

    >>> f0 = announce_highest(1) # Only announce Player 1 score gains
    >>> f1 = f0(12, 0) # player 0's score = 12; player 1's score = 0. now the highest score in one turn is 0(default value).
    >>> f2 = f1(12, 9) # player 0's score = 12; player 1's score = 9. so increasement = 9 > 0. now the highest score in one turn is 9, then output the next line.
    9 point(s)! The most yet for Player 1
    >>> f3 = f2(20, 9) # player 0's score = 20; player 1's score = 9. so increasement = 0 < 9. now the highest score in one turn is still 9.
    >>> f4 = f3(20, 30) # player 0's score = 20; player 1's score = 30. so increasement = 30 - 9 = 21 > 9. now the highest score in one turn is 21, then output the next line.
    21 point(s)! The most yet for Player 1
    >>> f5 = f4(20, 47) # Player 1 gets 17 points; not enough for a new high
    >>> f6 = f5(21, 47)
    >>> f7 = f6(21, 77)
    30 point(s)! The most yet for Player 1
    """
    assert who == 0 or who == 1, 'The who argument should indicate a player.'
    # BEGIN PROBLEM 7
    player = 'Player 0' if not who else 'Player 1'
    def say(score0, score1):
        last_score_temp = last_score
        running_high_temp = running_high
        if not who: # For player 0
            increases = score0 - last_score # player 0's current turn score - last_score equals the increasement
            if increases > running_high:
                running_high_temp = increases
                print(running_high_temp, 'point(s)! The most yet for Player 0')
            last_score_temp = score0
        else:
            increases = score1 - last_score
            if increases > running_high:
                running_high_temp = increases
                print(running_high_temp, 'point(s)! The most yet for Player 1')
            last_score_temp = score1
        return announce_highest(who, last_score_temp, running_high_temp)

    return say
    # END PROBLEM 7


#######################
# Phase 3: Strategies #
#######################


def always_roll(n):
    """Return a strategy that always rolls N dice.

    A strategy is a function that takes two total scores as arguments (the
    current player's score, and the opponent's score), and returns a number of
    dice that the current player will roll this turn.

    >>> strategy = always_roll(5)
    >>> strategy(0, 0)
    5
    >>> strategy(99, 99)
    5
    """
    def strategy(score, opponent_score):
        return n
    return strategy


def make_averaged(original_function, trials_count=1000):
    """Return a function that returns the average value of ORIGINAL_FUNCTION
    when called.

    To implement this function, you will have to use *args syntax, a new Python
    feature introduced in this project.  See the project description.

    >>> dice = make_test_dice(4, 2, 5, 1)
    >>> averaged_dice = make_averaged(dice, 1000)
    >>> averaged_dice()
    3.0
    """
    # BEGIN PROBLEM 8
    def average_value(*args): # *args represents a tuple. so we can pass one or several formal parameters.
        total, i = 0, 0
        while i < trials_count:
            total = total + original_function(*args)
            i = i + 1
        return total / trials_count
    
    return average_value
    # END PROBLEM 8


def max_scoring_num_rolls(dice=six_sided, trials_count=1000):
    """Return the number of dice (1 to 10) that gives the highest average turn
    score by calling roll_dice with the provided DICE over TRIALS_COUNT times.
    Assume that the dice always return positive outcomes.

    >>> dice = make_test_dice(1, 6)
    >>> max_scoring_num_rolls(dice)
    1
    """
    # BEGIN PROBLEM 9
    "*** YOUR CODE HERE ***"
    # 1 to 10 all need to calculate the average
    averaged_dice = make_averaged(roll_dice, trials_count)
    highest, num = -1, -1
    for i in range(1, 11):
        # the number of dice equals i, so we need to use roll_dice(num_rolls, dice=six_sided)
        average = averaged_dice(i, dice)
        if average > highest:
            highest = average
            num = i
    return num
    # END PROBLEM 9


def winner(strategy0, strategy1):
    """Return 0 if strategy0 wins against strategy1, and 1 otherwise."""
    score0, score1 = play(strategy0, strategy1)
    if score0 > score1:
        return 0
    else:
        return 1


def average_win_rate(strategy, baseline=always_roll(6)):
    """Return the average win rate of STRATEGY against BASELINE. Averages the
    winrate when starting the game as player 0 and as player 1.
    """
    win_rate_as_player_0 = 1 - make_averaged(winner)(strategy, baseline)
    win_rate_as_player_1 = make_averaged(winner)(baseline, strategy)

    return (win_rate_as_player_0 + win_rate_as_player_1) / 2


def run_experiments():
    """Run a series of strategy experiments and report results."""
    if True:  # Change to False when done finding max_scoring_num_rolls
        six_sided_max = max_scoring_num_rolls(six_sided)
        print('Max scoring num rolls for six-sided dice:', six_sided_max)

    if False:  # Change to True to test always_roll(8)
        print('always_roll(8) win rate:', average_win_rate(always_roll(8)))

    if False:  # Change to True to test bacon_strategy
        print('bacon_strategy win rate:', average_win_rate(bacon_strategy))

    if False:  # Change to True to test extra_turn_strategy
        print('extra_turn_strategy win rate:', average_win_rate(extra_turn_strategy))

    if False:  # Change to True to test final_strategy
        print('final_strategy win rate:', average_win_rate(final_strategy))

    "*** You may add additional experiments as you wish ***"



def bacon_strategy(score, opponent_score, cutoff=8, num_rolls=6):
    """This strategy rolls 0 dice if that gives at least CUTOFF points, and
    rolls NUM_ROLLS otherwise.
    """
    # BEGIN PROBLEM 10
    return 0 if free_bacon(opponent_score) >= cutoff else num_rolls
    # END PROBLEM 10


def extra_turn_strategy(score, opponent_score, cutoff=8, num_rolls=6):
    """This strategy rolls 0 dice when it triggers an extra turn. It also
    rolls 0 dice if it gives at least CUTOFF points and does not give an extra turn.
    Otherwise, it rolls NUM_ROLLS.
    """
    # BEGIN PROBLEM 11
    # 如果扔 0 个会触发 extra_turn，就扔 0 个
    # 如果扔 0 个不触发 extra_turn，那就根据bacon_strategy来进行
    score_temp = score + free_bacon(opponent_score) # 扔 0 个之后的当前玩家得分
    return 0 if extra_turn(score_temp, opponent_score) or free_bacon(opponent_score) >= cutoff else num_rolls
    # END PROBLEM 11


def final_strategy(score, opponent_score):
    """Write a brief description of your final strategy.
    
    目前只知道当前玩家得分以及对手的得分。
    规则1：如果扔 0 个可以触发下一轮，就尽可能扔 0 个；
    规则2：如果扔 0 个不能触发下一轮，但是free_bacon(opponent_score) >= make_averaged(six_sided)(使用平均值作为cutoff)，也扔0个；
    规则3：如果扔 0 个不能触发下一轮，且free_bacon(opponent_score) < make_averaged(six_sided)，就使用max_scoring_num_rolls()找出能够得到最大平均分的骰子数量，然后扔这么多。
    """
    # BEGIN PROBLEM 12
    "不会"
    # END PROBLEM 12

##########################
# Command Line Interface #
##########################

# NOTE: Functions in this section do not need to be changed. They use features
# of Python not yet covered in the course.


@main
def run(*args):
    """Read in the command-line argument and calls corresponding functions."""
    import argparse
    parser = argparse.ArgumentParser(description="Play Hog")
    parser.add_argument('--run_experiments', '-r', action='store_true',
                        help='Runs strategy experiments')

    args = parser.parse_args()

    if args.run_experiments:
        run_experiments()