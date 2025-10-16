#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int64.hpp"

class Str_hasher : public rclcpp::Node{
    private:
    rclcpp::Publisher<std_msgs::msg::UInt64>::SharedPtr m_publisher;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr m_subscriber;
    rclcpp::TimerBase::SharedPtr m_timer;

    std_msgs::msg::String m_str;

    void str_callback(const std_msgs::msg::String &str){
        m_str = str;
    }

    void callback(){
        std_msgs::msg::UInt64 hash;
        hash.data = 5831;

        for (auto c : m_str.data)
            hash.data = 33 * hash.data + c;

        RCLCPP_INFO(this->get_logger(), "Hashed random string: %zu", hash.data);
    }

    public:
    Str_hasher() : Node{"str_hasher"}{
        using namespace std::chrono_literals;

        m_publisher = this->create_publisher<std_msgs::msg::UInt64>("hash", 10);
        m_subscriber = this->create_subscription<std_msgs::msg::String>("rand_str", 10, std::bind(&Str_hasher::str_callback, this));
        m_timer = this->create_wall_timer(500ms, std::bind(&Str_hasher::callback, this));
    }
};

int main(const int argc, const char *const *argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Str_hasher>());
    rclcpp::shutdown();

    return 0;
}