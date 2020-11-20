#include <iostream>
#include <vector>

#include "GenuineConsumer.h"
#include "GenuineProducer.h"

#define CONSUMERS 2
#define PRODUCERS 3
#define BUF_SIZE 100000

int main()
{
    Buffer<std::pair<float, float>> buffer(BUF_SIZE);

    std::vector<GenuineConsumer*> consumers;
    std::vector<GenuineProducer*> producers;

    for(int j = 0; j < PRODUCERS; j++)
    {
        producers.push_back(new GenuineProducer(buffer));
    }

    for(int i = 0; i < CONSUMERS; i++)
    {
        consumers.push_back(new GenuineConsumer(buffer, CONSUMERS));
    }

    for (auto& p : producers) p->start_work();
    for (auto& c : consumers) c->start_work();

    for (auto& p : producers) p->join_thread();
    for (auto& c : consumers) c->join_thread();

    for (auto& p : producers) delete p;
    for (auto& c : consumers) delete c;

    std::cout << "Job done successfully!" << std::endl;

    return 0;
}
