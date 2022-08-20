#include "Catch2/Catch.hpp"
#include <iostream>
#include <list>
#include <algorithm>

/*
		Imagine that you are in charge of scheduling a conference room.

	You are presented with a set S = {a1, a2, ..., an} of p_size proposed activities
	that wish to reserve the conference room, and the room can serve only one activity at a time.
	Each activity ai has a start time si and a finish time fi,	where 0 <= si < fi < infinite.
	If selected, activity ai takes place during the half-open time interval [si, fi).
	Activities ai and aj are compatible if the intervals [si, fi) and [sj, fj) do not overlap.
	That is, ai and aj are compatible if si >= fj or sj >= fi.
	Or you can say: before ai start aj must finish, or before aj start ai must finish.
	(Assume that if your staff needs time to change over the room from one activity to the next,
	the changeover time is built into the intervals.)

	In the activity-selection problem, your goal is to select a maximum-p_size subset of mutually compatible activities.
	Assume that the activities are sorted in monotonically increasing order of finish time:

	f1 <= f2 <= f3 <= ... <= fn-1 < fn				(15.1)

	Given input is a table below:
	i	|	1		2		3		4		5		6		7		8		9		10		11
-------------------------------------------------------------------------------------------------
	si	|	1		3		0		5		3		5		6		7		8		2		12
	fi	|	4		5		6		7		9		9		10		11		12		14		16
										Figure 15.1

	In figure 15.1. The subset {a3, a9, a11} consists of mutually compatible activities.
	But it is not a maximum subset, however, since the subset {a1, a4, a8, a11} is larger.
	In fact, {a1, a4, a8, a11} is a largest subset of mutually compatible activities,
	and another largest subset is {a2, a4, a9, a11}.
*/

struct Activity
{
	Activity() : start_time(0), finish_time(0) {}
	Activity(int p_start_time, int p_finish_time) : start_time(p_start_time), finish_time(p_finish_time) {}
	Activity(std::initializer_list<int>& p_args) : start_time(*p_args.begin()), finish_time(*(p_args.begin() + 1))
	{
		assert(p_args.size() == 2);
	}

	int start_time;
	int finish_time;
};

std::vector<Activity> recursive_activity_selector(const std::vector<Activity>& p_activities, int p_current_activity, int p_size)
{
	std::vector<Activity> result;

	if (0 == p_size)
	{
		return result;
	}

	// Corner case: The first activity is guaranteed to have the finish time soonest.
	if (0 == p_current_activity)
	{
		result.push_back(p_activities[p_current_activity]);
	}

	int next_activity = p_current_activity + 1;
	// While the current evaluate activity is not finish.
	while (next_activity < p_size && p_activities[next_activity].start_time < p_activities[p_current_activity].finish_time)
	{
		++next_activity;
	}

	if (next_activity < p_size)
	{
		result.push_back(p_activities[next_activity]);
		std::vector<Activity> activities = recursive_activity_selector(p_activities, next_activity, p_size);
		// Perform join operation on result and activities.
		result.insert(result.end(), activities.begin(), activities.end());
	}

	return result;
}



std::vector<Activity> greedy_activity_selector(std::vector<Activity> p_activities, int p_size)
{
	std::vector<Activity> activities;

	if (0 == p_size)
	{
		return activities;
	}

	activities.push_back(p_activities[0]);

	for (int current_activity(0), next_activity(1); next_activity < p_size; ++next_activity)
	{
		// Is current activity finished?
		if (p_activities[current_activity].finish_time <= p_activities[next_activity].start_time)
		{
			activities.push_back(p_activities[next_activity]);
			current_activity = next_activity;
		}
	}

	return activities;
}


TEST_CASE("Check longest_palindrome_subsequence.", "[longest_palindrome_subsequence]")
{
	std::vector<Activity> input{ {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {7, 11}, {8, 12}, {2, 14}, {12, 16} };

	SECTION("greedy_activity_selector.")
	{
		std::vector<Activity> activities{ greedy_activity_selector(input, input.size()) };

		for (auto& i : activities)
		{
			std::cout << '{' << i.start_time << ", " << i.finish_time << "} ";
		}

		std::cout << "\n";
	}

	SECTION("recursive_activity_selector.")
	{
		std::vector<Activity> activities{ recursive_activity_selector(input, 0, input.size()) };

		for (auto& i : activities)
		{
			std::cout << '{' << i.start_time << ", " << i.finish_time << "} ";
		}
		std::cout << "\n";
	}

}