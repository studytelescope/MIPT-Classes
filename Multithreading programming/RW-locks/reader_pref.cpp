#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <unistd.h>

using namespace std;

const int THREAD_NUM = 20;

int shared_data;

std::atomic<int> reader_entry;
std::atomic<int> writer_entry;
std::atomic<int> common_entry;

void reader(int i);
void writer(int i);

int main()
{
	reader_entry = 0;
	common_entry = 0;
	writer_entry = 0;

	std::vector<std::thread> threads(THREAD_NUM);

	for(int i = 0; i < THREAD_NUM; i++)
		if(i == 5 || i == 7)
			threads[i] = std::thread(writer, i);
		else
			threads[i] = std::thread(reader, i);

 	for (auto& th : threads)
 		th.join();

	return 0;
}


void reader(int reader_rank)
{
	int writer_cannot_write = 1;
	int reader_desired  	= 1;
	int common_desired  	= 1;
	int reader_expected  	= 0;
	int common_expected  	= 0;
	int writer_can_write  	= -1;

	while(reader_entry.load() != reader_expected);

	writer_entry.fetch_add(1);
	reader_entry.store(reader_desired);

	while(common_entry.load() != common_expected);
	common_entry.store(common_desired);

	printf("Reader %d reads %d\n", reader_rank, shared_data);


	reader_entry.store(reader_expected);
	common_entry.store(common_expected);

	usleep(200);

	writer_entry.fetch_sub(1);
}

void writer(int writer_rank)
{
	int common_desired = 1;
	int common_expected = 0;
	int writer_can_write = 0;

	while(writer_entry.load() != 0);

	while(common_entry.load() != common_expected)
		common_expected = 0;

    shared_data += writer_rank * 10;
    printf("Writer %d writes %d\n", writer_rank, shared_data);

    common_entry.store(common_expected);
}