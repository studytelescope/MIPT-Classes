#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <unistd.h>

using namespace std;

const int THREAD_NUM = 20;

int shared_data;

bool common_is_free = true;
bool common_is_busy = false;
bool writer_free = true;
bool writer_busy = false;
bool readers_free = true;
bool readers_busy = false;

std::atomic<int>  readers_gate;
std::atomic<bool> reader_entry;
std::atomic<bool> writer_entry;
std::atomic<bool> common_entry;

void reader(int i);
void writer(int i);

int main()
{
	reader_entry = true;
	common_entry = true;
	writer_entry = true;
	readers_gate = 0;

	std::vector<std::thread> threads(THREAD_NUM);

	for(int i = 0; i < THREAD_NUM; i++)
		if(i == 5 || i == 6 || i == 12 || i == 13 || i == 14)
			threads[i] = std::thread(reader, i);
		else
			threads[i] = std::thread(writer, i);

 	for (auto& th : threads)
 		th.join();

	return 0;
}


void reader(int reader_rank)
{
	while(!reader_entry.load());
	reader_entry.store(readers_free);

	while(!common_entry.load())
		while(readers_gate.load());

	common_entry.store(common_is_busy);

	printf("Reader %d reads %d\n", reader_rank, shared_data);

	reader_entry.store(readers_free);
	common_entry.store(common_is_free);
}

void writer(int writer_rank)
{
	readers_gate.fetch_add(1);

	while(!writer_entry.load());
	writer_entry.store(writer_busy);

	while(!common_entry.load());
	common_entry.store(common_is_busy);

    shared_data += writer_rank * 10;
    printf("Writer %d writes %d\n", writer_rank, shared_data);

    common_entry.store(common_is_free);
    writer_entry.store(writer_free);

    usleep(200);
    readers_gate.fetch_sub(1);
}