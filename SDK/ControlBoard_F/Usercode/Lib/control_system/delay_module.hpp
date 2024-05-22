#include "discrete_controller_base.hpp"
#include <vector>
#include <cstddef>

namespace control_system
{
template <typename T>
class DelayModule : public DiscreteControllerBase<T>
{
private:
    size_t pos_;

public:
    std::vector<T> data_;

    DelayModule(size_t delay)
    {
        Init(delay);
    }

    void Init(size_t delay)
    {
        data_.resize(delay);

        ResetState();
    }

    T Step(T input) override
    {
        auto delay_tick = data_.size();
        if (delay_tick == 0) return input;

        T result       = data_.at(pos_);
        data_.at(pos_) = input;
        if (pos_ < delay_tick - 1) {
            pos_++;
        } else {
            pos_ = 0;
        }

        return result;
    }

    void ResetState() override
    {
        std::fill(data_.begin(), data_.end(), 0);
        pos_ = 0;
    }
};

} // namespace control_system
