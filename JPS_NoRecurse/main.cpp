#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <assert.h>
#include "path.h"
#include "Just_A_star.h"

void TestEdgeCases() {
	unsigned char pMap[] = { 1 }; // Single node
	int pOutBuffer[10];

	int nRes = A_Star::FindPath(0, 0, 0, 0, pMap, 1, 1, pOutBuffer, 10);
	assert(nRes == 0); // Question of definition

	unsigned char pMap2[] = {
		1, 1, 1,
		1, 1, 1
	};
	int pOutBuffer2[2]; // Too small buffer

	nRes = A_Star::FindPath(0, 0, 2, 1, pMap2, 3, 2, pOutBuffer2, 2);
	assert(nRes == 3);
}

void TestInvalidLongPath() {
	unsigned char pMap[] = {
		1, 0, 0, 1, 1, 1,
		1, 0, 1, 1, 1, 1,
		1, 0, 0, 1, 1, 0,
		1, 0, 1, 1, 0, 1,
		1, 1, 1, 0, 1, 1,
		0, 0, 0, 0, 0, 1
	};
	int pOutBuffer[100];

	int nRes = A_Star::FindPath(0, 0, 5, 5, pMap, 6, 6, pOutBuffer, 100);
	assert(nRes == -1);
}

void TestInvalidPath() {
	unsigned char pMap[] = {
		0, 0, 1,
		0, 1, 1,
		1, 0, 1
	};
	int pOutBuffer[7];

	int nRes = A_Star::FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
	assert(nRes == -1);
}

void TestValidLongPath() {
	unsigned char pMap[] = {
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1,
		0, 0, 0, 0, 1, 1
	};
	int pOutBuffer[100];

	int nRes = A_Star::FindPath(0, 0, 5, 5, pMap, 6, 6, pOutBuffer, 100);
	assert(nRes == 10);
}

void TestValidOnePath() {
	unsigned char pMap[] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 1, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
	};
	int pOutBuffer[100];

	int nRes = A_Star::FindPath(4, 4, 3, 9, pMap, 10, 10, pOutBuffer, 100);
	assert(nRes == 22);

	assert(pOutBuffer[0] == 45);
	assert(pOutBuffer[9] == 77);
	assert(pOutBuffer[21] == 93);
}

void TestValidPath() {
	unsigned char pMap[] = {
		1, 1, 1, 1,
		0, 1, 0, 1,
		0, 1, 1, 1
	};
	int pOutBuffer[12];

	int nRes = A_Star::FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);
	assert(nRes == 3);

	assert(pOutBuffer[0] == 1);
	assert(pOutBuffer[1] == 5);
	assert(pOutBuffer[2] == 9);
}

void print_map(const unsigned char* pmap, const int width, const int height, int target_y, int target_x, int start_x, int start_y)
{
	std::cout << "\n=====================================================\n";

	for (int i = 0; i != height; ++i)
	{
		for (int j = 0; j != width; ++j)
		{
			if (j == target_y && i == target_x)
			{
				std::cout << "T";
			}
			else if (j == start_y && i == start_x)
			{
				std::cout << "S";
			}
			else
			{
				std::cout << (pmap[j + (i * width)] == 1 ? 1 : 0);
			}
		}

		std::cout << "\n";
	}
}

bool in_buffer(int* buffer, const int val, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (buffer[i] == val)
		{
			return true;
		}
	}

	return false;
}

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void load_map(const char* name, unsigned char* pMap)
{
	std::ifstream map_file{};
	map_file.open(name);
	std::string line;

	unsigned char* p_pmap = pMap;
	int count = 0;

	while (std::getline(map_file, line))
	{
		for (unsigned char x : line)
		{
			*p_pmap = '\x1';
			++p_pmap;
			++count;
		}
	}
}

int main()
{
	unsigned char pMap[] = {
		1, 1, 1, 1,
		0, 1, 0, 1,
		0, 1, 1, 1
	};
	int pOutBuffer[12];
	auto a_star_res = A_Star::FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12);

	unsigned char pMap2[] = {
		0, 0, 1,
		0, 1, 1,
		1, 0, 1 };
	int pOutBuffer2[7];
	//auto res2 = FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7);

	unsigned char pMap3[] = {
		1,1,1,1,1,1,1,1,1,1,
		0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1
	};
	int pOutBuffer3[50];
	//auto res3 = FindPath(0, 0, 9, 4, pMap3, 10, 5, pOutBuffer3, 20);

	unsigned char pMap5[] = {
		1, 1, 1, 1,
		0, 1, 0, 1,
		0, 1, 1, 1 };

	int pOutBuffer5[12];
	//auto res5 = FindPath(0, 0, 1, 2, pMap5, 4, 3, pOutBuffer5, 12);

	unsigned char pMap7[] = {
		1, 1, 1, 1,
		1, 1, 0, 1,
		1, 1, 0, 1
	};
	int pOutBuffer7_1[12];
	int pOutBuffer7_2[12];


	unsigned char huge_map_500[500*500];
	load_map("500_500.txt", huge_map_500);
	int pOutBuffer_500[2000];

	unsigned char huge_map_750[750 * 750];
	load_map("750_750.txt", huge_map_750);
	int pOutBuffer_750[2000];

	//unsigned char huge_map_1000[1000 * 1000];
	//load_map("1000_1000.txt", huge_map_1000);
	//int pOutBuffer_1000[2000];

	auto res_500  = FindPath(10, 10, 24, 24, huge_map_500, 25, 25, pOutBuffer_500, 2000);
	auto res_750  = FindPath(0, 0, 749, 749, huge_map_750, 750, 750, pOutBuffer_750, 3000);
	//auto res_1000 = FindPath(0, 0, 999, 999, huge_map_1000, 1000, 1000, pOutBuffer_1000, 2000);

	constexpr int width = 100;
	constexpr int height = 100;

	int size = width * height;

	int pOutBuffer_X[10000];

	unsigned char map_X[width * height];

	std::fill_n(map_X, size, 0x01);

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, height - 1); // guaranteed unbiased

	auto rand_x = uni(rng);
	auto rand_y = uni(rng);
	auto target_x = uni(rng);
	auto target_y = uni(rng);

	auto res_x = A_Star::FindPath(0, 0, width - 1, height - 1, map_X, width, height, pOutBuffer_X, 10000);

	//for (int i = 0; i < 10; ++i)
	//{
	//	rand_x = uni(rng);
	//	rand_y = uni(rng);
	//	target_x = uni(rng);
	//	target_y = uni(rng);

	//	res_x = FindPath(rand_x, rand_y, target_x, target_y, map_X, width, height, pOutBuffer_X, 10000);

	//	std::cout << "Rand " << rand_x << " " << rand_y << " Target >> " << target_x << " " << target_y;

	//	if (res_x != -1)
	//	{
	//		std::cout << " Found!" << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << " No path!" << std::endl;
	//	}
	//}

	unsigned char forum_map[] = {
		0,0,0,0,0,1,0,0,0,
		0,0,0,0,0,1,0,0,0,
		0,1,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0
	};

	unsigned char forum_map_mirrored[] = {
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 0, 0, 1, 0, 0, 0, 0, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 0, 1, 0,
		0, 1, 1, 1, 1, 1, 1, 1, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0
	};	

	int forum_normal[20];
	int forum_mirrored[20];

	auto forum_normal_res = A_Star::FindPath(4, 4, 5, 0, forum_map, 9, 6, forum_normal, 20);
	auto forum_mirrrored_res = FindPath(4, 4, 3, 0, forum_map_mirrored, 9, 6, forum_mirrored, 20);

	unsigned char cross[] = {
		1, 1, 0, 1, 0,
		1, 1, 0, 0, 1,
		0, 1, 0, 0, 0,
		1, 1, 0, 1, 1,
		0, 1, 1, 1, 1
	};
	int cross_out[10];
	int cross_out_two[10];

	unsigned char pattern_one[] = {
		1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0
	};
	int pattern_one_out[50];
	int pattern_one_out_two[50];


	auto cross_res = A_Star::FindPath(0, 0, 4, 4, cross, 5, 5, cross_out, 20);
	auto cross_res_mirrored = FindPath(4, 4, 0, 0, cross, 5, 5, cross_out_two, 20);
	assert(cross_res == cross_res_mirrored);

	auto pattern_res = A_Star::FindPath(0, 6, 4, 3, pattern_one, 7, 7, pattern_one_out, 50);
	auto pattern_res_mirrored = A_Star::FindPath(4, 3, 0, 6, pattern_one, 7, 7, pattern_one_out_two, 50);
	assert(pattern_res == pattern_res_mirrored);

	unsigned char turn_test[] =
	{
		1,1,1,1,1,0,1,1,
		0,1,0,0,1,0,1,0,
		1,1,0,1,1,0,1,1,
		1,0,0,1,0,0,0,1,
		1,1,0,1,1,0,1,1,
		0,1,0,0,1,0,1,0,
		1,1,0,1,1,0,1,1,
		1,0,0,1,0,0,0,1,
		1,1,0,1,1,1,1,1
	};
	int turn_test_buffer[50];
	auto turn_test_res = A_Star::FindPath(3, 4, 1, 8, turn_test, 8, 9, turn_test_buffer, 50);

	unsigned char fail_test[] =
	{
		0,1,1,1,0,
		0,1,0,1,0,
		0,0,1,1,0,
		1,1,1,0,1
	};

	int shit_buffer[10];
	int shit_buffer2[10];
	auto fail_test_2 = A_Star::FindPath(0, 3, 1, 1, fail_test, 5, 4, shit_buffer2, 10);
	auto fail_test_1 = A_Star::FindPath(0, 3, 1, 1, fail_test, 5, 4, shit_buffer, 5);

	//TestEdgeCases();
	TestInvalidLongPath();
	TestInvalidPath();
	TestValidLongPath();
	TestValidOnePath();
	TestValidPath();

	unsigned char same_length_test[] = {
		1, 1, 0, 1, 1, 1,
		1, 1, 1, 1, 0, 1,
		1, 1, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1,
		0, 0, 0, 0, 1, 1
	};
	int same_length_buffer[100];
	int same_length_buffer_two[100];

	auto res6 = A_Star::FindPath(0, 0, 1, 2, pMap5, 4, 3, pOutBuffer5, 12);
	assert(res6 == 3);

	auto res7 = A_Star::FindPath(3, 2, 0, 0, pMap7, 4, 3, pOutBuffer7_1, 12);
	assert(res7 == 5);
	auto res7_1 = A_Star::FindPath(0, 0, 3, 2, pMap7, 4, 3, pOutBuffer7_2, 12);
	assert(res7_1 == 5);


	auto res8 = A_Star::FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 12);
	assert(res8 == -1);

	auto res9 = A_Star::FindPath(9, 4, 0, 0, pMap3, 10, 5, pOutBuffer3, 5);
	assert(res9 == 31);
	auto res10 = A_Star::FindPath(0, 0, 9, 4, pMap3, 10, 5, pOutBuffer3, 5);


	int same_length_res = A_Star::FindPath(0, 0, 5, 5, same_length_test, 6, 6, same_length_buffer, 100);

	//This one has two paths -> One long one short, must overlap at some point and are overwriting their previous parents.
	int same_length_res_opposite = A_Star::FindPath(5, 5, 0, 0, same_length_test, 6, 6, same_length_buffer_two, 100);
	//Index 3 & 9 are looping -> Must be where they overlap?

	assert(same_length_res == same_length_res_opposite);

	unsigned char git_test[] =
	{
		1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,
		1,1,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // 4
		0,0,0,0,0,0,0,0,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
		0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1, // 10
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1, // 15
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1, // 20
		1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 // 24
	};
	print_map(git_test, 39, 25, 21, 20, 0, 0);
	int git_buffer[200];
	int git_buffer_2[200];
	int git_buffer_3[200];
	int git_buffer_4[200];
	int git_buffer_5[200];
	int git_buffer_6[200];
	int git_buffer_7[200];
	int git_buffer_8[200];

	auto git_buffer_res = A_Star::FindPath(0, 0, 20, 20, git_test, 39, 25, git_buffer, 200); //Should be 154
	auto git_buffer_res_1 = A_Star::FindPath(20, 20, 0, 0, git_test, 39, 25, git_buffer_2, 200); //Should be 154
	assert(git_buffer_res == git_buffer_res_1);
	auto git_buffer_res_2 = A_Star::FindPath(38, 0, 0, 24, git_test, 39, 25, git_buffer_3, 200); //Should be 62
	auto git_buffer_res_3 = A_Star::FindPath(0, 24, 38, 0, git_test, 39, 25, git_buffer_4, 200); //Should be 62
	assert(git_buffer_res_2 == git_buffer_res_3);

	auto north = A_Star::FindPath(19, 0, 19, 24, git_test, 39, 25, git_buffer_5, 200); //Should be 60
	auto south = A_Star::FindPath(19, 24, 19, 0, git_test, 39, 25, git_buffer_6, 200); //Should be 60
	assert(north == south);

	auto east = A_Star::FindPath(0, 12, 38, 12, git_test, 39, 25, git_buffer_7, 200); //Should be 78
	auto west = A_Star::FindPath(38, 12, 0, 12, git_test, 39, 25, git_buffer_8, 200); //Should be 78
	assert(east == west);

	assert(git_buffer_res == 154);
	assert(git_buffer_res_1 == 154);

	int short_test_buffer_north[15];
	int short_test_buffer_east[15];
	int short_test_buffer_south[15];
	int short_test_buffer_west[15];

	unsigned char short_test[] =
	{
		1,1,1,1,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,0,1,
		1,0,0,1,1,
		1,0,0,1,0,
		1,0,0,1,1,
		1,0,0,0,1,
		1,1,1,1,1
	};

	//5 width 10
	auto final_test_north = A_Star::FindPath(2, 0, 2, 10, short_test, 5, 11, short_test_buffer_north, 50);
	auto final_test_east = A_Star::FindPath(4, 5, 0, 5, short_test, 5, 11, short_test_buffer_east, 50);
	auto final_test_south = A_Star::FindPath(2, 10, 2, 0, short_test, 5, 11, short_test_buffer_south, 50);
	auto final_test_west = A_Star::FindPath(0, 5, 4, 5, short_test, 5, 11, short_test_buffer_west, 50);
	assert(final_test_north == 14);
	assert(final_test_south == 14);
	assert(final_test_east == 14);
	assert(final_test_west == 14);

	const unsigned char filkry_map[] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //starts at 0
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //10
		1, 1, 1, 0, 0, 0, 0, 1, 1, 1, //20
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, //30
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, //40
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, //50
		1, 1, 1, 0, 1, 1, 0, 1, 1, 1, //60
		1, 1, 1, 0, 1, 0, 0, 1, 1, 1, //70
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //80
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, //90
	};

	int filkry_buffer_one[20];
	int filkry_buffer_two[20];
	int filkry_buffer_three[20];
	int filkry_buffer_four[20];

	//Should be 11
	auto filkry_res = A_Star::FindPath(4, 8, 4, 1, filkry_map, 10, 10, filkry_buffer_one, 20);
	auto filkry_res_2 = A_Star::FindPath(4, 1, 4, 8, filkry_map, 10, 10, filkry_buffer_two, 20);
	assert(filkry_res == 11);
	assert(filkry_res_2 == 11);

	//should be 17 (Works normal but not mirrored)
	auto f_2 = A_Star::FindPath(5, 3, 4, 1, filkry_map, 10, 10, filkry_buffer_three, 20);
	auto f_3 = A_Star::FindPath(4, 1, 5, 3, filkry_map, 10, 10, filkry_buffer_four, 20);
	assert(f_2 == 17);
	assert(f_3 == 17);

	unsigned char another_test[] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 1, 0, 1, 1, 1, 1,
		1, 1, 0, 0, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1
	};
	int another_test_buffer[14];
	auto sigh_res = A_Star::FindPath(2, 3, 7, 3, another_test, 8, 7, another_test_buffer, 14);

	unsigned char other_git_map[] =
	{
		1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // 4
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // 10
		1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // 15
		1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // 20
	};//    0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8

	std::vector<int> res;
	res.resize(600);

	int start_x = 0;
	int start_y = 0;
	int tgt_x = 32;
	int tgt_y = 2;

	int rv = A_Star::FindPath(start_x, start_y, tgt_x, tgt_y, other_git_map, 39, 20, res.data(), res.size());

	unsigned char big_map_10[] = {
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,0,
		1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int big_map_buffer[100];
	int big_map_buffer_mirrored[100];
	int big_map_buffer_other[100];
	int big_map_a_star[100];

	auto big_map_res = A_Star::FindPath(1, 1, 35, 12, big_map_10, 39, 22, big_map_buffer, 256);
	auto big_map_res_mirrored = A_Star::FindPath(35, 12, 1, 1, big_map_10, 39, 22, big_map_buffer_mirrored, 256);

	auto a_star_big = A_Star::FindPath(1, 1, 35, 12, big_map_10, 39, 22, big_map_a_star, 256);

	std::cout << "Return (should be 95): " << big_map_res << "\n" << "pOutBuffer: ";
	for (int i = 0; i < big_map_res && i < 256; i++)
		std::cout << big_map_buffer[i] << " ";
	std::cout << "\n\n";
	std::cout << "Return (should be 95): " << a_star_big << "\n" << "pOutBuffer: ";
	for (int i = 0; i < a_star_big && i < 256; i++)
		std::cout << big_map_a_star[i] << " ";
	std::cout << "\n\n";

	for (int i = 0; i < a_star_big; ++i)
	{
		if (big_map_a_star[i] != big_map_buffer_other[i])
		{
			auto ok = true;
		}
	}

	TestEdgeCases();
	TestInvalidLongPath();
	TestInvalidPath();
	TestValidLongPath();
	TestValidOnePath();

	return 0;
}




