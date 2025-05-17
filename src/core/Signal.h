#pragma once
#include <functional>
#include <vector>
#include <algorithm>

template <typename... Args>
class Signal {
public:
    using SlotType = std::function<void(Args...)>;
    using SlotId = size_t;

    SlotId connect(const SlotType& slot) {
        slots.emplace_back(nextId, slot);
        return nextId++;
    }

    void disconnect(SlotId id) {
        slots.erase(std::remove_if(slots.begin(), slots.end(),
                                   [id](const auto& p) { return p.first == id; }),
                    slots.end());
    }

    void emit(Args... args) {
        for (const auto& [id, slot] : slots) {
            slot(args...);
        }
    }

private:
    SlotId nextId = 0;
    std::vector<std::pair<SlotId, SlotType>> slots;
};
