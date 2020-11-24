#include <iostream>
#include <vector>

#include "GenuineConsumer.h"
#include "GenuineProducer.h"

#define PRODUCERS 3         // Set number of producer objects here
#define CONSUMERS 5         // Set number of consumer objects here
#define BUF_SIZE 1000000    // Set buffer size here
#define ITER 100000000      // Set number of iterations per producer

int main()
{
    // Create buffer object with size BUF_SIZE
    Buffer<std::pair<float, float>> buffer(BUF_SIZE);

    // Create vectors for several consumer & producer objects
    std::vector<GenuineConsumer*> consumers;
    std::vector<GenuineProducer*> producers;

    // Fill producer vector
    for(int j = 0; j < PRODUCERS; j++)
    {
        producers.push_back(new GenuineProducer(buffer, ITER));
    }

    // Fill consumer vector
    for(int i = 0; i < CONSUMERS; i++)
    {
        consumers.push_back(new GenuineConsumer(buffer, CONSUMERS));
    }

    // Start work of every producer and consumer
    for (auto& p : producers) p->start_work();
    for (auto& c : consumers) c->start_work();

    std::cout << "Job started!" << std::endl;

    // Join producer and consumer threads with main thread
    for (auto& p : producers) p->join_thread();
    for (auto& c : consumers) c->join_thread();

    // Free allocated heap memory
    for (auto& p : producers) delete p;
    for (auto& c : consumers) delete c;

    std::cout << "Job done successfully!" << std::endl;

    return 0;
}
