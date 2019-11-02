#pragma once

#include <cstddef>
#include "event_processor.h"

namespace async {

    /**
     * Тип обработчика ассинхронных команд
     */
    using handle_t = homework::EventProcessor *;

    /**
     * Подключение/создание обработчика комманд
     */
    handle_t connect(std::size_t bulk);

    /**
     * Метод для отправки комманды по парсингу строки
     */
    void receive(handle_t handle, const char *data, std::size_t size);

    /**
     * Отсоединяемся/удаляем обработчик команд
     */
    void disconnect(handle_t handle);

}
