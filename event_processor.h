#ifndef EVENT_PROCESSOR_H

#include <deque>
#include <string>
#include <atomic>
#include <mutex>
#include <future>

namespace homework{
    /**
     * Обработчик команд
     */
    class EventProcessor{
    private:
        /**
         * Размер блока команд
         */
        std::size_t             bulk;

        /**
         * Синхронизатор для работы с очередью команд
         */
        std::mutex              guard_mutex;

        /**
         * Результат окончания работы цикла обработки сообщений, используем его для корректного завершения потоков
         */
        std::future<void>       loop;

        /**
         * Признак работы цикла обработки сообщений. Атомарный что бы не мучаться с синхронизацией
         */
        std::atomic_bool        running;

        /**
         * Очередь сообщений
         */
        std::deque<std::string> events;

        /**
         * Запуск обработчика сообщений
         */
        void process();

        /**
         * Завершение обработки очереди команд и остановка обработчика со слиянием потокв
         */
        void stop();
    public:
        EventProcessor(std::size_t b);

        /**
         * Добавление сообщения в очередь
         */
        void add_event(std::string);
        ~EventProcessor();

    };
}
#endif