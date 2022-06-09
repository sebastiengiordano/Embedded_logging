
#include <stdint.h>


void check_assertion(uint8_t value) {
    MY_ASSERT(value > 0, "In check_assertion, value = " + std::to_string(value))
}

int main() {
    ESP_LOGI("TAG", "hello from main app.\n");
    ESP_LOGW("TAG", "hello from main app.\n");
    check_assertion(0);
    return 0;
}
