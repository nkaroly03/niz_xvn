#include <algorithm>
#include <array>
#include <chrono>
#include <memory>
#include <random>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class Rand_str_generator : public rclcpp::Node{
    private:
    std::mt19937_64 m_rand;
    rclcpp::TimerBase::SharedPtr m_timer;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_publisher;

    void callback(){
        std::array<uint8_t, 128> char_counts{};
        std_msgs::msg::String s;

        std::uniform_int_distribution<char> distr{32, 126};

        for (size_t i = 0; i < 20; ++i){
            auto c = distr(m_rand);
            ++char_counts[c];
            s.data += c;
        }

        for (size_t i = 0; i < char_counts.size(); ++i){
            while (char_counts[i] > 1){
                --char_counts[i];
                s.data.erase(std::find(s.data.begin(), s.data.end(), static_cast<char>(i)));
            }
        }

        RCLCPP_INFO(this->get_logger(), "random string without duplicate characters: %s\n", s.data.c_str());
        m_publisher->publish(s);
    }

    public:
    Rand_str_generator() : Node{"random_string_generator"}{
        using namespace std::chrono_literals;

        m_publisher = this->create_publisher<std_msgs::msg::String>("rand_str", 10);
        m_timer = this->create_wall_timer(500ms, std::bind(&Rand_str_generator::callback, this));
    }
};

int main(const int argc, const char *const *argv){

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Rand_str_generator>());
    rclcpp::shutdown();

    return 0;
}