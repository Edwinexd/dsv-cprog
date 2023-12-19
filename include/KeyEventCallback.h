#include "Component.h"
#include "Constants.h"
#include <memory>
#include <utility>



enum KeyPressType{
    DOWN,
    UP
};

class Component;

class KeyEventCallback
{

    private:
        int32_t assigned_key;
        void (*callback_fn)(int32_t , KeyPressType);
        std::weak_ptr<Component> target_comp;
    public:

    KeyEventCallback(int32_t n_key, void (*n_cfn)(int32_t, KeyPressType), std::weak_ptr<Component> n_comp) : assigned_key(n_key), callback_fn(n_cfn), target_comp(std::move(n_comp))
    {}

    int32_t getKeyCode() const
    {
        return assigned_key;
    }

    void operator()(KeyPressType press_type) const
    {
        callback_fn(assigned_key, press_type);
    }

    std::weak_ptr<Component> get_component() const
    {
        return std::weak_ptr(target_comp);
    }

    friend bool operator==(const std::shared_ptr<Component>& lhs, const KeyEventCallback rhs)
    {
        if(auto src = rhs.target_comp.lock())
        {
            return lhs == src;
        }
        else {
            return false;
        }
    }
    
};


