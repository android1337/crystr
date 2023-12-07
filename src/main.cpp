//#include "crycall.hpp" // see https://github.com/Android1337/crycall for an all-potential virtual implementation
#include "crystr.hpp"

int main() {
    auto encrypted_str = crystr("Hello, this is an encrypted string!");

    printf("Decrypted String: %s", encrypted_str.decrypt());

    encrypted_str.clear();

    return 0;
}
