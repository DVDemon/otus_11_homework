#include "async.h"
#include <string>
namespace async{

    handle_t connect(std::size_t bulk){
        homework::EventProcessor *event_processor_ptr = new homework::EventProcessor(bulk);
        return event_processor_ptr;
    }

    void receive(handle_t handle, const char *data, std::size_t size){
        if (handle){
            handle->add_event(std::string(data, size));
        }
    }

    void disconnect(handle_t handle){
        delete handle;
    }

} // namespace async
