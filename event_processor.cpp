#include "event_processor.h"
#include "producer.h"
#include "consumer_file.h"
#include "consumer_out.h"

homework::EventProcessor::EventProcessor(std::size_t b) : bulk(b), running(true){
    process();
}

void homework::EventProcessor::add_event(std::string val){
    std::lock_guard<std::mutex> lock(guard_mutex);
    events.push_back(val);
}

void homework::EventProcessor::process(){
    auto procedure = [this](){
        Producer producer(this->bulk);
        ConsumerOut consumer_out(std::cout);
        ConsumerFile consumer_file;

        producer.add_customer(&consumer_file);
        producer.add_customer(&consumer_out);


        std::string cmd;
        while(running){
            {
                std::lock_guard<std::mutex> lock(this->guard_mutex);
                if(!this->events.empty()){      
                    std::string s = *this->events.begin();
                    this->events.pop_front();

                    // парсим строку
                    std::string delimiter = "\n";
                    size_t pos = 0;
                    std::string token;
                    while ((pos = s.find(delimiter)) != std::string::npos) {
                        token = s.substr(0, pos);
                        if(!token.empty()){
                            producer.produce(token);
                        }
                        s.erase(0, pos + delimiter.length());
                    }

                    if(!s.empty()){
                            producer.produce(s);
                        }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
           
        producer.flush();
    };

    loop = std::async(procedure);

}

void homework::EventProcessor::stop(){
    bool empty=false;
    do{
       {
           std::lock_guard<std::mutex> lock(this->guard_mutex); 
           empty = events.empty();
       }
       if(!empty) std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }while(!empty);
    running = false;
    loop.wait();
}

homework::EventProcessor::~EventProcessor(){
    stop();
}